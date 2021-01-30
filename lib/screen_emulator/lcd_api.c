#include "lcd_api.h"

#include <stdint.h>
#include <stdbool.h>

#include "str_ops.h"
#include "tcp_client.h"

bool lcd_draw_pixel(uint16_t x, uint16_t y, bool status) {
	printf("\n[d] %s()", __FUNCTION__);
	bool res = false;
	char tx_text[50] = "";
	snprintf(tx_text, sizeof(tx_text), "%d %d %d", x, y, status);
	uint32_t tcp_server_ip;
	res = try_strl2ipv4("127.0.0.1", strlen("127.0.0.1"), &tcp_server_ip);
	if (true == res) {
		res = sent_to_tcp_server(tx_text, strlen(tx_text), LCD_PORT,
				tcp_server_ip);
	}
	return res;
}
