#include "microavia_task.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "uTests.h"

#define MAGIC 0xB0
#define MAX_TX_BUF_SIZE 1000U
#define HEADER_SIZE (sizeof (Message) - sizeof (((Message *)0)->data))

#pragma pack(push, 1)
typedef struct xMessage_t {
    uint8_t magic;   // 1   header  0
    uint32_t crc;    // 4    header  4
    uint16_t len;    // 2    header  5
    uint8_t *data;   // 4            7
    uint8_t size[0]; // 0           11
} Message;

#pragma pack(pop)
// static SerialDevice serial;

static uint8_t g_tx_buf[MAX_TX_BUF_SIZE]; // not all compilers allow dynamic allocation on STACK

uint32_t calc_crc (uint8_t *in_data, uint16_t data_len) {
    if ((0 < data_len) && (NULL != in_data)) {
        return 0x51525354;
    }
    return 0;
}

static uint32_t make_message (Message *const in_msg, uint8_t *const in_data, uint16_t data_len) {
    int ret = -1;
    if (in_msg) {
        in_msg->magic = MAGIC;
        if ((0 < data_len) && (NULL != in_data)) {
            in_msg->crc = calc_crc (in_data, data_len);
            in_msg->len = data_len;
            in_msg->data = in_data;
            ret = 0;
        }
    }
    return ret;
}

static uint32_t serialize_message (Message *const in_msg, uint8_t *const out_buf, uint16_t buf_len) {
    printf ("\n[d] %s() len %d", __FUNCTION__, buf_len);

    size_t total_size = HEADER_SIZE + in_msg->len;
    if ((total_size <= buf_len) && (in_msg) && (out_buf)) {
        memcpy (out_buf, in_msg, HEADER_SIZE);
        memcpy (out_buf + HEADER_SIZE, in_msg->data, in_msg->len);
    } else {
        total_size = 0;
    }

    return total_size;
}

uint32_t send_packet (uint8_t *const in_data, uint16_t data_len) {
    printf ("\n[d] %s() len %d", __FUNCTION__, data_len);
    uint32_t frame_len = 0U;
    static uint8_t busy = 0;
    if (0 == busy) { /*to be reentrant */
        busy = 1;
        const size_t tx_buf_size = data_len + HEADER_SIZE;
        printf ("\n[d]   tx_buf_size %d", tx_buf_size);
        if ((tx_buf_size < MAX_TX_BUF_SIZE) && (in_data)) {
            Message tx_msg = {0};
            make_message (&tx_msg, in_data, data_len);

            memset (g_tx_buf, 0x00, MAX_TX_BUF_SIZE);
            frame_len = serialize_message (&tx_msg, g_tx_buf, tx_buf_size);

            if (0U < frame_len) {
                // serial.send(g_tx_buf, frame_len);
                // wait end of transfer.
            }
        }
        busy = 0;
    }

    return frame_len;
}

bool test_microavia (void) {
    bool res = false;
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (11, sizeof (Message));
    EXPECT_EQ (11, (int)((Message *)0)->size);
    EXPECT_EQ (7, (int)((Message *)0)->data); // fail
    EXPECT_EQ (7, HEADER_SIZE);

    uint8_t frame[100];
    uint8_t exp_frame[] = {0xB0, 0x54, 0x53, 0x52, 0x51, 4, 0, 1, 2, 3, 4};
    uint8_t tx_data[4] = {1, 2, 3, 4};
    Message msg = {0};
    EXPECT_EQ (0, make_message (&msg, tx_data, 4));
    printf ("\n[d] %s() 4", __FUNCTION__);
    EXPECT_EQ (11, serialize_message (&msg, frame, 100));
    EXPECT_EQ_MEM (frame, exp_frame, 11);
    EXPECT_EQ (11, send_packet (tx_data, 4));

    return true;
}
