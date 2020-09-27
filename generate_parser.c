#include "generate_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "str_ops.h"

xReg_map_t RegMap[MAX_NUM_REG];

//< REG="Basic Control" Addr=0

bool parse_text_after_prefix(char *cur_file_str, int in_str_len,char *out_text, char *prefix) {
    bool res = false;
    int prefix_len = strlen(prefix);
    char *ptr = strstr(cur_file_str, prefix);
    if (ptr) {
    	printf("\n spot prefix [%s]", prefix);
    	res = true;
    	int i = 0;
        for(i=0; i<in_str_len; i++) {
           if('"' != *(ptr+prefix_len+i)) {
        	   out_text[i] = *(ptr+prefix_len+i);
        	   res=true;
           } else {
        	   break;
           }
        }
        out_text[i] = 0x00;
    }else{
    	res = false;
    	printf("\n lack of prefix [%s]", prefix);
    }
    return res;
}

bool parse_uint8_after_prefix(char *cur_file_str, int in_str_len, uint8_t *val, char *prefix) {
    bool res = false;
    int prefix_len = strlen(prefix);
    char *ptr = strstr(cur_file_str, prefix);
    if (ptr) {
    	printf("\n spot prefix [%s]", prefix);
    	res = try_strl2uint8 ( ptr+prefix_len,4, val);
    	if (false == res) {
    		printf("\n unable to parse uint8 in [%s] val %u \n", ptr+prefix_len, *val);
    	}
    }
    return res;
}

//< REG="Basic Control" Addr=0
//TODO parse int after prefix
bool parse_reg_addr(char *cur_file_str, int strlen, uint8_t *reg_addr){
    bool res = false;
    char *ptr = strstr(cur_file_str,"Addr=");
    if (ptr) {
    	res = try_strl2uint8 ( ptr+5,2, reg_addr);
    	if (false==res) {
    		printf("\n unable to parse [%s] \n",ptr+5);
    	}
    }
    return res;
}

//0.15.1| RW/SC| Reset | Software reset
bool parse_bit_num(char *cur_file_str, int strlen, uint8_t *bit_num){
	bool res = false;
	char *ptr = strstr(cur_file_str,"bit=");
    if (ptr) {
    	res = try_strl2uint8 ( ptr+4,2, bit_num);
    }
	return res;
}

//0.bit=13 val=0 RW |Speed Select | 10 Mbps
bool parse_bit_val(char *cur_file_str, int strlen, uint8_t *bit_val){
	bool res = false;
	char *ptr = strstr(cur_file_str,"val=");
    if (ptr) {
    	res = try_strl2uint8 ( ptr+4, 1, bit_val);
    	if(false==res){
    		printf("\n in str %s",ptr+4);
    	}
    }
	return res;
}

static bool compose_case( FILE *out_file_prt) {
	bool res = false;
	if(out_file_prt){
		res = true;
	}
	fprintf(out_file_prt, "\n\nstatic bool parse_ksz8081_reg (uint8_t reg_addr, FILE *out_file_prt) {");
		fprintf(out_file_prt, "\n    bool res = false;");
	    fprintf(out_file_prt, "\n    uint16_t reg16b_val = ksz8081RegMap[reg_addr].reg_val;");
	fprintf(out_file_prt, "\n    switch ( reg_addr ) {");
    for (int i = 0; i < 255; i++) {
    	if ( true==RegMap[i].valid ) {
    		fprintf(out_file_prt, "\n        case %u: ",i);
    		fprintf(out_file_prt, "\n            proc_reg_cnt++;");
    		fprintf(out_file_prt, "\n            res = parse_%s_register_%u (reg16b_val, out_file_prt, reg_addr);",RegMap[i].reg_name,i);
    		fprintf(out_file_prt, "\n        break;");
    	}
    }
    fprintf(out_file_prt, "\n        default:");
    fprintf(out_file_prt, "\n            fprintf (out_file_prt, \"\n Lack of parser for reg %%s addr 0x%%x val 0x%%x\", ksz8081_reg_2_name[reg_addr], reg_addr, reg16_val);");
    fprintf(out_file_prt, "\n        break;");
    fprintf(out_file_prt, "\n    }");
    fprintf(out_file_prt, "\n    return res;");
    fprintf(out_file_prt, "\n}");
    return res;
}

static bool init_reg_map (void) {
    for (int i = 0; i < MAX_NUM_REG; i++) {
        RegMap[i].valid=false;
    }
    return true;
}

