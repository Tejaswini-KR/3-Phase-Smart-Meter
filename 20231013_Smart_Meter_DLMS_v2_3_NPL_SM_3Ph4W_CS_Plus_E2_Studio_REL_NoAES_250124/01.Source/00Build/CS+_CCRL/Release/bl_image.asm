#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\core\bl_image.c
#@   -cpu=S3
#@   -cref=Release\bl_image.cref
#@   -o Release\bl_image.obj
#@   -dev=C:\Program Files (x86)\Renesas Electronics\CS+\CC\Device\RL78\Devicefile\DR5F10NPL.DVF
#@   -g
#@   -g_line
#@   -goptimize
#@   -I ..\..\shared\metrology\metrologylibrary\headers
#@   -I ..\..\shared\metrology\filter\headers
#@   -I ..\..\shared\Flash\fsl\CCRL\incrl78
#@   -I ..\..\shared\Flash\fsl\CCRL\librl78
#@   -I ..\..\shared\dlms2\hash
#@   -I ..\..\shared\dlms2\hash\CCRL
#@   -I ..\..\shared\dlms2\gcm
#@   -I ..\..\shared\dlms2\dlmslibrary\header
#@   -I ..\..\shared\dlms2\aes
#@   -I ..\..\shared\Compiler\CCRL
#@   -I ..\..\shared\Bootloader\header
#@   -I ..\..\bootloader\wrapper
#@   -I ..\..\bootloader\startup
#@   -I ..\..\bootloader\driver
#@   -I ..\..\bootloader\display
#@   -I ..\..\bootloader\core
#@   -I ..\..\bootloader\serialflash
#@   -I ..\..\bootloader\compiler\CCRL
#@   -memory_model=small
#@   -far_rom
#@   -signed_char
#@   -merge_string
#@   -asm_path=Release
#@   -c
#@   -MAKEUD=Release
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_e76ca8fe7b9543b89cbb80ead2b8cf6clgdgl3js.l5q
#@  compiled at Mon Jun 10 17:42:21 2024

	.EXTERN _g_bl_info
	.EXTERN _g_bl_startup_status
	.PUBLIC _g_bl_image_read_ROM_buffer
	.PUBLIC _BL_IMAGE_EraseImageInSerialFlash
	.EXTERN _BL_SFL_DeviceErase64KB
	.EXTERN _BL_OPERATION_SetConfirmCode
	.EXTERN _BL_SFL_DeviceRead
	.EXTERN _BL_FLASH_WriteBlock
	.EXTERN _BL_OPERATION_ClearConfirmCode
	.PUBLIC _BL_IMAGE_EraseUserAppInROM
	.EXTERN _BL_OPERATION_ReadConfirmCode
	.EXTERN _BL_FLASH_EraseBlock
	.PUBLIC _BL_IMAGE_Processing
	.EXTERN _BL_LCD_DisplayBackingUp
	.EXTERN _BL_LCD_DisplayUpdating
	.EXTERN _BL_IMAGE_TransferUserAppToROM
	.EXTERN _BL_LCD_DisplayRestoring
	.PUBLIC _BL_IMAGE_EraseImageData
	.PUBLIC _BL_IMAGE_Erase
	.EXTERN _BL_SFL_DeviceErase4KB
	.PUBLIC _BL_IMAGE_Write
	.PUBLIC _BL_IMAGE_BackupUserApp
	.EXTERN _BL_SFL_DeviceWrite
	.EXTERN _BL_memcpy_nn
	.EXTERN _BL_memcpy_nf

	.SECTION .text,TEXT
	.TYPE _BL_IMAGE_EraseImageInSerialFlash,function,.LFE1-_BL_IMAGE_EraseImageInSerialFlash
_BL_IMAGE_EraseImageInSerialFlash:
	.STACK _BL_IMAGE_EraseImageInSerialFlash = 8
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 98
	subw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 104
	cmp0 a
	clrw ax
	movw bc, ax
	bz $.BB@LABEL@1_2
.BB@LABEL@1_1:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw bc, #0x0008
	movw ax, bc
.BB@LABEL@1_2:	; if_else_bb
	movw [sp+0x02], ax
	mov [sp+0x00], #0x08
.BB@LABEL@1_3:	; bb
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 117
	call !_BL_SFL_DeviceErase64KB
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 119
	mov 0xFFFAB, #0xAC
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 114
	dec a
	mov [sp+0x00], a
	movw ax, [sp+0x02]
	incw ax
	movw bc, ax
	movw [sp+0x02], ax
	bnz $.BB@LABEL@1_3
