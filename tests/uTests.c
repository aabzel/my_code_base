#include "uTests.h"

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HAS_SD_CARD
#include "test_parse_sd_card_regs.h"
#endif

#ifdef CD_CARD_CRC7
#include "test_sd_card_crc.h"
#endif

#include "utils.h"

#ifdef SYSTEM_EXPLORE
#include "system_explore.h"
#endif

#ifdef INTERVIEW_TASKS
#include "dsol_task.h"
#endif

#ifdef SORT_LIST
#include "test_sort_list.h"
#endif

#ifdef HAS_LCD_TEST
#include "lcd_api.h"
#endif

#ifdef EXAFORE
#include "exafore_task.h"
#endif

#ifdef BIT_UTILS
#include "test_bin_utils.h"
#endif

#ifdef BYTE_UTILS
#include "test_byte_utils.h"
#endif

#ifdef HAS_AURIGA_TASK
#include "test_auriga_task.h"
#endif

#ifdef DHAS_ALGORITHMS
#include "algorithms.h"
#include "algorithms_test.h"
#include "test_algorithms.h"
#endif

#ifdef HAS_VECTOR_CALC
#include "test_vector_calc.h"
#endif

#if 0
#include "decode_string.h"
#include "test_decode_string.h"
#endif

#ifdef MICROAVIA_TASK
#include "microavia_task.h"
#endif

#include "bit_utils.h"
#include "check_address.h"
//#include "compiler_test.h"
#include "test_mk_2_dot.h"
#include "test_stack_num.h"

#ifdef HAS_HOTEL
#include "hotel.h"
#include "test_hotel.h"
#endif

#ifdef HAS_EVAL_CACHE
#include "test_evaluate_cache.h"
#endif

//#include "amount_of_uio_states.h"
#ifdef HAS_ARRAY
#include "arrays.h"
#include "test_arrays.h"
#endif

#if 0
#include "bin_utils_test.h"
#include "compare_version_test.h"
#include "tree_lions.h"
#endif

#ifdef HAS_TIC12400
#include "parse_tja1101_regs.h"
#endif

#ifdef HAS_GENERATE_REG_PARSER_TEST
#include "generate_parser_test.h"
#endif

#if HAS_BIN_HEAP
#include "bin_heap.h"
#include "bin_heap_array.h"
#endif

#ifdef TEST_SHA256
#include "sha256_test.h"
#endif /*TEST_SHA256*/

#ifdef TEST_AES
#include "aes_test.h"
#endif /*TEST_AES*/

#ifdef TEST_ARRAY
#include "arrays_test.h"
#endif /*TEST_ARRAY*/

//#include "bin_search_tree.h"
//#include "bin_tree.h"
//#include "bin_tree_draw.h"
//#include "combinations.h"
#ifdef HAS_CONVERT
#include "convert.h"
#include "test_convert.h"
#endif

#ifdef HAS_LEET_CODE
#include "test_decode_way.h"
#include "test_hash_set.h"
#endif

#include "float_utils.h"

#ifdef TEST_LINKED_LIST
#include "linked_list.h"
#include "linked_list_array.h"
//#include "sort_linked_list.h"
#include "test_linked_list.h"
#endif

//#include "min_path.h"
//#include "min_path_diag_scale.h"
#ifdef HAS_PARSE_MK
#include "mk_to_dot.h"
#endif
//#include "parse_keepass.h"
#ifdef HAS_PERMUTATION
#include "permutations.h"
#ifdef HAS_PERMUTATIONS_TEST
#include "permutations_test.h"
#endif /*HAS_PERMUTATIONS_TEST*/
#endif /*HAS_PERMUTATION*/

//#include "russian_doll_envelopes_test.h"
//#include "scan_serial_port.h"
//#include "slidingWindowMax.h"
//#include "slidingWindowMid.h"
#include "str_ops.h"

#ifdef TEST_STR_OPS
#include "test_str_ops.h"
#endif
//#include "test_avl_tree.h"
#ifdef TEST_FIFO
#include "test_fifo_char.h"
#endif
//#include "test_lifo_char.h"
#include "utils.h"

