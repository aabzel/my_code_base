#include "test_stack_num.h"

#include <stdbool.h>

#include "stack_num.h"
#include "uTests.h"

bool test_stack_num (void) {
    printf ("\n%s()", __FUNCTION__);
    numStack_t *stack_instance;
    EXPECT_TRUE (stack_init (&stack_instance, 4));

    EXPECT_TRUE (stack_push (stack_instance, 1)); stack_debug(stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 2)); stack_debug(stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 3)); stack_debug(stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 4)); stack_debug(stack_instance);

    EXPECT_TRUE (stack_push (stack_instance, 5)); stack_debug(stack_instance);
    EXPECT_TRUE (stack_push (stack_instance, 6)); stack_debug(stack_instance);

    int out_data;
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (6, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (5, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (4, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (3, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (2, out_data);
    EXPECT_TRUE (stack_pop (stack_instance, &out_data));
    stack_debug(stack_instance);
    EXPECT_EQ (1, out_data);

    stack_free (stack_instance);

    return true;
}