.BB@LABEL@1_4:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 121
	addw sp, #0x04
	ret
.LFE1:
	.TYPE _BL_IMAGE_EraseUserAppInROM,function,.LFE2-_BL_IMAGE_EraseUserAppInROM
_BL_IMAGE_EraseUserAppInROM:
	.STACK _BL_IMAGE_EraseUserAppInROM = 6
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 267
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 273
	mov a, #0x07
	call !_BL_OPERATION_SetConfirmCode
	movw ax, #0x0008
	movw [sp+0x00], ax
.BB@LABEL@2_1:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 281
	call !_BL_FLASH_EraseBlock
	cmp0 a
	bnz $.BB@LABEL@2_7
.BB@LABEL@2_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 285
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 279
	incw ax
	movw [sp+0x00], ax
	cmpw ax, #0x001F
	bc $.BB@LABEL@2_1
.BB@LABEL@2_3:	; if_break_bb.bb18_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw ax, #0x001F
	movw [sp+0x00], ax
.BB@LABEL@2_4:	; bb18
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 293
	call !_BL_FLASH_EraseBlock
	cmp0 a
	bnz $.BB@LABEL@2_7
.BB@LABEL@2_5:	; if_break_bb27
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 297
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 291
	incw ax
	movw [sp+0x00], ax
	cmpw ax, #0x01D3
	bc $.BB@LABEL@2_4
.BB@LABEL@2_6:	; bb36
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 301
	mov a, #0x07
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 303
	clrb a
	pop bc
	ret
.BB@LABEL@2_7:	; bb38
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 304
	oneb a
	pop bc
	ret
.LFE2:
	.TYPE _BL_IMAGE_Processing,function,.LFE3-_BL_IMAGE_Processing
_BL_IMAGE_Processing:
	.STACK _BL_IMAGE_Processing = 12
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 312
	subw sp, #0x06
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 198
	movw ax, !0x2000
	cmpw ax, #0xFFFF
	sknz
.BB@LABEL@3_1:	; if_then_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 203
	mov !LOWW(_g_bl_info), #0x05
.BB@LABEL@3_2:	; if_break_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 208
	cmp !LOWW(_g_bl_startup_status+0x00003), #0x02
	bnc $.BB@LABEL@3_4
.BB@LABEL@3_3:	; if_else_bb55.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	clrb !LOWW(_g_bl_info)
	br $.BB@LABEL@3_12
.BB@LABEL@3_4:	; if_then_bb18.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 212
	mov a, #0x02
	call !_BL_OPERATION_ReadConfirmCode
	dec a
	bnz $.BB@LABEL@3_6
.BB@LABEL@3_5:	; if_else_bb53.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 248
	mov a, #0x02
	call !_BL_OPERATION_ClearConfirmCode
	br $.BB@LABEL@3_3
.BB@LABEL@3_6:	; if_then_bb24.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 215
	mov a, !LOWW(_g_bl_info)
	cmp a, #0x05
	bnc $.BB@LABEL@3_8
.BB@LABEL@3_7:	; if_then_bb30.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 218
	inc a
	mov !LOWW(_g_bl_info), a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 221
	mov a, #0x03
	call !_BL_OPERATION_ClearConfirmCode
	br $.BB@LABEL@3_12
.BB@LABEL@3_8:	; if_else_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 226
	mov a, !LOWW(_g_bl_info+0x00001)
	cmp0 a
	bnz $.BB@LABEL@3_10
.BB@LABEL@3_9:	; if_then_bb38.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 228
	inc a
	mov !LOWW(_g_bl_info+0x00001), a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 231
	mov a, #0x05
	br $.BB@LABEL@3_11
.BB@LABEL@3_10:	; if_else_bb41.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 236
	oneb a
.BB@LABEL@3_11:	; if_else_bb41.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	call !_BL_OPERATION_SetConfirmCode
	mov a, #0x09
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 242
	or a, !LOWW(_g_bl_startup_status)
	clr1 a.1
	mov !LOWW(_g_bl_startup_status), a
.BB@LABEL@3_12:	; BL_IMAGE_CheckUserApp@1.exit
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 320
	mov a, #0x04
	call !_BL_OPERATION_ReadConfirmCode
	dec a
	bnz $.BB@LABEL@3_14
