/*****************************************************************************
 * @file    macro_utils.h
 * 
 * @details This include for compatibility with new MCAL based libraries
 *****************************************************************************/

#ifndef MACRO_UTILS_H_
#define MACRO_UTILS_H_

#ifdef HAS_MCAL
#error "This file can't be used in MCAL builds"
#else
#include "rx_utils.h"

#define ARRAY_SIZE      RX_ARRAY_SIZE
#endif

#endif
