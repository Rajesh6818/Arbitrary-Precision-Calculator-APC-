#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    //Logic for Subtraction of two numbers
    //1.Declare temp pointers
    node *temp1 = tail1;
    node *temp2 = tail2;

    int data1 = 0;
    int data2 = 0;
    int diff = 0, borrow = 0;

    //2.Traverse till list1 becomes NULL
    while(temp1 != NULL)
    {
        //3.Fetch data from list1
        data1 = temp1->data;
        //4.Fetch data from list2
        if(temp2 == NULL)
        {
            data2 = 0;
        }
        else
        {
            data2 = temp2->data;
        }
        //5.Apply borrow if exists
        data1 = data1 - borrow;

        //6.Check if borrow is needed
        if(data1 < data2)
        {
            diff = (data1 + 10) - data2;
            borrow = 1;
        }
        else
        {
            diff = data1 - data2;
            borrow = 0;
        }

        //7.Insert result at first
        insert_first(headR, tailR, diff);

        //8.Move to previous nodes
        temp1 = temp1->prev;

        if(temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }
}
 