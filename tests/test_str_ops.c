#include "test_str_ops.h"

#include "str_ops.h"
#include "uTests.h"

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_camel_case_2_snake_case (void) {
    printf ("\n%s", __FUNCTION__);

    EXPECT_FALSE (is_camel_case ("CAMEL_CASE"));
    EXPECT_TRUE (is_camel_case ("camelCase"));

    EXPECT_EQ_STR (toSnakeCase ("_"), "");
    EXPECT_EQ_STR (toSnakeCase ("camel__case"), "camel__case");
    EXPECT_EQ_STR (toSnakeCase ("CamelCase"), "camel_case");
    EXPECT_EQ_STR (toSnakeCase ("camelCase"), "camel_case");
    EXPECT_EQ_STR (toSnakeCase ("camel_case"), "camel_case");
    EXPECT_EQ_STR (toSnakeCase ("CAMEL_CASE"), "CAMEL_CASE");
    return true;
}

bool test_extract_sub_string (void) {
    char outStr[100] = "";
    int cmpRes;
    char inStr[100] = "";
    strncpy (inStr, "Device [TSTI_V2] Serial 0x%llx from IP %s MAC %s user <@aabdev>", sizeof (inStr));
    parse_substr_name (inStr, strlen (inStr), outStr, '[', ']');
    cmpRes = strcmp (outStr, "TSTI_V2");
    if (0 != cmpRes) {
        printf ("outStr %s exp TSTI_V2", outStr);
        return false;
    }

    strncpy (inStr, "Device [TSTI_V2] Serial 0x%llx from IP %s MAC %s user <@aabdev>", sizeof (inStr));
    parse_substr_name (inStr, strlen (inStr), outStr, '<', '>');
    cmpRes = strcmp (outStr, "@aabdev");
    if (0 != cmpRes) {
        printf ("outStr %s exp @aabdev", outStr);
        return false;
    }
    return true;
}

