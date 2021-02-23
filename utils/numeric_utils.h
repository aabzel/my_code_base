/*****************************************************************************
 * @file    numeric_utils.h
 * 
 * @details This include for compatibility with new MCAL based libraries
 *****************************************************************************/

#ifndef NUMERIC_UTILS_H_
#define NUMERIC_UTILS_H_

#ifdef HAS_MCAL
#error "This file can't be used in MCAL builds"
#else
#include "rx_utils.h"

#define max8u  rx_max8u 
#define min8u  rx_min8u 
#define max16u rx_max16u 
#define min16u rx_min16u 
#define max32u rx_max32u 
#define min32u rx_min32u 
#define max8   rx_max8 
#define min8   rx_min8 
#define max16  rx_max16 
#define min16  rx_min16 
#define max32  rx_max32 
#define min32  rx_min32 
#endif

#endif
