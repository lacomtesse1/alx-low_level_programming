#include "lists.h"

/**
 * 
 */
size_t print_listint(const listint_t *head)
{
	size_t count = 0;

	while (head)
	{
		printf("%d\n", head->n);
		count++;
		head = head->next;
	}

	return (count);
}
