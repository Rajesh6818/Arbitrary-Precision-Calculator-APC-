#include "apc.h"
void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    //Logic for Multiplication of two numbers
    node *temp2 = tail2;
    node *headR1 = NULL, *tailR1 = NULL;
    node *headR2 = NULL, *tailR2 = NULL;
    node *headAR = NULL, *tailAR = NULL;
    int count = 0;
    while (temp2 != NULL)
    {
        headR2 = tailR2 = NULL;
        int carry = 0;
        // Add shifting zeros
        for (int i = 0; i < count; i++)
        {
            insert_last(&headR2, &tailR2, 0);
        }
        node *temp1 = tail1;
        while (temp1 != NULL)
        {
            int product = temp1->data * temp2->data + carry;
            int digit = product % 10;
            carry = product / 10;
            insert_first(&headR2, &tailR2, digit);
            temp1 = temp1->prev;
        }
        if (carry)
        {
            insert_first(&headR2, &tailR2, carry);
        }
        // First result
        if (headR1 == NULL)
        {
            headR1 = headR2;
            tailR1 = tailR2;
        }
        else
        {
            addition(tailR1, tailR2, &headAR, &tailAR);     //The numbers will be added
            delete_list(&headR1, &tailR1);
            delete_list(&headR2, &tailR2);
            headR1 = headAR;
            tailR1 = tailAR;
            headAR = tailAR = NULL;
        }
        temp2 = temp2->prev;
        count++;
    }
    *headR = headR1;
    *tailR = tailR1;
}

 