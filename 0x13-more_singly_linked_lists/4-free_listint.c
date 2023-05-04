#include "lists.h"

/**
 * free_listint - frees a linked list
 * @head: pointer to the head of the list to be freed
 */
void free_listint(listint_t *head)
{
	listint_t *current;

	while (head)
	{
		current = head->next;
		free(head);
		head = current;
	}
}
