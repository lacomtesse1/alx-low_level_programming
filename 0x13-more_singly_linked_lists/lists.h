#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>

/**

struct node_s - singly linked list
@data: integer
@next: points to the next node
Description: singly linked list node structure
*/
typedef struct node_s
{
int data;
struct node_s *next;
} node_t;
size_t print_node_list(const node_t *h);
size_t node_list_len(const node_t *h);
node_t *add_node_at_start(node_t **head, const int data);
node_t *add_node_at_end(node_t **head, const int data);
void free_node_list(node_t *head);
void free_node_list2(node_t **head);
int pop_node_list(node_t **head);
node_t *get_node_at_index(node_t *head, unsigned int index);
int sum_node_list(node_t *head);
node_t *insert_node_at_index(node_t **head, unsigned int idx, int data);
int delete_node_at_index(node_t **head, unsigned int index);
node_t *reverse_node_list(node_t **head);
size_t print_node_list_safe(const node_t *head);
size_t free_node_list_safe(node_t **h);
node_t *find_node_list_loop(node_t *head);

#endif
