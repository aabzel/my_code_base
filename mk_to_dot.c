#include "mk_to_dot.h"

#include "fifo_char.h"
#include "str_ops.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool calc_mk_node(char *in_file_name, char *out_root_node_name) {
	printf("\n%s()", __FUNCTION__);
	char file_name[1000];
	strcpy(file_name,in_file_name);
	char *ch;
	ch=strstr(in_file_name,"Makefile");
	if(NULL!=ch){
		replace_char (file_name, '.', '_');
		replace_char (file_name, '\\', '_');
		replace_char (file_name, '/', '_');
		replace_char (file_name, ':', '_');
		strcpy(out_root_node_name,file_name);
		return true;
	}

	ch=strstr(in_file_name,"board.mk");
	if(NULL!=ch){
		replace_char (file_name, '.', '_');
		replace_char (file_name, '\\', '_');
		replace_char (file_name, '/', '_');
		replace_char (file_name, ':', '_');
		strcpy(out_root_node_name,file_name);
		return true;
	}
	ch=strstr(in_file_name,"board_cfg.mk");
	if(NULL!=ch){
		replace_char (file_name, '.', '_');
		replace_char (file_name, '\\', '_');
		replace_char (file_name, '/', '_');
		replace_char (file_name, ':', '_');
		strcpy(out_root_node_name,file_name);
		return true;
	}

	//char *bname = basename(in_file_name);
	//printf("\n base name %s", bname);
	//replace_char (bname, '.', '_');
	//strcpy(out_root_node_name,bname);

	bool discard = false;
	int str_len = strlen(file_name);
	int i ;
	for ( i = str_len; 0<=i; i--) {
		if(('/'==file_name[i])||('\\'==file_name[i])){
			discard=true;
		}
		if (true==discard) {
			file_name[i]='_';
		}
	}
	for (i=0; i<str_len; i++) {
		if('_'!=file_name[i]){
			replace_char (&file_name[i], '.', '_');
			strcpy(out_root_node_name,&file_name[i]);
			return true;
		}
	}
	return false;
}

#define NUM_COLORS 15
const char *avaulableColors[]={
 "black",
 "blue",
 "blueviolet",
 "brown1",
 "gold",
 "brown4",
 "chartreuse",
 "green",
 "chocolate1",
 "cyan",
 "purple",
 "darkgreen",
 "magenta",
 "navy",
 "fuchsia"
};

static bool assigne_edge_collor(char *out_edge_color){
	//TODO assigne rand from list
	int i = rand()%NUM_COLORS;
	strcpy(out_edge_color,avaulableColors[i]);
	return true;
}

bool proc_mk_file (char *fileName, char *outFileName) {

#ifdef DEBUD_PROC_MK
	printf("\n%s()", __FUNCTION__);
#endif

    FILE *filePrt = NULL;
    FILE *outFilePrt = NULL;
    bool res = false;
    char childMkFile[500];
    char child_c_file_node[500];
    char child_c_file[500];
    char childMkNode[500];
    char rootMkFile[500];
    char curFileStr[500];
    char rootMknodeName[500];
    char root_node_name[100];
    char edge_color[100];

    assigne_edge_collor(edge_color);

    calc_mk_node(fileName,root_node_name);

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
    fprintf (outFilePrt, "\n\n%s [ label = \"%s\"];", root_node_name, rootMkFile);

    filePrt = fopen (fileName, "r");
    if (filePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof (curFileStr), filePrt)) {

            memset (childMkFile, 0x00, sizeof (childMkFile));
            memset (childMkNode, 0x00, sizeof (childMkNode));

            bool mk_res = parse_mk (curFileStr, childMkFile, sizeof (childMkFile));
            if (true == mk_res) {
                strncpy (childMkNode, childMkFile, sizeof (childMkNode));
                replace_char (childMkNode, '.', '_');
                fprintf (outFilePrt, "\n%s [ label = \"%s\", style=filled, fillcolor=lightskyblue];", childMkNode,
                         childMkFile);
                fprintf (outFilePrt, "\n%s->%s [color=%s];", root_node_name, childMkNode, edge_color);
            } else {
                // printf ("\nUnable to parse line: %d %s", line, curFileStr);
                line++;
            }
            if (false == mk_res) {
                memset (child_c_file, 0x00, sizeof (child_c_file));
                bool c_res = parse_c (curFileStr, child_c_file, sizeof (child_c_file));
                if (true == c_res) {
                    strncpy (child_c_file_node, child_c_file, sizeof (child_c_file_node));
                    replace_char (child_c_file_node, '.', '_');
                    fprintf (outFilePrt, "\n%s [ label = \"%s\", style=filled, fillcolor=cornsilk];", child_c_file_node,
                             child_c_file);
                    fprintf (outFilePrt, "\n%s->%s [color=%s];", root_node_name, child_c_file_node, edge_color);
                    printf ("\n %s", child_c_file);
                }
            }
        }

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

