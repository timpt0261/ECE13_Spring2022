// Reuben Chavez
// May 25, 2022
// Spring 2022

#include <stdio.h>
#include <string.h>
#include "Message.h"
#include "BOARD.h"

int main(void) {
    printf("Beginning test harness for Negotiation, compiled on %s %s\n", __DATE__, __TIME__);

    // Testing Message_CalculateCheckSum    
    // Testing CheckSumm
    printf("Testing Message_CalculateCheckSum\n");

    static char test_payload[MESSAGE_MAX_PAYLOAD_LEN];
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                sprintf(test_payload, PAYLOAD_TEMPLATE_ACC, 12);
                if (Message_CalculateChecksum(test_payload) == 0x6E) {
                    printf("\tPasses first test\n");
                } else {
                    printf("\tFails first test\n");
                }
                strcpy(test_payload, "");
                break;
            case 1:
                sprintf(test_payload, PAYLOAD_TEMPLATE_CHA, 78);
                if (Message_CalculateChecksum(test_payload) == 0x69) {
                    printf("\tPasses second test\n");
                } else {
                    printf("\tFails second test\n");
                }
                strcpy(test_payload, "");
                break;
            case 2:
                sprintf(test_payload, PAYLOAD_TEMPLATE_RES, 16, 10, 20);
                if (Message_CalculateChecksum(test_payload) == 0x6C) {
                    printf("\tPasses third test\n");
                } else {
                    printf("\tFails third test\n");
                }
                strcpy(test_payload, "");
                break;
            case 3:
                sprintf(test_payload, PAYLOAD_TEMPLATE_REV, 46);
                if (Message_CalculateChecksum(test_payload) == 0x6F) {
                    printf("\tPasses fouth test\n");
                } else {
                    printf("\tFails fourth test\n");
                }
                strcpy(test_payload, "");
                break;
            case 4:
                sprintf(test_payload, PAYLOAD_TEMPLATE_SHO, 18, 12);
                if (Message_CalculateChecksum(test_payload) == 0x5E) {
                    printf("\tPasses fifth test\n");
                } else {
                    printf("\tFails fifth test\n");
                }
                strcpy(test_payload, "");
                break;
        }
    }

    // Testing Message_ParseMessage
    printf("Testing Message_ParseMessage\n\n");
    char payload_pm[MESSAGE_MAX_PAYLOAD_LEN];
    char checksum_string_pm[MESSAGE_CHECKSUM_LEN];
    static BB_Event bb_event;
    // initializing bb_event
    bb_event.type = BB_EVENT_NO_EVENT;
    bb_event.param0 = 0;
    bb_event.param1 = 0;
    bb_event.param2 = 0;

    int result;
    //
    ////     First case check for SUCCESS
    ////     Last Three cases check that the STANDARD_ERROR is returned
    for (int i = 0; i < 9; i++) {
        switch (i) {
            case 0:
                // set payload to CHA, 14
                strcpy(payload_pm, "CHA,4");
                // set checksum_string to a string version of the checksum
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == SUCCESS && bb_event.type == BB_EVENT_CHA_RECEIVED &&
                        bb_event.param0 == 4) {
                    printf("\tTest 1: Passes\n");
                } else {
                    printf("\tTest 1: Fails\n");
                }

                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;
            case 1:
                strcpy(payload_pm, "REV,45");
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == SUCCESS && bb_event.type == BB_EVENT_REV_RECEIVED &&
                        bb_event.param0 == 45) {
                    printf("\tTest 2: Passes\n");
                } else {
                    printf("\tTest 2: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 2:
                // the payload does not match the checksum
                strcpy(payload_pm, "SHO,61,16");
                sprintf(checksum_string_pm, "57");
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == STANDARD_ERROR && bb_event.type == BB_EVENT_ERROR &&
                        bb_event.param0 == BB_ERROR_BAD_CHECKSUM && bb_event.param1 == 0 && bb_event.param2 == 0) {
                    printf("\tTest 3: Passes\n");
                } else {
                    printf("\tTest 3: Fails\n");
                }

                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 3:
                // the checksum string is more than two characters long
                strcpy(payload_pm, "CHA,9");
                sprintf(checksum_string_pm, "257");
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);
                if (result == STANDARD_ERROR && bb_event.type == BB_EVENT_ERROR &&
                        bb_event.param0 == BB_ERROR_CHECKSUM_LEN_EXCEEDED) {
                    printf("\tTest 4: Passes\n");
                } else {
                    printf("\tTest 4: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 4:
                // the check sum is not too short
                strcpy(payload_pm, "RES,5,46,8");
                sprintf(checksum_string_pm, "4");
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);
                if (result == STANDARD_ERROR && bb_event.type == BB_EVENT_ERROR &&
                        bb_event.param0 == BB_ERROR_CHECKSUM_LEN_INSUFFICIENT) {
                    printf("\tTest 5: Passes\n");
                } else {
                    printf("\tTest 5: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 5:
                // the message does not match any message template
                strcpy(payload_pm, "FAR, 42");
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);
                if (result == STANDARD_ERROR && bb_event.type == BB_EVENT_ERROR &&
                        bb_event.param0 == BB_ERROR_INVALID_MESSAGE_TYPE) {
                    printf("\tTest 6: Passes\n");
                } else {
                    printf("\tTest 6: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 6:
                strcpy(payload_pm, "ACC,4");
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == SUCCESS && bb_event.type == BB_EVENT_ACC_RECEIVED &&
                        bb_event.param0 == 4) {
                    printf("\tTest 7: Passes\n");
                } else {
                    printf("\tTest 7: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 7:
                strcpy(payload_pm, "SHO,20,78");
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == SUCCESS && bb_event.type == BB_EVENT_SHO_RECEIVED &&
                        bb_event.param0 == 20 && bb_event.param1 == 78) {
                    printf("\tTest 8: Passes\n");
                } else {
                    printf("\tTest 8: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;

            case 8:
                strcpy(payload_pm, "RES,20,6,88");
                sprintf(checksum_string_pm, "%x", Message_CalculateChecksum(payload_pm));
                result = Message_ParseMessage(payload_pm, checksum_string_pm, &bb_event);

                if (result == SUCCESS && bb_event.type == BB_EVENT_RES_RECEIVED &&
                        bb_event.param0 == 20 && bb_event.param1 == 6 && bb_event.param2 == 88) {
                    printf("\tTest 9: Passes\n");
                } else {
                    printf("\tTest 9: Fails\n");
                }
                strcpy(payload_pm, "");
                strcpy(checksum_string_pm, "");
                bb_event.type = BB_EVENT_NO_EVENT;
                bb_event.param0 = 0;
                bb_event.param1 = 0;
                bb_event.param2 = 0;
                break;
        }
    }

    //    // Testing Encode
    printf("Testing Encode\n\n");

    Message test_message;
    char message[MESSAGE_MAX_LEN];

    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                test_message.type = MESSAGE_ACC;
                test_message.param0 = 7;

                Message_Encode(message, test_message);
                if (strcmp(message, "$ACC,7*5A\n") == 0) {
                    printf("\tFirst Test: passes\n");
                } else {
                    printf("\tFirst Test: fails\n");
                }
                strcpy(message, "");
                break;

            case 1:
                test_message.type = MESSAGE_SHO;
                test_message.param0 = 46;
                test_message.param1 = 53;

                Message_Encode(message, test_message);
                if (strcmp(message, "$SHO,46,53*50\n") == 0) {
                    printf("\tSecond Test: passes\n");
                } else {
                    printf("\tSecond Test: fails\n");
                }
                strcpy(message, "");
                break;

            case 2:
                test_message.type = MESSAGE_RES;
                test_message.param0 = 85;
                test_message.param1 = 6;
                test_message.param2 = 47;

                Message_Encode(message, test_message);
                if (strcmp(message, "$RES,85,6,47*50\n") == 0) {
                    printf("\tThird Test: passes\n");
                } else {
                    printf("\tThird Test: fails\n");
                }
                strcpy(message, "");
                break;
        }
    }

    // Testting Decode
    printf("Testting Decode\n\n");
    BB_Event dme;
    char md_test[MESSAGE_MAX_LEN];
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                sprintf(md_test, "$CHA,4*52\n");
                for (int i = 0; i < strlen(md_test); i++) {
                    Message_Decode(md_test[i], &dme); // it will pass in a single character rather than a whole string
                }
                if (dme.type == BB_EVENT_CHA_RECEIVED && dme.param0 == 4) {
                    printf("\t1st Test: Passes\n");
                } else {
                    printf("\t1st Test: Fails\n");
                }
                break;

            case 1:


                strcpy(md_test, "");
                sprintf(md_test, "$SHO,%d,%d*%02x\n", 7, 9, 0x5A);
                for (int j = 0; j < strlen(md_test); j++) {
                    Message_Decode(md_test[j], &dme);
                }
                if (dme.type == BB_EVENT_SHO_RECEIVED && dme.param0 == 7 && dme.param1 == 9) {
                    printf("\t2nd Test: Passes\n");
                } else {
                    printf("\t2nd Test: Fails\n");
                }
                break;

            case 2:

                strcpy(md_test, "");
                sprintf(md_test, "$ACC,%u*%02x\n", 5, 0x58);
                for (int k = 0; k < strlen(md_test); k++) {
                    Message_Decode(md_test[k], &dme);
                }
                if (dme.type == BB_EVENT_ACC_RECEIVED && dme.param0 == 5) {
                    printf("\t3rd Test: Passes\n");
                } else {
                    printf("\t3rd Test: Fails\n");
                }
                break;

            case 3:
                strcpy(md_test, "");
                sprintf(md_test, "$RES,%u,%u,%u*%02x\n", 3, 5, 9, 0x57);
                for (int k = 0; k < strlen(md_test); k++) {
                    Message_Decode(md_test[k], &dme);
                }
                if (dme.type == BB_EVENT_RES_RECEIVED && dme.param0 == 3 && dme.param1 == 5 && dme.param2 == 9) {
                    printf("\t4th Test: Passes\n");
                } else {
                    printf("\t4th Test: Fails\n");
                }
                break;

            case 4:
                strcpy(md_test, "");
                sprintf(md_test, "$REV,90*64\n");
                for (int k = 0; k < strlen(md_test); k++) {
                    Message_Decode(md_test[k], &dme);
                }
                if (dme.type == BB_EVENT_REV_RECEIVED && dme.param0 == 90) {
                    printf("\t5th Test: Passes\n");
                } else {
                    printf("\t5th Test: Fails\n");
                }
                break;
        }
    }
    return 0;
}