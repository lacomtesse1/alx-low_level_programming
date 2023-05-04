#include "lists.h"

/**
 * pop_listint - deletes the head node of a linked list
 * @head: pointer to the first element in the linked list
 *
 * Return: the data inside the element that was deleted,
 *         or 0 if the list is empty
 */
int pop_listint(listint_t **head)
{
	listint_t *temp_node;
	int deleted_data;

	if (!head || !*head)
		return (0);

	deleted_data = (*head)->n;
	temp_node = (*head)->next;
	free(*head);
	*head = temp_node;

	return (deleted_data);
}
