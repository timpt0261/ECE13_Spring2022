//Leo Lin
//May 26th, 2022
//Spring 2022
#include "Message.h"
#include "BOARD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    Waiting_For_Start_Delimiter, Recording_Payload, Recording_Checksum,
} functions;

static functions states;
static int i = 0;
static int j = 0;
static const char *comma = ",";
static char payload[MESSAGE_MAX_PAYLOAD_LEN];
static char checksum[MESSAGE_CHECKSUM_LEN];

uint8_t Message_CalculateChecksum(const char* payload) {
    uint8_t result = 0; // set the result to the first element in the payload array
    for (int s = 0; s < strlen(payload); s++) {
        result ^= payload[s]; // xor the result
    }
    return result; // return it eventually
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {

    uint8_t value = strtoul(checksum_string, NULL, 16); // convert the string into an unsigned 8 bit integer
    char payloadCpy[MESSAGE_MAX_PAYLOAD_LEN];
    strcpy(payloadCpy, payload);
    if (strlen(checksum_string) < 2) { // if the checksum string is less than two characters long
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
        return STANDARD_ERROR;

    } else if (strlen(checksum_string) > 2) { // if the checksum string is more than two characters long 
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_CHECKSUM_LEN_EXCEEDED;
        return STANDARD_ERROR;

    } else if (Message_CalculateChecksum(payload) != value) { // if the payload does not match the checksum
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_BAD_CHECKSUM;
        return STANDARD_ERROR;

    } else {
        char *MessageID = strtok(payloadCpy, comma); // get the message ID

        if (strcmp(MessageID, "CHA") == FALSE) {
            message_event->type = BB_EVENT_CHA_RECEIVED;
            uint16_t p0 = atoi(strtok(NULL, comma));
            message_event->param0 = p0;
            return SUCCESS;
        } else if (strcmp(MessageID, "ACC") == FALSE) {
            message_event->type = BB_EVENT_ACC_RECEIVED;
            uint16_t p1 = atoi(strtok(NULL, comma));
            message_event->param0 = p1;
            return SUCCESS;

        } else if (strcmp(MessageID, "REV") == FALSE) {
            message_event->type = BB_EVENT_REV_RECEIVED;
            uint16_t p2 = atoi(strtok(NULL, comma));
            message_event->param0 = p2;
            return SUCCESS;

        } else if (strcmp(MessageID, "SHO") == FALSE) {
            message_event->type = BB_EVENT_SHO_RECEIVED;
            int p3 = atoi(strtok(NULL, comma));
            int p4 = atoi(strtok(NULL, comma));
            message_event->param0 = p3;
            message_event->param1 = p4;
            return SUCCESS;

        } else if (strcmp(MessageID, "RES") == FALSE) {
            message_event->type = BB_EVENT_RES_RECEIVED;
            int p5 = atoi(strtok(NULL, comma));
            int p6 = atoi(strtok(NULL, comma));
            int p7 = atoi(strtok(NULL, comma));
            message_event->param0 = p5;
            message_event->param1 = p6;
            message_event->param2 = p7;
            return SUCCESS;

        } else {
            message_event->type = BB_EVENT_ERROR;
            message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE;
            return STANDARD_ERROR;
        }
    }
}

int Message_Encode(char *message_string, Message message_to_encode) {
    char payload[MESSAGE_MAX_PAYLOAD_LEN];
    if (message_to_encode.type == MESSAGE_NONE) {
        return 0;
    } else {
        if (message_to_encode.type == MESSAGE_CHA) {
            sprintf(payload, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0); // load payload message to message

        } else if (message_to_encode.type == MESSAGE_ACC) {
            sprintf(payload, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);

        } else if (message_to_encode.type == MESSAGE_REV) {
            sprintf(payload, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);

        } else if (message_to_encode.type == MESSAGE_SHO) {
            sprintf(payload, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);

        } else if (message_to_encode.type == MESSAGE_RES) {
            sprintf(payload, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
        }

        sprintf(message_string, MESSAGE_TEMPLATE, payload, Message_CalculateChecksum(payload));
        // load the message and checksum (result from payload) into message template, convert that to the message string
        return strlen(message_string);
    }
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {
    switch (states) {
        case Waiting_For_Start_Delimiter:
            if (char_in == '$') { // if the char_in is $
                states = Recording_Payload; // go to the next state
            }
            break;

        case Recording_Payload:
            if (strlen(payload) > MESSAGE_MAX_PAYLOAD_LEN) { // if the payload strength exceeds the max payload length
                decoded_message_event->type = BB_EVENT_ERROR; // set the type to error
                decoded_message_event->param0 = BB_ERROR_PAYLOAD_LEN_EXCEEDED; // set the error type
                states = Waiting_For_Start_Delimiter;
                return STANDARD_ERROR;

            } else if (char_in == '$' || char_in == '\n') { // unexpected delimiter
                decoded_message_event->type = BB_EVENT_ERROR; // set the type to error
                decoded_message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE; // set the error type
                states = Waiting_For_Start_Delimiter;
                return STANDARD_ERROR;
            }

            if (char_in != '*') { // while the next char is not *
                payload[i] = char_in; // add the next character into the payload array
                i++;
                states = Recording_Payload;
            }
            if (char_in == '*') { // if the char is *
                i = 0;
                states = Recording_Checksum;
            }
            break;

        case Recording_Checksum:
            if (char_in != '\n') { // while the next char is not \n
                if (isxdigit(char_in) != 0) { // if the character is a hexadecimal value
                    checksum[j] = char_in; // record the character
                    j++; // increment j
                    states = Recording_Checksum;
                } else {
                    decoded_message_event->type = BB_EVENT_ERROR; // set the type to error
                    decoded_message_event->param0 = BB_ERROR_BAD_CHECKSUM; // set the error type
                    states = Waiting_For_Start_Delimiter;
                    return STANDARD_ERROR;
                }
            }
            if (char_in == '\n') {
                j = 0;
                int result = Message_ParseMessage(payload, checksum, decoded_message_event);
                if (result == SUCCESS) {
                    memset(payload, 0, sizeof (payload));
                    memset(checksum, 0, sizeof (checksum));
                    states = Waiting_For_Start_Delimiter;
                    return SUCCESS;

                } else {
                    decoded_message_event->type = BB_EVENT_ERROR; // set the type to error
                    decoded_message_event->param0 = BB_ERROR_MESSAGE_PARSE_FAILURE; // set the error type
                    states = Waiting_For_Start_Delimiter;
                    return STANDARD_ERROR;
                }
            }
            break;
    }
}