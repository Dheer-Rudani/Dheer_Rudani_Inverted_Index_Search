/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#include "Inverted_search.h"

int create_database(hash_t *arr, Slist *head)
{
    FILE *fp = NULL;
    while (head != NULL)
    {
        //Open the file
        fp = fopen(head->f_name, "r");
        if(fp == NULL)
        {
            printf("Error!\nFailed to open the file \"%s\" (or) File not present\nRecheck the files\n", head->f_name);
            return FAILURE;
        }
        
        //Read one word and update details at appropriate index
        char *str;
        while((fscanf(fp, "%s", str)) != EOF)
        {
            int ind, flag = 1;
            // printf("%s\n", str);
            //Finding the index
            if(str[0] >= 97 && str[0] <=122)
                ind = str[0] - 97;
            else if(str[0] >= 65 && str[0] <= 90)
                ind = str[0] - 65;
            else if(str[0] >= 48 && str[0] <= 57)
                ind = 26;
            else 
                ind = 27;

            //If there is no node from that particular index
            if(arr[ind].link == NULL)
            {
                //Creating a mainnode, subnode and linking them
                main_n *mnew = create_mainnode(str,1);
                sub_n *snew = create_subnode(head->f_name,1);
                arr[ind].link = mnew;
                mnew->s_link = snew;
                
            } 
            //If there is node at that index
            else if(arr[ind].link != NULL)
            {
                //Traverse the mainnode until the lastnode and compare the new data
                main_n *temp = arr[ind].link, *prev1 = NULL;
                while(temp != NULL)
                {
                    //Compare the mainnode word with new word
                    if(strcmp(temp->word, str) == 0)
                    {
                        compare_sub(temp, head->f_name);
                        break;
                    }

                    if(temp->m_link == NULL)
                        prev1 = temp;

                    temp = temp->m_link;
                }

                //If there is no node then create one, update and link it
                if(prev1 != NULL)
                {
                    main_n *mnew = create_mainnode(str,1);
                    sub_n *snew = create_subnode(head->f_name,1);
                    prev1->m_link = mnew;
                    mnew->s_link = snew;   
                }
            }
        }
        head = head->next;
    }  

    printf("INFO: Database is created successfully.\n");
    return SUCCESS;
}

//It creates the mainnode and returns its address
main_n *create_mainnode(char *str, int file_c)
{
    //Allocating a new location 
    main_n *new = malloc(sizeof(main_n));
    
    //Validating the allocated memory
    if(new == NULL)
        return NULL;
    
    //Updating the values
    new->word = strdup(str); // Use strdup to make the word pointer to point to different memory location
    new->file_count = file_c;
    new->m_link = NULL;
    new->s_link = NULL;
    
    return new;
}

//It creates the subnode and returns its address
sub_n *create_subnode(char *str, int word_c)
{
    //Allocating a new memory location
    sub_n *new = malloc(sizeof(sub_n));

    //Validating the memory location
    if(new == NULL)
        return NULL;

    //Updating the values
    new->file_name = strdup(str);// Use strdup to make the filename pointer to point to different memory location
    new->sub_link = NULL;
    new->word_count = word_c;

    return new;
}

//It compares the file names present in the sub nodes
int compare_sub(main_n *str1, char *str2)
{
    sub_n *temp2 = str1->s_link, *prev = NULL;
    
    //Traverse and compare the file name
    while(temp2 != NULL)
    {
        //If the file name present 
        if(strcmp(temp2->file_name, str2) == 0)
        {
            temp2->word_count++; //Update the word count
            return SUCCESS;
        }

        if(temp2->sub_link == NULL)
            prev = temp2;
        
        temp2 = temp2->sub_link;
    }

    //If filename not present 
    if(prev != NULL)
    {
        sub_n *snew = create_subnode(str2, 1); //Creating a new subnode
        prev->sub_link = snew; //linking the subnode with previous subnode
        str1->file_count++; //Incrementing the file count
    }

    return SUCCESS;
}

