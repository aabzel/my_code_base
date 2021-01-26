#include "auriga_task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

xSomeStruct_t node;

/* Counts the number of items in a list.
 */
int count_list_items (const list_t *head) {
    int cnt = 0;
    list_t *cur_node = (list_t *)head;
    while (cur_node != NULL) {
        cnt++;
        cur_node = cur_node->next;
    }
    return cnt;
}

/* Inserts a new list item after the one specified as the argument.
 */
void insert_next_to_list (list_t *item, int data) {
    list_t *new_item = NULL;
    list_t *cur_item = item;
    new_item = (list_t *)malloc (sizeof (list_t));
    if (new_item) {
        new_item->data = data;
        new_item->next = item->next;
        cur_item->next = new_item;
    }
}

/* Removes an item following the one specificed as the argument.
 */
void remove_next_from_list (list_t *item) {
    list_t *cur_item = NULL;
    list_t *del_item = NULL;
    if (NULL != item) {
        cur_item = item;
        if (item->next) {
            del_item = item->next;
            cur_item->next = del_item->next;
            del_item->next = NULL;
            free (del_item);
            if (del_item) {
                del_item = NULL;
            }
        }
    }
}

/* Returns item data as text.
 */
char *item_data (const list_t *list) {
    static char buf[12];
    strncpy (buf, "", sizeof (buf));
    if (NULL != list) {
        snprintf (buf, sizeof (buf), "%d", list->data);
    }
    return buf;
}

void show_linded_list (list_t *head) {
    list_t *cur_node = head;
    printf ("\n Start of list\n");
    while (cur_node != NULL) {
        printf ("%s ", item_data (cur_node));
        cur_node = cur_node->next;
    }
    printf ("\n End of list\n");
}