#if 0
static bool test_parse_mac (void) {
    bool res = false;
    char inStr[1000];
    uint8_t curMac[6];
    uint8_t expMac[6] = {0xd4, 0x3b, 0x04, 0xa0, 0xa2, 0x21};
    strncpy (inStr, "Device: CAN_FLASHER Serial 0x202b17d3015a from IP 192.168.0.11 MAC d4:3b:04:a0:a2:21",
             sizeof (inStr));
    EXPECT_TRUE( parse_mac (inStr, sizeof (inStr), curMac);
    if (false == res) {
        printf ("\nunable to parse mac");
        return false;
    }
    EXPECT_TRUE( is_mem_equal (curMac, expMac, 6);
    if (false == cmpRes) {
        printf ("\nexp mac d4:3b:04:a0:a2:21");
        printf ("\ncur mac ");
        print_mac_addr (curMac);
        return false;
    }

    return true;
}
#endif

#if 0
static bool test_parse_serial (void) {
    char inStr[1000];
    char outStr[1000];
    char expStr[1000];
    bool res = false;
    strncpy (expStr, "202B17D3015A", sizeof (outStr));
    strncpy (inStr, "Device: IOV4_A Serial 0x907a08b from IP 192.168.0.11 MAC d4:3b:04:a0:a2:214:a0:a2:21",
             sizeof (inStr));
    uint64_t serial64BitNumber = 0;
    EXPECT_TRUE(parse_serial (inStr, sizeof (inStr), &serial64BitNumber);
    if (true == res) {
        if (0x907a08b != serial64BitNumber) {
            printf ("\n Serial 0x[%08llx] exp 0x907a08b", (long long unsigned int)serial64BitNumber);
            return false;
        }
    } else {
        printf ("\n Unable to extract Serial from string [%s]", inStr);
        return false;
    }

    return true;
}
#endif

#if DEPLOY_TEST_COM_PARSER
static bool test_parse_vi_devname (void) {
    char inStr[1000];

    strncpy (inStr,
             "vi\n\rCanFlasher on CanFlash Version 0.17.1.1.34 GCC Release 11/7/2020 19:34:29 FlashId:E58F0042 "
             "Serial:202B17D3015A by Arrival\n\r1.013:I [SYS] Ok!\n\r-->",
             sizeof (inStr));
    char *dev_name;
    dev_name = parse_product_name (inStr, sizeof (inStr));
    int cmp_res = strcmp (dev_name, "CanFlasher");
    if (0 != cmp_res) {
        printf ("\n unable to parse CanFlasher from [%s] \n\r Extracted [%s]", inStr, dev_name);
        return false;
    }
    return true;
}
#endif

#if DEPLOY_TEST_COM_PARSER
static bool test_parse_vi (void) {
    char inStr[1000];
    char outStr[1000];
    char expStr[1000];
    bool res = false;
    strncpy (expStr, "202B17D3015A", sizeof (outStr));
    strncpy (inStr,
             "vi\n\rCanFlasher on CanFlash Version 0.17.1.1.34 GCC Release 11/7/2020 19:34:29 FlashId:E58F0042 "
             "Serial:202B17D3015A by Arrival\n\r1.013:I [SYS] Ok!\n\r-->",
             sizeof (inStr));
    uint64_t serial64BitNumber = 0U;
    EXPECT_TRUE(parse_serial (inStr, sizeof (inStr), &serial64BitNumber);
    if (true == res) {
        if (0x0000202B17D3015A != serial64BitNumber) {
            printf ("\n Serial 0x[%08llx] exp 0x0000202B17D3015A", (long long unsigned int)serial64BitNumber);
            return false;
        }
    } else {
        printf ("\n Unable to extract Serial from string [%s]", inStr);
        return false;
    }

    EXPECT_TRUE( test_parse_vi_devname ();
    if (false == res) {
        printf ("\n Unable to extract dev name form vi");
        return false;
    }

    return true;
}
#endif

#ifdef TEST_PARSE_REG
static bool test_parse_phy_addr (void) {
    printf ("\n%s()", __FUNCTION__);
    char inStr[100];
    uint8_t reg_addr = 0;

    bool res = false;

    strncpy (inStr, "reg addr: 02 reg val: 0x0180 Ob_0000_0001_1000_0000", sizeof (inStr));

    EXPECT_TRUE( parse_8bit_reg_addr (inStr, strlen (inStr), &reg_addr);

        if (2 != reg_addr) {
        printf ("\n phy addr exp 2 real [%u]", reg_addr);
        return false;
        }


    strncpy (inStr, "reg addr: 09 reg val: 0x0000 Ob_0000_0000_0000_0000", sizeof (inStr));

    EXPECT_TRUE(parse_8bit_reg_addr (inStr, sizeof (inStr), &reg_addr);

        if (9 != reg_addr) {
        printf ("\n phy addr exp 9 real %u", reg_addr);
        return false;
        }

    return true;
}
#endif

#if 0
static bool test_parse_phy_reg_vals (void) {
    printf ("\n%s()", __FUNCTION__);
    bool res;
    char inStr[500];
    uint16_t reg16_val;
    strncpy (inStr, "reg addr: 02 reg val: 0x0180 Ob_0000_0001_1000_0000", sizeof (inStr));

    EXPECT_TRUE(try_canch_hex_uint16 (inStr, strlen (inStr), &reg16_val);

        if ((0x0180 != reg16_val)) {
            printf ("\n reg16_val %x exp  0x0180", reg16_val);
            return false;
        }


    strncpy (inStr, "reg addr: 19 reg val: 0x3241 Ob_0011_0010_0100_0001", sizeof (inStr));
    EXPECT_TRUE( try_canch_hex_uint16 (inStr, strlen (inStr), &reg16_val);
    if ((0x3241 != reg16_val)) {
        printf ("\n reg16_val %x exp 0x3241 ", reg16_val);
        return false;
    }

    strncpy (inStr, "reg addr: 27 reg val: 0x2020 Ob_0010_0000_0010_0000", sizeof (inStr));
    EXPECT_TRUE( try_canch_hex_uint16 (inStr, strlen (inStr), &reg16_val);
    if (0x2020 != reg16_val) {
        printf ("\n reg16_val %x exp 0x2020 ", reg16_val);
        return false;
    }
    return true;
}
#endif

#if 0
static char *val_2_str (int i) {
    printf ("\n%s() %d", __FUNCTION__, i);
    static char buff[10];
    snprintf (buff, sizeof (buff), " %d ", i);
    return buff;
}
#endif

bool unit_test (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    bool res = false;
    (void)res;
#ifdef BYTE_UTILS
    EXPECT_TRUE(test_byte_utils ());
#endif

#ifdef CD_CARD_CRC7
    EXPECT_TRUE(test_crc());
#endif

#ifdef SORT_LIST
    EXPECT_TRUE (test_sort_list ());
#endif

#ifdef HAS_SD_CARD
    EXPECT_TRUE (test_parse_reg_sd_card ());
#endif

#ifdef TEST_HEAP_MEM
    EXPECT_TRUE (test_free_zero ());
    // EXPECT_TRUE(test_malloc_zero()); fails
    EXPECT_TRUE (test_malloc ());
    test_heap ();
    test_heap_set ();
#endif

#ifdef TEST_DSOL
    EXPECT_TRUE (test_dsol ());
#endif

#ifdef WIN_UTILS
#ifdef HAS_LCD_TEST
    char tx_text[] = "\n\r[d]Test TCP server";
    uint32_t tcp_server_ip;
    EXPECT_TRUE (try_strl2ipv4 ("127.0.0.1", strlen ("127.0.0.1"), &tcp_server_ip);
                 EXPECT_TRUE (sent_to_tcp_server (tx_text, strlen (tx_text), LCD_PORT, tcp_server_ip)));
#endif
#endif

#ifdef EXAFORE
    EXPECT_TRUE (test_struct ());
#endif

#ifdef MICROAVIA_TASK
    EXPECT_TRUE (test_microavia ());
#endif

#ifdef HAS_TREE_LIONS
    EXPECT_TRUE (test_lion_man_task ());
    EXPECT_TRUE (run_tree_lions ());
#endif

#ifdef HAS_TEST_ALGORITHM
    EXPECT_TRUE( test_algorithms ();

#endif

#ifdef HAS_VECTOR_CALC
    EXPECT_TRUE( test_vector_calc ();
#endif

#ifdef HAS_HOTEL
    EXPECT_TRUE(test_guests ();
#endif

#ifdef TEST_LINKED_LIST
    EXPECT_TRUE( test_linked_list_ints ();
#endif

#ifdef TEST_HASH_SET
    EXPECT_TRUE( test_hash_set ();
#endif

#if 0
    EXPECT_TRUE(test_text_addr ();
#endif

#ifdef TEST_STACK_NUM
    EXPECT_TRUE(test_stack ();
#endif

#ifdef TEST_ENCODE_STRING
    EXPECT_TRUE( test_encode_string ();
#endif

#if 0
    EXPECT_TRUE( test_decode_ways ();
#endif
    //    res = test_is_mapped ( );
    //    if (false == res) {
    //        printf ("test_is_mapped error");
    //        return IS_MAP_ERROR;
    //    }

#if 0
    EXPECT_TRUE( test_valid_ip_address ();
#endif

#if 0
    uint32_t nn=10;
    while (1) {
      nn *=2 ;
      EXPECT_TRUE(work_with_stack (nn, 0x55);
      if (false == res) {
          printf ("work_with_stack error %d", nn);
          return STACK_ERROR;
      }else{
    	  printf ("\n stack alloc  %d", nn);
    	  //printf (".");
      }
    }
#endif

    // return 1;
#ifdef HAS_AURIGA_TASK
    printf ("\n%s %s", val_2_str (3), val_2_str (4));
    EXPECT_TRUE( test_auriga_task ());
#endif

#ifdef BIT_UTILS
    EXPECT_TRUE( test_bin_utils ());
#endif

#ifdef TEST_MATRIX_ACCESS
    EXPECT_TRUE( test_matrix_accsess ());
#endif

#if 0
    EXPECT_TRUE(  test_static ());
#endif

#ifdef HAS_CONVERT
    EXPECT_TRUE(test_convert ());
#endif

#ifdef HAS_GENERATE_REG_PARSER_TEST
    //#error test_build
    EXPECT_TRUE(test_generate_reg_parser ();
#endif

#ifdef TEST_ARRAY
    EXPECT_TRUE( test_array ();
#endif

#ifdef HAS_PERMUTATIONS_TEST
    EXPECT_TRUE(test_permutation ();
#endif

#ifdef HAS_COMBINATION_TEST
    EXPECT_TRUE(test_combinations ();
#endif

#ifdef HAS_ALGORITHM_TEST
    EXPECT_TRUE( test_algorithm ();
#endif

#ifdef BEAM_TRAIL
    test_print_matrix ();

    struct Results cube;
    int A[4] = {3, 2, 4, 3};
    int array_of_numbers[6] = {1, 2, 3, 4, 5, 6};
    permute_from_set (2, array_of_numbers, 6);
    return FINE;
#endif

    // cube = solution(A, 4, 2, 4);

#if 0
    int ret = solution4 (955); // 1101110111
    if (ret != 4) {
        return BIN_PERIOD_ERROR;
    }
#endif

#ifdef HAS_COMPARE_VERSION_TEST
    EXPECT_TRUE( compare_version_test ();
#endif

#ifdef HAS_BIN_UTILS_TEST
    EXPECT_TRUE( test_binary_gap ();
#endif

#if 0
    // uint8_t regAddr = 0x00;
    // uint16_t regVal = 0x0000;
    uint8_t shift;
    uint64_t reg64Val;
    res = try_strl2uint64 ("202B17D3015A", strlen ("202B17D3015A"), &reg64Val);
    if (0x202B17D3015A != reg64Val) {
        printf ("202B17D3015A");
        printf ("\n reg64Val %08llx exp 202B17D3015A", (long long unsigned int)reg64Val);
        return PARSE_HEX_ERROR;
    }
#endif

#if 0
    res = try_strl2uint64 ("0x202B17D3015A", strlen ("0x202B17D3015A"), &reg64Val);
    if (0x202B17D3015A != reg64Val) {
        printf ("0x202B17D3015A");
        printf ("\n reg64Val %08llx exp 202B17D3015A", (long long unsigned int)reg64Val);
        return PARSE_HEX_ERROR;
    }
#endif

#if 0
    EXPECT_TRUE( is_hex_str ("ab1234ba", 8, &shift);
#endif

#if 0
    EXPECT_TRUE(is_hex_str ("0x1234ba", 8, &shift);
#endif

#if 0
    EXPECT_TRUE( test_parse_serial ();
#endif

#if 0
    EXPECT_TRUE( test_parse_mac ();
#endif

#ifdef TEST_PARSE_REG
    EXPECT_TRUE( test_parse_phy_addr ();
    EXPECT_TRUE( test_parse_phy_reg_vals ();
#endif

#ifdef TEST_SHA256
    EXPECT_TRUE( test_sha256 ();
#endif

#ifdef TEST_AES
    EXPECT_TRUE( test_aes ();
#endif

#if 0
    EXPECT_TRUE( test_parse_vi ();
#endif

#ifdef TEST_FLOART
    printf ("a %f b %f a+b %f", a, b, c);
    sample16bit = float_to_uint16 (c);
    if (20000U != sample16bit) {
        return FLOAR_TO_SAMPLE_ERROR;
    }
#endif

#ifdef TEST_FLOATS
    print_biggest_mantissa ();
    sample16bit = float_to_uint16 (c);
    if (0U != sample16bit) {
        return FLOAR_TO_SAMPLE_ERROR;
    }
    float val1;
    float val2;
    float val3;
    float epsilon = 1e-6;
    val1 = 0.2;
    val2 = 0.2 + epsilon;
    val3 = val2 - val1;
    printf ("\n val3 %f \n", val3);
    printf ("\n val3 %e \n", val3);
    // samval1;ple16bit = float_to_uint16 (23234.2f);
    // if (23234U != sample16bit) {
    // return FLOAR_TO_SAMPLE_ERROR;
    //}

    // sample16bit = float_to_uint16 (-23234.2f);
    // if (0U != sample16bit) {
    // return FLOAR_TO_SAMPLE_ERROR;
    //}
#endif

#if 0
    init_file_name ();
    print_pad_nums ();
#endif

#ifdef TEST_MY_PRINTF
    EXPECT_TRUE( test_my_printf ();
#endif

#ifdef TEST_MAX_ENFELOP
    EXPECT_TRUE( maxEnvelopes_test ());
#endif

#if TEST_LIST_SORT
    EXPECT_TRUE( test_list_sort ());
#endif

#ifdef TEST_STR_OPS
    EXPECT_TRUE( test_str_ops ());
#endif

#ifdef TEST_FIFO
    EXPECT_TRUE( test_fifo_char ());
#endif

#ifdef HAS_TEST_PARSE_MK
    EXPECT_TRUE( test_mk_2_dot ());
#endif

#if DEPLOY_TEST_SINGLE_NUMBER
    EXPECT_TRUE( test_single_number ());
#endif

#if DEPLOY_TEST_BOOL_EXPRESS
    EXPECT_TRUE( test_lifo ());
    EXPECT_TRUE( test_Valid_Parentheses ());
    EXPECT_TRUE( test_calc_paratasis_nesting ());
    EXPECT_TRUE( test_parse_num_operands ());
    EXPECT_TRUE( test_operand_extract ());
    EXPECT_TRUE( test_parse_and ());
    EXPECT_TRUE( test_parse_not ());
    EXPECT_TRUE( test_parseBoolExpr ());
#endif

#if DEPLOY_TEST_NUM_STRING
    EXPECT_TRUE( test_num_to_bin_str ();
#endif
    // int ret = 0;
#if TEST_ATOI
    EXPECT_TRUE( test_myAtoi ();
#endif

#if 0
    EXPECT_TRUE( test_reverse ();
    EXPECT_TRUE( test_detect_change ();
#endif

#if DEPLOY_DIF_SUB_STR_ERROR
    EXPECT_TRUE(test_lengthOfLongestSubstring ();

#endif

#if DEPLOY_TEST_AVL_TREE
    EXPECT_TRUE( test_avl_tree ();

#endif

#if 0
    EXPECT_TRUE(test_heap_api ());
    EXPECT_TRUE( test_delim_amount ();
    EXPECT_TRUE( test_string_clean ();
#endif

#if DEBUG_MAIL
    EXPECT_TRUE( test_split ();

#endif

#if 0
    EXPECT_TRUE( test_sliding_window_max ();

    EXPECT_TRUE( test_is_bin_tree ();

#endif

#if TEST_HEAP_DELET_ONE
    EXPECT_TRUE( test_bin_heap_rand_add_and_del_one ();

#endif

#if TEST_HEAP_DELET
    EXPECT_TRUE( test_bin_heap_delete ();

#endif

#if TEST_HEAP_SAME
    EXPECT_TRUE( test_bin_heap_same_add ();

#endif

#if TEST_HEAP_CON
    EXPECT_TRUE( test_bin_heap_dec_add ();

#endif

#if BIN_HEAP_RAND_ADD
    EXPECT_TRUE(test_bin_heap_rand_add ();

#endif

#if 0
    EXPECT_TRUE( test_algo ();

    EXPECT_TRUE( test_k_smallest ();

    EXPECT_TRUE( test_medianSlidingWindow ();

#endif

#if 0
    EXPECT_TRUE(test_valid_float_number ();

#endif
#if TEST_KDBX
    EXPECT_TRUE( try_to_open_kdbx_file ();

#endif

#if TEST_STR_STR
    EXPECT_TRUE( test_stsstr ();

#endif

#if TEST_MIN_PATH
    EXPECT_TRUE( test_min_path ();

#endif

#if TEST_MIN_PATH_DIAG
    EXPECT_TRUE( test_min_path_diag ();

#endif

#if TEST_MIN_DIAG_SCALE_SUMM
    EXPECT_TRUE( test_min_diag_scale_summ ();

#endif

#if TEST_FIND_MIN_DIAG_SCALE_SUMM
    EXPECT_TRUE( test_find_min_diag_scale_summ ();

    EXPECT_TRUE( test_find_min_diag_scale_summ2 ();

#endif

#ifdef TEST_FLOAT
    EXPECT_TRUE( test_float ();
#endif

#ifdef TEST_UIO_COMB
    EXPECT_TRUE(save_the_amount_of_uio ();
#endif

#ifdef TEST_ARR_COMB
    test_heap ();
    EXPECT_TRUE( test_array_combinations ();

#endif

#if TEST_YA_TASK
    EXPECT_TRUE( test_ya_task ();

#endif

#ifdef TEST_UNIQ_DIAG_PATH_TASK
    EXPECT_TRUE( test_uniq_path_diag ();

#endif

#ifdef TEST_UNIQ_PATH_TASK
    EXPECT_TRUE( test_uniq_path ();

#endif

#ifdef DEPLOY_REMAINED_TESTS
    EXPECT_TRUE( test_parse_bin_tree_init_array ();

    EXPECT_TRUE( test_bin_tree_init_array ();


    EXPECT_TRUE( test_bin_tree ();

    EXPECT_TRUE( test_reverse_list ();


    EXPECT_TRUE( test_max_bit_val ();


    EXPECT_TRUE( test_grey_conversation ();


    int arr1[] = {1, 2};
    int arr2[] = {2, 1};
    EXPECT_TRUE( is_permutation (arr1, arr2, 2);


    int arra1[] = {1, 2, 5};
    int arra2[] = {2, 1, 6};
    EXPECT_TRUE(is_permutation (arra1, arra2, 3);


    outArray = generate_num_array (4);
    if (NULL != outArray) {
        if (0 != outArray[0]) {
            return 1;
        }
        if (1 != outArray[1]) {
            return 2;
        }
        if (2 != outArray[2]) {
            return 3;
        }
        if (3 != outArray[3]) {
            return 4;
        }
        free (outArray);
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 1);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 1, outStr);
#endif
    cmpRes = strcmp (outStr, "ACD");
    if (0 != cmpRes) {
        printf ("error intStr %s outStr %s", intStr, outStr);
        free (outStr);
        return 12;
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 0);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 0, outStr);
#endif
    cmpRes = strcmp (outStr, "BCD");
    free (outStr);
    if (0 != cmpRes) {
        printf ("error %s", outStr);
        return 22;
    }

    outStr = generate_num_string (4);
    if (NULL != outStr) {
        cmpRes = strcmp (outStr, "0123");
        free (outStr);
        if (0 != cmpRes) {
            return 33;
        }

    } else {
        return 35;
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 5);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 5, outStr);
    printf ("\n");
#endif
    free (outStr);

    EXPECT_TRUE( test_linked_list ();

#endif
    printf ("\n %s done", __FUNCTION__);
    return true;
}

#if 0
int test_heap_api (void) {
    bool res = false;

    res = test_bin_heap_par_ind_arr ();
    if (false == res) {
        return ARR_HEAP_ERROR;
    }

    res = test_min_bin_heap_delete_val ();
    if (false == res) {
        return ARR_MIN_BIN_HEAP_DELETE_VAL_ERROR;
    }

    res = test_bin_heap_delete_val ();
    if (false == res) {
        return ARR_HEAP_DELETE_VAL_ERROR;
    }

    res = test_max_bin_heap_insert ();
    if (false == res) {
        return ARR_MAX_HEAP_INSERT_ERROR;
    }

    res = test_min_bin_heap_insert ();
    if (false == res) {
        return ARR_MIN_HEAP_ERROR;
    }

    res = test_bin_heap_remove ();
    if (false == res) {
        return ARR_HEAP_GET_ERROR;
    }
    return 0;
}
#endif

#if 0
bool test_max_bit_val (void) {
    bool res = true;
    uint32_t maxVal = 0;
    maxVal = max_val (1);
    if (1 != maxVal) {
        res = false;
    }

    maxVal = max_val (2);
    if (3 != maxVal) {
        res = false;
    }
    maxVal = max_val (3);
    if (7 != maxVal) {
        res = false;
    }
    maxVal = max_val (4);
    if (15 != maxVal) {
        res = false;
    }

    res = false;
    int returnSize = 0;
    int *arr = grayCode (2, &returnSize);
    if (arr) {
        if (4 == returnSize) {
            if (0 == arr[0]) {
                if (3 == arr[2]) {
                    res = true;
                }
            }
        }
        free (arr);
    }

    return res;
}
#endif

#if 0
bool test_grey_conversation (void) {
    bool res = true;
    if (0 != bin_to_gray (0)) {
        res = false;
    }
    if (1 != bin_to_gray (1)) {
        res = false;
    }
    if (3 != bin_to_gray (2)) {
        res = false;
    }
    if (2 != bin_to_gray (3)) {
        res = false;
    }
    return res;
}
#endif

#if TEST_LIST
bool test_linked_list (void) {
    bool res = true;
    list_node_t *llHead = NULL;
    int numOfElen = 0;
    int array1[] = {1, 2, 3, 4};
    int array2[] = {1, 2, 3, 4, 5, 6};
    res = linked_list_add_array (&llHead, array1, 4);
    if (true == res) {
        numOfElen = list_num_of_elements (llHead);
        if (1 != numOfElen) {
            printf ("List Num Error %d\n", numOfElen);
            res = false;
        }
    } else {
        printf ("List Add1 Error\n");
    }

    res = linked_list_add_array (&llHead, array2, 6);
    if (true == res) {
        numOfElen = list_num_of_elements (llHead);
        if (2 != numOfElen) {
            printf ("List Num Error %d\n", numOfElen);
            res = false;
        }
    } else {
        printf ("List Add2 Error\n");
    }
#if DEBUG_LL
    print_list (llHead);
#endif

    res = linked_list_deinit (llHead);
    if (false == res) {
        printf ("List Deinit Error\n");
    }

    return res;
}

#endif
#if 0
bool test_parse_bin_tree_init_array (void) {
    bool res = true;
    int array [] =
        { 1, 2, 3, 4, 5, NOT_NUM, 6, 7, NOT_NUM, NOT_NUM, NOT_NUM, NOT_NUM, 8 };
    int sizeOfArray = sizeof(array) / sizeof(array [0]);
    parse_bin_tree (array, sizeOfArray);

    return res;
}
#endif

#if 0
bool test_bin_tree_init_array (void) {
    bool res = false;
    TreeNode_t * root = NULL;

    int parentNode = 0;

    parentNode = get_parent_index (1, 100);
    if (0 != parentNode) {
        return false;
    }
    parentNode = get_parent_index (3, 100);
    if (1 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (8, 100);
    if (3 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (12, 100);
    if (5 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (13, 100);
    if (6 != parentNode) {
        return false;
    }

    int array [8] =
        { 1, 2, 3, 4, 5, 6, 7, 8 };
    int sizeOfArray = sizeof(array) / sizeof(array [0]);
    assemble_tree_from_array (&root, array, sizeOfArray);
    res = print_tree_to_file (root, "array_tree.txt");
    return res;
}
#endif

#if 0
bool test_bin_tree (void) {
    TreeNode_t *root = NULL;
    bool res = false;
    int sumOfLeaves = 0;
    create_binary_search_tree (&root, 10);
    if (NULL != root) {
        int depth = max_depth (root);
        printf ("\ndepth:%d\n", depth);
        sumOfLeaves = deepestLeavesSum (root);
        printf ("\n SumOfLeaves:%d\n", sumOfLeaves);
        res = print_tree_to_file (root, "rand_tree.txt");
    }
    return res;
}
#endif

#if TEST_LIST
bool test_reverse_list (void) {
    bool res = false;
    ListNode *head = NULL;
    ListNode *revhead = NULL;

    list_add_node_front (&head, 1);
    list_add_node_front (&head, 2);
    list_add_node_front (&head, 3);
    list_add_node_front (&head, 4);

    show_list (head);

    revhead = reverseList (head);

    show_list (revhead);

    reverse_rec (&revhead);

    show_list (revhead);

    if (NULL != revhead) {
        res = true;
    }

    return res;
}
#endif

#if DEPLOY_TEST_UNIQ_PATH
bool test_uniq_path (void) {
    int numPath;

    numPath = uniquePaths (2, 2);
    if (2 != numPath) {
        return false;
    }
    printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
    numPath = uniquePaths (3, 2);
    if (3 != numPath) {
        return false;
    }

    numPath = uniquePaths (38, 10);
    if (1101716330 != numPath) {
        printf ("\n wrong numPath %d\n", numPath);
        return false;
    }

    numPath = uniquePaths (7, 3);
    if (28 != numPath) {
        printf ("\n wrong numPath %d\n", numPath);
        return false;
    }

    numPath = uniquePaths (51, 9);
    if (1916797311 != numPath) {
        printf ("\nnumPath 51 9  %d\n", numPath);
        return false;
    }

    return true;
}
#endif

#if 0
bool test_uniq_path_diag (void) {
    bool res = false;
    int numPath;
    numPath = uniquePathDiag (2, 2);
    if (3 == numPath) {
        printf ("\n exp %d real %d", 3, numPath);
        res = true;
    }
    numPath = uniquePathDiag (2, 3);
    if (5 != numPath) {
        printf ("\n exp %d real %d", 5, numPath);
        return false;
    }

    numPath = uniquePathDiag (3, 2);
    if (5 != numPath) {
        printf ("\n exp %d real %d", 5, numPath);
        return false;
    }
    numPath = uniquePathDiag (3, 3);
    if (13 != numPath) {
        printf ("\n 3x3 exp %d real %d", 13, numPath);
        return false;
    }
    numPath = uniquePathDiag (3, 4);
    if (25 != numPath) {
        printf ("\n 3x4 exp %d real %d", 25, numPath);
        return false;
    }
    numPath = uniquePathDiag (6, 6);

    numPath = uniquePathDiag (7, 7);
    // printf ("\n 6x6 numPath = %d", numPath);

    return res;
}
#endif

#if 0
bool test_ya_task (void) {
    bool res = false;
    int sizeOfArr = 0;
    int numOnes = 0;
    int arr[] = {0, 1, 1, 0, 1, 1, 0};
    sizeOfArr = sizeof (arr) / sizeof (arr[0]);

    numOnes = findMaxConsecutiveOnesFlip1 (arr, sizeOfArr);
    //printf ("\n findMaxConsecutiveOnesFlip1: %d\n", numOnes);

    numOnes = findMaxConOnesDel1 (arr, sizeOfArr);
    //printf ("\n findMaxConsecutiveOnesFlip1_: %d\n", numOnes);

    numOnes = findMaxConsecutiveOnes (arr, sizeOfArr);
    if (2 != numOnes) {
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 6);
    if (false == res) {
        printf ("\n unspot single zero 6");
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 0);
    if (false == res) {
        printf ("\n unspot single zero 0");
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 3);
    if (false == res) {
        printf ("\n unspot single zero 3");
        return false;
    }

    numOnes = count_max_amout_of_one_after_del (arr, sizeOfArr);
    if (4 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    numOnes = findMaxConOnesDel1 (arr, sizeOfArr);
    if (4 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    int arr2[] = {0, 1, 1, 1, 1, 1, 0};
    sizeOfArr = sizeof (arr2) / sizeof (arr2[0]);
    numOnes = count_max_amout_of_one_after_del (arr2, sizeOfArr);
    if (5 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    numOnes = findMaxConOnesDel1 (arr2, sizeOfArr);
    if (5 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    return res;
}
#endif

#if 1 == COMBINATION
bool test_array_combinations (void) {
    bool res = false;
    int arr[] = {1, 2, 3};
    int arrSize = sizeof (arr) / sizeof (arr[0]);
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **arrayOfArr = NULL;
    arrayOfArr = subsets (arr, arrSize, &returnSize, &returnColumnSizes);
    if (7 == returnSize) {
        res = true;
    }
    print_array_of_diff_arrays (arrayOfArr, returnSize, returnColumnSizes);

    return res;
}
#endif

#if TEST_STR_STR
bool test_stsstr (void) {
    char text[100];
    char pattern[100];
    char *nullPtr = NULL;
    const char *resPtr;

    strcpy (text, "uArT_BaYpass tExt to uart");
    strcpy (pattern, "");
    resPtr = str_case_str (text, pattern);
    if (NULL == resPtr) {
        printf ("\nDid not spot\n");
        return false;
    }

    strcpy (text, "uArT_BaYpass tExt to uart");
    strcpy (pattern, "bAy");
    resPtr = str_case_str (text, pattern);
    if (NULL == resPtr) {
        printf ("\nDid not spot\n");
        return false;
    }
    // printf ("\n[%s] [%s]\n", text, pattern);

    strcpy (pattern, "paTtern");
    resPtr = str_case_str (text, pattern);
    if (NULL != resPtr) {
        printf ("\nfalse spot\n");
        return false;
    }
    // printf ("\n[%s] [%s]\n", text, pattern);

    resPtr = str_case_str (text, nullPtr);
    if (NULL != resPtr) {
        printf ("\nfalse spot pattern NULL\n");
        return false;
    }
    // printf ("\n[%s] [%s]\n", text, pattern);

    resPtr = str_case_str (nullPtr, text);
    if (NULL != resPtr) {
        printf ("\nfalse spot text NULL\n");
        return false;
    }
    // printf ("\n[%s] [%s]\n", text, pattern);
    return true;
}
#endif

#if 0
bool test_float (void) {
    bool res = true;
    float val = 3.25f;
    print_bit_representation (val);
    print_bit_representation (0.15625f);

    return res;
}
#endif

#if 0
bool test_min_path (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathSum ((int *) grid, numOfLine, numOfcolomn);
    if (7 == minSum) {
        res = true;
    } else {
        return false;
    }

    // save_array_as_dot ("map1.dot", (int *) grid, 3, 3);

    // minPath ((int *) grid, sizeOfGrid, gridColSize);
    int grid2 [10] [10];
    numOfLine = 10;
    numOfcolomn = 10;
    init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    // init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    // minSum = minPathSum ((int *) grid2, 10, 10);
    // save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    minPath ((int *) grid2, numOfLine, numOfcolomn);

    return res;
}
#endif

#if 0
bool test_min_path_diag_atmospher (void) {
    bool res = false;

    int grid5 [5] [5] =
        {
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 } };
    res = minPathDiag ((int *) grid5, 5, 5);

    return res;
}
#endif

#if 0
bool test_min_path_diag (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathDiagSum ((int *) grid, numOfLine, numOfcolomn);
    if (5 == minSum) {
        res = true;
    } else {
        return false;
    }
#define TEST_DIM 3
    int grid1 [TEST_DIM] [TEST_DIM];
    res = init_one_map ((int *) grid1, TEST_DIM, TEST_DIM);
    minSum = minPathDiagSum ((int *) grid1, TEST_DIM, TEST_DIM);
    if (TEST_DIM == minSum) {
        res = true;
    } else {
        return false;
    }

#define TEST_DIM2 8
    int grid2 [TEST_DIM2] [TEST_DIM2];
    // init_rod_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    // init_rand_array((int *) grid2, TEST_DIM2, TEST_DIM2);
    // init_box_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    init_ramp_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    minPathDiag ((int *) grid2, TEST_DIM2, TEST_DIM2);
    // int grid2 [10] [10];
    // numOfLine = 10;
    // numOfcolomn = 10;
    // init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    // init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    // minSum = minPathSum ((int *) grid2, 10, 10);
    // save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    // minPath ((int *) grid2, numOfLine, numOfcolomn);
#if TEST_3_3
    int grid3[3][3] = {{1, 93, 9}, {1, 95, 9}, {4, 2, 9}};
    minPathDiag ((int *)grid3, 3, 3);
#endif

    res = test_min_path_diag_atmospher ();
    if (false == res) {
        return false;
    }
    return res;
}
#endif

#if 0
bool test_min_diag_scale_summ (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 1, 1 },
            { 1, 1, 1 },
            { 1, 1, 1 } };
    float totalSum = minPathDiagScaleSum ((int *) grid, 3, 3);
    if (is_floats_equal (totalSum, 2.828f)) {
        res = true;
    } else {
        printf ("\n totalSum %f \n", totalSum);
    }
    return res;
}
#endif

#if 0
bool test_find_min_diag_scale_summ2 (void) {
    bool res = false;
#define TEST_ARR_DIM2 7
    int grid [TEST_ARR_DIM2] [TEST_ARR_DIM2];
    init_ramp_map ((int *) grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    res = minPathDiagScale ((int *) grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    if (true == res) {
        res = true;
    }
    return res;
}
#endif

#if 0
bool test_find_min_diag_scale_summ (void) {
    bool res = false;
    int grid [5] [5] =
        {
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 } };
    res = minPathDiagScale ((int *) grid, 5, 5);
    if (true == res) {
        res = true;
    }
    return res;
}
#endif
#if 0
bool test_valid_float_number (void) {
    bool res;
    char string[100];

#if 1

    strcpy (string, " 4e3.");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "53K");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".1.");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "3. ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0..");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "3.");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "078332e437");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".2e81");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "1  ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".  ");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".1");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "1 ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0e");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }
#endif

    strcpy (string, "1 4");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, " 0.1 ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }
    strcpy (string, "2e10");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    return true;
}
#endif

#if 0
bool test_medianSlidingWindow (void) {
    bool res = false;

    int arr100 [] =
        {
            16807,
            282475249,
            622650073,
            984943658,
            144108930,
            470211272,
            101027544,
            457850878,
            458777923,
            7237709,
            823564440,
            115438165,
            784484492,
            74243042,
            114807987,
            137522503,
            441282327,
            16531729,
            823378840,
            143542612,
            896544303,
            474833169,
            264817709,
            998097157,
            817129560,
            131570933,
            197493099,
            404280278,
            893351816,
            505795335,
            954899097,
            636807826,
            563613512,
            101929267,
            580723810,
            704877633,
            358580979,
            624379149,
            128236579,
            784558821,
            530511967,
            110010672,
            551901393,
            617819336,
            399125485,
            156091745,
            356425228,
            899894091,
            585640194,
            937186357,
            646035001,
            25921153,
            510616708,
            590357944,
            771515668,
            357571490,
            44788124,
            927702196,
            952509530,
            130060903,
            942727722,
            83454666,
            108728549,
            685118024,
            118797801,
            60806853,
            571540977,
            194847408,
            35308228,
            158374933,
            75260298,
            824938981,
            595028635,
            962408013,
            137623865,
            997389814,
            20739063,
            107554536,
            635339425,
            654001669,
            777724115,
            269220094,
            34075629,
            478446501,
            864546517,
            351934195,
            581030105,
            557810404,
            146319451,
            908194298,
            500782188,
            657821123,
            753799505,
            102246882,
            269406752,
            816731566,
            884936716,
            807130337,
            578354438,
            892053144,
            153851501,
            4844897,
            616783871,
            382955828,
            330111137,
            227619358,
            723153177,
            70982397,
            147722294,
            70477904,
            51621609,
            606946231,
            190959745,
            912844175,
            341853635,
            808266298,
            343098142,
            456880399,
            534827968,
            280090412,
            195400260,
            589673557,
            6441594,
            889688008,
            57716395,
            524325968,
            14119113,
            515204530,
            388471006,
            681910962,
            904797942,
            400285365,
            322842082,
            463179852,
            828530767,
            832633821,
            73185695,
            316824712,
            260973671,
            815859901,
            267248590,
            51724831,
            194314738,
            318153057,
            111631616,
            877819790,
            304555640,
            213110679,
            541437335,
            49077006,
            996497972,
            63936098,
            270649095,
            428975319,
            685583454,
            351345223,
            272112289,
            398556760,
            334948905,
            724586126,
            532236123,
            23129506,
            836045813,
            436476770,
            60935238,
            936329094,
            915896220,
            304987844,
            34712366,
            881140534,
            281725226,
            901915394,
            197941363,
            348318738,
            152607844,
            784559590,
            543436550,
            290145159,
            681808623,
            977764947,
            750597385,
            971307217,
            737195272,
            755539,
            399399247,
            462242385,
            459413496,
            951894885,
            537140623,
            848682420,
            12028144,
            86531968,
            289335735,
            755699915,
            623161625,
            992663534,
            43046042,
            358796011,
            943454679,
            771024152,
            479575244,
            507977295,
            119878818,
            49590396,
            828087692,
            621301815,
            154112991,
            104740033,
            222122669,
            889119397,
            238489553,
            882410547,
            944975825,
            567121210,
            866729662,
            536830211,
            719533808,
            517273377,
            592822761,
            41000625,
            902737335,
            127401868,
            994977995,
            140002776,
            532062767,
            49997439,
            433829874,
            464689331,
            428540556,
            968456301,
            859468872,
            911300560,
            168120094,
            298918984,
            967113755,
            124639789,
            462851407,
            957828015,
            678030193,
            105222769,
            893015680,
            944303455,
            4016855,
            732267506,
            784170963,
            454233502,
            145586676,
            329863108,
            353963249,
            323602331,
            1277844,
            1887638,
            660760808,
            561939997,
            685428651,
            897054849,
            465645203,
            461495731,
            440796531,
            796198014,
            522395419,
            779636775,
            203042009,
            175530180,
            640687929,
            351995223,
            459244054,
            458588260,
            174076737,
            834991545,
            44747317,
            34837525,
            837204200,
            578134256,
            486421564,
            609960597,
            668306648,
            683337704,
            907225550,
            605925150,
            416541976,
            24301412,
            411938554,
            111482797,
            524102504,
            760348381,
            293034748,
            855007065,
            290659378,
            379847699,
            778878209,
            338725129,
            121578553,
            552265483,
            501650447,
            218264607,
            471180773,
            363045322,
            494664305,
            706755176,
            495170053,
            616927224,
            437784630,
            360280366,
            121205400,
            284660444,
            487495370,
            684570285,
            502883016,
            252193898,
            637608155,
            129841133,
            189515557,
            262696576,
            707953178,
            509658266,
            307187357,
            347221711,
            42227878,
            847320614,
            746474819,
            195795737,
            586983133,
            678620591,
            290623720,
            135048762,
            667306633,
            262976197,
            112576031,
            925238588,
            555860589,
            795054873,
            843998877,
            959637304,
            21979358,
            832861200,
            599777254,
            168068960,
            794014915,
            545293947,
            442645480,
            452207730,
            103669955,
            564674546,
            547837107,
            28841238,
            989340000,
            18984926,
            690545035,
            988774857,
            110561113,
            420250114,
            862929593,
            300601360,
            118498354,
            322968418,
            439025357,
            738342585,
            163313729,
            122721015,
            780776563,
            32106102,
            588860917,
            380786643,
            172819419,
            971062967,
            572547747,
            83245269,
            529855395,
            812423303,
            490404473,
            978719103,
            754711748,
            47424385,
            345205658,
            518163459,
            520045406,
            937673930,
            250739824,
            614285132,
            129300973,
            493959603,
            600246897,
            618907920,
            367603950,
            9135231,
            64488480,
            171620203,
            350213900,
            939824520,
            681462533,
            603481258,
            937217003,
            13618676,
            255820950,
            113423934,
            143558780,
            168279879,
            836941832,
            463482574,
            828433549,
            346174542,
            415306249,
            523252771,
            156766310,
            601915879,
            752200983,
            798669970,
            473392040,
            666082723,
            20073650,
            222902971,
            118753229,
            666190318,
            473917746,
            118710299,
            151687230,
            344185621,
            554270776,
            637850124,
            108668244,
            26076958,
            981747696,
            116666771,
            958829064,
            322791560,
            614056598,
            790318751,
            493869940,
            240764503,
            462789551,
            711192801,
            123427205,
            119315080,
            164780418,
            3559274,
            838659649,
            63040413,
            810783320,
            51519025,
            237322012,
            586901783,
            458854788,
            151624117,
            76424008,
            263081550,
            90265324,
            404319195,
            754451257,
            318824511,
            304835690,
            270438666,
            187262410,
            48760593,
            766490553,
            799809565,
            92190960,
            556228742,
            540151403,
            911254352,
            746007307,
            928256141,
            525244910,
            633413200,
            492192799,
            970343127,
            566120171,
            429157787,
            250334414,
            450031625,
            244116641,
            174619517,
            13055348,
            377901842,
            287114315,
            927515974,
            177181445,
            476211373,
            805972220,
            795739911,
            265509239,
            90245054,
            63641305,
            172556929,
            61382253,
            652354189,
            5815166,
            537204356,
            772359304,
            651659860,
            73645898,
            609005592,
            442901720,
            463866116,
            625151580,
            78098867,
            495149352,
            476026939,
            208178698,
            401494901,
            324160811,
            797716616,
            482756891,
            501848671,
            402331728,
            356326671,
            597951661,
            343077045,
            102303120,
            421620240,
            268317158,
            38299453,
            39769627,
            333685350,
            962853711,
            38535563,
            274629594,
            550207533,
            66401727,
            115307827,
            948398795,
            114919531,
            657737442,
            140351516,
            950885006,
            98478515,
            4466924,
            706642601,
            957627097,
            596168661,
            440967103,
            368034324,
            799980108,
            18044936,
            72002281,
            547517015,
            151043710,
            265963216,
            130301905,
            343775973,
            111767781,
            225882720,
            807270791,
            791481169,
            910297865,
            702715827,
            532329536,
            238616728,
            872357125,
            628320384,
            796580167,
            502789949,
            835500476,
            8416046,
            300521576,
            777568666,
            158577467,
            977260520,
            862627384,
            516341991,
            178425210,
            905333258,
            14428211,
            622268744,
            225419518,
            464685718,
            722321934,
            132666825,
            436280767,
            854658689,
            523449818,
            528073014,
            566211825,
            822102918,
            173958028,
            987333029,
            500078034,
            708006727,
            55151240,
            6933754,
            571486540,
            427408396,
            913090935,
            401203083,
            69048048,
            287846865,
            709087011,
            31615252,
            367553064,
            301377876,
            137017237,
            746232675,
            628070245,
            94482710,
            773470415,
            791728192,
            560024710,
            707454747,
            722463037,
            356701299,
            97368447,
            88949715,
            329241693,
            647259579,
            132567129,
            115195164,
            995333979,
            473553501,
            439295525,
            191110289,
            502574958,
            517114033,
            62211800,
            562165089,
            528087670,
            812535217,
            430880846,
            499521038,
            936509543,
            8240338,
            849385936,
            98603321,
            954597719,
            73536496,
            124791247,
            67943788,
            617428359,
            270425987,
            767145035,
            707765235,
            498383912,
            152185684,
            924745989,
            866683784,
            120263734,
            76422667,
            826500519,
            862972615,
            669167045,
            318665976,
            142326661,
            373365825,
            5182819,
            1271631,
            483422903,
            751072698,
            162936798,
            230092639,
            341914004,
            29909503,
            763800679,
            333748765,
            88207391,
            737904107,
            236264924,
            207314365,
            114057121,
            48114454,
            205777106,
            840127450,
            110051703,
            448530832,
            583071032,
            499932141,
            48961654,
            412281977,
            440942217,
            742753900,
            142357289,
            302173465,
            978084747,
            476003622,
            816289879,
            258459317,
            359301516,
            56564048,
            484182762,
            637121029,
            532649039,
            166052708,
            266605903,
            987502657,
            996510761,
            924375752,
            86561466,
            785108621,
            974044557,
            292006996,
            554426955,
            115266930,
            54021494,
            346645555,
            96192221,
            233429312,
            586802293,
            141231427,
            500142232,
            432477444,
            209234791,
            178402198,
            311549152,
            434444856,
            63273570,
            227464303,
            264627439,
            947712914,
            324735799,
            78626766,
            570591835,
            67981921,
            110846043,
            121122752,
            688574086,
            75289719,
            526439150,
            230168410,
            822418623,
            185044669,
            282409605,
            312349943,
            8437311,
            657922431,
            101977992,
            45139816,
            396138699,
            496786971,
            875180639,
            45501370,
            30325836,
            525679891,
            147182857,
            594094833,
            300383328,
            601518177,
            510474410,
            139217683,
            14885176,
            505523489,
            887972091,
            283070434,
            681484711,
            976226904,
            463491026,
            763464891,
            132610790,
            494500522,
            308559364,
            931706890,
            539924884,
            399116813,
            10341441,
            9907127,
            591316179,
            844185784,
            598994537,
            45329870,
            88387561,
            264032581,
            894374165,
            508545802,
            937357732,
            231367332,
            645347854,
            214459759,
            947609847,
            739972377,
            637940462,
            626979010,
            726943819,
            710298150,
            119413377,
            230900941,
            42143836,
            434826720,
            245832299,
            92396112,
            856734759,
            56219956,
            788974390,
            728536152,
            348330048,
            342695014,
            123959044,
            320514918,
            5240150,
            817350101,
            897741295,
            910819821,
            885295731,
            398644501,
            662128245,
            129154961,
            748946057,
            927703510,
            974593928,
            935350805,
            653662173,
            366782137,
            229309669,
            67439096,
            725004503,
            121447421,
            850318675,
            595278518,
            867224300,
            260276489,
            835740262,
            743532054,
            128868263,
            18358643,
            902024889,
            245245250,
            608776735,
            891469415,
            726031364,
            407052494,
            595850963,
            543867758,
            887985652,
            156485092,
            524957316,
            887766714,
            771761420,
            192958060,
            345807450,
            895063368,
            207078741,
            448891847,
            208199196,
            746004787,
            885902501,
            652188234,
            364093128,
            925270571,
            886377448,
            44687875,
            242817253,
            810641871,
            821669329,
            476562293,
            261433719,
            164973471,
            307738820,
            25725764,
            521681079,
            511142630,
            839594410,
            95688080,
            350266113,
            462863342,
            951398138,
            778248382,
            845146044,
            705698828,
            920998393,
            157863575,
            70800980,
            39109000,
            967945596,
            73005947,
            590767370,
            3266087,
            644506543,
            313952733,
            236262852,
            172490261,
            88376824,
            876554400,
            511982380,
            68370778,
            789871857,
            425373423,
            278059498,
            421567014,
            728252845,
            236261662,
            945468509,
            257726610,
            929596849,
            790709218,
            821019290,
            288775055,
            922285743,
            319518555,
            439236385,
            137606534,
            499086275,
            864877321,
            823811151,
            759921226,
            703775251,
            803694459,
            20632783,
            30316714,
            372366437,
            388337879,
            384907698,
            715914100,
            810383137,
            768094285,
            836445878,
            717918284,
            489470342,
            311164915,
            626045960,
            432063067,
            834735140,
            675810707,
            309543566,
            293320728,
            12000562,
            977466363,
            820241969,
            109242890,
            739712623,
            567222278,
            624917313,
            790245761,
            267127010,
            362834840,
            104576978,
            983646000,
            809207394,
            334734507,
            623187656,
            430166551,
            24761786,
            706993431,
            204554544,
            619880739,
            892408776,
            688507584,
            105074252,
            544374108,
            808275514,
            497991454,
            998595019,
            801783028,
            107466671,
            158592370,
            434756663,
            215867947,
            785684024,
            907424543,
            802916854,
            629306008,
            389114981,
            767780552,
            5986288,
            265768163,
            792508359,
            994411019,
            348255379,
            28195356,
            871419461,
            108408487,
            955308353,
            279743899,
            606985788,
            855794244,
            281369880,
            224582466,
            428738283,
            789665274,
            248300236,
            414318909,
            108898567,
            40621834,
            978847939,
            418069684,
            78169651,
            123289549,
            598709266,
            545747467,
            268000110,
            797619589,
            792486327,
            417097773,
            568625581,
            380889295,
            750607936,
            148637874,
            426245435,
            694558231,
            866566972,
            949983028,
            971319798,
            594139070,
            43874587,
            251766297,
            893369089,
            796102646,
            67029090,
            714958111,
            129966612,
            150957463,
            756872112,
            996923781,
            423551951,
            522329230 };
    // int k=321;

    int arr5 [] =
        { 2147483647, 1, 2, 3, 4, 5, 6, 7, 2147483647 };
    //  [2147483647, 1, 2, 3, 4, 5, 6, 7, 2147483647]
    int arr4 [] =
        { 2147483647, 2147483647 };

    int arr3 [] =
        { 1, 2 };

    int arr2 [] =
        { 1, 2, 3, 4, 2, 3, 1, 4, 2 };

    int arr [] =
        { 1, 3, -1, -3, 5, 3, 6, 7 };

    int numsSize = 0;

    numsSize = sizeof(arr100) / sizeof(arr100 [0]);
    res = check_array (arr100, numsSize, 321);
    if (false == res) {
        return res;
    }

    numsSize = sizeof(arr5) / sizeof(arr5 [0]);
    res = check_array (arr5, numsSize, 2);
    if (false == res) {
        return res;
    }

    numsSize = sizeof(arr4) / sizeof(arr4 [0]);
    res = check_array (arr4, numsSize, 2);
    if (false == res) {
        return res;
    }

    numsSize = sizeof(arr3) / sizeof(arr3 [0]);
    res = check_array (arr3, numsSize, 1);
    if (false == res) {
        return res;
    }

    numsSize = sizeof(arr) / sizeof(arr [0]);
    res = check_array (arr, numsSize, 3);
    if (false == res) {
        return res;
    }

    numsSize = sizeof(arr2) / sizeof(arr2 [0]);
    res = check_array (arr2, numsSize, 3);
    if (false == res) {
        return res;
    }

    return res;
}
#endif

#if 0
bool check_array (int *arr, int numsSize, int k) {
    bool res;
    int returnSize = 0;
    double *prt;
    double *prtCorrect;

    prt = medianSlidingWindow (arr, numsSize, k, &returnSize);
    if (prt) {
        if (returnSize == (numsSize - k + 1)) {
        }
    }

    prtCorrect = medianSlidingWindowArr (arr, numsSize, k, &returnSize);
    if (prtCorrect) {
        if (returnSize == (numsSize - k + 1)) {
        }
    }
    res = is_double_arr_equal (prtCorrect, prt, returnSize);
    if (false == res) {
        printf ("\n Arrays are not equals \n");
        printf ("\n right ");
        print_array_double (prtCorrect, returnSize);
        printf ("\n calced ");
        print_array_double (prt, returnSize);
    }
    free (prt);
    free (prtCorrect);
    return res;
}
#endif

#if 0
bool test_bin_heap_same_add (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned) time (&t));
    for (int a = 5; 0 < a; a -= 1) {
        if (true == res) {
            int b = 10;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_same.dot");

    return res;
}
#endif

#if 0
bool test_bin_heap_rand_add (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned) time (&t));
    for (int a = 20; 0 < a; a -= 1) {
        if (true == res) {
            int b = rand () % 3;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand.dot");

    return res;
}
#endif

#if 0
bool test_bin_heap_rand_add_and_del_one (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned) time (&t));
    for (int a = 10; 0 < a; a -= 1) {
        if (true == res) {
            int b = rand () % 100;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand.dot");
    get_max (&binMaxHeapRoot);

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand_after_del.dot");

    return res;
}
#endif

#if 0
bool test_bin_heap_dec_add (void) {
    bool res = true;
    TreeNode_t *binMaxHeapRoot = NULL;
    for (int a = 10; 0 < a; a -= 2) {
        if (true == res) {
            res = max_heap_insert (&binMaxHeapRoot, a);
            if (false == res) {
                printf ("\n max_heap_insert %d err\n", a);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n tree is not heap!\n");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_dec.dot");

    return res;
}
#endif

#if 0
bool test_bin_heap_delete (void) {
    bool res = true;
    TreeNode_t *binMaxHeapRoot = NULL;
    for (int a = 10; 0 < a; a--) {
        if (true == res) {
            res = max_heap_insert (&binMaxHeapRoot, a);
            if (false == res) {
                printf ("\n max_heap_insert %d err\n", a);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n tree is not heap!\n");
            }
        }
    }

    int val = 0;
    for (int a = 10; 0 < a; a--) {
        if (true == res) {
            val = get_max (&binMaxHeapRoot);
            if (val != a) {
                res = false;
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_del.dot");

    return res;
}
#endif

#if 0
bool test_is_bin_tree (void) {
    bool res = false;

    TreeNode_t node1;
    TreeNode_t node2;

    node1.val = 1;
    node1.left = &node2;
    node1.right = NULL;

    node2.val = 1;
    node2.left = NULL;
    node2.right = NULL;

    res = is_bin_search_tree (&node1);
    if (true == res) {
        printf ("\n Error! 1\n");
        return false;
    }

    TreeNode_t node3;
    TreeNode_t node4;

    init_tree_node (&node3, 1, NULL, &node4);
    init_tree_node (&node4, 1, NULL, NULL);

    res = is_bin_search_tree (&node3);
    if (true == res) {
        printf ("\n Error! 2\n");
        return false;
    }

    TreeNode_t node11;
    TreeNode_t node22;
    TreeNode_t node33;
    TreeNode_t node44;
    TreeNode_t node55;

    init_tree_node (&node11, 10, &node22, &node33);
    init_tree_node (&node22, 5, NULL, NULL);
    init_tree_node (&node33, 15, &node44, &node55);
    init_tree_node (&node44, 6, NULL, NULL);
    init_tree_node (&node55, 20, NULL, NULL);

    print_tree_to_file (&node11, "not_BST.dot");
    res = is_bin_search_tree (&node11);
    if (true == res) {
        printf ("\n Error! 3\n");
        return false;
    }

    TreeNode_t nod0;
    TreeNode_t nod1;
    TreeNode_t nod2;
    TreeNode_t nod3;
    TreeNode_t nod4;
    TreeNode_t nod5;
    TreeNode_t nod6;
    TreeNode_t nod7;
    init_tree_node (&nod0, 3, &nod1, &nod2);
    init_tree_node (&nod1, 1, &nod3, &nod4);
    init_tree_node (&nod2, 5, &nod5, &nod6);
    init_tree_node (&nod3, 0, NULL, NULL);
    init_tree_node (&nod4, 2, NULL, &nod7);
    init_tree_node (&nod5, 4, NULL, NULL);
    init_tree_node (&nod6, 6, NULL, NULL);
    init_tree_node (&nod7, 3, NULL, NULL);
    print_tree_to_file (&nod0, "not_BST2.dot");

    res = is_bin_search_tree (&nod0);
    if (true == res) {
        printf ("\n Error! 4\n");
        return false;
    }

    TreeNode_t nd0;
    TreeNode_t nd1;
    init_tree_node (&nd0, -2147483648, NULL, &nd1);
    init_tree_node (&nd1, 2147483647, NULL, NULL);

    res = is_bin_search_tree (&nd0);
    if (false == res) {
        printf ("\n Error! 5\n");
        return false;
    }

    return true;
}
#endif

#if 0
bool test_delim_amount (void) {

    char text[] = "Hello world";
    char pattern[] = "lo";
    int amountOfItem = 0;
    amountOfItem = count_amount_of_item (text, pattern);
    if (2 != amountOfItem) {
        printf ("\n-1\n");
        return false;
    }

    amountOfItem = count_amount_of_item (text, "He");
    if (1 != amountOfItem) {
        printf ("\n0\n");
        return false;
    }

    amountOfItem = count_amount_of_item (text, "ld");
    if (1 != amountOfItem) {
        printf ("\n1\n");
        return false;
    }
    amountOfItem = count_amount_of_item ("a b c d e", " ");
    if (5 != amountOfItem) {
        printf ("\n2\n");
        return false;
    }

    amountOfItem = count_amount_of_item ("1231567190", "1");
    if (3 != amountOfItem) {
        printf ("\n3\n");
        return false;
    }

    amountOfItem = count_amount_of_item ("qpeptypiop", "p");
    if (4 != amountOfItem) {
        printf ("\n4\n");
        return false;
    }

    return true;
}
#endif

#if 0
bool test_split (void) {
    int amountOfval = 0;
    int resCmp = 0;

    char **ArrOfStrings;
    // printf ("\n sizeof(char *) %ld \n", sizeof(char *));
    amountOfval = split ("Hello world", "wo", &ArrOfStrings);
    if (2 != amountOfval) {
        printf ("\n%s: %d\n", __FUNCTION__, amountOfval);
        return false;
    }

    if (NULL == ArrOfStrings) {
        printf ("\nNull pointer to array of pointer: %p\n", ArrOfStrings);
        return false;
    } else {
        printf ("\n (ArrOfStrings [0]): <%s> \n", ArrOfStrings[0]);
        printf ("\n (ArrOfStrings [1]): <%s> \n", ArrOfStrings[1]);

        // printf ("\n *ArrOfStrings+1: %llu\n",(long long unsigned int) *ArrOfStrings + ((char *)1));
    }

    resCmp = strncmp ((char *)ArrOfStrings[0], "Hello ", strlen ("Hello "));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *)ArrOfStrings[0]);
        return false;
    }
    resCmp = strncmp ((char *)ArrOfStrings[1], "rld", strlen ("rld"));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *)(ArrOfStrings[1]));
        return false;
    }

    return true;
}
#endif

#if 0
bool test_bin_heap_par_ind_arr (void) {

    int parentIndex = 0;
    parentIndex = get_perent_index (0);
    if (-1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    parentIndex = get_perent_index (1);
    if (0 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    parentIndex = get_perent_index (2);
    if (0 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (3);
    if (1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (4);
    if (1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (6);
    if (2 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_right_child_index (3);
    if (8 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_left_child_index (2);
    if (5 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    return true;
}
#endif

#if 0
bool test_max_bin_heap_insert (void) {
    BinaryHeap_t binHeapObj;
    binHeapObj.length = 0;
    bool res = true;
    time_t t;
    srand ((unsigned) time (&t));

    res = bin_heap_init (&binHeapObj, 20);
    if (true == res) {
        for (int a = 0; a < 20; a++) {
            if (true == res) {
                int b = rand () % 50;
                res = heap_insert_val (&binHeapObj, true, b);
                if (false == res) {
                    printf ("\n [%s] %d heap_insert_val\n", __FUNCTION__, __COUNTER__);
                    return false;
                }
                res = is_bin_heap (&binHeapObj, true);
                if (false == res) {
                    printf ("\n [%s] %d is_bin_heap\n", __FUNCTION__, __COUNTER__);
                    return false;
                }
            }
        }

        res = is_bin_heap (&binHeapObj, true);
        if (false == res) {
            printf ("\n [%s] %d is_bin_heap\n", __FUNCTION__, __COUNTER__);
            return false;
        }
        res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array.dot");
    }

    return true;
}
#endif

#if 0
bool test_min_bin_heap_insert (void) {
    BinaryHeap_t binHeapObj;
    binHeapObj.length = 0;
    bool res = true;
    time_t t;
    srand ((unsigned) time (&t));

    res = bin_heap_init (&binHeapObj, 20);

    for (int a = 0; a < 20; a++) {
        if (true == res) {
            int b = rand () % 50;
            res = heap_insert_val (&binHeapObj, false, b);
            if (false == res) {
                printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
                return false;
            }
            res = is_bin_heap (&binHeapObj, false);
            if (false == res) {
                printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
                return false;
            }
        }
    }

    res = is_bin_heap (&binHeapObj, false);
    if (false == res) {
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = draw_bin_heap_in_file (&binHeapObj, "min_bin_heap_array.dot");

    return true;
}
#endif

#if 0
bool test_string_clean (void) {
    int cmpres;
    char *ptrString = NULL;
    ptrString = select_sub_string ("qwerty", "ui");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "qwerty");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    ptrString = select_sub_string ("qweRTy", "RT");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "qwe");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    ptrString = select_sub_string ("QWerty", "QW");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    return true;
}
#endif

#if DEPLOY_TEST_BIN_HEAP
bool test_min_bin_heap_delete_val (void) {
    bool res = false;
    BinaryHeap_t minBinHeapObj;
    res = bin_heap_init (&minBinHeapObj, 20);
    if (res) {
        res = fill_up_heap_continuous_vals (&minBinHeapObj, 20, false);
        if (false == res) {
            printf ("\nUnable to fill up array\n");
        }
    }
    draw_bin_heap_in_file (&minBinHeapObj, "min_bin_heap_array1_20.dot");

    int valIndex;
    res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0, &valIndex);
    if (true == res) {
        res = bin_heap_remove_val (&minBinHeapObj, false, 10);
        if (true == res) {
            draw_bin_heap_in_file (&minBinHeapObj, "min_bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0, &valIndex);
            if (true == res) {
                printf ("\nphantom  val in the heap\n");
                res = false;
            } else {
                res = true;
            }
        } else {
            printf ("\nUnable to remove val\n");
        }
    } else {
        printf ("\nNo expected val 10\n");
    }
    bin_heap_deinit (&minBinHeapObj);

    return res;
}
#endif

#if 0
bool test_bin_heap_delete_val (void) {
    bool res = false;
    BinaryHeap_t maxBinHeapObj;
    int valIndex;
    res = bin_heap_init (&maxBinHeapObj, 20);
    if (res) {
        res = fill_up_heap_continuous_vals (&maxBinHeapObj, 20, true);
        if (false == res) {
            printf ("\nUnable to fill up array\n");
        }
    }
    draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20.dot");

    res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0, &valIndex);
    if (true == res) {
        res = bin_heap_remove_val (&maxBinHeapObj, true, 10);
        if (true == res) {
            draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0, &valIndex);
            if (true == res) {
                printf ("\nPhantom  val in the heap\n");
                res = false;
            } else {
                res = true;
            }
        } else {
            printf ("\nUnable to remove val\n");
        }
    } else {
        printf ("\nNo extected val 10\n");
    }
    bin_heap_deinit (&maxBinHeapObj);

    return res;
}
#endif

#if 0
bool fill_up_heap_continuous_vals (BinaryHeap_t *binHeap, int maxVal, bool isMaxHeap) {
    bool res = true;
    if (binHeap) {
        for (int ind = 1; ind <= maxVal; ind++) {
            if (true == res) {
                res = heap_insert_val (binHeap, isMaxHeap, ind);
            }
        }
    }
    return res;
}
#endif

#if 0
bool test_bin_heap_remove (void) {
    BinaryHeap_t binHeapObj;

    bool res = true;
    time_t t;
    srand ((unsigned)time (&t));

    res = bin_heap_init (&binHeapObj, 20);
    if (res) {
        for (int ind = 0; ind < 20; ind++) {
            if (true == res) {
                int b = rand () % 50;
                res = heap_insert_val (&binHeapObj, true, b);
                if (false == res) {
                    printf ("\n [%s] %d insert_val ind=%d\n", __FUNCTION__, __COUNTER__, ind);
                    return false;
                }
                res = is_bin_heap (&binHeapObj, true);
                if (false == res) {
                    res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array_error.dot");
                    printf ("\n [%s] %d is_max_bin_heap ind=%d\n", __FUNCTION__, __COUNTER__, ind);
                    return false;
                }
            }
        }
        res = draw_bin_heap_in_file (&binHeapObj, "rand_bin_heap_array.dot");

        printf ("\n");
        for (int a = 0; a < 20; a++) {
            int val = heap_pop (&binHeapObj, true);
            printf (" %d ", val);
            res = is_bin_heap (&binHeapObj, true);
            if (false == res) {
                res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array_error.dot");
                printf ("\n [%s] %d is_max_bin_heap a=%d\n", __FUNCTION__, __COUNTER__, a);
                return false;
            }
        }
        printf ("\n");
        res = is_bin_heap (&binHeapObj, true);
        if (false == res) {
            printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
            return false;
        }
        res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array.dot");
    }
    return res;
}
#endif

#if 0
bool test_sliding_window_max (void) {
    bool res;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int numsSize = 0;
    int returnSize;
    numsSize = sizeof (arr) / sizeof (arr[0]);
    int *resArr;
    resArr = maxSlidingWindow (arr, numsSize, 3, &returnSize);
    if (resArr) {
        res = true;
        print_curr_array (resArr, returnSize);
        free (resArr);
    }
    return res;
}
#endif

#if 0
void assemble_tree_from_array (TreeNode_t **root, int *arr, int arraySize) {
    printf ("\n arraySize: %d\n", arraySize);
    for (int index = 0; index < arraySize; index++) {
        bst_insert (root, arr[index]);
    }
}
#endif

#if 0
// Creates a binary search tree
void create_binary_search_tree (TreeNode_t **root, int how_many_elements) {
    int number = 0, counter = 0;
    time_t t;
    srand ((unsigned)time (&t));
    for (counter = 1; counter <= how_many_elements; counter++) {
        number = rand () / 100;
        bst_insert (root, number);
    }
    printf ("\nThe binary search tree is: \n");
    print_inorder_traversal (*root);
}
#endif

#if 0
#define NN 5
int Amatrix[NN][NN];


void init_matrix_a (void) {
    int i, j;
    for (j = 0; j < NN; j++) {
        for (i = 0; i < NN; i++) {
            Amatrix[i][j] = i + j;
            printf ("\n %p i=%u j=%u", &Amatrix[i][j], i, j);
        }
    }
    printf ("\n");
}
#endif

#if 0
void print_matrix_ji (void) {
    int i = 0, j = 0;
    for (j = 0; j < NN; j++) {
        for (i = 0; i < NN; i++) {
            // printf("%u ",Amatrix[i][j]);
            Amatrix[i][j]++;
        }
    }
}
#endif

#if 0
// fast
void print_matrix_ij (void) {
    int i = 0, j = 0;
    for (i = 0; i < NN; i++) {
        for (j = 0; j < NN; j++) {
            // printf("%u ",Amatrix[i][j]);
            Amatrix[i][j]++;
        }
    }
}
#endif

#if 0
bool test_print_matrix (void) {
    init_matrix_a ();
    clock_t begin = clock ();
    print_matrix_ji ();
    clock_t end = clock ();
    double time_spent_ji = (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock ();
    print_matrix_ij ();
    end = clock ();
    double time_spent_ij = (double)(end - begin) / CLOCKS_PER_SEC;
    printf ("\nElapsed: ji %f seconds\n", time_spent_ji);
    printf ("\nElapsed: ij %f seconds\n", time_spent_ij);
    // Elapsed: ji 0.015000 seconds
    // Elapsed: ij 0.000000 seconds

    // Elapsed: ji 0.265000 seconds
    // Elapsed: ij 0.266000 seconds

    // Elapsed: ji 0.672000 seconds
    // Elapsed: ij 0.219000 seconds

    // Elapsed: ji 3.297000 seconds
    // Elapsed: ij 0.906000 seconds
    return true;
}
#endif
