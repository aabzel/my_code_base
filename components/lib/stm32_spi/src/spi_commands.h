#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_spi_send (int32_t argc, char *argv[]);
bool cmd_spi_receive (int32_t argc, char *argv[]);
bool cmd_spi_diag (int32_t argc, char *argv[]);

#define SPI_COMMANDS                                                                                                   \
    SHELL_CMD ("spi_diag", "spid", cmd_spi_diag, "SPI diag"),                                                          \
        SHELL_CMD ("spi_send", "spis", cmd_spi_send, "SPI send"),                                                      \
        SHELL_CMD ("spi_receive", "spir", cmd_spi_receive, "SPI receive"),

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMANDS_H */
