#ifndef COMMON_STREAM_H_
#define COMMON_STREAM_H_

#include "ostream.h"

ostream_t *ccp_stream_init(void);
void ccp_stream_dump(const char *cmd);
uint16_t ccp_stream_get_position(void);
char *ccp_stream_get_data(void);

#endif /* COMMON_STREAM_H_ */
