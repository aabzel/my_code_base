/*****************************************************************************
 * @file    pointer_utils.h
 *
 * @attention Violates #1833-D: MISRA 2012 Rule 11.5: conversion from type
 * void * not allowed.
 *
 * @attention Violates #1834-D: MISRA 2012 Rule 11.4: cast from number
 * to pointer not allowed.
 *
 * @attention Violates #1752-D: MISRA 2012 Rule 18.4: pointer arithmetic
 * not allowed.
 *
 * @attention Violates #2041-D: MISRA 2012 Rule 11.6: cast from type "uint32_t"
 * to type "const void *" not allowed.
 *
 * @attention Violates #1836-D: MISRA 2012 Rule 11.8: cast drops "const".
 *****************************************************************************/

#ifndef POINTER_UTILS_H
#define POINTER_UTILS_H

/*****************************************************************************
 * @brief   Converts 32-bit value to 32-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  32-bit pointer.
 *****************************************************************************/
static inline const uint32_t *u32_to_cu32p (uint32_t value);

/*****************************************************************************
 * @brief   Converts 32-bit value to const void pointer.
 * @param   value 32-bit value to convert.
 * @return  const void pointer.
 *****************************************************************************/
static inline const void *u32_to_cvp (uint32_t value);

/*****************************************************************************
 * @brief   Converts 8-bit pointer to 32-bit value.
 * @param   value 8-bit pointer.
 * @return  32-bit value.
 *****************************************************************************/
static inline uint32_t u8p_to_u32 (uint8_t *value);

/*****************************************************************************
 * @brief   Converts 32-bit value to 8-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  8-bit pointer.
 *****************************************************************************/
static inline uint8_t *u32_to_u8p (uint32_t value);

/*****************************************************************************
 * @brief   Converts 32-bit value to constant 8-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  constant 8-bit pointer.
 *****************************************************************************/
static inline const uint8_t *u32_to_cu8p (uint32_t value);

/*****************************************************************************
 * @brief   Converts 32-bit value to volatile 8-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  volatile 8-bit pointer.
 *****************************************************************************/
static inline volatile uint8_t *u32_to_vu8p (uint32_t value);

/*****************************************************************************
 * @brief   Converts 32-bit value to constant 16-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  constant 16-bit pointer.
 *****************************************************************************/
static inline const uint16_t *u32_to_cu16p (uint32_t value);

/*****************************************************************************
 * @brief   Converts 32-bit value to volatile 16-bit pointer.
 * @param   value 32-bit value to convert.
 * @return  volatile 16-bit pointer.
 *****************************************************************************/
static inline volatile uint16_t *u32_to_vu16p (uint32_t value);

/*****************************************************************************
 * @brief   Converts constant char pointer to 32-bit value.
 * @param   value constant char pointer.
 * @return  32-bit value.
 *****************************************************************************/
static inline uint32_t ccp_to_u32 (const char *value);

/*****************************************************************************
 * @brief   Converts 32-bit value to char pointer.
 * @param   value 32-bit value to convert.
 * @return  char pointer.
 *****************************************************************************/
static inline const char *u32_to_ccp (uint32_t value);

/*****************************************************************************
 * @brief   Converts void pointer to uint8_t pointer.
 * @param   ptr pointer to convert.
 * @return  uint8_t pointer.
 *****************************************************************************/
static inline uint8_t *vp_2_u8p (void *ptr);

/*****************************************************************************
 * @brief   Converts void pointer to uint32_t pointer.
 * @param   ptr pointer to convert.
 * @return  uint32_t pointer.
 *****************************************************************************/
static inline uint32_t *vp_2_u32p (void *ptr);
/*****************************************************************************
 * @brief   Converts void pointer to uint32_t pointer.
 * @param   ptr pointer to convert.
 * @return  uint32_t pointer.
 *****************************************************************************/
static inline uint32_t vp_2_u32 (void *ptr);

/*****************************************************************************
 * @brief   Converts uint8_t pointer to void pointer.
 * @param   ptr pointer to convert.
 * @return  void pointer.
 *****************************************************************************/
static inline void *u8p_2_vp (uint8_t *ptr);