bool parse_c (char *in_file_str, char *out_temp_str, int out_temp_str_len) {
#ifdef DEBUD_PROC_MK
	printf("\n%s()", __FUNCTION__);
#endif
    bool res = false;
    if (NULL != in_file_str) {
        int inStrLen = strlen (in_file_str);
        if (0 < inStrLen) {
            if (NULL != strstr (in_file_str, ".c")) {
                char fifoArray[1000];
                Fifo_array_t outfilefifo;
                fifo_init (&outfilefifo, sizeof (fifoArray), fifoArray);
                for (int i = 0; i < inStrLen; i++) {
                    if (true == is_allowed_char_file (in_file_str[i])) {
                        if ('#' == in_file_str[i]) {
                            i = inStrLen;
                            break;
                        }
                        if (('\n' != in_file_str[i]) && ('\r' != in_file_str[i]) && (' ' != in_file_str[i])) {
                            fifo_push (&outfilefifo, in_file_str[i]);
                        }
                    } else {
                        fifo_reset (&outfilefifo);
                    }
                }
                uint16_t fileNameLen = 0;
                fifo_peek_array (&outfilefifo, out_temp_str, &fileNameLen);
                if (0 < fileNameLen) {
                    if (NULL != strstr (out_temp_str, ".c")) {
                        // printf ("\n mk file: [%s]", tempStr);
                        if (NULL == strstr (out_temp_str, ".cmm")) {
                            res = true;
                        }
                    } else {
                        fifo_reset (&outfilefifo);
                        memset (out_temp_str, 0x00, out_temp_str_len);
                    }
                }
            }
        }
    }

    return res;
}

//
bool parse_mk (char *in_file_str, char *tempStr, int outStrLen) {
#ifdef DEBUD_PROC_MK
	printf("\n%s()", __FUNCTION__);
#endif
    bool res = false;
    uint16_t fileNameLen = 0;
    char fifoArray[1000];
    if (NULL != in_file_str) {
        int inStrLen = strlen (in_file_str);
        if (0 < inStrLen) {
            if (NULL != strstr (in_file_str, ".mk")) {
                Fifo_array_t outfilefifo;
                fifo_init (&outfilefifo, sizeof (fifoArray), fifoArray);
                for (int i = 0; i < inStrLen; i++) {
                    if (true == is_allowed_char_file (in_file_str[i])) {
                        if ('#' == in_file_str[i]) {
                            i = inStrLen;
                            break;
                        }
                        if (('\n' != in_file_str[i]) && ('\r' != in_file_str[i]) && (' ' != in_file_str[i])) {
                            fifo_push (&outfilefifo, in_file_str[i]);
                        }
                    } else {
                        fifo_reset (&outfilefifo);
                    }
                }
                fifo_peek_array (&outfilefifo, tempStr, &fileNameLen);
                if (0 < fileNameLen) {
                    if (NULL != strstr (tempStr, ".mk")) {
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


bool is_allowed_char_file (char ch) {
    if ('=' == ch) {
        return false;
    }

    if ('/' == ch) {
        return false;
    }
    if ('\\' == ch) {
        return false;
    }
    if ('%' == ch) {
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
