#include "test_validate_ip_address.h"

#include "uTests.h"

bool test_valid_ip_address(void) {
	printf ("\n%s()", __FUNCTION__);
	EXPECT_EQ_STR("IPv4",validIPAddress("172.16.254.1"));
	EXPECT_EQ_STR("IPv6",validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334"));
	return true;
}
