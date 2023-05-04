#include "lists.h"

/**
 * get_nodeint_at_index - returns the node at a certain index in a linked list
 * @head: pointer to the head of the linked list
 * @index: index of the node to return
 *
 * Return: pointer to the node at the given index, or NULL if not found
 */
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index)
{
	unsigned int count = 0;
	listint_t *current_node = head;

	while (current_node && count < index)
	{
		current_node = current_node->next;
		count++;
	}

	return (current_node ? current_node : NULL);
}
