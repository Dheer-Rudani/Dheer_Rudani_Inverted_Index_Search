/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int save_database(hash_t *arr)
{
    //Check whether the database is created or not
    if(check_empty(arr) == EMPTY)
        return EMPTY;

    //Reading the file name
    char str[25];
    printf("Enter the backup file name: ");
    scanf("%s", str);
    printf("\n");

    //Validating the backup file name
    if(validate_backup(str) == FAILURE)
        return FAILURE;

    //Openong the file in write mode
    FILE *bkp = fopen(str, "w");

    //Validating whether the file is opened or not
    if(bkp == NULL)
    {
        printf("Error!\nFailed to open the file\n");
        return FAILURE;
    }

    // Loop through each index in the hash table
    for(int i = 0; i < 28; i++)
    {
        if(arr[i].link != NULL)
        {
            // Print the index number
            fprintf(bkp,"#%d",i);
            main_n *t1 = arr[i].link;

            // Traverse through the main nodes at this index
            while(t1 != NULL)
            {
                sub_n *t2 = t1->s_link;
                // Print the word and its associated file count
                fprintf(bkp,";%s;%d", t1->word, t1->file_count);

                // Traverse through the sub-nodes (file names) for this word
                while(t2 != NULL)
                {
                    // Print the file name and its word count
                    fprintf(bkp,";%s;%d;", t2->file_name, t2->word_count);
                    t2 = t2->sub_link; //Move the subnode pointer
                }
                t1 = t1->m_link;//Move the mainnode pointer
            }
            fprintf(bkp,"#\n");
        }
    }
    fclose(bkp);
    printf("INFO: Database is saved successfully\n");
    return SUCCESS;
}

//It will validate the backup file name
int validate_backup(char *str)
{
    //Finding the address of the .
    char *addr = strchr(str, '.');

    //Validating whether the '.' is present or not
    if(addr == NULL)
    {
        printf("Error!\nIncorrect file name \"%s\"\nEnter file name of .txt extension\n", str);
        return FAILURE;
    }
    //If it is present the validating whether it is .txt or not
    else
    {
        if(strcmp(addr, ".txt") != 0)
        {
            printf("Error!\nIncorrect file name \"%s\"\nEnter file name of .txt extension\n", str);
            return FAILURE;
        }
        return SUCCESS;
    }
}