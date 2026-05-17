#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    //Logic for addition of two numbers
    int sum=0,carry=0,rem=0;
    node*temp1=tail1;
    node*temp2=tail2;
    while(temp1 != NULL || temp2 != NULL || carry)
    {
        sum = carry;    //to store carry
        if(temp1)
        {
            sum += temp1->data;
            temp1 = temp1->prev;
        }
        if(temp2)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }
        carry = sum / 10;
        sum = sum % 10;
        insert_first(headR, tailR, sum);
    }
}