//Leo Lin
//June 1st, 2022
//Spring 2022

#include "Ascii.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "Agent.h"
#include "BattleBoats.h"
#include "Negotiation.h"
#include "Message.h"
#include "Field.h"
#include "BOARD.h"
#include "CircularBuffer.h"
#include "FieldOled.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Uart1.h"

typedef struct AGENT {
    AgentState state;
    NegotiationData secret;
    NegotiationData commitment;
    Field own;
    Field opp;
    Message message;
    uint8_t counter;

} AGENT;

static AGENT agent;
static BB_Event event;
// static Field ownmap;
// static Field oppmap;

int main(void) {
    //AgentInit--------------------------------------------------------------------------------------------------------------------------------
    AgentInit();
    if (agent.state == AGENT_STATE_START) {
        printf("Passed the 1st AgentInit() test\n");
    } else {
        printf("Failed the 1st AgentInit() test\n");
    }

    if (agent.counter == 0) {
        printf("Passed the 2nd AgentInit() test\n");
    } else {
        printf("Failed the 2nd AgentInit() test\n");
    }
    printf("\n");
    //AgentRun--------------------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                agent.state = AGENT_STATE_START;
                event.type = BB_EVENT_START_BUTTON;
                Message result1 = AgentRun(event);
                if (result1.type == MESSAGE_CHA && AgentGetState() == AGENT_STATE_CHALLENGING) {
                    printf("AGENT_STATE_START: Passed the 1st Start test\n");
                } else {
                    printf("AGENT_STATE_START: Failed the 1st Start test\n");
                }
                printf("\n");
                break;

            case 1:
                agent.state = AGENT_STATE_CHALLENGING;
                event.type = BB_EVENT_ACC_RECEIVED;
                Message result3 = AgentRun(event);
                if (result3.type == MESSAGE_REV) {
                    printf("AGENT_STATE_CHALLENGING: Passed the ACC test\n");
                } else {
                    printf("AGENT_STATE_CHALLENGING: Failed the ACC test\n");
                }
                printf("\n");
                break;

            case 2:
                agent.state = AGENT_STATE_ACCEPTING;
                event.type = BB_EVENT_REV_RECEIVED;
                Message result4 = AgentRun(event);
                if (result4.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_END_SCREEN) {
                    printf("AGENT_STATE_ACCEPTING: Cheating detected. Passed the 1st REV test\n");
                } else {
                    printf("AGENT_STATE_ACCEPTING: Failed the 1st REV test\n");
                    printf("If you see this failure, then the test was passed successfully b/c in the 3 REV test, only one of the test can pass.\n");
                }
                printf("\n");
                break;

            case 3:
                agent.state = AGENT_STATE_ACCEPTING;
                event.type = BB_EVENT_REV_RECEIVED;
                Message result5 = AgentRun(event);
                if (result5.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_DEFENDING) {
                        printf("AGENT_STATE_ACCEPTING: HEADS detected. Passed the 2nd REV test\n");
                } else {
                        printf("AGENT_STATE_ACCEPTING: Failed the 2nd REV test\n");
                        printf("If you see this failure, then the test was passed successfully b/c in the 3 REV test, only one of the test can pass.\n");

                }
                
                printf("\n");
                break;

            case 4:
                agent.state = AGENT_STATE_ACCEPTING;
                event.type = BB_EVENT_REV_RECEIVED;
                Message result6 = AgentRun(event);
                if (agent.message.type == MESSAGE_SHO && AgentGetState() == AGENT_STATE_ATTACKING) {
                    printf("AGENT_STATE_ACCEPTING: TAILS detected. Passed the 3rd REV test\n");
                } else {
                    printf("AGENT_STATE_ACCEPTING: Failed the 3rd REV test\n");
                    printf("If you see this failure, then the test was passed successfully b/c in the 3 REV test, only one of the test can pass.\n");
                }
                printf("\n");
                break;

            case 5:
                agent.state = AGENT_STATE_ATTACKING;
                event.type = BB_EVENT_RES_RECEIVED;
                Message result7 = AgentRun(event);
                if (result7.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_DEFENDING){
                    printf("AGENT_STATE_ATTACKING: Passed the 1st RES test\n");
                } else {
                    printf("AGENT_STATE_ATTACKING: Failed the 1st RES test\n");
                }             
                printf("\n");
                break;
            
            case 6:
                agent.state = AGENT_STATE_DEFENDING;
                event.type = BB_EVENT_SHO_RECEIVED;
                Message result8 = AgentRun(event);
                if (AgentGetState() == AGENT_STATE_WAITING_TO_SEND){
                    printf("AGENT_STATE_DEFENDING: Passed the 1st SHO test\n");
                } else {
                    printf("AGENT_STATE_DEFENDING: Failed the 1st SHO test\n");
                }         
                printf("\n");
                break;
            
            case 7:
                agent.state = AGENT_STATE_WAITING_TO_SEND;
                event.type = BB_EVENT_MESSAGE_SENT;
                Message result9 = AgentRun(event);
                if (result9.type == MESSAGE_SHO && AgentGetState() == AGENT_STATE_ATTACKING){
                    printf("AGENT_STATE_DEFENDING: Passed the 1st messagesent test\n");
                } else {
                    printf("AGENT_STATE_DEFENDING: Failed the 1st messagesent test\n");
                }         
                printf("\n");
                break;

            case 8:
                agent.state = AGENT_STATE_END_SCREEN;
                event.type = BB_EVENT_RESET_BUTTON;
                Message result10 = AgentRun(event);
                if (result10.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_START){
                    printf("AGENT_STATE_DEFENDING: Passed the 1st reset test\n");
                } else {
                    printf("AGENT_STATE_DEFENDING: Failed the 1st reset test\n");
                }         
                printf("\n");
                break;
        }
    }
}

