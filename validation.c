/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

// Function to read and validate command line arguments
int read_and_validate(char **argv, int argc, Slist **head)
{
    // Check if the number of arguments is less than 2 (i.e., no files provided)
    // if(argc < 2)
    // {
    //     // Print error message and exit if no files are provided
    //     printf("Error!\nLess number of arguments\nEnter the arguments as -> ./a.out <file_name1.txt> <file_name2.txt> ... <file_nameN.txt>\n");
    //     return FAILURE;  
    // }
    // else
        printf("\nINFO: Arguments Validated Successfully.\n"); 
    sleep(1);  

    // Loop through all files provided as command-line arguments
    for(int  i = 1; i < argc; i++)
    {
        char *addr = NULL;
        addr = strchr(argv[i], '.');  // Find the position of the dot in the file name (extension)

        // Check if there is no dot in the file name 
        if(addr == NULL)
        {
            printf("\nError!\nIncorrect file name \"%s\"\nEnter file name of .txt extension\nFile Ignored, operation continued\n", argv[i]);
            continue;
        }
        else
        {
            // If the file has an extension but it's not ".txt", print an error and ignore the file
            if(strcmp(addr, ".txt") != 0)
            {
                printf("\nError!\nIncorrect file name \"%s\"\nEnter file name of .txt extension\nFile Ignored, operation continued\n", argv[i]);
                continue;
            }

            // Check if the file is already in the linked list
            if(check_in_list(*head, argv[i]) == NOT_FOUND)
            {
                // If not found, insert the file into the list
                if(insert_at_last(head, argv[i]) == FAILURE)
                {
                    // If insert operation fails, print error and return FAILURE
                    printf("\nError!\nCould't perform insert list operation\n");
                    return FAILURE;
                }
            } 
            else
            {
                // If file is already in the list (duplicate), print a message and continue with the next file
                printf("\nError!\nDuplicate file found\nCurrent file \"%s\" is ignored, operation continued\n", argv[i]);
                continue;
            } 
        }
    }

    if(*head == NULL)
        printf("\nINFO: No filename(s) entered\n");
    else
        printf("\nINFO: Filename(s) validated and list is updated Successfully.\n");
    sleep(1); 
}
