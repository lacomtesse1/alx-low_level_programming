#include "lists.h"

/**
 * free_listint_safe - it frees a linked list even if it contains a loop
 * @h: pointer to  first node in  linked list
 *
 * Return: number of nodes freed
 */
size_t free_listint_safe(listint_t **h)
{
	size_t nodes_freed = 0;
	int diff;
	listint_t *next_node;

	if (!h || !*h)
		return (0);

	while (*h)
	{
		diff = *h - (*h)->next;
		if (diff > 0)
		{
			next_node = (*h)->next;
			free(*h);
			*h = next_node;
			nodes_freed++;
		}
		else
		{
			free(*h);
			*h = NULL;
			nodes_freed++;
			break;
		}
	}

	*h = NULL;

	return (nodes_freed);
}

