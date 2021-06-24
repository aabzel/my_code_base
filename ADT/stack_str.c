#include "stack_str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: how to dynamically allocate array of pointers
bool stack_str_init(strStack_t **stack_instance, int des_capacity) {
  bool res = false;
  (*stack_instance) = (strStack_t *)malloc(sizeof(strStack_t));
  if (NULL != (*stack_instance)) {
    ((*stack_instance)->data_ptr) =
        (char *)malloc(des_capacity * sizeof(char *));
    if (NULL != ((*stack_instance)->data_ptr)) {
      (*stack_instance)->index.capacity = des_capacity;
      (*stack_instance)->index.pos = 0;
      (*stack_instance)->is_init = true;
      res = true;
    }
  }
  return res;
}

bool stack_str_realloc(strStack_t *stack_instance, int new_des_capacity) {
  bool res = false;
  if (new_des_capacity == stack_instance->index.capacity) {
    return true;
  }
  if (stack_instance->index.capacity < new_des_capacity) {
    char **array = (char *)malloc(sizeof(char *) * new_des_capacity);
    if (array) {
      if (0 < (stack_instance->index.pos)) {
        memcpy(array, stack_instance->data_ptr,
               sizeof(char *) * (stack_instance->index.pos));
        free(stack_instance->data_ptr);
        stack_instance->data_ptr = array;
        stack_instance->index.capacity = new_des_capacity;
        res = true;
      }
    }
  } else {
    if ((stack_instance->index.pos < new_des_capacity) &&
        (0 < stack_instance->index.pos)) {
      char **array = (char *)malloc(sizeof(char *) * new_des_capacity);
      if (array) {
        memcpy(array, stack_instance->data_ptr,
               sizeof(int) * (stack_instance->index.pos));
        memset(stack_instance->data_ptr, 0x00,
               sizeof(int) * (stack_instance->index.capacity));
        free(stack_instance->data_ptr);
        stack_instance->data_ptr = array;
        stack_instance->index.capacity = new_des_capacity;
        res = true;
      }
    }
  }
  return res;
}

bool stack_str_push(strStack_t *stack_instance, char *in_str) {
  bool res = false;
  if (stack_instance) {
    res = true;
    bool temp_res = stack_indexer_is_full(&((stack_instance)->index));
    if (true == temp_res) {
      // printf ("\n stack_ is_full");
      int cur_cap = (stack_instance)->index.capacity;
      res = stack_str_realloc(stack_instance, cur_cap + (cur_cap / 2));
      if (false == res) {
        //  printf ("\n stack_realloc error");
      }
    }
    if (true == res) {
      // TODO is that array of ptrs?
      ((stack_instance->data_ptr[(stack_instance)->index.pos])) =
          strdup(in_str);
      if (NULL != (stack_instance->data_ptr[(stack_instance)->index.pos])) {
        res = stack_indexer_push(&((stack_instance)->index));
      }
    }
  } else {
    printf("\n Error");
  }
  return res;
}

// Мы не знаем размер строки которую надо возвращать. В стеке может быть строка
// произвольного размера stack_str_pop должно возвращать указатель на строку
// предварительно выделив память для этотого.
bool stack_str_pop(strStack_t *stack_instance, char **out_str) {
  //    printf ("\n%s()", __FUNCTION__);
  bool res = false;
  int pos = stack_instance->index.pos;
  if (0 == pos) {
    printf("\n errro empty stack", pos);
    return false;
  }
  int len_of_out_str = 0;
  char *temp_str;
  len_of_out_str = strlen(stack_instance->data_ptr[pos - 1]);
  if (0 < len_of_out_str) {
    temp_str = strdup(stack_instance->data_ptr[pos - 1]);
  } else {
    temp_str = strdup("");
  }
  *out_str = temp_str;
  // strcpy(out_str, stack_instance->data_ptr[pos - 1]);
  free(stack_instance->data_ptr[pos - 1]);
  stack_instance->data_ptr[pos - 1] = NULL;
  //  printf ("\n pos=%d data [%s]", pos, out_str);
  res = stack_indexer_pop(&(stack_instance->index));
  if ((stack_instance->index.pos < (stack_instance->index.capacity / 2)) &&
      (2 < stack_instance->index.capacity)) {
    //	printf (" realloc");
    res = stack_str_realloc(stack_instance, stack_instance->index.capacity / 2);
  }
  return res;
}

bool stack_str_peek(strStack_t *stack_instance, char *out_str) {
  bool res = false;
  int pos = stack_instance->index.pos;
  strcpy(out_str, ((stack_instance->data_ptr[pos - 1])));
  return res;
}

void stack_str_free(strStack_t *stack_instance) {
  if (stack_instance) {
    if (stack_instance->data_ptr) {
      for (int i = 0; i < stack_instance->index.pos; i++) {
        free((stack_instance->data_ptr[i]));
        (stack_instance->data_ptr[i]) = NULL;
      }
      free(stack_instance->data_ptr);
      stack_instance->data_ptr = NULL;
    }
    free(stack_instance);
    stack_instance = NULL;
  }
}

bool stack_str_debug(strStack_t *stack_instance) {
  bool res = false;
  if (stack_instance) {
    printf("\n");
    for (int i = 0; i < (stack_instance->index.pos); i++) {
      if ((stack_instance->data_ptr[i])) {
        printf(" [%s]", (stack_instance->data_ptr[i]));
        res = true;
      }
    }
  }
  return res;
}