.BB@LABEL@3_13:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 326
	call !_BL_LCD_DisplayBackingUp
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 329
	mov a, #0x06
	call !_BL_OPERATION_SetConfirmCode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 332
	call !_BL_IMAGE_BackupUserApp
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 335
	mov a, #0x06
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 338
	mov a, #0x04
	call !_BL_OPERATION_ClearConfirmCode
.BB@LABEL@3_14:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 344
	mov a, #0x03
	call !_BL_OPERATION_ReadConfirmCode
	dec a
	bnz $.BB@LABEL@3_26
.BB@LABEL@3_15:	; if_then_bb11
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 350
	call !_BL_LCD_DisplayUpdating
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 353
	movw !LOWW(_g_bl_info), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 357
	movw !LOWW(_g_bl_startup_status), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 358
	set1 !LOWW(_g_bl_startup_status).0
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 364
	oneb a
	call !_BL_IMAGE_TransferUserAppToROM
	mov x, a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 366
	cmp0 a
	bnz $.BB@LABEL@3_20
.BB@LABEL@3_16:	; if_then_bb21
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 369
	mov a, #0x02
	call !_BL_IMAGE_TransferUserAppToROM
	mov x, a
	mov a, #0xFD
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 372
	and a, !LOWW(_g_bl_startup_status)
	cmp0 x
	bnz $.BB@LABEL@3_18
.BB@LABEL@3_17:	; if_then_bb28
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 375
	set1 a.1
	br $.BB@LABEL@3_24
.BB@LABEL@3_18:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 380
	clr1 !LOWW(_g_bl_startup_status).1
	mov a, x
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 382
	add a, #0xFE
	cmp a, #0x02
	bnc $.BB@LABEL@3_25
.BB@LABEL@3_19:	; if_then_bb50
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 386
	mov a, #0x05
	call !_BL_OPERATION_SetConfirmCode
	mov a, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 388
	or a, !LOWW(_g_bl_startup_status)
	br $.BB@LABEL@3_24
.BB@LABEL@3_20:	; if_else_bb57
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, #0xFD
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 399
	and a, !LOWW(_g_bl_startup_status)
	mov b, a
	mov !LOWW(_g_bl_startup_status), a
	mov a, x
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 401
	cmp a, #0x01
	bnz $.BB@LABEL@3_22
.BB@LABEL@3_21:	; if_then_bb66
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, b
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 403
	set1 a.5
	br $.BB@LABEL@3_24
.BB@LABEL@3_22:	; if_else_bb71
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 405
	cmp a, #0x04
	bnz $.BB@LABEL@3_25
.BB@LABEL@3_23:	; if_then_bb77
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, b
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 407
	set1 a.4
.BB@LABEL@3_24:	; if_break_bb84.PartialDrain
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov !LOWW(_g_bl_startup_status), a
.BB@LABEL@3_25:	; if_break_bb84
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 415
	mov a, #0x03
	call !_BL_OPERATION_ClearConfirmCode
.BB@LABEL@3_26:	; if_break_bb85
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 421
	mov a, #0x05
	call !_BL_OPERATION_ReadConfirmCode
	dec a
	.bnz !.BB@LABEL@3_50
.BB@LABEL@3_27:	; if_then_bb91
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 427
	call !_BL_LCD_DisplayRestoring
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 139
	mov a, #0x09
	call !_BL_OPERATION_SetConfirmCode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 142
	call !_BL_IMAGE_EraseUserAppInROM
	dec a
	bnz $.BB@LABEL@3_31
.BB@LABEL@3_28:	; if_then_bb91.BL_IMAGE_RestoreUserApp@1.exit_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov [sp+0x02], #0x02
.BB@LABEL@3_29:	; BL_IMAGE_RestoreUserApp@1.exit
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 184
	mov a, #0x09
	call !_BL_OPERATION_ClearConfirmCode
	mov a, [sp+0x02]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 431
	cmp0 a
	.bnz !.BB@LABEL@3_48
.BB@LABEL@3_30:	; if_else_bb99
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 440
	movw !LOWW(_g_bl_info), ax
	br !.BB@LABEL@3_49
.BB@LABEL@3_31:	; if_then_bb91.bb.i_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	clrw ax
	movw [sp+0x02], ax
	mov a, #0x20
	movw [sp+0x00], ax
.BB@LABEL@3_32:	; bb.i
	movw ax, #0x0400
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 153
	push ax
	movw ax, [sp+0x04]
	movw bc, ax
	movw ax, [sp+0x02]
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x02]
	movw bc, ax
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 156
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_FLASH_WriteBlock
	cmp0 a
	bnz $.BB@LABEL@3_39
