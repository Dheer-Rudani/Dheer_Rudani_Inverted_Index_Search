/*
    Name: Dheer Rudani
    Description: Inverted Index Search 
    Date: 12/02/2025
*/

#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE 1
#define NOT_FOUND 2
#define FOUND 3
#define NOT_EMPTY 4
#define EMPTY 5

//Declarations
typedef struct node
{
    int index;
    struct mainnode *link;
}hash_t;

typedef struct mainnode
{
    char *word;
    int file_count;
    struct mainnode *m_link;
    struct subnode *s_link;
}main_n;

typedef struct subnode
{
    char *file_name;
    int word_count;
    struct subnode *sub_link;
}sub_n;

typedef struct list
{
    char *f_name;
    struct list *next;
}Slist;

//Initial functions
int create_hash(hash_t *arr, int size);
int read_and_validate(char **argv, int argc, Slist **head);
int check_in_list(Slist *head, char *f_name);
int insert_at_last(Slist **head, char *f_name);
int create_database(hash_t *arr, Slist *head);
void print_slist(Slist *head);

//Create
main_n *create_mainnode(char *str, int file_c);
sub_n *create_subnode(char *str, int word_c);
int compare_sub(main_n *str1, char *str2);

//Display
int display_database(hash_t *arr);
int check_empty(hash_t *arr);

//Search 
int search_database(hash_t *arr);

//Save
int validate_backup(char *str);
int save_database(hash_t *arr);

//Update 
int update_database(hash_t *arr, Slist **head);
int validate_backup_update(char *str);
int insert_last(hash_t *arr, int ind, char *word, int file_c, char **file_name, int *word_c);
int insert_sub(main_n *mnew, char *file_name, int word_c);
int replace_char(char *file);
int compare_list(Slist **head, char **file_name, int file_c);

#endif