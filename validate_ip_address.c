#include "validate_ip_address.h"

#include "convert.h"

char * validIPAddress(char * IP) {
    bool res;
	printf ("\n%s()", __FUNCTION__);
    char *ip_type = "undef";
    int32_t len= strlen(IP);
    uint32_t ip_val;
    uint16_t ip6_val[8];
	res = try_strl2ipv4 (IP, len, &ip_val);
	if (true==res) {
		ip_type = "IPv4";
	}
	res = try_strl2ipv6 (IP, len, ip6_val);
	if (true==res) {
		ip_type = "IPv6";
	}
	return ip_type;
}