.BB@LABEL@3_33:	; if_break_bb22.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 163
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 151
	addw ax, #0x0400
	movw [sp+0x00], ax
	movw ax, [sp+0x02]
	sknc
.BB@LABEL@3_34:	; if_break_bb22.i
	incw ax
.BB@LABEL@3_35:	; if_break_bb22.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw [sp+0x02], ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 151
	clrw bc
	cmpw ax, bc
	movw ax, [sp+0x00]
	sknz
.BB@LABEL@3_36:	; if_break_bb22.i
	cmpw ax, #0x7C00
.BB@LABEL@3_37:	; if_break_bb22.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	bc $.BB@LABEL@3_32
.BB@LABEL@3_38:	; if_break_bb22.i.bb46.i.thread_crit_edge
	clrb a
	mov [sp+0x02], a
	br $.BB@LABEL@3_40
.BB@LABEL@3_39:	; bb.i.bb46.i.thread_crit_edge
	mov [sp+0x02], #0x03
.BB@LABEL@3_40:	; bb46.i.thread
	clrw ax
	movw [sp+0x04], ax
	mov a, #0x7C
	movw [sp+0x00], ax
.BB@LABEL@3_41:	; bb32.i
	movw ax, #0x0400
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 169
	push ax
	movw ax, [sp+0x06]
	movw bc, ax
	movw ax, [sp+0x02]
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x04]
	movw bc, ax
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 172
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_FLASH_WriteBlock
	cmp0 a
	bnz $.BB@LABEL@3_47
.BB@LABEL@3_42:	; if_break_bb43.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 179
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 167
	addw ax, #0x0400
	movw [sp+0x00], ax
	movw ax, [sp+0x04]
	sknc
.BB@LABEL@3_43:	; if_break_bb43.i
	incw ax
.BB@LABEL@3_44:	; if_break_bb43.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw [sp+0x04], ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 167
	cmpw ax, #0x0007
	movw ax, [sp+0x00]
	sknz
.BB@LABEL@3_45:	; if_break_bb43.i
	cmpw ax, #0x4C00
.BB@LABEL@3_46:	; if_break_bb43.i
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	bc $.BB@LABEL@3_41
	br !.BB@LABEL@3_29
.BB@LABEL@3_47:	; BL_IMAGE_RestoreUserApp@1.exit.thread
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 184
	mov a, #0x09
	call !_BL_OPERATION_ClearConfirmCode
.BB@LABEL@3_48:	; if_then_bb98
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 436
	oneb a
	call !_BL_OPERATION_SetConfirmCode
.BB@LABEL@3_49:	; if_break_bb100
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 445
	mov a, #0x05
	addw sp, #0x06
	br !_BL_OPERATION_ClearConfirmCode
.BB@LABEL@3_50:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 449
	addw sp, #0x06
	ret
.LFE3:
	.SECTION BLShareTx_n,TEXT
	.TYPE _BL_IMAGE_EraseImageData,function,.LFE4-_BL_IMAGE_EraseImageData
_BL_IMAGE_EraseImageData:
	.STACK _BL_IMAGE_EraseImageData = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 468
	oneb a
	call !_BL_IMAGE_EraseImageInSerialFlash
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 472
	clrb a
	ret
.LFE4:
	.TYPE _BL_IMAGE_Erase,function,.LFE5-_BL_IMAGE_Erase
_BL_IMAGE_Erase:
	.STACK _BL_IMAGE_Erase = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 484
	movw de, ax
	movw ax, bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 487
	cmpw ax, #0x0008
	bc $.BB@LABEL@5_2
.BB@LABEL@5_1:	; bb16
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 499
	oneb a
	ret
.BB@LABEL@5_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 492
	addw ax, #0x0008
	movw bc, ax
	movw ax, de
	call !_BL_SFL_DeviceErase4KB
	cmp0 a
	clrb a
	skz
.BB@LABEL@5_3:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, #0x02
.BB@LABEL@5_4:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 492
	ret
.LFE5:
	.TYPE _BL_IMAGE_Write,function,.LFE6-_BL_IMAGE_Write
_BL_IMAGE_Write:
	.STACK _BL_IMAGE_Write = 10
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 512
	push de
	push hl
	movw hl, ax
	movw ax, [sp+0x08]
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 515
	or a, x
	bz $.BB@LABEL@6_10
.BB@LABEL@6_1:	; entry
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw ax, [sp+0x02]
	or a, x
	bz $.BB@LABEL@6_10
