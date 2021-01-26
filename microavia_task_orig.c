#include "microavia_task.h"

#pragma pack(push, 1)
struct Message {
    uint8_t magic;
    uint32_t crc;
    uint16_t len;
    uint8_t *data;
}
#pragma pack(pop)

static SerialDevice serial;

int make_message (struct Message *msg, uint8_t *data, uint16_t len) {
    msg->magic = 0xB0;
    msg->crc = calc_crc (data, len);
    msg->len = len;
    msg->data = data;

    return 0;
}

int serialize_message (Message *msg, uint8_t *buf, uint16_t len) {
    size_t header_size = sizeof (msg) - sizeof (msg->data);
    size_t total_size = header_size + msg->len;

    if (total_size <= len) {
        memcpy (buf, &msg, header_size);
        memcpy (buf + header_size, msg->data, msg->len);
        return total_size;
    }

    return 0;
}

int send_packet (uint8_t *data, uint16_t len) {
    const size_t BUF_SIZE = len + sizeof (Message);

    Message msg;
    make_message (&msg, data, len);

    uint8_t buf[BUF_SIZE];
    int data_len = serialize_message (&msg, buf, BUF_SIZE);

    if (data_len != 0) {
        serial.send (buf, data_len);
    }

    return data_len;
}
