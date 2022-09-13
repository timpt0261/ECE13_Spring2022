// Reuben Chavez
// May 25, 2022
// Spring 2022

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "Negotiation.h"
#include "BOARD.h"

int main(void)
{

    printf("Beginning test harness for Negotiation, compiled on %s %s\n", __DATE__, __TIME__);
    // testing NegotiationHash

    printf("Testing Negotiation Hash\n");

    NegotiationData input_ND;
    NegotiationData expected_ND;
    NegotiationData output_ND;

    expected_ND = 43182;
    output_ND = NegotiationHash(12345);

    if (expected_ND == output_ND)
    {
        printf("\tPasses first Test\n");

        // set seed to current time -> creates a more rand number

        srand(time(0));

        uint8_t count_1 = 0; // stores count

        for (int i = 0; i < 10; i++)
        {
            // set input to rand number
            input_ND = rand();
            // calculate expected answer
            expected_ND = (input_ND * input_ND) % PUBLIC_KEY;
            // set output to Negotiation Hash
            output_ND = NegotiationHash(input_ND);
            // in case expected and out put aren't equal
            if (expected_ND != output_ND)
            {
                printf("Doesn't Pass Second Test, expected: %u, output %u\n", expected_ND, output_ND);
                break;
            }
            count_1++;
        }

        if (count_1 == 10)
        {
            printf("\tPasses second Test\n");
            printf("===Negotiation Hash Passes==+\n\n");
        }

        // Testing Negotiation Verify
        printf("Testing Negotiation Verify\n");
        int seed = time(0);
        srand(seed);

        NegotiationData secret;
        NegotiationData commintment; // second parameter for Negotiation verify
        NegotiationData secret_hash;     // used to test secret hash
        int expected_NV, output_NV, count_2;

        // for ten iteration
        for (int i = 0; i < 10; i++)
        {
            secret = rand(); // set secret to random numbers
            commintment = rand();
            // set secret_hash equal to hash of secret
            secret_hash = (secret * secret) % PUBLIC_KEY;

            // set expected to True of False
            expected_NV = commintment & secret_hash ? TRUE : FALSE;

            // set output to Negotiation Verify
            output_NV = NegotiationVerify(secret, commintment);

            // if expected and output aren't equal
            if (expected_NV != output_NV)
            {
                printf("\tNegotiationVerify: Failed\n");
                break;
            }
            count_2++;
        }

        if (count_2 == 10)
        {
            printf("\t NegotiationVerify: Passes\n");
        }

        // testing Negotiation OutComme
        printf("Testing NegotiationCoinFLip\n");

        NegotiationData A;
        NegotiationData B;
        NegotiationOutcome expected_NCF, outcome_NCF;

        // Testing with five cases
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                // set A and B to randomly picked number from online random gen
                A = 3;
                B = 55;
                // find parity of A ^ B online
                // store expected answer
                expected_NCF = HEADS;
                // set outcome to Negotiate Coin Flip
                outcome_NCF = NegotiateCoinFlip(A, B);
                // if not equal print test failed
                if (expected_NCF != outcome_NCF)
                {
                    printf("\tTest 1: Fail\n");
                    break;
                }
                // otherwise test passes
                printf("\tTest 1: Pass\n");
                // repeat for other cases
                break;
            case 1:
                A = 12;
                B = 92;

                expected_NCF = TAILS;
                outcome_NCF = NegotiateCoinFlip(A, B);
                if (expected_NCF != outcome_NCF)
                {
                    printf("\tTest 2: Fail\n");
                    break;
                }
                printf("\tTest 2: Pass\n");
                break;
            case 2:
                A = 20;
                B = 37;

                expected_NCF = HEADS;
                outcome_NCF = NegotiateCoinFlip(A, B);
                if (expected_NCF != outcome_NCF)
                {
                    printf("\tTest 3: Fail\n");
                    break;
                }
                printf("\tTest 3: Pass\n");
                break;
                ;
            case 3:
                A = 80;
                B = 54;

                expected_NCF = TAILS;
                outcome_NCF = NegotiateCoinFlip(A, B);
                if (expected_NCF != outcome_NCF)
                {
                    printf("\tTest 4: Fail\n");
                    break;
                }
                printf("\tTest 4: Pass\n");
                break;
            case 4:
                A = 20;
                B = 41;

                expected_NCF = HEADS;
                outcome_NCF = NegotiateCoinFlip(A, B);
                if (expected_NCF != outcome_NCF)
                {
                    printf("\tTest 5: Fail\n");
                    break;
                }
                printf("\tTest 5: Pass\n");
                break;
            }
        }
    }
    return 0;
}