bool generate_reg_parser(char *in_file_name, char *out_file_name) {
	printf("\n%s()\n", __FUNCTION__);
	bool res = false;
	char cur_file_str[500];
	char reg_name[500];
	init_reg_map();
	memset(cur_file_str, 0, sizeof(cur_file_str));
	memset(reg_name, 0, sizeof(reg_name));
	FILE *inFilePrt = NULL;
	FILE *out_file_prt = NULL;
	out_file_prt = fopen (out_file_name, "w");
	inFilePrt = fopen(in_file_name, "r");
	if(NULL==inFilePrt ){
		printf("\n lack of input file [%s]\n", in_file_name);
	}
	if ((NULL != inFilePrt) && (NULL!=out_file_prt)) {
		//int line = 0;
		while (NULL != fgets(cur_file_str, sizeof(cur_file_str), inFilePrt)) {
			memset(reg_name, 0, sizeof(reg_name));
        	uint8_t reg_addr=0xFF;
            bool res_name = parse_text_after_prefix(cur_file_str, strlen(cur_file_str), reg_name,"REG=\"");
            bool res_addr = parse_uint8_after_prefix(cur_file_str, strlen(cur_file_str), &reg_addr,"Addr=");
            if((true==res_addr)  && (true==res_name)) {
            	RegMap[reg_addr].reg_addr=reg_addr;
            	RegMap[reg_addr].valid = true;
            	printf("\n Reg %s addr [%u]",reg_name, reg_addr);
            	replace_char (reg_name, ' ', '_');
            	replace_char (reg_name, '/', '_');
            	replace_char (reg_name, '-', '_');
            	lower_case_str(reg_name);

            	strncpy(RegMap[reg_addr].reg_name,reg_name, sizeof(RegMap[reg_addr].reg_name));
            	//static bool parse_basic_control_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
        		fprintf(out_file_prt, "\n\nstatic bool parse_%s_register_%u (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {",reg_name,reg_addr);
        		fprintf(out_file_prt, "\n    bool res = false;");
        		fprintf(out_file_prt, "\n    if ( %u == reg_addr ) {",reg_addr);
        		fprintf(out_file_prt, "\n        res = true;");
        		fprintf(out_file_prt, "\n    }");
            } else {
            	if(false==res_name){
                	printf("\n Unable to parse register name in [%s]",cur_file_str);
            	}
            	if(false==res_addr){
                	printf("\n Unable to parse register addr in [%s]",cur_file_str);
            	}
            }
            uint8_t bit_num = 0;
            uint8_t bit_val = 0;
            char bit_type[10];
            char bit_text[1000];
            bool res_bit_num = parse_bit_num(cur_file_str, sizeof(cur_file_str),  &bit_num);
            bool res_bit_val = parse_bit_val(cur_file_str, sizeof(cur_file_str), &bit_val);
            bool res_bit_type = parse_text_after_prefix(cur_file_str, sizeof(cur_file_str), bit_type,"type=\"");
            bool res_bit_text = parse_text_after_prefix(cur_file_str, sizeof(cur_file_str), bit_text,"text=\"");
            if ((res_bit_type)&&(res_bit_text)&&(true==res_bit_num)  && (true==res_bit_val) && (1==bit_val)) {
            	fprintf(out_file_prt, "\n    if (reg16b_val & (1<<%u)) {", bit_num);
            	fprintf(out_file_prt, "\n        fprintf (out_file_prt,\"\\n reg %%02u bit%02u:1  %s %s\", reg_addr);", bit_num ,bit_type,bit_text);
            	fprintf(out_file_prt, "\n    }");
            }
            if ((res_bit_type)&&(res_bit_text)&&(true==res_bit_num)  && (true==res_bit_val) && (0==bit_val)) {
            	fprintf(out_file_prt, "\n    if (0==(reg16b_val & (1<<%u))) {", bit_num);
            	fprintf(out_file_prt, "\n        fprintf (out_file_prt,\"\\n reg %%02u bit%02u:0  %s %s\", reg_addr);", bit_num ,bit_type,bit_text);
            	fprintf(out_file_prt, "\n    }");
            }

            if(strstr(cur_file_str,">")){
            	fprintf(out_file_prt, "\n    return res;");
            	fprintf(out_file_prt, "\n}");
            }
            //line++;
            memset(cur_file_str, 0, sizeof(cur_file_str));
		}

		res = compose_case(out_file_prt);

		fclose(inFilePrt);
		res = true;
		fprintf(out_file_prt,
				"\n\n // Support: aabzele@gmail.com Alexander Barunin");
		fclose (out_file_prt);
	}
	return res;
}
