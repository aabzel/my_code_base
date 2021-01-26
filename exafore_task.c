#include "exafore_task.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "uTests.h"

#define HEADER_SIZE (sizeof (Message) - sizeof (((Message *)0)->data))
#define HEADER_SIZE_FULL (sizeof (MessageFull) - sizeof (((MessageFull *)0)->data))

#pragma pack(push, 1)
typedef struct xMessage_t {
    uint8_t id;      // 1    header  0
    uint32_t crc;    // 4    header  4
    uint16_t len;    // 2    header  5
    uint8_t *data;   // 4            7
    uint8_t size[0]; // 0            11
} Message;
#pragma pack(pop)

typedef struct xMessageFull_t {
    uint8_t id;      // 1    header
    uint32_t crc;    // 4    header
    uint16_t len;    // 2    header
    uint8_t *data;   // 4
    uint8_t size[0]; // 0
} MessageFull;

bool test_struct (void) {
    printf ("\n[d] %s()", __FUNCTION__);

    EXPECT_EQ (11, sizeof (Message));
    EXPECT_EQ (11, (int)((Message *)0)->size);
    EXPECT_EQ (7, HEADER_SIZE);
    // EXPECT_EQ (0, sizeof (Message) - ( int ) ( ( ( (Message*) 0) )->id) ) ;// run-time error
    // EXPECT_EQ (4, (int)((MessageFull *) 0 )->crc ) ;// run-time error

    EXPECT_EQ (16, sizeof (MessageFull));
    EXPECT_EQ (16, (int)((MessageFull *)0)->size);
    // EXPECT_EQ (12, HEADER_SIZE_FULL);
    // EXPECT_EQ (0, sizeof (MessageFull) - ( int ) ( ( ( (MessageFull*) 0) )->id) ) ; // run-time error
    // EXPECT_EQ (4, (int)((MessageFull *) 0 )->crc ) ;// run-time error
    // EXPECT_EQ (5, (int)((MessageFull *) 0 )->len ) ;// run-time error
    // EXPECT_EQ (7, (int)((MessageFull *) 0 )->data ) ;// run-time error

    return true;
}
