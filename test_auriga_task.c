#include "test_auriga_task.h"

#include "auriga_task.h"
#include "uTests.h"

static bool test_auriga_task_case2 (void) {
    list_t head;
    head.data = 1;
    head.next = NULL;
    EXPECT_EQ (1, count_list_items (&head));

    insert_next_to_list (&head, 2);
    insert_next_to_list (&head, 3);
    insert_next_to_list (&head, 4);
    insert_next_to_list (&head, 5);
    insert_next_to_list (&head, 6);

    EXPECT_EQ (6, count_list_items (&head));
    show_linded_list (&head);
    return true;
}

static bool test_auriga_task_case4(void) {
    list_t *head=NULL;
    EXPECT_EQ (0, count_list_items (head));
    show_linded_list (head);
    return true;
}

static bool test_auriga_task_case1(void) {
    list_t head;
    head.data = 1;
    head.next = NULL;

    EXPECT_EQ (1, count_list_items (&head));
    show_linded_list (&head);

    return true;
}

static bool test_auriga_task_case3 (void) {
    list_t head;
    head.data = 1;
    head.next = NULL;
    EXPECT_EQ (1, count_list_items (&head));

    insert_next_to_list (&head, 2);
    EXPECT_EQ (2, count_list_items (&head));

    insert_next_to_list (&head, 3);
    EXPECT_EQ (3, count_list_items (&head));

    insert_next_to_list (&head, 4);
    EXPECT_EQ (4, count_list_items (&head));

    insert_next_to_list (&head, 5);
    EXPECT_EQ (5, count_list_items (&head));

    insert_next_to_list (&head, 6);
    EXPECT_EQ (6, count_list_items (&head));

    remove_next_from_list (&head);
    EXPECT_EQ (5, count_list_items (&head));

    remove_next_from_list (&head);
    EXPECT_EQ (4, count_list_items (&head));
    show_linded_list (&head);

    return true;
}

bool test_auriga_task (void) {
	printf ("\n[d] %s()\n", __FUNCTION__);
    EXPECT_TRUE (test_auriga_task_case1 ());
    EXPECT_TRUE (test_auriga_task_case2 ());
    EXPECT_TRUE (test_auriga_task_case3 ());
    EXPECT_TRUE (test_auriga_task_case4 ());
    return true;
}
