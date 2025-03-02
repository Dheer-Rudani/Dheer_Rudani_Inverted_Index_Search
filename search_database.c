/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int search_database(hash_t *arr)
{
    //Check if the database is empty or not
    if(check_empty(arr) == EMPTY)
        return EMPTY;

    //Declaring a char buffer 
    char str[50];
    printf("Enter the word to be searched: ");
    scanf("%s", str);
    printf("\n");

    int ind;
    //Finding the index
    if(str[0] >= 97 && str[0] <=122)
        ind = str[0] - 97;
    else if(str[0] >= 65 && str[0] <= 90)
        ind = str[0] - 65;
    else if(str[0] >= 48 && str[0] <= 57)
        ind = 26;
    else 
        ind = 27;

    //If the index is empty
    if(arr[ind].link == NULL)
        return NOT_FOUND;

    //Declaring the traversing variable
    main_n *temp = arr[ind].link;

    while(temp != NULL)
    {
        if(strcmp(temp->word, str) == 0)
        {
            printf("[%d]\t",ind);
            printf("%s : %d file(s) ", temp->word, temp->file_count);

            sub_n *t2 = temp->s_link;

            // Traverse through the sub-nodes (file names) for this word
            while(t2 != NULL)
            {
                // Print the file name and its word count
                printf(": %s : %d time(s)\n\t", t2->file_name, t2->word_count);
                t2 = t2->sub_link; //Move the subnode pointer
            }
            return FOUND;
        }
        temp = temp->m_link;//Move the mainnode pointer
    }
    return NOT_FOUND;
}