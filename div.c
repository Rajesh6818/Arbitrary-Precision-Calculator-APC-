#include "apc.h"
// DIVISION FUNCTION 
// Performs division using repeated subtraction method
// Similar to manual long division

void division(node *head1, node *headOPR2, node *tailOPR2, node **headR, node **tailR)
{
    node *headOPR1 = NULL, *tailOPR1 = NULL;  // Current dividend
    node *head_sr = NULL, *tail_sr = NULL;    // Subtraction result

    node *temp = head1;

    //  STEP 1: TAKE FIRST DIGIT 
    if (temp == NULL)
        return;

    insert_last(&headOPR1, &tailOPR1, temp->data);

    //  STEP 2: BUILD INITIAL DIVIDEND 
    while (compare_list(headOPR1, headOPR2) == OPERAND2 && temp->next != NULL)
    {
        temp = temp->next;

        if (insert_last(&headOPR1, &tailOPR1, temp->data) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }
    }

    // STEP 3: MAIN DIVISION LOOP 
    while (temp != NULL)
    {
        int subcount = 0;

        //  STEP 4: REPEATED SUBTRACTION
        int cmp = compare_list(headOPR1, headOPR2);

        while (cmp == OPERAND1 || cmp == SAME)
        {
            head_sr = tail_sr = NULL;

            // Subtract divisor from current dividend
            subtraction(tailOPR1, tailOPR2, &head_sr, &tail_sr);

            // Free old dividend
            delete_list(&headOPR1, &tailOPR1);

            // Update dividend
            headOPR1 = head_sr;
            tailOPR1 = tail_sr;

            remove_pre_zeros(&headOPR1);
            
            subcount++;

            // Update comparison
            cmp = compare_list(headOPR1, headOPR2);
        }

        //  STEP 5: STORE QUOTIENT DIGIT 
        if (insert_last(headR, tailR, subcount) == FAILURE)
        {
            printf("ERROR: Insertion failed\n");
            return;
        }

        temp = temp->next;

        // STEP 6: BRING DOWN NEXT DIGIT 
        if (temp != NULL)
        {
            if (insert_last(&headOPR1, &tailOPR1, temp->data) == FAILURE)
            {
                printf("ERROR: Insertion failed\n");
                return;
            }

            // Remove leading zeros for correctness
            remove_pre_zeros(&headOPR1);
        }
    }
}