#include "compare_version.h"

#include "algorithms.h"
#include "convert.h"

// 7.5.2.4  =4
int calc_rank (char *version) {
    int len = strlen (version);
    int rank = 0, i;
    if (0 < len) {
        rank = 1;
    }
    for (i = 0; i < len; i++) {
        if ('.' == version[i]) {
            rank++;
        }
    }
    return rank;
}

// how to extract substring from the string

//"7.5.2.4" 0 ->7
//"7.5.2.4" 1 ->5
//"7.5.2.4" 3 ->4
int extract_val (char *version, int k, int rank) {
    printf ("\nv [%s] p %u r %u\n ", version, k, rank);
    int32_t value = 0;
    int len = strlen (version);
    char *pos = version;
    int32_t str_len = 0;
    if (k < rank) {
        if (0 == k) {
            pos = version;
            if (1 < rank) {
                str_len = strchr (pos, '.') - version;
            } else {
                str_len = len;
            }
        } else if (k == rank - 1) {
            for (int i = 0; i < k; i++) {
                pos = strchr (pos + 1, '.');
            }
            str_len = &version[len] - (pos)-1;
            pos++;
        } else {
            for (int i = 0; i < k; i++) {
                pos = strchr (pos + 1, '.');
            }
            str_len = strchr (pos + 1, '.') - (pos)-1;
            pos++;
        }
    } else {
        // error
    }
    if (0 < str_len) {
        printf ("\n str [%s] len %u", pos, str_len);
        bool res = try_strl2int32_dec (pos, str_len, (int32_t *)&value);
        if (false == res) {
            printf ("\ndigit [%s] len [%u] pos [%u]\n ", pos, str_len, k);
            value = 0;
        }
    } else {
        printf ("\ndigit len error\n ");
    }
    return value;
}

int compareVersion (char *version1, char *version2) {
    int v_rank1 = calc_rank (version1);
    int v_rank2 = calc_rank (version2);
    int max_rank = max_int (v_rank1, v_rank2);
    int i;
    for (i = 0; i < max_rank; i++) {
        int d1 = extract_val (version1, i, v_rank1);
        int d2 = extract_val (version2, i, v_rank2);
        if (d2 < d1) {
            return 1;
        }
        if (d1 < d2) {
            return -1;
        }
    }
    return 0;
}
