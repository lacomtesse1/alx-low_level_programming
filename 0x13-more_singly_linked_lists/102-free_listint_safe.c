#include "lists.h"

/**
 * 
 */
size_t free_listint_safe(listint_t **head)
{
    size_t count = 0;
    int diff;
    listint_t *temp;

    if (!head || !*head)
        return (0);

    while (*head)
    {
        diff = *head - (*head)->next;
        if (diff > 0)
        {
            temp = (*head)->next;
            free(*head);
            *head = temp;
            count++;
        }
        else
        {
            free(*head);
            *head = NULL;
            count++;
            break;
        }
    }

    *head = NULL;

    return (count);
}
