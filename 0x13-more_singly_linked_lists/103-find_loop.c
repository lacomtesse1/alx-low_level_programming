#include "lists.h"

/**
 * find_listint_loop - it finds  loop in linked list
 * @head: linked list to search for..
 * Return: where the loop starts, or NULL
 */
listint_t *find_listint_loop(listint_t *list_head)
{
    listint_t *slow_ptr = list_head;
    listint_t *fast_ptr = list_head;

    if (!list_head)
        return (NULL);

    while (slow_ptr && fast_ptr && fast_ptr->next)
    {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
        if (fast_ptr == slow_ptr)
        {
            slow_ptr = list_head;
            while (slow_ptr != fast_ptr)
            {
                slow_ptr = slow_ptr->next;
                fast_ptr = fast_ptr->next;
            }
            return (fast_ptr);
        }
    }

    return (NULL);
}

