#include "lists.h"

/**
 * print_listint - prints all the elements of a linked list
 * @head: pointer to the head of a linked list of type listint_t to print
 *
 * This function prints all the integer values stored in each node of a linked
 * list of type listint_t, starting from the head of the list.
 *
 * Return: the number of nodes in the list
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
