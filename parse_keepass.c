#include "parse_keepass.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "aes.h"
#include "crypto-ms.h"
#include "helper.h"
#include "sha256.h"
#include "utils.h"

KeePassFileHeader_t keePassHeader;

char *IDtoNameTUT[11] = { "ID_END_OF_HEADER", "ID_COMMENT", "ID_CIPHER",
		"ID_COMPRESSION_FLAGS", "ID_MASTER_SEED", "ID_TRANSFORM_SEED",
		"ID_TRANSFORM_ROUNDS", "ID_ENCRYPTION_IV", "ID_PROTECTED_STREAM_KEY",
		"ID_STREAM_START_BYTES", "ID_INNER_RANDOM_STREAM" };

#define SIG_SIZE 4U
#define SIG_VER_SIZE 4U

//static char kdbx_filename[] = "db.key";

size_t kdbx_headerentries_read(FILE *kdbx_fd, kdbx_header_entry_t *entries) {
	size_t ret = 0;
	size_t result = 0;
	uint8_t id = 0;
	if (entries == NULL)
		return 0;
	do {
		// headers have variable lengths.
		// we need to read: [1 byte hdr-id] [2 byte data-len] [data-len bytes of value]
		// if hdr-id == 0x00: header ends, encrypted payload starts.

		ret = fread(&id, sizeof(uint8_t), 1, kdbx_fd);
		if (ret != 1) {
			printf("[!] fread(id) failed.");
			break;
		} else {
			//printf("\n read id %u ", id);
			if (HEADER_ID_COUNT < id) {
				printf("\n read id [%u]", id);
				id = END;
				continue;
			}
			entries[id].id = id;
			ret = fread(&entries[id].len, sizeof(uint16_t), 1, kdbx_fd);
			if (ret != 1) {
				printf("\n[!] fread(hdrlen) failed.");
				break;
			} else {
				//printf("read id len %u ", entries[id].len);
				entries[id].data = (uint8_t*) malloc(entries[id].len);

				if (entries[id].data == NULL) {
					printf("[!] malloc(entries[id].len) failed.");
					break;
				} else {
					ret = fread(entries[id].data, entries[id].len, 1, kdbx_fd);
					if (ret != 1) {
						printf("[!] fread(entries[%d].data) failed.", id);
						break;
					} else {
						if ((id == COMPRESSIONFLAGS)
								|| (id == INNERRANDOMSTREAMID)) {
							memcpy(&entries[id].dw, entries[id].data, 4);
							memcpy(&entries[id].qw, entries[id].data, 4);
						} else if (id == TRANSFORM_ROUNDS) {
							memcpy(&entries[id].qw, entries[id].data, 8);
						}
						result++;
					}

				}

			}
		}

	} while (id != END);

	return result;
}

void kdbx_headerentries_dump(kdbx_header_entry_t *h) {
	printf("[*] kdbx header entries:\n");
	printf("[-]    END_0 :             len: %u    ",h[0].len);
	print_hex_buf( h[0].data, h[0].len);

	printf("\n[-]    COMMENT_1:        len: %u     ",h[1].len);
	print_hex_buf(  h[1].data, h[1].len);

	printf("\n[-]    CIPHERID_2:      len: %u      ",h[2].len);
	print_hex_buf( h[2].data, h[2].len);

	printf("\n[-]    COMPRESSION_FLAGS_3:    %08x\n", h[3].dw);

	printf("\n[-]    MASTER_SEED_4:        len: %u  ",h[MASTER_SEED].len);
	print_hex_buf(  h[MASTER_SEED].data, h[MASTER_SEED].len);

	printf("\n[-]    TRANSFORM_SEED_5:     len: %u  ",h[TRANSFORM_SEED].len);
	print_hex_buf(  h[TRANSFORM_SEED].data, h[TRANSFORM_SEED].len);

	printf("\n[-]    TRANSFORM_ROUNDS_6:     %016llx\n",			(unsigned long long) h[6].qw);

	printf("\n[-]    ENCRYPTION_IV_7:   len: %u ",h[ENCRYPTION_IV].len);
	print_hex_buf(  h[ENCRYPTION_IV].data, h[ENCRYPTION_IV].len);

	printf("\n[-]    PROTECTED_STREAM_KEY_8: len: %u ", h[8].len);
	print_hex_buf(  h[8].data, h[8].len);

	printf("\n[-]    STREAM_START_BYTES_9:  len: %u  ",h[9].len);
	print_hex_buf(  h[9].data, h[9].len);


	uint16_t header_len = 0;
	for (int i=0;i<HEADER_ID_COUNT;i++) {
		if(0<h[i].len){
    		header_len +=h[i].len+2+1;
		}
	}
	printf("\n[*] header_len: %u  ",header_len);

	return;
}

