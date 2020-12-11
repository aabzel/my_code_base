#include "test_stack_num.h"

#include <stdbool.h>
#include <stdlib.h>

#include "stack_num.h"
#include "stack_str.h"
#include "uTests.h"

bool test_stack_num (void) {
    printf ("\n%s()", __FUNCTION__);
    numStack_t *stack_instance;
    EXPECT_TRUE (stack_init (&stack_instance, 4));

    EXPECT_TRUE (stack_push (stack_instance, 1));
    stack_debug (stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 2));
    stack_debug (stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 3));
    stack_debug (stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 4));
    stack_debug (stack_instance);

    EXPECT_TRUE (stack_push (stack_instance, 5));
    stack_debug (stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 6));
    stack_debug (stack_instance);

    int out_data;
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (6, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (5, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (4, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (3, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (2, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug (stack_instance);
    EXPECT_EQ (1, out_data);

    stack_free (stack_instance);

    return true;
}


bool test_stack_str (void) {
    printf ("\n%s()", __FUNCTION__);
    strStack_t *stack_str_instance;
    EXPECT_TRUE (stack_str_init (&stack_str_instance, 4));

    EXPECT_TRUE (stack_str_push (stack_str_instance, "1"));
    stack_str_debug (stack_str_instance);
    EXPECT_TRUE (stack_str_push (stack_str_instance, "2"));
    stack_str_debug (stack_str_instance);
    EXPECT_TRUE (stack_str_push (stack_str_instance, "3"));
    stack_str_debug (stack_str_instance);
    EXPECT_TRUE (stack_str_push (stack_str_instance, "4"));
    stack_str_debug (stack_str_instance);
    EXPECT_TRUE (stack_str_push (stack_str_instance, "5"));
    stack_str_debug (stack_str_instance);
    EXPECT_TRUE (stack_str_push (stack_str_instance, "6"));
    stack_str_debug (stack_str_instance);
#if 1

    char out_str[100];
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance); // [1] [2] [3] [4] [5]
    EXPECT_EQ_STR ("6", out_str);//
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance); //[1] [2] [3] [4]
    EXPECT_EQ_STR ("5", out_str); // error
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance);
    EXPECT_EQ_STR ("4", out_str);
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance);
    EXPECT_EQ_STR ("3", out_str);
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance);
    EXPECT_EQ_STR ("2", out_str);
    EXPECT_TRUE (stack_str_pop (stack_str_instance, out_str));
    stack_str_debug (stack_str_instance);
    EXPECT_EQ_STR ("1", out_str);

    stack_str_free (stack_str_instance);
#endif
    return true;
}

bool test_ptr_array (void) {
    printf ("\n%s()", __FUNCTION__);
	char **ch_ptr = NULL;
	int i=0;
	ch_ptr = malloc (10*sizeof(int *));
	for ( i=0; i<10;i++) {
		char buff[55];
		sprintf(buff,"%d",i);
		ch_ptr[i] = strdup(buff);
	}

	for ( i = 0; i < 10; i++) {
		printf("\n%s",ch_ptr[i]);
	}

	for ( i = 0; i < 10; i++) {
		free(ch_ptr[i]);
		ch_ptr[i] = NULL;
	}

	free(ch_ptr);
	ch_ptr=NULL;
    return true;
}


bool test_stack (void) {
	EXPECT_TRUE( test_ptr_array ());
	EXPECT_TRUE( test_stack_num ());
	EXPECT_TRUE( test_stack_str () );
    return true;
}
