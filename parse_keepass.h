#ifndef PARSE_KEE_PASS_H
#define PARSE_KEE_PASS_H

#include "custom_type.h"

#include <stdio.h>

#define SIGNATURE 0x9AA2D903

#define KEEPASS_1X (0xB54BFB65)
#define KEEPASS_2X_PRE_RELEASE  (0xB54BFB66)
#define KEEPASS_2X_POST_RELEASE  (0xB54BFB67)

#define ID_END_OF_HEADER          (0x00u)
#define ID_COMMENT                (0x01u)
#define ID_CIPHER                 (0x02u)
#define ID_COMPRESSION_FLAGS      (0x03u)
#define ID_MASTER_SEED            (0x04u)
#define ID_TRANSFORM_SEED         (0x05u)
#define ID_TRANSFORM_ROUNDS       (0x06u)
#define ID_ENCRYPTION_IV          (0x07u)
#define ID_PROTECTED_STREAM_KEY   (0x08u)
#define ID_STREAM_START_BYTES     (0x09u)
#define ID_INNER_RANDOM_STREAM    (0x0Au)



bool try_to_open_kdbx_file (void);
bool parse_header (FILE *filePtr);

#endif /* PARSE_KEE_PASS_H */