#if 0
static bool parse_header(FILE *kdbx_fd) {
	bool res = true;
	uint8_t id = 0;
	uint16_t data_len = 0;
	size_t numItems = 0;

	numItems = fread(&id, sizeof(uint8_t), 1, kdbx_fd);
	if (1 == numItems) {
		printf("\nID 0x%02X %s ", id, IDtoNameTUT[id]);
	}

	numItems = fread(&data_len, sizeof(uint16_t), 1, kdbx_fd);
	if (1 == numItems) {
		printf("\ndata_len 0x%04X %d byte ", data_len, data_len);
		uint8_t *dataPtr = malloc(data_len + 1);
		if (dataPtr) {
			numItems = fread(dataPtr, data_len, 1, kdbx_fd);
			if (1 == numItems) {
				switch (id) {
				case ID_END_OF_HEADER:
					if (4 == data_len) {
						res = false;

					}
					break;

				case ID_ENCRYPTION_IV:
					memset(keePassHeader.encryption_iv, 0x00,
							sizeof(keePassHeader.encryption_iv));
					if (data_len < sizeof(keePassHeader.encryption_iv)) {
						memcpy(keePassHeader.encryption_iv, dataPtr, data_len);
						printf("\n got encryption_iv   ");
					} else {
						printf("\n ID_ENCRYPTION_IV size %u expected %u",
								data_len,
								(unsigned int) sizeof(keePassHeader.encryption_iv));
					}
					break;

				case ID_MASTER_SEED:
					if (data_len == sizeof(keePassHeader.master_seed)) {
						memcpy(keePassHeader.master_seed, dataPtr, data_len);
						printf("\n got master seed ");
					}
					break;
				case ID_TRANSFORM_SEED:
					memcpy(keePassHeader.transform_seed, dataPtr,
							sizeof(keePassHeader.transform_seed));
					break;
				case ID_TRANSFORM_ROUNDS:

					memcpy(&keePassHeader.transform_rounds, dataPtr,
							sizeof(keePassHeader.transform_rounds));
					printf("\n transform_rounds %lu ",
							keePassHeader.transform_rounds);
					break;

				case ID_STREAM_START_BYTES:
					if (32 == data_len) {
						printf("\n got stream_start_bytes ");
						memcpy(&keePassHeader.stream_start_bytes, dataPtr,
								sizeof(keePassHeader.stream_start_bytes));
					} else {
						printf("\n stream_start_bytes error ");
					}

					break;
				}
			}
			printf("\n data_len ");
			print_mem(dataPtr, data_len);
			free(dataPtr);
		}
		printf("\n numItems %u items ", (unsigned int) numItems);

	} else {
		printf("\n Unable to alloc %d byte ", data_len);
	}
	return res;
}


bool parse_kee_pass_file_heaser(FILE *kdbx_fd) {
	size_t numItems = 0;
	bool res = false;
	uint32_t baseSignature = 0u;
	uint32_t versionSignature = 0u;
	uint32_t fileVersion = 0u;

	numItems = fread(&baseSignature, SIG_SIZE, 1, kdbx_fd);
	if (1 == numItems) {
		printf("\nbaseSignature 0x%X", baseSignature);
	}
	numItems = fread(&versionSignature, SIG_VER_SIZE, 1, kdbx_fd);
	if (1 == numItems) {
		printf("\nversionSignature 0x%X", versionSignature);
	}

	if (KEEPASS_2X_POST_RELEASE == versionSignature) {
		numItems = fread(&fileVersion, 4, 1, kdbx_fd);
		if (1 == numItems) {
			printf("\nfileVersion 0x%08X", fileVersion);
		}
		res = true;
		uint16_t cnt = 0;
		do {
			cnt++;
			res = parse_header(kdbx_fd);
		} while (true == res);
		printf("\nID cnt %u", cnt);

	}
	return res;
}
#endif

size_t kdbx_header_read(FILE *kdbx_fd, kdbx_header_t *header) {
	size_t ret = 0;
	if (header == NULL)
		return 0;

	ret = fread(header, sizeof(kdbx_header_t), 1, kdbx_fd);
	if (ret != 1)
		printf("[!] fread(kdbx_header) failed.");

	return ret;
}

void kdbx_header_dump(kdbx_header_t h) {
	printf("\n");
	printf("[*] kdbx header:\n");
	printf("[-]    file magic:          %08x\n", h.magic);
	printf("[-]    file identifier:     %08x\n", h.identifier);
	printf("[-]    file minor version:  %04x\n", (h.minor_version));
	printf("[-]    file major version:  %04x\n", (h.major_version));
	return;
}

