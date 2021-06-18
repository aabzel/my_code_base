#include "evbox_task_test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "evbox_task.h"
#include "uTests.h"


static bool test_hysteresis10(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(4U,hysteresis(95));
	EXPECT_EQ(4U,hysteresis(90));
	EXPECT_EQ(4U,hysteresis(89));
	EXPECT_EQ(4U,hysteresis(86));
	EXPECT_EQ(4U,hysteresis(85));
	EXPECT_EQ(3U,hysteresis(75));
	EXPECT_EQ(3U,hysteresis(65));
	EXPECT_EQ(3U,hysteresis(64));
	EXPECT_EQ(3U,hysteresis(61));
	EXPECT_EQ(3U,hysteresis(60));
    EXPECT_EQ(2U,hysteresis(50));
	EXPECT_EQ(2U,hysteresis(40));
	EXPECT_EQ(2U,hysteresis(39));
    EXPECT_EQ(2U,hysteresis(36));
    EXPECT_EQ(2U,hysteresis(35));
    EXPECT_EQ(1U,hysteresis(25));
    EXPECT_EQ(1U,hysteresis(15));
    EXPECT_EQ(1U,hysteresis(14));
    EXPECT_EQ(1U,hysteresis(11));
    EXPECT_EQ(1U,hysteresis(10));
	EXPECT_EQ(0U,hysteresis(5));
	
	return true;
}

static bool test_hysteresis9(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(0U,hysteresis(5));
    EXPECT_EQ(0U,hysteresis(10));
    EXPECT_EQ(0U,hysteresis(11));
    EXPECT_EQ(0U,hysteresis(14));
    EXPECT_EQ(0U,hysteresis(15));
    EXPECT_EQ(1U,hysteresis(25));
    EXPECT_EQ(1U,hysteresis(35));
    EXPECT_EQ(1U,hysteresis(36));
	EXPECT_EQ(1U,hysteresis(39));
	EXPECT_EQ(1U,hysteresis(40));
    EXPECT_EQ(2U,hysteresis(50));
	EXPECT_EQ(2U,hysteresis(60));
	EXPECT_EQ(2U,hysteresis(61));
	EXPECT_EQ(2U,hysteresis(64));
	EXPECT_EQ(2U,hysteresis(65));
	EXPECT_EQ(3U,hysteresis(75));
	EXPECT_EQ(3U,hysteresis(85));
	EXPECT_EQ(3U,hysteresis(86));
	EXPECT_EQ(3U,hysteresis(89));
	EXPECT_EQ(3U,hysteresis(90));
	EXPECT_EQ(4U,hysteresis(95));
	return true;
}


static bool test_hysteresis8(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(2U,hysteresis(50));

    EXPECT_EQ(2U,hysteresis(35));
    EXPECT_EQ(1U,hysteresis(25));
	
    EXPECT_EQ(1U,hysteresis(38));
    EXPECT_EQ(1U,hysteresis(36));
	
	EXPECT_EQ(2U,hysteresis(50));
    EXPECT_EQ(2U,hysteresis(64));
	
	EXPECT_EQ(2U,hysteresis(61));
	return true;
}



static bool test_hysteresis7(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(1U,hysteresis(25));

    EXPECT_EQ(1U,hysteresis(36));
    EXPECT_EQ(1U,hysteresis(39));
	
    EXPECT_EQ(1U,hysteresis(36));
    EXPECT_EQ(1U,hysteresis(39));
	
	EXPECT_EQ(1U,hysteresis(36));
    EXPECT_EQ(1U,hysteresis(39));
	
	EXPECT_EQ(3U,hysteresis(75));
	return true;
}



static bool test_hysteresis6(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(3U,hysteresis(75));

    EXPECT_EQ(3U,hysteresis(64));
    EXPECT_EQ(3U,hysteresis(61));
	
    EXPECT_EQ(3U,hysteresis(64));
    EXPECT_EQ(3U,hysteresis(61));
	
	EXPECT_EQ(3U,hysteresis(64));
    EXPECT_EQ(3U,hysteresis(61));
	
	EXPECT_EQ(2U,hysteresis(55));
	return true;
}

static bool test_hysteresis5(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(1U,hysteresis(25 ));
	EXPECT_EQ(2U,hysteresis(63 ));
	return true;
}

static bool test_hysteresis4(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(4U,hysteresis(95));
	EXPECT_EQ(2U,hysteresis(36));
	return true;
}


static bool test_hysteresis3(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(1U,hysteresis(25));
	EXPECT_EQ(3U,hysteresis(88));
	return true;
}

static bool test_hysteresis2(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(0U,hysteresis(0));
	EXPECT_EQ(0U,hysteresis(13));
	EXPECT_EQ(1U,hysteresis(38));
	return true;
}

static bool test_hysteresis1(void){
	printf("\n %s():",__FUNCTION__);
	EXPECT_EQ(4U,hysteresis(95));
	EXPECT_EQ(4U,hysteresis(86));
	EXPECT_EQ(1U,hysteresis(25));
	EXPECT_EQ(1U,hysteresis(11));
	EXPECT_EQ(2U,hysteresis(50));
	EXPECT_EQ(2U,hysteresis(36));
	EXPECT_EQ(3U,hysteresis(75));
	EXPECT_EQ(3U,hysteresis(61));
	return true;
}

bool test_hysteresis(void){
	printf("\n %s():",__FUNCTION__);
    EXPECT_TRUE(test_hysteresis1());
    EXPECT_TRUE(test_hysteresis2());
	EXPECT_TRUE(test_hysteresis3());
	EXPECT_TRUE(test_hysteresis4());
	EXPECT_TRUE(test_hysteresis5());
    EXPECT_TRUE(test_hysteresis6());
    EXPECT_TRUE(test_hysteresis7());
	EXPECT_TRUE(test_hysteresis8());
	EXPECT_TRUE(test_hysteresis9());
	EXPECT_TRUE(test_hysteresis10());
	return true;
}
