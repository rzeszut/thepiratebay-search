#ifndef LIST_H_GJQUOEX2
#define LIST_H_GJQUOEX2

/** Structure representing simple single-linked list. */
struct list_t {
    void *data;
    struct list_t *next;
};

struct list_t *list_create(void *data, struct list_t *next);

void list_free(struct list_t *lst);

void list_free_with_data(struct list_t *lst, void (*data_free)(void *));

#define list_head(lst) (lst)->data

#define list_tail(lst) (lst)->next

#endif /* end of include guard: LIST_H_GJQUOEX2 */
