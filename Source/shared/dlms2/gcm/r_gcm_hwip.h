/***********************************************************************************************************************
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name	   : r_gcm_hwip.h
* Description  : Header file of GCM Hardware IP Library.
***********************************************************************************************************************/
#ifndef __r_gcm_hwip_h__
#define __r_gcm_hwip_h__

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#ifdef __CCRL__
#include "r_stdint.h"
#elif __ICCRL78__
#include <stdint.h>
#endif /* __CCRL__ */
#include "r_dlms_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define GCM_OK				(0)
#define GCM_NG				(-1)

#define GCM_AESKEY_LEN_128	(0u)
#define GCM_AESKEY_LEN_192	(1u)
#define GCM_AESKEY_LEN_256	(2u)

#define GCM_BLOCK_SIZE		(16)
#define GCM_WORK_SIZE_L		(11)			/* 11 lword (44 byte) */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
/* interface function */
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
int32_t R_gcm_Init(uint16_t key_len);
void R_gcm_Close(void);
int32_t R_gcm_enc(uint8_t *plain, uint8_t *cipher, uint32_t data_len, uint8_t *key, uint8_t *atag, uint32_t atag_len, uint8_t *iv, uint32_t iv_len, uint8_t *aad, uint32_t aad_len);
int32_t R_gcm_dec(uint8_t *cipher, uint8_t *plain, uint32_t data_len, uint8_t *key, uint8_t *atag, uint32_t atag_len, uint8_t *iv, uint32_t iv_len, uint8_t *aad, uint32_t aad_len);
#else
#define R_gcm_Init(a) 									(0)
#define R_gcm_Close() 									;
#define R_gcm_enc(a, b, c, d, x, e, f, g, h, i) 		(0)
#define R_gcm_dec(a, b, c, d, x, e, f, g, h, i) 		(0)
#endif//defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)

#endif