.BB@LABEL@6_2:	; bb10
	movw ax, de
	addw ax, hl
	movw [sp+0x00], ax
	movw ax, bc
	sknc
.BB@LABEL@6_3:	; bb10
	incw ax
.BB@LABEL@6_4:	; bb10
	cmpw ax, #0x0008
	movw ax, [sp+0x00]
	sknz
.BB@LABEL@6_5:	; bb10
	cmpw ax, #0x0001
.BB@LABEL@6_6:	; bb10
	bnc $.BB@LABEL@6_10
.BB@LABEL@6_7:	; if_break_bb26
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 527
	push de
	movw ax, [sp+0x04]
	movw de, ax
	movw ax, bc
	addw ax, #0x0008
	movw bc, ax
	movw ax, hl
	call !_BL_SFL_DeviceWrite
	pop bc
	cmp0 a
	clrb a
	skz
.BB@LABEL@6_8:	; if_break_bb26
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, #0x02
.BB@LABEL@6_9:	; if_break_bb26
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 534
	ret
.BB@LABEL@6_10:	; bb40
	oneb a
	br $.BB@LABEL@6_9
.LFE6:
	.TYPE _BL_IMAGE_BackupUserApp,function,.LFE7-_BL_IMAGE_BackupUserApp
_BL_IMAGE_BackupUserApp:
	.STACK _BL_IMAGE_BackupUserApp = 146
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 545
	subw sp, #0x8C
	clrb a
	mov [sp+0x03], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 553
	clrb a
	call !_BL_IMAGE_EraseImageInSerialFlash
	movw ax, #0x2000
	movw [sp+0x04], ax
	mov [sp+0x02], #0xB8
.BB@LABEL@7_1:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw ax, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 558
	movw bc, ax
	movw ax, sp
	addw ax, #0x000C
	movw [sp+0x00], ax
	movw de, #0x0080
	call !_BL_memcpy_nn
	movw ax, #0x0080
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 559
	push ax
	clrb x
	movw [sp+0x0A], ax
	movw ax, [sp+0x02]
	movw de, ax
	movw ax, [sp+0x06]
	clrw bc
	call !_BL_SFL_DeviceWrite
	mov x, a
	pop bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 562
	mov 0xFFFAB, #0xAC
	mov a, [sp+0x03]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 559
	or x, a
	mov a, x
	mov [sp+0x03], a
	movw ax, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 556
	addw ax, #0x0080
	movw [sp+0x04], ax
	mov a, [sp+0x02]
	dec a
	mov [sp+0x02], a
	bnz $.BB@LABEL@7_1
.BB@LABEL@7_2:	; bb.bb22_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw ax, #0x7C00
	movw [sp+0x04], ax
	movw ax, #0x0DA0
	movw [sp+0x0A], ax
	movw ax, [sp+0x04]
	movw [sp+0x06], ax
.BB@LABEL@7_3:	; bb22
	movw ax, #0x0080
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 568
	push ax
	mov a, [sp+0x0A]
	mov c, a
	movw ax, [sp+0x06]
	movw de, ax
	movw ax, sp
	addw ax, #0x000E
	movw [sp+0x02], ax
	call !_BL_memcpy_nf
	pop ax
	movw ax, #0x0080
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 569
	push ax
	movw ax, [sp+0x02]
	movw de, ax
	movw ax, [sp+0x0A]
	movw bc, ax
	movw ax, [sp+0x08]
	call !_BL_SFL_DeviceWrite
	mov x, a
	pop bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 572
	mov 0xFFFAB, #0xAC
	mov a, [sp+0x03]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 569
	or x, a
	mov a, x
	mov [sp+0x03], a
	movw ax, [sp+0x06]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 566
	addw ax, #0x0080
	movw [sp+0x06], ax
	movw ax, [sp+0x08]
	sknc
.BB@LABEL@7_4:	; bb22
	incw ax
.BB@LABEL@7_5:	; bb22
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	movw [sp+0x08], ax
	movw ax, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 566
	addw ax, #0x0080
	movw [sp+0x04], ax
	movw ax, [sp+0x0A]
	addw ax, #0xFFFF
	movw [sp+0x0A], ax
	bnz $.BB@LABEL@7_3
.BB@LABEL@7_6:	; bb46
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 0
	mov a, [sp+0x03]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_image.c", 576
	addw sp, #0x8C
	ret
.LFE7:
	.SECTION .bss,BSS
	.TYPE _g_bl_image_read_ROM_buffer,object,1024
_g_bl_image_read_ROM_buffer:
	.DS (1024)
