#include "lists.h"

/**
 * free_listint2 - Frees a linked list
 * @head: Pointer to the listint_t list to be freed
 *
 * Return: Void
 */
void free_listint2(listint_t **head)
{
	listint_t *current;

	if (head == NULL || *head == NULL)
		return;

	while (*head != NULL)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
	}

	*head = NULL;
}
