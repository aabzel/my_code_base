#include "parse_keepass.h"

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

char *IDtoNameTUT [11] =
    {
        "ID_END_OF_HEADER",
        "ID_COMMENT",
        "ID_CIPHER",
        "ID_COMPRESSION_FLAGS",
        "ID_MASTER_SEED",
        "ID_TRANSFORM_SEED",
        "ID_TRANSFORM_ROUNDS",
        "ID_ENCRYPTION_IV",
        "ID_PROTECTED_STREAM_KEY",
        "ID_STREAM_START_BYTES",
        "ID_INNER_RANDOM_STREAM" };

bool try_to_open_kdbx_file (void) {
    bool res = false;
    FILE *filePtr = NULL;
    filePtr = fopen ("db.kdbx", "rb");
    if (NULL != filePtr) {
        printf ("\n the file has been opened");
        /*Read signature*/
        size_t numItems = 0;
        uint32_t baseSignature = 0u;
        uint32_t versionSignature = 0u;
        uint32_t fileVersion = 0u;

        numItems = fread (&baseSignature, 4, 1, filePtr);
        if (1 == numItems) {
            printf ("\nbaseSignature 0x%X", baseSignature);
        }
        numItems = fread (&versionSignature, 4, 1, filePtr);
        if (1 == numItems) {
            printf ("\nversionSignature 0x%X", versionSignature);
        }

        if (KEEPASS_2X_POST_RELEASE == versionSignature) {
            numItems = fread (&fileVersion, 4, 1, filePtr);
            if (1 == numItems) {
                printf ("\nfileVersion 0x%08X", fileVersion);
            }
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
            parse_header (filePtr);
        }

        fclose (filePtr);
        res = true;
    } else {
        printf ("\n Unable to open the file");
    }
    return res;
}

bool parse_header (FILE *filePtr) {
    bool res = false;
    uint8_t id = 0;
    uint16_t DataLen = 0;
    size_t numItems = 0;

    numItems = fread (&id, 1, 1, filePtr);
    if (1 == numItems) {
        printf ("\nID 0x%02X %s ", id, IDtoNameTUT[id]);
    }

    numItems = fread (&DataLen, 2, 1, filePtr);
    if (1 == numItems) {
        printf ("\nDataLen 0x%04X %d byte", DataLen, DataLen);
        uint8_t *dataPtr = malloc (DataLen + 1);
        if (dataPtr) {
            numItems = fread (dataPtr, DataLen, 1, filePtr);
            if (1 == numItems) {
                print_mem (dataPtr, DataLen);
                free(dataPtr);
            }

        }else{
            printf("\n Unable to alloc %d byte",DataLen);
        }
    }
    return res;
}



