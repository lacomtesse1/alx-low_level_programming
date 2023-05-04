#include "lists.h"

/**
 * insert_nodeint_at_index - Inserts a new node in a linked list at a given index
 * @head: Pointer to the first node of the list
 * @idx: Index where the new node is inserted
 * @n: Data to insert in the new node
 *
 * Return: Pointer to the new node, or NULL
 */
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
{
	unsigned int i;
	listint_t *new_node;
	listint_t *temp_node = *head;

	new_node = malloc(sizeof(listint_t));
	if (!new_node || !head)
		return (NULL);

	new_node->n = n;
	new_node->next = NULL;

	if (idx == 0)
	{
		new_node->next = *head;
		*head = new_node;
		return (new_node);
	}

	for (i = 0; temp_node && i < idx; i++)
	{
		if (i == idx - 1)
		{
			new_node->next = temp_node->next;
			temp_node->next = new_node;
			return (new_node);
		}
		else
			temp_node = temp_node->next;
	}

	return (NULL);
}