bool test_lengthOfLongestSubstring (void) {
    int val;
    bool res;
    res = is_diff_chars ("12345", 5);
    if (false == res) {
        return false;
    }

    res = is_diff_chars ("1214", 4);
    if (true == res) {
        return false;
    }

    val = lengthOfLongestSubstring ("pwwkew");
    if (3 != val) {
        // printf ("\npwwkew val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bpfbhmipx");
    if (7 != val) {
        // printf ("\nbpfbhmipx val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("aab");
    if (2 != val) {
        printf ("\naab val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("abcabcbb");
    if (3 != val) {
        printf ("\nabcabcbb val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bbbbb");
    if (1 != val) {
        printf ("\nbbbbb val:%d \n", val);
        return false;
    }

    return true;
}

bool test_detect_change (void) {
    char *old_sub_string = NULL;
    char *newSubString = NULL;
    int old_sub_stringLen = -1;
    int newSubStringLen = -1;
    int cmpRes = 0;
    // "aaabb"
    // "aaa11bb"
    detect_change ("aaabb", "aaa11bb", &old_sub_string, &old_sub_stringLen, &newSubString, &newSubStringLen);
    EXPECT_EQ (0, old_sub_stringLen);
    EXPECT_EQ (2, newSubStringLen);
    // EXPECT_EQ_STR("", old_sub_string);
    EXPECT_EQ_STR_LEN ("11", newSubString, 2);

    detect_change ("aaa11bb", "aaabb", &old_sub_string, &old_sub_stringLen, &newSubString, &newSubStringLen);
    EXPECT_EQ (2, old_sub_stringLen);
    EXPECT_EQ (0, newSubStringLen);
    EXPECT_EQ_STR_LEN ("11", old_sub_string, 2);
    // EXPECT_EQ_STR("", newSubString);

    detect_change ("aa111bb", "aa22bb", &old_sub_string, &old_sub_stringLen, &newSubString, &newSubStringLen);
    EXPECT_EQ (3, old_sub_stringLen);
    EXPECT_EQ (2, newSubStringLen);
    EXPECT_EQ_STR_LEN ("111", old_sub_string, 3);
    EXPECT_EQ_STR_LEN ("22", newSubString, 2);

    return true;
}

//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2
//"aabb"5,   "aa11bb"7  oldSub""0    newSub"11"2
//"abb"5,   "a11bb"7  oldSub""0    newSub"11"2
//"bb"5,   "11bb"7  oldSub""0    newSub"11"2
//"b"5,   "11b"7  oldSub""0    newSub"11"2
//""0,   "11"2  oldSub""0    newSub"11"2

// Examples:
//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2    < "11" inserted at index 3  old_sub_stringLen 0  newSubStringLen:
// 2 "aa111bb"7, "aa22bb"6   oldSub"111"3 newSub"22"2    < "11" inserted at index 3  old_sub_stringLen 3
// newSubStringLen:
// 2

bool test_reverse (void) {
    int cmpRes = 0;
    char tempStr[100];
    strcpy (tempStr, "12345");
    reverseString (tempStr, 5);
    cmpRes = strcmp (tempStr, "54321");
    if (0 != cmpRes) {
        printf ("\ntempStr [%s]\n", tempStr);
        return false;
    }

    return true;
}

bool test_myAtoi (void) {
    int val;
    char inStr[40];

    strcpy (inStr, "20000000000000000000");
    val = myAtoi (inStr);
    if (INT32_MAX != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "+1");
    val = myAtoi (inStr);
    if (1 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-91283472332");
    val = myAtoi (inStr);
    if (INT32_MIN != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "4193 with words");
    val = myAtoi (inStr);
    if (4193 != val) {
        printf ("\n%s %d [%s] outVal [%d]", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d val %d exp(%d)", __FUNCTION__, __COUNTER__, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "   -42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d [%s] val %d exp(%d)", __FUNCTION__, __COUNTER__, inStr, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
    }

    strcpy (inStr, "words and 987");
    val = myAtoi (inStr);
    if (0 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "21");
    val = myAtoi (inStr);
    if (21 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }
    return true;
}

bool test_num_to_bin_str (void) {
    int cmpRes = 0;
    cmpRes = strcmp ("1010_1010_1010_1010_1010_1010_1010_1010", uint32_to_bin_str (0xAAAAAAAA));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0101_0101_0101_0101_0101_0101_0101_0101", uint32_to_bin_str (0x55555555));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0000_0000_0000_0000_0000_0000_0000_0000", uint32_to_bin_str (0x00000000));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("1111_1111_1111_1111_1111_1111_1111_1111", uint32_to_bin_str (0xFFFFFFFF));
    if (0 != cmpRes) {
        return false;
    }
    return true;
}

#if 0

bool test_operand_extract(void) {
	int operLen = -1;
	EXPECT_EQ(1, get_index_in_string("(f,t)", 5, 0, &operLen));
	EXPECT_EQ(1, operLen);
	operLen = -1;
	EXPECT_EQ(3, get_index_in_string("(f,t)", 5, 1, &operLen));
	EXPECT_EQ(1, operLen);
	operLen = -1;
	EXPECT_EQ(1, get_index_in_string("(&(t,f,t),!(t))", 15, 0, &operLen));
	EXPECT_EQ(8, operLen);
	operLen = -1;
	EXPECT_EQ(10, get_index_in_string("(&(t,f,t),!(t))", 15, 1, &operLen));
	EXPECT_EQ(4, operLen);
	return true;
}

bool test_parse_and(void) {
	EXPECT_TRUE(parse_and("(t,t,t)", 7));
	EXPECT_FALSE(parse_and("(t,f,t)", 7));
	EXPECT_FALSE(parse_and("(t,&(f,t),t)", 12));
	return true;
}
// "(t,f,t)"          3
// "(t,f)"            2
// "(f,t)"            2
// "(&(t,f,t),!(t))"  2
// "(&(t,&(f,t),t),!(t))"  2

bool test_parse_not(void) {
	EXPECT_TRUE(parse_not("(f)", 3));
	EXPECT_TRUE(parse_not("!(t)", 4));
	EXPECT_FALSE(parse_not("!(f)", 4));
	EXPECT_FALSE(parse_not("(t)", 3));
	EXPECT_FALSE(parse_not("!(f)", 4));
	return true;
}

bool test_parse_num_operands(void) {
	EXPECT_EQ(1, parse_num_operands("(f)", 3));
	EXPECT_EQ(1, parse_num_operands("(t)", 3));
	EXPECT_EQ(4, parse_num_operands("(t,f,t,t)", 9));
	EXPECT_EQ(3, parse_num_operands("(t,f,t)", 7));
	EXPECT_EQ(2, parse_num_operands("(t,f)", 5));
	EXPECT_EQ(2, parse_num_operands("(&(t,f,t),!(t))", 15));
	EXPECT_EQ(2, parse_num_operands("(&(t,&(f,t),t),!(t))", 20));
	return true;
}

bool test_parseBoolExpr(void) {
	EXPECT_TRUE(parseBoolExpr("!(&(f))"));
	EXPECT_FALSE(parseBoolExpr("&(f)"));
	EXPECT_TRUE(parseBoolExpr("&(t)"));
	EXPECT_FALSE(parseBoolExpr("!(&(!(&(f)),&(t),|(f,f,t)))"));
	EXPECT_TRUE(parseBoolExpr("(t)"));
	EXPECT_FALSE(parseBoolExpr("(f)"));
	EXPECT_TRUE(parseBoolExpr("!(f)"));
	EXPECT_FALSE(parseBoolExpr("|(&(t,f,t),!(t))"));
	EXPECT_TRUE(parseBoolExpr("|(f,t)"));
	EXPECT_FALSE(parseBoolExpr("&(t,f)"));
	return true;
}

bool test_calc_paratasis_nesting(void) {
	int amountOfPairs = 0;
	EXPECT_EQ(1, calc_paratasis_nesting("(t,f,t)", &amountOfPairs));
	EXPECT_EQ(1, amountOfPairs);

	EXPECT_EQ(1, calc_paratasis_nesting("(t,f)", &amountOfPairs));
	EXPECT_EQ(1, amountOfPairs);

	EXPECT_EQ(2, calc_paratasis_nesting("(&(t,f,t),!(t))", &amountOfPairs));
	EXPECT_EQ(3, amountOfPairs);

	EXPECT_EQ(3, calc_paratasis_nesting("(&(t,&(f,t),t),!(t))", &amountOfPairs));
	EXPECT_EQ(4, amountOfPairs);

	return true;
}


bool test_Valid_Parentheses(void) {
	EXPECT_TRUE(is_valid_parentheses("()[]{}"));
	EXPECT_TRUE(is_valid_parentheses("(t,f,t)"));
	EXPECT_TRUE(is_valid_parentheses("(&(t,&(f,t),t),!(t))"));
	return true;
}
#endif

static bool test_replace_substr (void) {
    char text[100];

    strncpy (text, "ksz8081_reg_parser.c", sizeof (text));
    EXPECT_TRUE (replace_substring (text, ".c", ".h"));
    EXPECT_EQ_STR (text, "ksz8081_reg_parser.h");

    strncpy (text, "aabzelaabzelaabzelaabzel", sizeof (text));
    EXPECT_TRUE (replace_substring (text, "bz", "MOS"));
    EXPECT_EQ_STR (text, "aaMOSelaaMOSelaaMOSelaaMOSel");

    strncpy (text, "aabzelaabzel", sizeof (text));
    EXPECT_TRUE (replace_substring (text, "bz", "MOS"));
    EXPECT_EQ_STR (text, "aaMOSelaaMOSel");

    strncpy (text, "aabzel", sizeof (text));
    EXPECT_FALSE (replace_substring (text, "spb", "mos"));
    EXPECT_EQ_STR (text, "aabzel");

    strncpy (text, "qwertyuioo", sizeof (text));
    EXPECT_TRUE (replace_substring (text, "rty", "ZXC"));
    EXPECT_EQ_STR (text, "qweZXCuioo");

    strncpy (text, "qwertyuiop", sizeof (text));
    EXPECT_TRUE (replace_substring (text, "qwe", "ASD"));
    EXPECT_EQ_STR (text, "ASDrtyuiop");

    strncpy (text, "asdfghjkl", sizeof (text));
    EXPECT_TRUE (replace_substring (text, "jkl", "BNM"));
    EXPECT_EQ_STR (text, "asdfghBNM");

    return true;
}

static bool test_str_char_replace (void) {
    // printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    char fileName[100];
    int cmpRes = 0;
    strncpy (fileName, "spc58_pass.mk", sizeof (fileName));
    replace_char (fileName, '.', '_');
    cmpRes = strcmp (fileName, "spc58_pass_mk");
    if (0 == cmpRes) {
        return true;
    }
    return false;
}

static bool test_count_substring (void) {
    EXPECT_EQ (4, count_substring ("aabzelaabzelaabzelaabzel", "ab"));
    EXPECT_EQ (1, count_substring ("aabzel", "ab"));
    EXPECT_EQ (2, count_substring ("aabzelaabzel", "ab"));
    return true;
}

static bool test_try_canch_hex_uint8 (void) {
    uint8_t val8b = 0;
    char inStr[400];
    strncpy (inStr, "       INT_STAT[0x02]: 0x00000600 0b_0000_0000_0000_0000_0000_0110_0000_0000", sizeof (inStr));
    EXPECT_TRUE (try_canch_hex_uint8 (inStr, strlen (inStr), &val8b));
    EXPECT_EQ (0x02, val8b);

    strncpy (inStr, "      ANA_STAT1[0x0b]: 0x00000000 0b_0000_0000_0000_0000_0000_0000_0000_0000", sizeof (inStr));
    EXPECT_TRUE (try_canch_hex_uint8 (inStr, strlen (inStr), &val8b));
    EXPECT_EQ (0x0b, val8b);
    return true;
}

static bool test_try_canch_hex_uint32 (void) {
    uint32_t val32b = 0;
    char inStr[400];
    strncpy (inStr, "       INT_STAT[0x02]: 0x00000600 0b_0000_0000_0000_0000_0000_0110_0000_0000", sizeof (inStr));
    EXPECT_TRUE (try_canch_hex_uint32 (inStr, strlen (inStr), &val32b));
    EXPECT_EQ (0x00000600, val32b);

    strncpy (inStr, "         CONFIG[0x1a]: 0x00832800 0b_0000_0000_1000_0011_0010_1000_0000_0000", sizeof (inStr));
    EXPECT_TRUE (try_canch_hex_uint32 (inStr, strlen (inStr), &val32b));
    EXPECT_EQ (0x00832800, val32b);
    return true;
}

static bool test_2_upper_case (void) {
    EXPECT_EQ_STR ("TJA1145", upper_case_str ("tja1145"));
    EXPECT_EQ_STR ("KSZ8081", upper_case_str ("ksz8081"));
    return true;
}

static bool test_find_the_difference (void) {
    char diff_char;
    printf ("\n%s()", __FUNCTION__);
    diff_char = findTheDifference ("abcd", "abcde");
    EXPECT_EQ ('e', diff_char);

    diff_char = findTheDifference ("", "y");
    EXPECT_EQ ('y', diff_char);

    diff_char = findTheDifference ("ae", "aea");
    EXPECT_EQ ('a', diff_char);

    diff_char = findTheDifference ("a", "aa");
    EXPECT_EQ ('a', diff_char);
    return true;
}

bool test_str_ops (void) {
    EXPECT_TRUE (test_camel_case_2_snake_case ());
    EXPECT_TRUE (test_2_upper_case ());
    EXPECT_TRUE (test_count_substring ());
    EXPECT_TRUE (test_extract_sub_string ());
    EXPECT_EQ (true, test_try_canch_hex_uint8 ());
    EXPECT_EQ (true, test_try_canch_hex_uint32 ());
    EXPECT_EQ (true, test_replace_substr ());
    EXPECT_EQ (true, test_str_char_replace ());
    EXPECT_TRUE (test_detect_change ());
    EXPECT_TRUE (test_find_the_difference ());
    return true;
}