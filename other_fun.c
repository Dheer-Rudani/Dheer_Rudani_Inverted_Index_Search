/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int create_hash(hash_t *arr, int size)
{
    //Creating hash table
    for(int i = 0; i < size; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }
}

int insert_at_last(Slist **head, char *f_name)
{
    //Allocating the memory
    Slist *new = malloc(sizeof(Slist));
    
    //Validating the allocated memory
    if(new == NULL)
        return FAILURE;

    //Update the data and link
    new->f_name = f_name;
    new->next = NULL;
    
    //Traverse the existing list if list exist
    Slist *temp = *head;
    if(temp != NULL)
    {
        while(temp->next != NULL)
            temp = temp->next;
        //Update the last node to point to new node
        temp->next = new;
    }
    else
        //Update the head pointer to new node
        *head = new;
        
    return SUCCESS;
}

//To check in the list
int check_in_list(Slist *head, char *f_name)
{
    while(head != NULL)
    {
        if(strcmp(head->f_name, f_name) == 0)
            return FOUND;
        head = head->next;
    }
    return NOT_FOUND;
}

//To print the list
void print_slist(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head->f_name);
		    head = head -> next;
	    }

	    printf("NULL\n");
    }
}