size_t kdbx_payload_read (FILE *kdbx_fd, kdbx_payload_t *p) {
	size_t ret = 0;
	uint64_t off_start = 0;
	uint64_t off_end = 0;

	if (p == NULL)
		return 0;

	p->encrypted = NULL;
	p->decrypted = NULL;
	off_start = ftell(kdbx_fd);
	//printf("\n off_start [%lu]", off_start);
	//printf("\n errno [%u]", errno);
	if (0xFFFFFFFF == off_start) {
		printf("\n errno [%u]", errno);
	}
	p->offset_start = off_start;
	//printf("\n Offset start [%u] %x byte", p->offset_start, p->offset_start);

	fseek(kdbx_fd, 0, SEEK_END);
	off_end = ftell(kdbx_fd);
	//printf("\n Offset end [%u] %x byte", off_end, off_end);

	p->len = (off_end - off_start);
	fseek(kdbx_fd, off_start, SEEK_SET); //? -1

	if (0 < p->len) {
		p->encrypted = (uint8_t*) malloc(p->len);
		if (p->encrypted == NULL) {
			printf("[!] malloc(payload->encrypted) failed.");
			return 0;
		} else {
			printf("\n Allocated %u byte",(unsigned int) p->len);
			memset(p->encrypted, 0, p->len);
			ret = fread(p->encrypted, p->len, 1, kdbx_fd);
			if (ret != 1) {
				printf("[!] fread(payload) failed.");
			}
			p->decrypted = (uint8_t*) malloc(p->len);
			if(p->decrypted){
				memcpy(p->decrypted,p->encrypted,p->len);
			}
		}
	} else {
		printf ("\n payload len zero");
	}

	return ret;
}

void kdbx_payload_dump(kdbx_payload_t p) {
	printf("\n");
	printf("[*] kdbx payload:\n");
	printf("[-]    payload offset:      0x%llx  %u\n",
			(unsigned long long) p.offset_start, (unsigned int) p.offset_start);
	printf("[-]    payload len:         0x%x %u\n", (unsigned int) p.len,
			(unsigned int) p.len);

	return;
}


bool header_arr_to_bin(kdbx_database_t *db) {
	bool res = false;
	if(8==db->kdbxheader[TRANSFORM_ROUNDS].len) {
		res= true;
	    memcpy(&keePassHeader.transform_rounds, db->kdbxheader[TRANSFORM_ROUNDS].data ,sizeof(keePassHeader.transform_rounds));
	} else {
		printf("Error");
	}
	return res;
}

bool kdbx_decrypt_payload(kdbx_database_t *db, char *pass_word, uint8_t *key_hash) {
	bool res = false;
	uint8_t pass[1024] = { 0 };
	uint8_t hash[32] = { 0 };
	uint8_t composite_key[32] = { 0 };
	uint8_t composite_data[64] = { 0 };
	uint8_t transform_key[32] = { 0 };
	uint8_t transform_key_sh[32] = { 0 };
	uint8_t master_key[32] = { 0 };
	uint8_t masterkey_input[64] ={0};
	size_t masterkey_input_len = 0;

	//header_arr_to_bin(db);
	kdbx_header_entry_t *hdr = &db->kdbxheader[0];
	memset(pass, 0, sizeof(pass));
	memset(composite_data, 0, 64);
	memset(transform_key, 0, 32);
	memset(transform_key_sh, 0, 32);

	memset(master_key, 0, 32);

	memcpy(pass, pass_word, strlen(pass_word));
	printf("[+] trying: [%s]\r", pass);

	//sha256_hash(hash, (uint8_t *) pass, 32);
	sha256_hash(hash, (uint8_t *) pass, strlen(pass_word));
	printf("\n[*] pass_hash \n");
	print_hex_buf (hash, 32);

	sha256_hash(composite_key, hash, sizeof(hash));

	printf("\n[*] composite_key \n");
	print_hex_buf (composite_key, 32);

	memcpy(transform_key, composite_key, sizeof(transform_key));
	printf("\n[*] transform_key ");
	print_hex_buf (transform_key, 32);

	aes_transformkey(db->kdbxheader, transform_key, sizeof(transform_key));

    sha256_hash(transform_key_sh, transform_key, sizeof(transform_key));


    printf("\n[*] Master seed len %u", hdr[MASTER_SEED].len); // 32

    masterkey_input_len = sizeof(transform_key) + hdr[MASTER_SEED].len;
    printf("\n[*] Master in key len  %u", (unsigned int) masterkey_input_len); // ?

    if(masterkey_input_len < hdr[MASTER_SEED].len) {
      // should never happen, as masterkey len is (currently) 16 bit
        puts("[!] masterkey_input len integer overflow.");
        return 0;
    }
    //concat
    memcpy(masterkey_input, hdr[MASTER_SEED].data, hdr[MASTER_SEED].len);
    memcpy(masterkey_input+hdr[MASTER_SEED].len, transform_key_sh, sizeof(transform_key_sh));

    sha256_hash(master_key, masterkey_input, masterkey_input_len);
	printf("\n[*] master_key \n");
	print_hex_buf (master_key, 32);

    res = aes_decrypt_check(hdr, master_key, &db->payload);

	return res;
}

