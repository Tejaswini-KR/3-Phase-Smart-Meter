#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\core\bl_flash.c
#@   -cpu=S3
#@   -cref=Release\bl_flash.cref
#@   -o Release\bl_flash.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_c9486d3930d548ad9e934245a3cb98b80covjqv4.wwd
#@  compiled at Thu Jan 25 17:43:00 2024

	.PUBLIC _g_fsl_descriptor
	.PUBLIC _BL_FLASH_EraseBlock
	.EXTERN _FSL_Init
	.EXTERN _FSL_Open
	.EXTERN _FSL_PrepareFunctions
	.EXTERN _FSL_Erase
	.EXTERN _FSL_Close
	.PUBLIC _BL_FLASH_WriteBlock
	.EXTERN _FSL_BlankCheck
	.EXTERN _FSL_Write
	.EXTERN _FSL_IVerify

	.SECTION .text,TEXT
	.TYPE _BL_FLASH_EraseBlock,function,.LFE1-_BL_FLASH_EraseBlock
_BL_FLASH_EraseBlock:
	.STACK _BL_FLASH_EraseBlock = 6
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 75
	push ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 80
	di
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 83
	movw de, #LOWW(_g_fsl_descriptor)
	mov a, #LOW(HIGHW(_g_fsl_descriptor))
	call !!_FSL_Init
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 84
	call !!_FSL_Open
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 85
	call !!_FSL_PrepareFunctions
	movw ax, [sp+0x00]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 88
	call !!_FSL_Erase
	cmp0 a
	clrb a
	skz
.BB@LABEL@1_1:	; if_then_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	oneb a
.BB@LABEL@1_2:	; if_then_bb
	mov [sp+0x00], a
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 94
	call !!_FSL_Close
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 97
	ei
	mov a, [sp+0x00]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 101
	pop bc
	ret
.LFE1:
	.TYPE _BL_FLASH_WriteBlock,function,.LFE2-_BL_FLASH_WriteBlock
_BL_FLASH_WriteBlock:
	.STACK _BL_FLASH_WriteBlock = 22
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 111
	push de
	push bc
	push ax
	subw sp, #0x0C
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 119
	di
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 122
	movw de, #LOWW(_g_fsl_descriptor)
	mov a, #LOW(HIGHW(_g_fsl_descriptor))
	call !!_FSL_Init
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 123
	call !!_FSL_Open
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 124
	call !!_FSL_PrepareFunctions
	movw ax, [sp+0x0E]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 127
	shlw ax, 0x06
	movw bc, ax
	movw ax, [sp+0x0C]
	shrw ax, 0x0A
	addw ax, bc
	movw [sp+0x02], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 130
	call !!_FSL_BlankCheck
	cmp0 a
	clrb a
	skz
.BB@LABEL@2_1:	; if_then_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	oneb a
.BB@LABEL@2_2:	; if_then_bb
	mov [sp+0x01], a
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 136
	mov [sp+0x0A], #0x40
	mov [sp+0x00], #0x04
.BB@LABEL@2_3:	; bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	movw ax, [sp+0x10]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 141
	movw [sp+0x04], ax
	movw ax, [sp+0x0E]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 142
	movw [sp+0x08], ax
	movw ax, [sp+0x0C]
	movw [sp+0x06], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 143
	movw ax, sp
	addw ax, #0x0004
	call !!_FSL_Write
	movw ax, [sp+0x0C]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 139
	addw ax, #0x0100
	movw [sp+0x0C], ax
	movw ax, [sp+0x0E]
	sknc
.BB@LABEL@2_4:	; bb
	incw ax
.BB@LABEL@2_5:	; bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	movw [sp+0x0E], ax
	movw ax, [sp+0x10]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 139
	add a, #0x01
	movw [sp+0x10], ax
	mov a, [sp+0x00]
	dec a
	mov [sp+0x00], a
	bnz $.BB@LABEL@2_3
.BB@LABEL@2_6:	; bb35
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	movw ax, [sp+0x02]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 150
	call !!_FSL_IVerify
	cmp0 a
	bz $.BB@LABEL@2_8
.BB@LABEL@2_7:	; if_then_bb42
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 0
	oneb a
	mov [sp+0x01], a
.BB@LABEL@2_8:	; if_break_bb43
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 156
	call !!_FSL_Close
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 159
	ei
	mov a, [sp+0x01]
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_flash.c", 163
	addw sp, #0x12
	ret
.LFE2:
	.SECTION .constf,CONSTF
	.TYPE _g_fsl_descriptor,object,3
_g_fsl_descriptor:
	.DS (1)
	.DB 0x18
	.DB 0x01
