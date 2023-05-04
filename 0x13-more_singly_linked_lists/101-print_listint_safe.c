#include "lists.h"
#include <stdio.h>

size_t looped_listint_len(const listint_t *h);
size_t print_listint_safe(const listint_t *h);

/**
 * 
 */
size_t looped_listint_len(const listint_t *h)
{
	const listint_t *slow = NULL, *fast = NULL;
	size_t count = 1;

	if (h == NULL || h->next == NULL)
		return (0);

	slow = h->next;
	fast = (h->next)->next;

	while (fast)
	{
		if (slow == fast)
		{
			slow = h;
			while (slow != fast)
			{
				count++;
				slow = slow->next;
				fast = fast->next;
			}

			slow = slow->next;
			while (slow != fast)
			{
				count++;
				slow = slow->next;
			}

			return (count);
		}

		slow = slow->next;
		fast = (fast->next)->next;
	}

	return (0);
}

/**
 * print_listint_safe - Prints a listint_t list safely.
 * @h: A pointer to the head of the listint_t list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_listint_safe(const listint_t *h)
{
	size_t count, index = 0;

	count = looped_listint_len(h);

	if (count == 0)
	{
		for (; h != NULL; count++)
		{
			printf("[%p] %d\n", (void *)h, h->n);
			h = h->next;
		}
	}

	else
	{
		for (index = 0; index < count; index++)
		{
			printf("[%p] %d\n", (void *)h, h->n);
			h = h->next;
		}

		printf("-> [%p] %d\n", (void *)h, h->n);
	}

	return (count);
}

