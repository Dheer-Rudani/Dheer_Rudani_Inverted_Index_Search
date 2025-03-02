/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int main(int argc, char **argv)
{
    //Creating a hash table
    hash_t arr[28];
    if(create_hash(arr, 28) == FAILURE)
    {
        printf("Error!\nFailed to creat hash table\n");
        return FAILURE;
    }

    //Declaring the list pointer and monitoring variable
    Slist *head = NULL;
    int cre_flag = 0;

    //Validation
    if(read_and_valid
        ate(argv, argc, &head) == FAILURE)
        return FAILURE;

    // printf("\n");
    // print_slist(head);

    //Reading the choice
    int choice;
    while(1)
    {
        //Reading the choice
        printf("\nWhat do you wan't to perform?\n");
        printf("1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        //Perfoming the action based upon the choice
        switch (choice)
        {
            case 1:
            if(head == NULL)
            {
                printf("Error!\nCannot create database.\nYou can only update database\n");
                break;
            }
            else if(cre_flag == 0)
            {
                if(create_database(arr, head) == FAILURE)
                {
                    printf("\nError!\nFailed to perform database creation\n");
                    return FAILURE;
                }
                cre_flag = 1; //Check flag to indicate that data base is crested or not
            }
            else
                printf("INFO: Database is already created.....\n");
                break;

            case 2:
               if(display_database(arr) == EMPTY)
               {
                    printf("INFO: Database is not yet created....\n");
               }
               break;

            case 3:
                int res = search_database(arr); 
                if(res == EMPTY)
                    printf("INFO: Database is not yet created....\n");
                else if(res == NOT_FOUND)
                    printf("INFO: Word Not Found\n");                    
                break;

            case 4: 
                if(save_database(arr) == EMPTY)
                    printf("INFO: Database is not yet created....\n");
                break;

            case 5:
                if(cre_flag == 1)
                {
                    printf("INFO: Database is already created.\nCannot update the database\n");
                    break;
                }
                else if(update_database(arr, &head) == FAILURE)
                    break;
                printf("INFO: Database is updated successfully\n");
                break;

            case 6:
                return SUCCESS;
            
            default:
                printf("Error!\nInvalid Choice\n");
                break;
        }
    }
}
