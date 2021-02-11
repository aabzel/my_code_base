#include "test_sort_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "linked_list.h"
#include "sort_list.h"
#include "uTests.h"


bool test_sort_list (void){
    printf ("\n%s()", __FUNCTION__);
	ListNode_t *headNode = NULL;
	EXPECT_TRUE(list_add_node_front (&headNode, 1));
	EXPECT_TRUE(list_add_node_front (&headNode, 3));
	EXPECT_TRUE(list_add_node_front (&headNode, 2));
	EXPECT_TRUE(list_add_node_front (&headNode, 5));
	EXPECT_TRUE(list_add_node_front (&headNode, -7));
	EXPECT_TRUE(list_add_node_front (&headNode, -1));
	print_linked_list (headNode);

	//headNode = sortList(headNode);
	headNode = sort_list_merge(headNode);

	print_linked_list (headNode);
	printf ("\n%s() done!", __FUNCTION__);
	return false;
}
