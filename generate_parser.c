#include "generate_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "str_ops.h"

//< REG="Basic Control" Addr="0"
bool parse_reg_name(char *cur_file_str, int strlen, char * reg_nane){
    bool res = false;
    char *ptr = strstr(cur_file_str,"REG=\"");
    if (ptr) {
    	int i = 0;
        for(i=0; i<strlen; i++) {
           if('"'!=*(ptr+5+i)) {
        	   reg_nane[i] = *(ptr+5+i);
        	   res=true;
           } else {
        	   break;
           }
        }
        reg_nane[i] = 0x00;
    }
    return res;
}

//< REG="Basic Control" Addr=0
bool parse_reg_addr(char *cur_file_str, int strlen, uint8_t *reg_addr){
    bool res = false;
    char *ptr = strstr(cur_file_str,"Addr=");
    if (ptr) {
    	res = try_str2uint8 ( ptr+5, reg_addr);
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


bool generate_reg_parser(char *in_file_name, char *out_file_name) {
	printf("\n%s()\n", __FUNCTION__);
	bool res = false;
	char cur_file_str[500];
	char reg_nane[500];
	memset(reg_nane, 0, sizeof(reg_nane));
	FILE *inFilePrt = NULL;
	FILE *out_file_prt = NULL;
	out_file_prt = fopen (out_file_name, "w");
	inFilePrt = fopen(in_file_name, "r");
	if ((NULL != inFilePrt) && (NULL!=out_file_prt)) {
		//int line = 0;
		while (NULL != fgets(cur_file_str, sizeof(cur_file_str), inFilePrt)) {
        	uint8_t reg_addr;
            bool res_name = parse_reg_name(cur_file_str, strlen(cur_file_str), reg_nane);
            bool res_addr = parse_reg_addr(cur_file_str, strlen(cur_file_str), &reg_addr);
            if((res_addr==res)  && (true==res_name)) {
            	replace_char (reg_nane, ' ', '_');
            	lower_case_str(reg_nane);
            	//static bool parse_basic_control_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
        		fprintf(out_file_prt, "\nstatic bool parse_%s_register_%u (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {",reg_nane,reg_addr);
        		fprintf(out_file_prt, "\n    bool res = false;");
            }
            uint8_t bit_num = 0;
            uint8_t bit_val = 0;

            bool res_bit_num = parse_bit_num(cur_file_str, sizeof(cur_file_str),  &bit_num);
            bool res_bit_val = parse_bit_val(cur_file_str, sizeof(cur_file_str), &bit_val);
            if ((true==res_bit_num)  && (true==res_bit_val) && (1==bit_val)) {
            	fprintf(out_file_prt, "\n    if (reg16b_val & (1<<%u)) {", bit_num);
            	fprintf(out_file_prt, "\n        fprintf (out_file_prt,\"\\n reg %%02u bit%u:1\", reg_addr);", bit_num );
            	fprintf(out_file_prt, "\n    }");
            	//    if (reg16b_val & RESET_BIT_15) {
                //fprintf (out_file_prt, "\n  reg %02u bit15: RW PHY reset", reg_addr);
            }
            if ((true==res_bit_num)  && (true==res_bit_val) && (0==bit_val)) {
            	fprintf(out_file_prt, "\n    if (0==(reg16b_val & (1<<%u))) {", bit_num);
            	fprintf(out_file_prt, "\n        fprintf (out_file_prt,\"\\n reg %%02u bit%u:0\", reg_addr);", bit_num );
            	fprintf(out_file_prt, "\n    }");
            	//    if (reg16b_val & RESET_BIT_15) {
                //fprintf (out_file_prt, "\n  reg %02u bit15: RW PHY reset", reg_addr);
            }


            if(strstr(cur_file_str,">")){
            	fprintf(out_file_prt, "\n    return res;");
            	fprintf(out_file_prt, "\n}");
            }
            //line++;
		}
		fclose(inFilePrt);
		res = true;
		fprintf(out_file_prt,
				"\n\n // Support: aabzele@gmail.com Alexander Barunin");
		fclose (out_file_prt);
	}
	return res;
}
