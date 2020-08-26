#include "mk_to_dot.h"

#include "fifo_char.h"
#include "str_ops.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <regex.h>

bool proc_mk_file (char *fileName, char *outFileName) {
    FILE *filePrt = NULL;
    FILE *outFilePrt = NULL;
    bool res = false;
    char childMkFile[500];
    char childMkNode[500];
    char rootMkFile[500];
    char curFileStr[500];
    char rootMknodeName[500];

    res = parse_mk (fileName, rootMkFile, sizeof (rootMkFile));
    if (false == res) {
        return false;
    }
    strncpy (rootMknodeName, rootMkFile, sizeof (rootMknodeName));
    replace_char (rootMknodeName, '.', '_');

    outFilePrt = fopen (outFileName, "a");
    if (NULL == outFilePrt) {
        return false;
    }
    fprintf (outFilePrt, "\n\n%s [ label = \"%s\"];", rootMknodeName, rootMkFile);

    filePrt = fopen (fileName, "r");
    if (filePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof (curFileStr), filePrt)) {

            memset (childMkFile, 0x00, sizeof (childMkFile));
            memset (childMkNode, 0x00, sizeof (childMkNode));

            res = parse_mk (curFileStr, childMkFile, sizeof (childMkFile));
            if (true == res) {
                strncpy (childMkNode, childMkFile, sizeof (childMkNode));
                replace_char (childMkNode, '.', '_');
                fprintf (outFilePrt, "\n%s [ label = \"%s\"];", childMkNode, childMkFile);
                fprintf (outFilePrt, "\n%s->%s", rootMknodeName, childMkNode);
            } else {
                // printf ("\nUnable to parse line: %d %s ", line, curFileStr);
                line++;
            }
        }

        // strncpy (tempStr, "", sizeof(tempStr));
        // parse_c (fileStr, tempStr,sizeof(tempStr));
        // printf ("\n %s", tempStr);

        res = true;
        fclose (filePrt);
    } else {
        printf ("Error");
    }
    if (outFilePrt) {
        fclose (outFilePrt);
    }
    return res;
}

bool parse_mk (char *fileStr, char *tempStr, int outStrLen) {
    bool res = false;
    uint16_t fileNameLen = 0;
    char fifoArray[1000];
    if (fileStr) {
        int inStrLen = strlen (fileStr);
        if (0 < inStrLen) {
            if (NULL != strstr (fileStr, "mk")) {
                Fifo_array_t outfilefifo;
                fifo_init (&outfilefifo, sizeof (fifoArray), fifoArray);
                for (int i = 0; i < inStrLen; i++) {
                    if (true == is_allowed_char_file (fileStr[i])) {
                        if ('#' == fileStr[i]) {
                            i = inStrLen;
                            break;
                        }
                        if (('\n' != fileStr[i]) && ('\r' != fileStr[i]) && (' ' != fileStr[i])) {
                            fifo_push (&outfilefifo, fileStr[i]);
                        }
                    } else {
                        fifo_reset (&outfilefifo);
                    }
                }
                fifo_peek_array (&outfilefifo, tempStr, &fileNameLen);
                if (0 < fileNameLen) {
                    if (NULL != strstr (tempStr, "mk")) {
                        // printf ("\n mk file: [%s]", tempStr);
                        res = true;
                    } else {
                        fifo_reset (&outfilefifo);
                        memset (tempStr, 0x00, outStrLen);
                    }
                }
            }
        }
    }
    return res;
}

// grep "    include $(ROOT)/components/toolboxes/io_toolbox/io_toolbox.mk" -E "\w+.mk"
bool test_parse_mk (void) {
    int cmpRes;
    printf ("\n[d] %s(): line %u",__FUNCTION__,__LINE__);
    char tempStr[1000];
    strncpy (tempStr, "", sizeof (tempStr));
    parse_mk ("    include $(ROOT)//components//toolboxes//io_toolbox//io_toolbox.mk\n", tempStr, sizeof (tempStr));
    cmpRes = strcmp ("io_toolbox.mk", tempStr);
    if (0 != cmpRes) {
        return false;
    }
    printf ("\n[d] %s(): line %u",__FUNCTION__,__LINE__);
    strncpy (tempStr, "", sizeof (tempStr));
    parse_mk ("include $(ROOT)/components/lib/spc58_mcan/spc58_mcan.mk", tempStr, sizeof (tempStr));
    cmpRes = strcmp ("spc58_mcan.mk", tempStr);
    if (0 != cmpRes) {
        return false;
    }
    return true;
}

bool is_allowed_char_file (char ch) {
    if ('/' == ch) {
        return false;
    }
    if ('\\' == ch) {
        return false;
    }
    if ('$' == ch) {
        return false;
    }
    if ('(' == ch) {
        return false;
    }
    if (')' == ch) {
        return false;
    }
    return true;
}

bool is_char_of_file (char ch) {
    if ('a' <= ch && (ch <= 'z')) {
        return true;
    }
    if ('A' <= ch && (ch <= 'Z')) {
        return true;
    }
    if ('_' == ch) {
        return true;
    }
    if ('.' == ch) {
        return true;
    }
    return false;
}
