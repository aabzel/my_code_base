#include "sd_card_commands.h"

#include <inttypes.h>
#include <stdint.h>

#include "board.h"
#include "convert.h"
#include "diskio.h"
#include "data_utils.h"
#include "log.h"
#include "spi.h"
#include "rx_uart.h"
#include "rx_uart_config.h"
#include "sd_card_driver.h"
#include "table_utils.h"

bool cmd_sd_card_init (int32_t argc, char *argv[]) {
    DSTATUS ret = SD_disk_initialize (0);
#if 0
    rx_printf ("SD card init %s " CRLF, (true == res) ? "OK" : "Error");
#endif
    return true;
}

bool cmd_sd_card_74ones_command (int32_t argc, char *argv[]) {
    bool res = false;
    res = sent_74_ones ();
    if (false == res) {
        LOG_ERROR (SYS, "74 ones train error");
        res = false;
    } else {
        LOG_INFO (SYS, "74 ones train fine!");
    }
    return res;
}

// cmd arg crc
bool cmd_sd_card_send_command (int32_t argc, char *argv[]) {
    bool res = false;
    LOG_INFO (SYS, "argc %u ", argc);
    if (2 == argc) {
        res = true;
        uint8_t cmd = 0;
        uint32_t arg = 0;
        if (true == res) {
            res = try_str2uint8 (argv[0], &cmd);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse cmd  %s", argv[0]);
            }
        }

        if (true == res) {
            res = try_str2uint32 (argv[1], &arg);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse arg  %s", argv[1]);
            }
        }

        if (true == res) {
            uint8_t buff[512+10];
            uint8_t ret = SD_sendCommand (cmd, arg);
            SdCommand_t *item = get_reg_inst( cmd);
            if(item){
                res = spi1_receive_array (buff,item->resp_len_byte+2);
                LOG_INFO (SYS, "SD_sendCommand cmd 0x%02x arg 0x%08x ret 0x%02x ", cmd, arg, ret);
                print_mem (buff, item->resp_len_byte+2);
            }
        }
    } else {
        LOG_ERROR (SYS, "Usage: sdsc cmd arg crc");
    }
    return res;
}

bool cmd_sd_card_write_sector (int32_t argc, char *argv[]){
	   bool res = false;
	    LOG_INFO (SYS, "argc %u ", argc);
	    if (1 == argc) {
	        res = true;
	        uint32_t block_numb = 0;
	        if (true == res) {
	            res = try_str2uint32 (argv[0], &block_numb);
	            if (false == res) {
	                LOG_ERROR (SYS, "Unable to parse block_numb  %s", argv[0]);
	            }
	        }

	        if (true == res) {
	            uint8_t buff[512 + 1];
	        	init_array_123(buff, 512);
	            res = sd_write_sector (block_numb, buff);
	            if (true == res) {
	                LOG_INFO (SYS, "[*] write block_numb %u OK", block_numb);
	            } else {
	                LOG_ERROR (SYS, "[!] error write block_numb %u", block_numb);
	            }
	        }
	    } else{
	        LOG_ERROR (SYS, "Usage: sdw block_numb");
	    }
	    return res;
}

bool cmd_sd_card_read_sector (int32_t argc, char *argv[]) {
    bool res = false;
    LOG_INFO (SYS, "argc %u ", argc);
    if (1 == argc) {
        res = true;
        uint32_t sector = 0;
        if (true == res) {
            res = try_str2uint32 (argv[0], &sector);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse sector  %s", argv[0]);
            }
        }

        if (true == res) {
            uint8_t buff[512 + 1];
            memset (buff, 0x00, sizeof (buff));
            DRESULT ret = SD_disk_read(0, buff, sector, 0);
            if (RES_OK == ret) {
                LOG_INFO (SYS, "read sector %u OK", sector);
            } else {
                LOG_ERROR (SYS, "error read sector %u", sector);
            }
            print_mem (buff, 512);
        }
    } else if(2 == argc){
        res = true;
        uint32_t block_numb = 0;
    	uint32_t uniq_cnt=0;
        if (true == res) {
            res = try_str2uint32 (argv[0], &block_numb);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse block_numb  %s", argv[0]);
            }
        }
        uint8_t buff[512 + 1];
    	while(0==uniq_cnt){
            memset (buff, 0x00, sizeof (buff));
            res = sd_read_sector (block_numb, buff);
            if (true == res) {
            	res = uniq_array(buff, 512);
            	if(true==res){
            		LOG_INFO (SYS, "uniq block_num %u ", block_numb);
            		uniq_cnt++;
                    print_mem (buff, 512);
            	}
            }
    		block_numb++;
    	}
    }else{
        LOG_ERROR (SYS, "Usage: sdr block_numb");
    }
    return res;
}

bool cmd_sd_card_diag (int32_t argc, char *argv[]) {
    bool res = false;
    res = is_card_connected ();
    rx_printf ("SD card %s" CRLF, (true == res) ? "connected" : "disconnected");
    // number of available blocks   8388608
    res = read_registers ();
    return res;
}

bool cmd_sd_card_ioctl(int32_t argc, char *argv[]) {
	uint32_t block_numb = 0;
	bool res = false;
	if (1 == argc) {
		uint8_t ctrl = 0 ;
		res = true;
		if (true == res) {
			res = try_str2uint8(argv[0], &ctrl);
			if (false == res) {
				LOG_ERROR(SYS, "Unable to parse ctrl  %s", argv[0]);
			}
		}
		if (true == res) {
    		uint8_t buff[512 + 1];
	    	DRESULT ret = SD_disk_ioctl(0, ctrl, buff);
            LOG_INFO (SYS, "SD_disk_ioctl ret 0x%02x ", ret);
		}
    } else {
	    LOG_ERROR(SYS, "Usage: sdt ctrl");
    }
    return res;
}
