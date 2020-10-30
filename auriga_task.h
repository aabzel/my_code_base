
#ifndef AURIGA_TASK_H
#define AURIGA_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_s {
    struct list_s *next; /* NULL for the last item in a list */
    int data;
} list_t;

/* Counts the number of items in a list.
 */
int count_list_items (const list_t *head);

/* Inserts a new list item after the one specified as the argument.
 */
void insert_next_to_list (list_t *item, int data);

/* Removes an item following the one specificed as the argument.
 */
void remove_next_from_list (list_t *item);

void show_linded_list (list_t *head_node);

#ifdef __cplusplus
}
#endif

#endif /* AURIGA_TASK_H */
