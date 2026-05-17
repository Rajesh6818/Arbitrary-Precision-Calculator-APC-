// Y.Rajesh
// Batch - 36A
/*This project implements an Arbitrary Precision Calculator using the C programming language 
to perform arithmetic operations on very large numbers that exceed the limits of standard data types.*/

#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;

    // Validation
	cla_validation(argc,argv);

    // Create 2 lists of operands
	create_list(argv[1],&head1,&tail1);
	create_list(argv[3],&head2,&tail2);

     //sign handling
    int sign1 = 1, sign2 = 1;

    if(argv[1][0] == '-')
        sign1 = -1;

    if(argv[3][0] == '-')
        sign2 = -1;
    
		char op = argv[2][0];
    switch(op)
    {
        //ADDITION
        case '+':
            if(sign1 == sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                if(sign1 == -1)
                    printf("-");
            }
            else
            {
                if(compare_list(head1, head2) == OPERAND1)
                {
                    subtraction(tail1, tail2, &headR, &tailR);

                    if(sign1 == -1)
                        printf("-");
                }
                else if(compare_list(head1, head2) == OPERAND2)
                {
                    subtraction(tail2, tail1, &headR, &tailR);

                    if(sign2 == -1)
                        printf("-");
                }
				else
				{
					insert_last(&headR,&tailR,0);
				}
            }
            break;
        //SUBTRACTION
        case '-':
            if(sign1 != sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                if(sign1 == -1)
                    printf("-");
            }
            else
            {
                if(compare_list(head1, head2) == OPERAND1)
                {
                    subtraction(tail1, tail2, &headR, &tailR);

                    if(sign1 == -1)
                        printf("-");
                }
                else if(compare_list(head1, head2) == OPERAND2)
                {
                    subtraction(tail2, tail1, &headR, &tailR);

                    if(sign1 == 1)
                        printf("-");
                }
				else
				{
					insert_last(&headR,&tailR,0);
				}
            }
            break;
        //MULTIPLICATION
        case 'x':
		case 'X':
            multiplication(tail1, tail2, &headR, &tailR);

            if(sign1 != sign2)
                printf("-");
            break;
        // DIVISION 
        case '/':
            division(head1, head2, tail2, &headR, &tailR);

			if(headR->data != 0 && sign1 != sign2)
			{
                printf("-");
			}
            break;
        default:
            printf("Invalid operator\n");
            return 0;
    }
    // print result
	remove_pre_zeros(&headR);
    print_list(headR);

    return 0;
}
