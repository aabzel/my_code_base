#include "test_mk_2_dot.h"

#include "uTests.h"
#include "mk_to_dot.h"

static bool test_parse_c (void) {
	printf("\n%s()", __FUNCTION__);
    int cmp_res;

    char tempStr[1000];
    strncpy (tempStr, "", sizeof (tempStr));
    parse_c ("CSRC += $(PATH_BOARD)/src/tsts_v1_driver.c\n", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("tsts_v1_driver.c", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    strncpy (tempStr, "", sizeof (tempStr));
    parse_c ("    CSRC += $(PATH_BOARD)/src/can_led_config.c", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("can_led_config.c", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    strncpy (tempStr, "", sizeof (tempStr));
    parse_c ("    CSRC += $(PATH_BOARD)/src/tsts_v1_msg_handler.c\n", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("tsts_v1_msg_handler.c", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    strncpy (tempStr, "", sizeof (tempStr));
    parse_c ("%.cmm: $(OBJDIR_)", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    return true;
}

// grep "    include $(ROOT)/components/toolboxes/io_toolbox/io_toolbox.mk" -E "\w+.mk"
static bool test_parse_mk (void) {
	printf("\n%s()", __FUNCTION__);
    int cmp_res;

    char tempStr[1000];
    strncpy (tempStr, "", sizeof (tempStr));
    parse_mk ("    include $(ROOT)//components//toolboxes//io_toolbox//io_toolbox.mk\n", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("io_toolbox.mk", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    strncpy (tempStr, "", sizeof (tempStr));
    parse_mk ("include $(ROOT)/components/lib/spc58_mcan/spc58_mcan.mk", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("spc58_mcan.mk", tempStr);
    if (0 != cmp_res) {
        return false;
    }

    strncpy (tempStr, "", sizeof (tempStr));
    parse_mk ("CAN_MANAGER_GENERATED_MK_NAME   = can_generated_patched.mk\n", tempStr, sizeof (tempStr));
    cmp_res = strcmp ("can_generated_patched.mk", tempStr);
    if (0 != cmp_res) {
        return false;
    }
    return true;
}

static bool test_parse_mk_node (void){
	printf("\n%s()", __FUNCTION__);
    int cmp_res;
    bool res;
    char root_node_name[500];
    memset(root_node_name,0x00,sizeof(root_node_name));
    res = calc_mk_node("C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/join_list.mk", root_node_name);
    if(false==res){
    	return false;
    }
    cmp_res = strcmp(root_node_name,"join_list_mk");
    if(cmp_res ){
    	printf("\n Unable to parse join_list.mk result [%s]",root_node_name);
    	return false;
    }
    memset(root_node_name,0x00,sizeof(root_node_name));
    res = calc_mk_node("C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/AEC_V2/board.mk", root_node_name);
    if(false==res){
    	return false;
    }
    cmp_res = strcmp(root_node_name,"C__Job_IO_V4_1_FW_controllers_abarunin_io_040_components_boards_AEC_V2_board_mk");
    if (cmp_res ) {
    	printf("\n Unable to parse AEC_V2/board.mk result [%s]",root_node_name);
    	return false;
    }
    memset(root_node_name,0x00,sizeof(root_node_name));
    res = calc_mk_node("C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/AEC_V2/cfg/board_cfg.mk", root_node_name);
    if(false==res){
    	return false;
    }
    cmp_res = strcmp(root_node_name,"C__Job_IO_V4_1_FW_controllers_abarunin_io_040_components_boards_AEC_V2_cfg_board_cfg_mk");
    if (cmp_res ) {
        printf("\n Unable to parse AEC_V2/cfg/board_cfg.mk result [%s]",root_node_name);
        return false;
    }

	return true;
}

bool test_mk_2_dot (void){
	printf("\n%s()", __FUNCTION__);
	EXPECT_TRUE( test_parse_mk_node());
	EXPECT_TRUE( test_parse_mk());
	EXPECT_TRUE( test_parse_c());
	return true;
}
