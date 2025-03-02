/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int update_database(hash_t *arr, Slist **head)
{
    //Declaring the variables to read the file name
    char str[25];
    printf("Enter the backup file name: ");
    scanf("%s", str);
    printf("\n");

    //Validating the entered file name
    if (validate_backup_update(str) == FAILURE)
        return FAILURE;

    //Opening the file in write mode
    FILE *fptr = fopen(str, "r");

    //Validating whether the file is open or not
    if (fptr == NULL) 
    {
        printf("Error!\nFailed to open file.\n");
        return FAILURE;
    }

    //Declaring the control variables
    char file[250], delim[3] = ";";  // Delimiters: # and ;
    while (fscanf(fptr, "%[^\n]\n", file) != EOF)  // Read a line (excluding newline)
    {
        //Replacing # by ; in start and end
        replace_char(file);

        //Declaring the storing variables
        int ind, *word_c, file_c;
        char word[20], **file_name;

        char *token = strtok(file, delim);
        //Read index
        ind = atoi(token);
        //Read word
        token = strtok(NULL, delim);

        while(token != NULL)
        {
            //Store word
            strcpy(word, token);
            token = strtok(NULL, delim);
            //Read fine count
            file_c = atoi(token);

            //Allocate memory for number file_name and word_count
            file_name = malloc(file_c * sizeof(char));
            word_c = malloc(file_c * sizeof(int));
            
            for(int i = 0; i < file_c; i++)
            {
                //Allocating the memory for file_name
                file_name[i] = malloc(50 * sizeof(char));
                token = strtok(NULL, delim);
                //Storing the file name
                strcpy(file_name[i], token);
                token = strtok(NULL, delim);
                //Stroing the word count
                word_c[i] = atoi(token);
            }

            //Checking the files entered through the CLA 
            compare_list(head, file_name, file_c);

            //Updating the hashtable data
            insert_last(arr, ind, word, file_c, file_name, word_c);

            //Updating the token value
            token = strtok(NULL, delim);
        }
    }
    fclose(fptr);
    return SUCCESS;
}


int validate_backup_update(char *str)
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
        //Compare to check whether the extension is .txt or not
        if(strcmp(addr, ".txt") != 0)
        {
            printf("Error!\nIncorrect file name \"%s\"\nEnter file name of .txt extension\n", str);
            return FAILURE;
        }

        //Open the file
        FILE *fp = fopen(str, "r");

        //Check whether the file is open or not
        if(fp == NULL)
        {
            printf("Error!\nFile not found\n");
            return FAILURE;
        }

        //Read the first line
        char file[100];
        int size;
        fscanf(fp, "%[^\n]", file);
        fclose(fp);
        size = strlen(file);

        //Check whether the start and end of the line has # or not
        if(file[0] == file[size - 1])
            return SUCCESS;
        else
        {
            printf("Error!\nThe entered file \"%s\" is not a backup file\n",str);
            return FAILURE;
        }
    }
}


int insert_last(hash_t *arr, int ind, char *word, int file_c, char **file_name, int *word_c)
{
    //Creating a main node and sub nodes
    main_n *mnew = create_mainnode(word, file_c);
    for(int i = 0; i < file_c; i++)
    {
        insert_sub(mnew, file_name[i], word_c[i]);
    }

    //Vailidating the mainnode
    if(mnew == NULL)
        return FAILURE;

    //Checking the node link and linking the new node appropriately
    if(arr[ind].link == NULL)
    {
        arr[ind].link = mnew;
    }
    else
    {
        //Declaring the traversing variable
        main_n *t1 = arr[ind].link;

        //Traversing till the last node
        while(t1->m_link != NULL)
        {
            t1 = t1->m_link;
        }

        //Linking the last node to new node
        t1->m_link = mnew;
    }
}

//It will insert the subnodes
int insert_sub(main_n *mnew, char *file_name, int word_c)
{
    //Creating a subnode
    sub_n *snew = create_subnode(file_name, word_c);

    //Validating the created node
    if(snew == NULL)
        return FAILURE;

    //Checking for the node link and linking appropriately
    if(mnew->s_link == NULL)
    {
        mnew->s_link = snew; //Linking the main node to subnode
    }
    else
    {
        //Declaring the traversing variable
        sub_n *temp = mnew->s_link;

        //Traversing till the last node
        while(temp->sub_link != NULL)
        {
            temp = temp->sub_link;
        }

        //Linking the last node with new node
        temp->sub_link = snew;
    }
    return SUCCESS;
}

//It will replace # by ;
int replace_char(char *file)
{
    int size = strlen(file);
    
    //Replacing the # by ; so that it can be ignored
    file[0] = file[size - 1] = ';';

    return SUCCESS;
}

int compare_list(Slist **head, char **file_name, int file_c)
{
    //Repeating for all file names
    for(int i = 0; i < file_c; i++)
    {
        Slist *temp = *head, *prev = NULL;

        while(temp != NULL)
        {
            if(strcmp(temp->f_name, file_name[i]) == 0)
            {
                if(prev == NULL) //Checking whether the data is present in first node or not
                {
                    *head = (*head)->next; //Moving the head pointer
                    free(temp); //Deleting the previous head node
                    temp = *head; // Move temp to the new head node after deletion
                    return SUCCESS;
                }
                else
                {
                    prev->next = temp->next; //Pointing the prev pointer to next node after the data node
                    free(temp); //Deleting the data node
                    temp = prev->next; // Move temp to the next node after deletion
                    return SUCCESS;
                }
            }
            prev = temp; //Moving the prev pointer
            temp = temp->next; //Moving the temp pointer to the next node
        }
    }

    return FAILURE; // In case no match is found
}