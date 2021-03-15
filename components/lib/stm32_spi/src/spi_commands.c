#include "spi_commands.h"

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "convert.h"
#include "diag_page.h"
#include "diag_report.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "spi.h"

static char *baud_rate_str(uint16_t baud_rate_val){
	static char *out_str="none";
	switch (baud_rate_val) {
	 case 0: out_str = "fPCLK/2"; break;
	 case 1: out_str = "fPCLK/4"; break;
	 case 2: out_str = "fPCLK/8"; break;
	 case 3: out_str = "fPCLK/16"; break;
	 case 4: out_str = "fPCLK/32"; break;
	 case 5: out_str = "fPCLK/64"; break;
	 case 6: out_str = "fPCLK/128"; break;
	 case 7: out_str = "fPCLK/256"; break;
	 default:
		 out_str = "undef";
		 break;
	}
	return out_str;
}
bool cmd_spi_diag (int32_t argc, char *argv[]) {
	uint16_t baud_rate_val = extract_subval_from_16bit (hspi1.Instance->CR1, 5,3);
	rx_printf ("baud_rate: %s" CRLF, baud_rate_str(baud_rate_val));
    rx_printf ("spi1_rxtx_cnt %u" CRLF, spi1_rxtx_cnt);
    rx_printf ("spi1_tx_cnt %u" CRLF, spi1_tx_cnt);
    rx_printf ("spi1_rx_cnt %u" CRLF, spi1_rx_cnt);
    rx_printf ("spi1_rx_cnt %u" CRLF, spi1_err_cnt);
    return false;
}

// spis 1 0x55
bool cmd_spi_send (int32_t argc, char *argv[]) {
    bool res = false;
    LOG_INFO (SYS, "argc %u ", argc);
    if (2 == argc) {
        res = true;
        uint8_t spi_num = 0;
        uint8_t tx_byte = 0;
        if (true == res) {
            res = try_str2uint8 (argv[0], &spi_num);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse spi_num  %s", argv[0]);
            }
        }

        if (true == res) {
            res = try_str2uint8 (argv[1], &tx_byte);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse tx_byte  %s", argv[1]);
            }
        }
        if (true == res) {
            uint8_t rx_byte = 0;
            res = spi1_send_receive_byte (tx_byte, &rx_byte);
            if (true == res) {
                LOG_INFO (SYS, "SPI%u tx: 0x%02x rx: 0x%02x", spi_num, tx_byte, rx_byte);
            } else {
                LOG_ERROR (SYS, "error SPI%u tx: 0x%02x rx: 0x%02x", spi_num, tx_byte, rx_byte);
            }
        }
    } else {
        LOG_ERROR (SYS, "Usage: spis spi_num tx_byte");
    }
    return res;
}

// spirv 12
bool cmd_spi_receive(int32_t argc, char *argv[]) {
	bool res = false;
	if (1 == argc) {
		res = true;
		uint32_t byte_num = 0;
		if (true == res) {
			res = try_str2uint32(argv[0], &byte_num);
			if (false == res) {
				LOG_ERROR(SYS, "Unable to parse tx_byte  %s", argv[1]);
			}
		}
		if (true == res) {
			for (int cnt = 0; cnt < byte_num; cnt++) {
				uint8_t rx_byte = 0xFF;
				res = spi1_receive_byte(&rx_byte);
				if (true == res) {
					rx_printf("%u: read byte: 0x%02x 0b%s" CRLF, cnt,rx_byte,
							utoa_bin8(rx_byte));
				} else {
					LOG_ERROR(SYS, "%u: error SPI1 read rx: 0x%02x 0b%s",cnt, rx_byte,
							utoa_bin8(rx_byte));
				}
			}
		}
	} else if(0 == argc){
		res = true;
		uint32_t cnt = 0;
    	uint8_t rx_byte = 0xFF;
		do{
			rx_byte = 0xFF;
	    	res = spi1_receive_byte(&rx_byte);
			if (true == res) {
				rx_printf("%u: read byte: 0x%02x 0b%s %s" CRLF, cnt,rx_byte,
						utoa_bin8(rx_byte),(0x00!=rx_byte)?"<--":"");
			} else {
				LOG_ERROR(SYS, "%u: error SPI1 read rx: 0x%02x 0b%s",cnt, rx_byte,
						utoa_bin8(rx_byte));
			}
			cnt++;
			wait_in_loop_ms (2);
		}while(0xFF!=rx_byte);
	}else {
		LOG_ERROR(SYS, "Usage: spirv byte_num");
	}
	return res;
}
