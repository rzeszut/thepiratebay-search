#include "list.h"

#include <stdlib.h>

struct list_t *list_create(void *data, struct list_t *next)
{
    struct list_t *cons = malloc(sizeof(struct list_t));

    cons->data = data;
    cons->next = next;

    return cons;
}

void list_free(struct list_t *lst)
{
    if (!lst) return;

    list_free(lst->next);
    free(lst);
}

void list_free_with_data(struct list_t *lst, void (*data_free)(void *))
{
    if (!lst) return;

    list_free(lst->next);
    data_free(lst->data);
    free(lst);
}

