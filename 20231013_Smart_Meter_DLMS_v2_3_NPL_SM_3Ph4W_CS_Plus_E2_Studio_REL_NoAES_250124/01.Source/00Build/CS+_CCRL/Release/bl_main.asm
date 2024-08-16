#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\bl_main.c
#@   -cpu=S3
#@   -cref=Release\bl_main.cref
#@   -o Release\bl_main.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_a7d2a87b3e734f4f8d59adbdd6242c1fvnxepyay.l00
#@  compiled at Mon Aug 12 12:54:18 2024

	.EXTERN _g_bl_info
	.PUBLIC _bl_main
	.EXTERN _BL_Startup
	.EXTERN _BL_OPERATION_ReadConfirmCode
	.EXTERN _BL_StopPeripherals

	.SECTION .text,TEXT
	.TYPE _bl_main,function,.LFE1-_bl_main
_bl_main:
	.STACK _bl_main = 6
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 65
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 70
	call !_BL_Startup
	cmp0 a
	sknz
.BB@LABEL@1_1:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 72
	mov 0xFFFAB, #0x00
.BB@LABEL@1_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 76
	mov a, #0x03
	call !_BL_OPERATION_ReadConfirmCode
	cmp0 a
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_3:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 0
	mov a, #0x04
	call !_BL_OPERATION_ReadConfirmCode
	cmp0 a
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_4:	; bb19
	cmp0 !LOWW(_g_bl_info+0x00001)
	bz $.BB@LABEL@1_7
.BB@LABEL@1_5:	; if_then_bb32
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 80
	mov a, !0x0332
	bf a.6, $.BB@LABEL@1_7
.BB@LABEL@1_6:	; if_then_bb42
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 0
	movw de, #0x00F0
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 86
	mov [de+0x00], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 87
	mov [de+0x0A], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 88
	mov [de+0x0C], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 89
	call !_BL_StopPeripherals
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 90
	nop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 91
	nop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 92
	nop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 93
	stop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 94
	nop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 95
	nop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 96
	nop
.BB@LABEL@1_7:	; if_break_bb44
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 105
	mov a, !0x0332
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 115
	call !_BL_StopPeripherals
	movw ax, #0x2000
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 118
	movw [sp+0x00], ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 120
	movw ax, [sp+0x00]
	movw de, ax
	movw ax, [de]
	cmpw ax, #0xFFFF
	bnz $.BB@LABEL@1_9
.BB@LABEL@1_8:	; if_else_bb65
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 128
	mov 0xFFFAB, #0x00
	pop ax
	ret
.BB@LABEL@1_9:	; if_then_bb63
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/bl_main.c", 123
	mov cs, #0x00
	movw ax, [sp+0x00]
	movw hl, ax
	call hl
	pop ax
	ret
.LFE1:
