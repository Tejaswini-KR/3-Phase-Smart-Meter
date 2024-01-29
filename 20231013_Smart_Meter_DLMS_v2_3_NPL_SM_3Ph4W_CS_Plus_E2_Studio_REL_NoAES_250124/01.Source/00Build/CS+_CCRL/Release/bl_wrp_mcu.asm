#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\wrapper\bl_wrp_mcu.c
#@   -cpu=S3
#@   -cref=Release\bl_wrp_mcu.cref
#@   -o Release\bl_wrp_mcu.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_c97847fce6a84601957b0e78634265255teiu00c.ded
#@  compiled at Thu Jan 25 17:43:01 2024

	.PUBLIC _MCU_Delay

	.SECTION .text,TEXT
	.TYPE _MCU_Delay,function,.LFE1-_MCU_Delay
_MCU_Delay:
	.STACK _MCU_Delay = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 72
	cmp0 !0x00A8
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 74
	bnz $.BB@LABEL@1_4
.BB@LABEL@1_1:	; if_then_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 84
	clrw bc
	cmpw ax, bc
	bz $.BB@LABEL@1_11
.BB@LABEL@1_2:	; if_break_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 0
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 94
	addw ax, #0xFFFF
	bz $.BB@LABEL@1_11
.BB@LABEL@1_3:	; bb12
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 98
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 99
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 100
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 101
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 102
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 103
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 104
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 105
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 106
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 107
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 108
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 109
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 110
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 111
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 112
	nop
	br $.BB@LABEL@1_2
.BB@LABEL@1_4:	; if_else_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 180
	cmp !0x00A8, #0x02
	bnz $.BB@LABEL@1_11
.BB@LABEL@1_5:	; if_then_bb26
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 190
	cmpw ax, #0x0005
	bnc $.BB@LABEL@1_7
.BB@LABEL@1_6:	; if_then_bb26.if_break_bb35_crit_edge
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 0
	clrw ax
	br $.BB@LABEL@1_8
.BB@LABEL@1_7:	; if_else_bb32
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 196
	shrw ax, 0x01
	decw ax
.BB@LABEL@1_8:	; if_break_bb35
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 201
	incw ax
.BB@LABEL@1_9:	; if_break_bb35
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 0
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 204
	addw ax, #0xFFFF
	bz $.BB@LABEL@1_11
.BB@LABEL@1_10:	; bb38
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 208
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 209
	nop
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 210
	nop
	br $.BB@LABEL@1_9
.BB@LABEL@1_11:	; return
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_mcu.c", 277
	ret
.LFE1:
