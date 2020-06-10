#ifndef TIC12400_BIT_OFFSETS_H
#define TIC12400_BIT_OFFSETS_H

typedef enum {
    REG_RESERVED_00H = 0x00U, /* Reserved Register address*/
    REG_DEVICE_ID = 0x01U, /* Device ID Register */
    REG_INT_STAT = 0x02U, /* Interrupt Status Register */
    REG_CRC = 0x03U, /* CRC Result Register */
    REG_IN_STAT_MISC = 0x04U, /* Miscellaneous Status Register */
    REG_IN_STAT_COMP = 0x05U, /* Comparator Status Register */
    REG_IN_STAT_ADC0 = 0x06U, /* ADC Status Register */
    REG_IN_STAT_ADC1 = 0x07U, /* ADC Status Register */
    REG_IN_STAT_MATRIX0 = 0x08U, /* Matrix Atatus Register 0 */
    REG_IN_STAT_MATRIX1 = 0x09U, /* Matrix Atatus Register 1 */
    REG_ANA_STAT0 = 0x0aU, /* ADC Raw Code Register 0 */
    REG_ANA_STAT1 = 0x0bU, /* ADC Raw Code Register 1 */
    REG_ANA_STAT2 = 0x0cU, /* ADC Raw Code Register 2 */
    REG_ANA_STAT3 = 0x0dU, /* ADC Raw Code Register 3 */
    REG_ANA_STAT4 = 0x0eU, /* ADC Raw Code Register 4 */
    REG_ANA_STAT5 = 0x0fU, /* ADC Raw Code Register 5 */
    REG_ANA_STAT6 = 0x10U, /* ADC Raw Code Register 6 */
    REG_ANA_STAT7 = 0x11U, /* ADC Raw Code Register 7 */
    REG_ANA_STAT8 = 0x12U, /* ADC Raw Code Register 8 */
    REG_ANA_STAT9 = 0x13U, /* ADC Raw Code Register 9 */
    REG_ANA_STAT10 = 0x14U, /* ADC Raw Code Register 10 */
    REG_ANA_STAT11 = 0x15U, /* ADC Raw Code Register 11 */
    REG_ANA_STAT12 = 0x16U, /* ADC Raw Code Register 12 */
    REG_RESERVED_17H = 0x17U, /* Reserved Register address*/
    REG_RESERVED_18H = 0x18U, /* Reserved Register address*/
    REG_RESERVED_19H = 0x19U, /* Reserved Register address*/
    REG_CONFIG = 0x1aU, /* Device Global Configuration Register */
    REG_IN_EN = 0x1BU, /* Input Enable Register */
    REG_CS_SELECT = 0x1cU, /* Current Source/Sink Selection Register */
    REG_WC_CFG0 = 0x1dU, /* Wetting Current Configuration Register 0 */
    REG_WC_CFG1 = 0x1eU, /* Wetting Current Configuration Register 1 */
    REG_CCP_CFG0 = 0x1fU, /* Clean Current Polling Register 0 */
    REG_CCP_CFG1 = 0x20U, /* Clean Current Polling Register 1 */
    REG_THRES_COMP = 0x21U, /* Comparator Threshold Control Register */
    REG_INT_EN_COMP1 = 0x22U, /* Comparator Input Interrupt Generation Control Register 1 */
    REG_INT_EN_COMP2 = 0x23U, /* Comparator Input Interrupt Generation Control Register 2 */
    REG_INT_EN_CFG0 = 0x24U, /* Global Interrupt Generation Control Register */
    REG_INT_EN_CFG1 = 0x25U, /* ADC Input Interrupt Generation Control Register 1 */
    REG_INT_EN_CFG2 = 0x26U, /* ADC Input Interrupt Generation Control Register 2 */
    REG_INT_EN_CFG3 = 0x27U, /* ADC Input Interrupt Generation Control Register 3 */
    REG_INT_EN_CFG4 = 0x28U, /* ADC Input Interrupt Generation Control Register 4 */
    REG_THRES_CFG0 = 0x29U, /* ADC Threshold Control Register 0 */
    REG_THRES_CFG1 = 0x2aU, /* ADC Threshold Control Register 1 */
    REG_THRES_CFG2 = 0x2bU, /* ADC Threshold Control Register 2 */
    REG_THRES_CFG3 = 0x2cU, /* ADC Threshold Control Register 3 */
    REG_THRES_CFG4 = 0x2dU, /* ADC Threshold Control Register 4 */
    REG_THRESMAP_CFG0 = 0x2eU, /* ADC Threshold Mapping Register 0 */
    REG_THRESMAP_CFG1 = 0x2fU, /* ADC Threshold Mapping Register 1 */
    REG_THRESMAP_CFG2 = 0x30U, /* ADC Threshold Mapping Register 2 */
    REG_MATRIX = 0x31U, /* Matrix Setting Register */
    REG_MODE = 0x32U, /* Mode Setting Register */

    REG_AMOUNT = 0x33U
} tic12400_reg_t;

#define VS_RATIO_23  (1<<23)
#define ADC_DIAG_T_22 (1<<22)
#define WET_D_IN3_EN_21 (1<<21)
#define WET_D_IN2_EN_20 (1<<20)
#define WET_D_IN1_EN_19 (1<<19)
#define WET_D_IN0_EN_18 (1<<18)
#define VS_MEAS_EN_17 (1<<17)
#define TW_CUR_DIS_CSI_16 (1<<16)
#define TW_CUR_DIS_CSO_13 (1<<13)
#define INT_CONFIG_12 (1<<12)
#define TRIGGER_11 (1<<11)
#define POLL_EN_10 (1<<10)
#define CRC_T_9 (1<<9)
#define RESET_0 (1<<0)


#define SSC_3 (1<<3)
#define SPI_FAIL_1 (1<<1)
#define POR_0 (1<<0)


#define AUTO_SCALE_DIS_CSI_22 (1<<22)
#define AUTO_SCALE_DIS_CSO_21 (1<<21)

#endif /* TIC12400_BIT_OFFSETS_H */
