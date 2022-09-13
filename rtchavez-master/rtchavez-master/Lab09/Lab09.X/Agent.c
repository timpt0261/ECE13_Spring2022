// Reuben Chavez
// May 25, 2022
// Spring 2022

#include "Ascii.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// user libraries
#include "Agent.h"
#include "BattleBoats.h"
#include "Negotiation.h"
#include "Message.h"
#include "Field.h"

// libraries for micro_conrtoller
#include "BOARD.h"
#include "CircularBuffer.h"
#include "FieldOled.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Uart1.h"

typedef struct AGENT
{
    AgentState state;
    NegotiationData secret;
    NegotiationData commitment;
    Field own;
    Field opp;
    Message message;
    uint8_t counter;

} AGENT;

static AGENT agent;
static char *errorMSG;
static FieldOledTurn turn;

#define RS 0xFFFF

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 *
 * It is not advised to call srand() inside of AgentInit.
 *  */
void AgentInit(void)
{
    agent.state = AGENT_STATE_START;
    agent.counter = 0;
    return;
}

void Reset(void)
{
    // reset all data
    agent.message.type = MESSAGE_NONE;
    // display new game message
    OledClear(OLED_COLOR_BLACK);
    OledDrawString("RESETTING");
    OledUpdate();
    // set state to start
    AgentSetState(AGENT_STATE_START);
    return;
}