/*****************************************************************************
 * @brief   Converts const uint8_t pointer to void pointer.
 * @param   ptr pointer to convert.
 * @return  void pointer.
 *****************************************************************************/
static inline void *cu8p_2_vp (const uint8_t *ptr);
/*****************************************************************************
 * @brief   Converts const uint8_t pointer to const uint32_t pointer.
 * @param   ptr pointer to convert.
 * @return  const uint32_t pointer.
 *****************************************************************************/
static inline const uint32_t *cu8p_2_cu32p (const uint8_t *ptr);

/*****************************************************************************
 * @brief   Converts constant void pointer to constant uint8_t pointer.
 * @param   ptr pointer to convert.
 * @return  constant uint8_t pointer.
 *****************************************************************************/
static inline const uint8_t *cvp_2_cu8p (const void *ptr);

/*****************************************************************************
 * @brief   Converts constant void pointer to 32-bit value.
 * @param   ptr pointer to convert.
 * @return  32-bit value.
 *****************************************************************************/
static inline uint32_t cvp_2_u32 (const void *ptr);

/*****************************************************************************
 * @brief   Adds value to uint8_t pointer.
 * @param   ptr pointer.
 * @param   value value to add.
 * @return  uint8_t pointer.
 *****************************************************************************/
static inline uint8_t *u8p_add (uint8_t *ptr, uint32_t value);

/*****************************************************************************
 * @brief   Adds value to const uint8_t pointer.
 * @param   ptr pointer.
 * @param   value value to add.
 * @return  const uint8_t pointer.
 *****************************************************************************/
static inline const uint8_t *cu8p_add (const uint8_t *ptr, uint32_t value);

#ifdef __ghs__
#pragma ghs nowarning 1833
#pragma ghs nowarning 1834
#pragma ghs nowarning 1752
#pragma ghs nowarning 2041
#pragma ghs nowarning 1836
#endif

static inline const uint32_t *u32_to_cu32p (uint32_t value) { return (const uint32_t *)value; }

static inline const void *u32_to_cvp (uint32_t value) { return (const void *)value; }

static inline uint32_t u8p_to_u32 (uint8_t *value) { return (uint32_t)value; }

static inline uint8_t *u32_to_u8p (uint32_t value) { return (uint8_t *)value; }

static inline volatile uint8_t *u32_to_vu8p (uint32_t value) { return (volatile uint8_t *)value; }

static inline const uint8_t *u32_to_cu8p (uint32_t value) { return (const uint8_t *)value; }

static inline const uint16_t *u32_to_cu16p (uint32_t value) { return (const uint16_t *)value; }

static inline volatile uint16_t *u32_to_vu16p (uint32_t value) { return (volatile uint16_t *)value; }

static inline uint32_t ccp_to_u32 (const char *value) { return (uint32_t)value; }

static inline const char *u32_to_ccp (uint32_t value) { return (const char *)value; }

static inline uint8_t *vp_2_u8p (void *ptr) { return (uint8_t *)ptr; }

static inline uint32_t *vp_2_u32p (void *ptr) { return (uint32_t *)ptr; }

static inline uint32_t vp_2_u32 (void *ptr) { return (uint32_t)ptr; }

static inline void *u8p_2_vp (uint8_t *ptr) { return (void *)ptr; }

static inline void *cu8p_2_vp (const uint8_t *ptr) { return (void *)ptr; }

static inline const uint8_t *cvp_2_cu8p (const void *ptr) { return (const uint8_t *)ptr; }

static inline const uint32_t *cu8p_2_cu32p (const uint8_t *ptr) { return (const uint32_t *)ptr; }

static inline uint32_t cvp_2_u32 (const void *ptr) { return (uint32_t)ptr; }

static inline const uint8_t *cu8p_add (const uint8_t *ptr, uint32_t value) { return ptr + value; }

static inline uint8_t *u8p_add (uint8_t *ptr, uint32_t value) { return ptr + value; }

#ifdef __ghs__
#pragma ghs endnowarning 1836
#pragma ghs endnowarning 2041
#pragma ghs endnowarning 1752
#pragma ghs endnowarning 1834
#pragma ghs endnowarning 1833
#endif

#endif /* POINTER_UTILS_H */
