/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int display_database(hash_t *arr)
{
    // Check if the database is empty
    if(check_empty(arr) == EMPTY)
        return EMPTY;

    // Print column headers for the database display
    printf("Ind\t%10s : No. of Files : %10s : No. of Words....\n\n","Word", "File name");

    // Loop through each index in the hash table
    for(int i = 0; i < 28; i++)
    {
        if(arr[i].link != NULL)
        {
            // Print the index number
            printf("[%d]\t",i);
            main_n *t1 = arr[i].link;

            // Traverse through the main nodes at this index
            while(t1 != NULL)
            {
                sub_n *t2 = t1->s_link;
                // Print the word and its associated file count
                printf("%10s :   %d file(s) ", t1->word, t1->file_count);

                // Traverse through the sub-nodes (file names) for this word
                while(t2 != NULL)
                {
                    // Print the file name and its word count
                    printf(": %10s :   %d time(s) ", t2->file_name, t2->word_count);
                    t2 = t2->sub_link; //Move the subnode pointer
                }
                printf("\n\t");
                t1 = t1->m_link;//Move the mainnode pointer
            }
            printf("\n");
        }
    }
}


// Checks whether the inverted index database is empty or not.
int check_empty(hash_t *arr)
{
    // Loop through all indexes and check if any index has a non-NULL link
    for(int  i = 0; i < 28; i++)
    {
        if(arr[i].link != NULL)
            return NOT_EMPTY;
    }
    // Return EMPTY if all indexes are empty
    return EMPTY;
}
