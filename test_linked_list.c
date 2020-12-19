#include "test_linked_list.h"

#include "linked_list.h"
#include "uTests.h"

ListNode_t *pHead;

ListNode_t Node1;
ListNode_t Node2;
ListNode_t Node3;
ListNode_t Node4;
ListNode_t Node5;

void list_print_fwd (void) {
    ListNode_t *curNode = &Node1;
    while (NULL != curNode->next) {
        printf (" %d", curNode->val);
        curNode = curNode->next;
    }
    printf (" %d", curNode->val);
    printf ("\n");
}

void list_print_rev (ListNode_t *pHead) {
    if (pHead) {
        list_print_rev (pHead->next);
        printf (" %d", pHead->val);
    }
}

void init_list (void) {
    pHead = &Node1;

    Node1.val = 1;
    Node1.next = &Node2;

    Node2.val = 2;
    Node2.next = &Node3;

    Node3.val = 3;
    Node3.next = &Node4;

    Node4.val = 4;
    Node4.next = &Node5;

    Node5.val = 5;
    Node5.next = NULL;
}


void list_print_reverse (void) {
    list_print_rev (&Node1);
    printf ("\n");
}

#define LIST_LENGTH 10
static bool test_add_front (void) {
	printf("\n[d] %s()",__FUNCTION__);
	ListNode_t* headNode = NULL;
	for (int i=0;i<LIST_LENGTH;i++) {
		EXPECT_TRUE(list_add_node_front (&headNode, i));
		EXPECT_NE( NULL,is_data_exist_linked_list(headNode, i));
	}
	EXPECT_EQ( NULL,is_data_exist_linked_list(headNode, 999));
    EXPECT_EQ(LIST_LENGTH,  linked_list_counts (headNode));

    EXPECT_TRUE(linked_list_deinit(&headNode));
	return true;
}


bool test_linked_list_ints(void) {
	printf("\n[d] %s()",__FUNCTION__);
    EXPECT_TRUE( test_add_front ());
    return true;
}


