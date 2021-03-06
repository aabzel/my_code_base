#include "generate_parser_test.h"

#include <string.h>

#include "generate_parser.h"
#include "uTests.h"

static bool test_parse_bit (void) {
    char cur_file_str[500];
    bool res = false;
    uint8_t bit_num;
    strncpy (cur_file_str, "0 bit=15 1| RW/SC| Reset | Software reset", sizeof (cur_file_str));
    res = parse_bit_num (cur_file_str, strlen (cur_file_str), &bit_num);
    if (false == res) {
        printf ("\n  parse_bit_num Error \n");
        return false;
    }
    EXPECT_EQ (15, bit_num);
    return true;
}

static bool test_parse_bit_val (void) {
    char cur_file_str[500];
    bool res = false;
    uint16_t bit_val;
    strncpy (cur_file_str, "0.bit=11 val=0 RW |Power-Down | Normal operation", sizeof (cur_file_str));
    res = parse_bit_val (cur_file_str, strlen (cur_file_str), &bit_val);
    if (false == res) {
        printf ("\n  parse_bit_val Error \n");
        return false;
    }
    EXPECT_EQ (0, bit_val);

    strncpy (cur_file_str, "0.bit=13 val=1 RW |Speed Select | 100 Mbps", sizeof (cur_file_str));
    res = parse_bit_val (cur_file_str, strlen (cur_file_str), &bit_val);
    if (false == res) {
        printf ("\n  parse_bit_val Error \n");
        return false;
    }
    EXPECT_EQ (1, bit_val);

    return true;
}

static bool test_parse_reg_addr (void) {
    printf ("\n%s()\n", __FUNCTION__);
    bool res = false;
    uint16_t reg_addr;
    char cur_file_str[500];
    strncpy (cur_file_str, "< REG=\"Basic Control\" Addr=0 t", sizeof (cur_file_str));
    res = parse_uint8_after_prefix (cur_file_str, strlen (cur_file_str), &reg_addr, "Addr=");
    if (false == res) {
        printf ("\nparse_reg_name Error \n");
        return false;
    }
    EXPECT_EQ (0, reg_addr);

    strncpy (cur_file_str, "REG=\"Basic Status\" Addr=1 ", sizeof (cur_file_str));
    res = parse_uint8_after_prefix (cur_file_str, strlen (cur_file_str), &reg_addr, "Addr=");
    if (false == res) {
        printf ("\nparse_reg_name Error \n");
        return false;
    }
    EXPECT_EQ (1, reg_addr);

    strncpy (cur_file_str, "< REG=\"PHY Control 1\"  Addr=0x1E ", sizeof (cur_file_str));
    res = parse_uint8_after_prefix (cur_file_str, strlen (cur_file_str), &reg_addr, "Addr=");
    if (false == res) {
        printf ("\nparse_reg_name Error \n");
        return false;
    }
    EXPECT_EQ (0x1E, reg_addr);

    return true;
}

static bool test_parse_bit_range (void) {
    printf ("\n%s()\n", __FUNCTION__);
    uint8_t bit_old;
    uint8_t bit_little;
    char cur_file_str[500];
    strncpy (cur_file_str, "range=11:10 val=2 type=\"RO\"  text=\"Asymmetric pause\"", sizeof (cur_file_str));
    EXPECT_TRUE (parse_bit_range (cur_file_str, strlen (cur_file_str), &bit_old, &bit_little, "range="));
    EXPECT_EQ (11, bit_old);
    EXPECT_EQ (10, bit_little);
    return true;
}

static bool test_parse_reg_name (void) {
    printf ("\n%s()\n", __FUNCTION__);
    bool res = false;
    char cur_file_str[500];
    strncpy (cur_file_str, "< REG=\"Basic Control\" Addr=0", sizeof (cur_file_str));
    char reg_nane[500];
    res = parse_text_after_prefix (cur_file_str, strlen (cur_file_str), reg_nane, "REG=\"");
    if (false == res) {
        printf ("\nparse_reg_name Error \n");
        return false;
    }

    EXPECT_EQ_STR ("Basic Control", reg_nane);

    return true;
}

bool test_generate_reg_parser (void) {
    printf ("\n%s()\n", __FUNCTION__);
    bool res = false;
    res = test_parse_reg_name ();
    if (false == res) {
        printf ("\nError test_parse_reg_name");
        return false;
    }

    res = test_parse_reg_addr ();
    if (false == res) {
        printf ("\nError test_parse_reg_addr\n");
        return false;
    }

    res = test_parse_bit ();
    if (false == res) {
        printf ("\nError test_parse_bit");
        return false;
    }

    res = test_parse_bit_val ();
    if (false == res) {
        printf ("\n Error test_parse_bit_val\n");
        return false;
    }

    res = test_parse_bit_range ();
    if (false == res) {
        printf ("\n Error test_parse_bit_range\n");
        return false;
    }

    return true;
}
