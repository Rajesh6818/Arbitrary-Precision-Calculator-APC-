#include "apc.h"
#include <ctype.h>   // For isdigit()

// COMMAND LINE VALIDATION 
int cla_validation(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 4)
    {
        printf("ERROR: Invalid number of arguments\n");
        return FAILURE;
    }

    //  OPERATOR VALIDATION 
    if (strlen(argv[2]) != 1)
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }

    char op = argv[2][0];

    if (op != '+' && op != '-' && op != 'x' && op != 'X' && op != '/')
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }

    //  OPERAND 1 VALIDATION
    int i = 0;

    // Case: only '+' or '-' → invalid
    if ((argv[1][0] == '+' || argv[1][0] == '-') && argv[1][1] == '\0')
    {
        printf("ERROR: Invalid operand\n");
        return FAILURE;
    }

    // Skip sign if present
    if (argv[1][0] == '+' || argv[1][0] == '-')
        i = 1;

    // Check all characters are digits
    for (; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("ERROR: Operand must be an integer\n");
            return FAILURE;
        }
    }

    // OPERAND 2 VALIDATION 
    i = 0;

    if ((argv[3][0] == '+' || argv[3][0] == '-') && argv[3][1] == '\0')
    {
        printf("ERROR: Invalid operand\n");
        return FAILURE;
    }

    if (argv[3][0] == '+' || argv[3][0] == '-')
        i = 1;

    for (; argv[3][i] != '\0'; i++)
    {
        if (!isdigit(argv[3][i]))
        {
            printf("ERROR: Operand must be an integer\n");
            return FAILURE;
        }
    }
    // DIVISION BY ZERO CHECK 
    if (op == '/')
    {
        int j = 0;

        // Skip sign
        if (argv[3][0] == '+' || argv[3][0] == '-')
            j = 1;

        // Check if all digits are zero (e.g., "000")
        while (argv[3][j] == '0')
            j++;

        if (argv[3][j] == '\0')
        {
            printf("ERROR: Division by zero not allowed!\n");
            return FAILURE;
        }
    }
    return SUCCESS;
}


// CREATE LIST FROM STRING 
void create_list(char *opr, node **head, node **tail)
{
    int i = 0;

    // Skip sign (+ or -)
    if (opr[0] == '+' || opr[0] == '-')
        i = 1;

    // Convert each digit into node
    while (opr[i])
    {
        if (isdigit(opr[i]))
        {
            int data = opr[i] - '0';

            if (insert_last(head, tail, data) == FAILURE)
            {
                printf("ERROR: Memory allocation failed\n");
                exit(1);
            }
        }
        i++;
    }
}


// REMOVE LEADING ZEROS 
void remove_pre_zeros(node **head)
{
    if (*head == NULL)
        return;

    node *temp = *head;

    // Remove zeros until non-zero digit or last node
    while (temp->data == 0 && temp->next != NULL)
    {
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
        temp = *head;
    }
}


// FIND LENGTH OF LIST 
int list_len(node *head)
{
    int len = 0;

    while (head != NULL)
    {
        len++;
        head = head->next;
    }

    return len;
}


// COMPARE TWO NUMBERS 
int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    // Compare based on length first
    if (len1 > len2)
        return OPERAND1;
    else if (len1 < len2)
        return OPERAND2;

    // If lengths equal, compare digit by digit
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return OPERAND1;
        else if (head1->data < head2->data)
            return OPERAND2;

        head1 = head1->next;
        head2 = head2->next;
    }

    return SAME;
}


// INSERT AT BEGINNING 
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    // If list is empty
    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}


// INSERT AT END
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    // If list is empty
    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}


// DELETE ENTIRE LIST 
int delete_list(node **head, node **tail)
{
    if (*head == NULL)
        return FAILURE;

    node *temp = *head;

    // Free all nodes
    while (temp != NULL)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }

    *tail = NULL;

    return SUCCESS;
}


// PRINT LIST 
void print_list(node *head)
{
    if (head == NULL)
    {
        printf("INFO: List is Empty\n");
        return;
    }

    // Print each digit
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}