bool kdbx_payload_crack(kdbx_database_t *db, char *password) {
	bool res = false;
	printf("[*] kdbx crack:\n");
	int len = strlen(password);
	if (0 < len) {
		password[len] = 0x00;
	}
	res = kdbx_decrypt_payload(db, password, NULL);
	if (res) {
		printf("[*] decryption successful with password \n");
		//printf("[*] decryption successful with password [%s]\n", password);
		res = true;
	} else {
		printf("[!] decryption error with password\n");
		//printf("[!] decryption error with password [%s]\n", password);
	}
	return res;
}

bool try_to_open_kdbx_file(char *file_name, char *pass_word) {
	bool res = false;
	FILE *kdbx_fd = NULL;
	kdbx_fd = fopen(file_name, "rb");
	if (NULL != kdbx_fd) {
		//printf("\n the file has been opened");
		/*Read signature*/
		size_t ret;
		kdbx_database_t kdbx_db ;
		memset(&kdbx_db, 0, sizeof(kdbx_db));

		kdbx_header_read (kdbx_fd, &kdbx_db.fileheader);
		kdbx_header_dump (kdbx_db.fileheader);

		kdbx_headerentries_read (kdbx_fd, kdbx_db.kdbxheader);
		kdbx_headerentries_dump (kdbx_db.kdbxheader);

		ret = kdbx_payload_read (kdbx_fd, &kdbx_db.payload);
		if (0 < ret) {
			kdbx_payload_dump (kdbx_db.payload);
	     	kdbx_payload_crack (&kdbx_db, pass_word);
		} else {
			printf("\n Lack payload");
		}

		fclose(kdbx_fd);

		return true;
#if 0
		parse_kee_pass_file_heaser(kdbx_fd);

		unsigned char pass_word_hash[32] = { 0 };
		unsigned char pass_word_32[32] = { 0 };
		memcpy(pass_word_32, pass_word, strlen(pass_word));

		sha256_hash(pass_word_hash, (unsigned char*) pass_word_32, 32);
		printf("\n pass len: [%s]\n", pass_word);
		printf("\n sha256 of key pass len: %u\n", strlen(pass_word));
		print_mem(pass_word_hash, 32);

		unsigned char composite_key[32] = { 0 };

		sha256_hash(composite_key, (unsigned char*) pass_word_hash, 32);
		printf("\n composite key\n");
		print_mem(composite_key, 32);
///
		unsigned char transformed_key[32];
		//unsigned char composite_key_sha256[32];

		memcpy(transformed_key, composite_key, 32);
		//unsigned char final_master_key;
		struct AES_ctx ctx;
		AES_init_ctx(&ctx, keePassHeader.transform_seed);
		printf("\n transform_rounds %lu ", keePassHeader.transform_rounds);
		for (uint64_t i = 0; i < keePassHeader.transform_rounds; i++) {
			AES_ECB_encrypt(&ctx, transformed_key);
		}

		unsigned char transformed_key_sha256[32] = { 0 };
		sha256_hash(transformed_key_sha256, transformed_key, 32);
		uint8_t key_64byte[64];
		concatenate_array(key_64byte, 64, keePassHeader.master_seed, 32,
				transformed_key_sha256, 32);  //????

		uint8_t master_key[32];
		sha256_hash(master_key, (unsigned char*) key_64byte,
				sizeof(key_64byte));
		printf("\n master key\n");
		print_mem(master_key, 32);

		AES_init_ctx(&ctx, master_key);
		AES_init_ctx_iv(&ctx, master_key, keePassHeader.encryption_iv);
		uint8_t db_block[32];

		size_t numItems;
		numItems = fread(db_block, 16, 1, kdbx_fd);
		if (1 == numItems) {
			AES_CBC_decrypt_buffer(&ctx, db_block, 16);
			printf("\n data base block\n");
			print_mem(db_block, 16);
		}
		int cmp_res;
		cmp_res = memcmp(db_block, keePassHeader.stream_start_bytes, 16);
		if (0 != cmp_res) {
			printf("\n Errror Master key wrong or fault in keepass data\n");
			printf("\n data base 1 block\n");
			print_mem(db_block, 16);
			printf("\n stream_start_bytes\n ");
			print_mem(keePassHeader.stream_start_bytes, 16);
		} else {
			printf("\n 1st block Fine \n");
		}

		fclose(kdbx_fd);
		res = true;
#endif
	} else {
		printf("\n Unable to open the file");
	}
	return res;
}