void ErrorCheck(BB_Event bb_error)
{
    char *error_msg;
    switch (bb_error.param0)
    {
    case BB_ERROR_BAD_CHECKSUM:
        strcpy(error_msg, "Bad CheckSum");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    case BB_ERROR_PAYLOAD_LEN_EXCEEDED:
        strcpy(error_msg, "Payload Len Exceeded");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    case BB_ERROR_CHECKSUM_LEN_EXCEEDED:
        strcpy(error_msg, "CheckSum Len Exceeded");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    case BB_ERROR_CHECKSUM_LEN_INSUFFICIENT:
        strcpy(error_msg, "CheckSum Len Insufficient");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    case BB_ERROR_INVALID_MESSAGE_TYPE:
        strcpy(error_msg, "Invalid Message Type");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    case BB_ERROR_MESSAGE_PARSE_FAILURE:
        strcpy(error_msg, "Message Parse Failure");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(error_msg);
        OledUpdate();
        break;
    }
    return;
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 *
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent.
 *
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event)
{
    // checks if the event.type is an error
    if (event.type == BB_EVENT_ERROR)
    {
        // checks which error it is
        ErrorCheck(event);
        // set message to Message None
        AgentSetState(AGENT_STATE_END_SCREEN);
        agent.message.type = MESSAGE_NONE;
    
        // return agent message
        return agent.message;
    }

    switch (agent.state)
    {
    case AGENT_STATE_START:
        // if Reset button
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }
        // if start button pressed
        if (event.type == BB_EVENT_START_BUTTON)
        {
            // generate A
            agent.secret = rand() & RS;
            agent.message.param0 = NegotiationHash(agent.secret);
            // send CHA
            agent.message.type = MESSAGE_CHA;
            // Initialze fields
            FieldInit(&agent.own, &agent.opp);
            // place own boats
            FieldAIPlaceAllBoats(&agent.own);

            AgentSetState(AGENT_STATE_CHALLENGING);
            break;
        }
        if (event.type == BB_EVENT_CHA_RECEIVED)
        {
            // generate B
            agent.secret = rand() & RS;
            
            // send ACC
            agent.commitment = event.param0;
            agent.message.type = MESSAGE_ACC;
            agent.message.param0 = agent.secret;
            
            // initliaze feild
            FieldInit(&agent.own, &agent.opp);
            // place own boats
            FieldAIPlaceAllBoats(&agent.own); 
            //should one field be the own or other field be opp?
            AgentSetState(AGENT_STATE_ACCEPTING);
            break;
        }
        agent.message.type = MESSAGE_NONE;
        break;

    case AGENT_STATE_CHALLENGING:
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }
        // ACC_Recived
        if (event.type == BB_EVENT_ACC_RECEIVED)
        {
            // send REV
            agent.message.type = MESSAGE_REV;
            agent.message.param0 = agent.secret;

            NegotiationOutcome outcome = NegotiateCoinFlip(agent.secret, event.param0);
            // negotiaoion
            if (outcome == HEADS)
            {
                turn = FIELD_OLED_TURN_MINE;

                AgentSetState(AGENT_STATE_WAITING_TO_SEND);
                
            }
            else
            {
                turn = FIELD_OLED_TURN_THEIRS;
                AgentSetState(AGENT_STATE_DEFENDING);
                
            }
        }else{
            agent.message.type = MESSAGE_NONE;
        }
        
        break;
    case AGENT_STATE_ACCEPTING:

        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }

        if (event.type == BB_EVENT_REV_RECEIVED)
        {
            NegotiationOutcome outcome = NegotiateCoinFlip(agent.secret, event.param0);
            // if cheating detected -> to end screen
            if (NegotiationVerify(event.param0, agent.commitment) == FALSE)
            {
                // dispaly cheating
                char *msg = "Cheating Detected";
                OledDrawString(msg);
                OledUpdate();
                AgentSetState(AGENT_STATE_END_SCREEN);
                agent.message.type = MESSAGE_NONE;
                return agent.message;
            }

            // if coinFlip == HEADs -> to Defending
            if (NegotiateCoinFlip(agent.secret, agent.commitment) == HEADS)
            {
                agent.message.type = MESSAGE_NONE;
                turn = FIELD_OLED_TURN_THEIRS;
                AgentSetState(AGENT_STATE_DEFENDING);
                
            }else{
                // else -> to Attacking
                turn = FIELD_OLED_TURN_MINE;
                // Randomly Guess where to hit enemy
                GuessData own_guess = FieldAIDecideGuess(&agent.opp);
                // set agent message to sho
                agent.message.type = MESSAGE_SHO;
                agent.message.param0 = own_guess.row;
                agent.message.param1 = own_guess.col;
                AgentSetState(AGENT_STATE_ATTACKING);
                
            }
        }else{
            agent.message.type = MESSAGE_NONE;
        }
       
        break;

    case AGENT_STATE_ATTACKING:
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }

        if (event.type == BB_EVENT_RES_RECEIVED)
        {
            // update record of enemy field
            GuessData own_guess;
            own_guess.col = event.param0;
            own_guess.row = event.param1;
            own_guess.result = event.param2;

            FieldUpdateKnowledge(&agent.opp, &own_guess);

            // if opponent ships sunk -> victory
            if (FieldGetBoatStates(&agent.opp) == 0x00)
            {
                agent.message.type = MESSAGE_NONE;
                // dispaly victory
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("Victory!!\n");
                OledUpdate();

                // to End Sceen
                AgentSetState(AGENT_STATE_END_SCREEN);
                return agent.message;
            }
            else
            {
                // else agent.state -> Defending
                agent.message.type = MESSAGE_NONE;
                turn = FIELD_OLED_TURN_THEIRS;
                AgentSetState(AGENT_STATE_DEFENDING);
                break;
            }
            
        }
        agent.message.type = MESSAGE_NONE;
        break;
    case AGENT_STATE_DEFENDING:
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }

        if (event.type == BB_EVENT_SHO_RECEIVED)
        {
            GuessData oppguess;
            oppguess.row = event.param0;
            oppguess.col = event.param1;
            FieldRegisterEnemyAttack(&agent.own, &oppguess);

            agent.message.type = MESSAGE_RES;
            agent.message.param0 = event.param0;
            agent.message.param1 = event.param1;
            agent.message.param2 = oppguess.result;
            // if defeat -> end screen
            if (FieldGetBoatStates(&agent.own) == 0x00)
            {
                agent.message.type = MESSAGE_NONE;
               OledClear(OLED_COLOR_BLACK);
                OledDrawString("Defeat\n");
                OledUpdate();
                AgentSetState(AGENT_STATE_END_SCREEN);
                return agent.message;
            }
            else
            {
                // else -> wating to send
                turn = FIELD_OLED_TURN_MINE;
                AgentSetState(AGENT_STATE_WAITING_TO_SEND);
            }
            break;
        }

        agent.message.type = MESSAGE_NONE;
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }
        if (event.type == BB_EVENT_MESSAGE_SENT)
        {
            // increment turn count
            agent.counter++;
            GuessData own_guess = FieldAIDecideGuess(&agent.opp);

            //  send SHO
            agent.message.type = MESSAGE_SHO;
            agent.message.param0 = own_guess.row;
            agent.message.param1 = own_guess.col;

            AgentSetState(AGENT_STATE_ATTACKING);
            break;
        }

        if(event.type == BB_EVENT_ERROR){
            ErrorCheck(event);
            AgentSetState(AGENT_STATE_END_SCREEN);
            agent.message.type = MESSAGE_ERROR;
            return agent.message;
        }
        agent.message.type = MESSAGE_NONE;
        break;
    case AGENT_STATE_END_SCREEN:
        if (event.type == BB_EVENT_RESET_BUTTON)
        {
            Reset();
            return agent.message;
        }
        agent.message.type = MESSAGE_NONE;
        break;
    default:
        agent.message.type = MESSAGE_NONE;
        break;

    
    }

    OledClear(OLED_COLOR_BLACK);
    FieldOledDrawScreen(&agent.own, &agent.opp, turn, agent.counter);
    return agent.message;
}
/** *
 * @return Returns the current state that AgentGetState is in.
 *
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void)
{
    return agent.state;
}

/** *
 * @param Force the agent into the state given by AgentState
 *
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState)
{
    agent.state = newState;
    return;
}