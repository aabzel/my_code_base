#include "decode_string.h"

#include "convert.h"
#include "stack_num.h"
#include "stack_str.h"

// Нужет стек для строк
// Нужет стек для натуральных чисел

// Как только встретили [ строку так сразу кладем ее в стек для чисел
// Как только встретили ] так срезу достаём число и строку и вставляем k раз

//   "3[a]2[bc]"        "aaabcbc"
//   "3[a2[c]]"         "accaccacc"
//   "2[abc]3[cd]ef"    "abcabccdcdcdef"
//   "abc3[cd]xyz"      "abccdcdcdxyz"

char *decodeString (char *in_text) {
    int len_of_text = strlen (in_text);
#ifdef DEBUG_DECODE_STR
    printf ("\n%s() <%s> len %d", __FUNCTION__, in_text, len_of_text);
#endif
    char *out_str = strdup ("");
    char *prefix_str = strdup ("");
    int i = 0;
    bool res = false;
    int cnt = 0;
    bool is_inside = true;
    bool is_prev_num = false;
    char *curr = strdup ("");
    numStack_t *stack_num_instance = NULL;
    strStack_t *strs = NULL;
    bool is_siffix = false;

    int opened_cnt = 0;
    int closed_cnt = 0;

    res = stack_init (&stack_num_instance, 4);
#ifdef DEBUG_DECODE_STR
    if (false == res) {
        printf ("\n stack_init error ");
    }
#endif
    res = stack_str_init (&strs, 4);
#ifdef DEBUG_DECODE_STR
    if (false == res) {
        printf ("\n stack_str_init error ");
    }
#endif
#ifdef DEBUG_DECODE_STR
    printf ("\n launch for");
#endif
    for (i = 0; i < len_of_text; i++) {
#ifdef DEBUG_DECODE_STR
        printf ("\nproc:%d:[%c] \n", i, in_text[i]);
#endif
        res = is_dec_digit (in_text[i]);
        if (true == res) {
#ifdef DEBUG_DECODE_STR
            printf ("\n catch digit [%c]", in_text[i]);
#endif
            uint8_t u8_value = 0;
            res = try_strl2uint8 (&in_text[i], 1, &u8_value);
            if (true == res) {
                cnt = cnt * 10 + (int)u8_value;
#ifdef DEBUG_DECODE_STR
                printf ("\n tmp cnt [%d]", cnt);
#endif
            } else {
                printf ("\n unable to parse %s", &in_text[i]);
            }
        }
        if (true == is_letter (in_text[i])) {
            if ((0 == opened_cnt) && (0 == closed_cnt)) {
                prefix_str = str_append (prefix_str, in_text[i]);
            } else if (opened_cnt == closed_cnt) {
                curr = str_append (curr, in_text[i]);
                if (i == (len_of_text - 1)) {
                    is_siffix = true;
                }
            } else {
                curr = str_append (curr, in_text[i]);
            }
#ifdef DEBUG_DECODE_STR
            printf ("\n [d] curr <%s> ", curr);
#endif
        }
        if ('[' == in_text[i]) {
            opened_cnt++;
            is_inside = true;
            if (0 < cnt) {
                res = stack_push (stack_num_instance, cnt);
                if (false == res) {
                    printf ("\n stack_push error ");
                } else {
                    printf ("\n stack_push fine %d ", cnt);
                }
            }
            cnt = 0;
            res = stack_str_push (strs, curr);
            if (false == res) {
                printf ("\n [e] stack_str_push error <%s>", curr);
            } else {
                printf ("\n [!] stack_str_push fine <%s> ", curr);
            }
            free (curr);
            curr = strdup ("");
        }
        if (']' == in_text[i]) {
            closed_cnt++;
            is_inside = false;
            // printf("\nstack %s", curr);
            int nums = 0, j = 0;
            char *decoded_part_str = strdup ("");
            res = stack_pop (stack_num_instance, &nums);
            if (true == res) {
#ifdef DEBUG_DECODE_STR
                printf ("\n  %d<%s>=", nums, curr);
#endif
                for (j = 0; j < nums; j++) {
#ifdef DEBUG_DECODE_STR
                    printf ("%s", curr);
#endif
                    decoded_part_str = str_cat_dyn (decoded_part_str, curr);
                }
                printf ("\n  decoded part <%s>", decoded_part_str);
            } else {
                printf ("\n [e] stack_pop error nums %d", nums);
            }
            free (curr);
            curr = NULL;
            res = stack_str_pop (strs, &curr);
            if (false == res) {
                printf ("\n [e] stack_str_pop error ");
                out_str = str_cat_dyn (out_str, decoded_part_str);
            } else {
                printf ("\n [d] stack_str_pop fine cur=<%s> out_str=<%s>", curr, decoded_part_str);
                curr = str_cat_dyn (curr, decoded_part_str);
                out_str = str_cat_dyn (strdup (""), curr);
            }
        }
    } // for

    if (0 < strlen (prefix_str)) {
        printf ("\n [d] prefix_str=<%s>", prefix_str);
        out_str = str_cat_dyn (prefix_str, out_str);
    }

    if (true == is_siffix) {
        if (0 < strlen (curr)) {
            printf ("\n [d] remain cur=<%s>", curr);
            out_str = str_cat_dyn (out_str, curr);
        }
    }
    return out_str;
}
