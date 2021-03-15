#ifndef SYS_H
#define SYS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define RAM_SIZE (8*1024)
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)

#define ROM_SIZE (128*1024)
#define ROM_START 0x08000000
#define ROM_END (ROM_START + ROM_SIZE)



void print_vector_table (void);
void print_sysinfo (void);
void Error_Handler (void);
bool find_addr_by_val(uint16_t byte_num, uint32_t val, uint32_t start_addr, uint32_t end_addr);

#ifdef __cplusplus
}
#endif

#endif // SYS_H
