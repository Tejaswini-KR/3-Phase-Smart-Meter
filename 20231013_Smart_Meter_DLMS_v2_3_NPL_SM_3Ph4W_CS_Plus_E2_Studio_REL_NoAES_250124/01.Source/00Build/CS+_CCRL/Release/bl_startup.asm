#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\startup\bl_startup.c
#@   -cpu=S3
#@   -cref=Release\bl_startup.cref
#@   -o Release\bl_startup.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_175b1f5c348849fdb15b284c7a665ea0kp11mqgf.ggs
#@  compiled at Mon Aug 12 12:54:20 2024

	.EXTERN _g_bl_info
	.EXTERN _g_bl_startup_status
	.PUBLIC _BL_Startup
	.EXTERN __COM_memset_f
	.EXTERN _R_PORT_Create
	.EXTERN _BL_SFL_Init
	.EXTERN _BL_RECOVERY_Init
	.PUBLIC _BL_StopPeripherals
	.EXTERN _R_UART2_Stop
	.EXTERN _R_TAU0_Channel0_Stop

	.SECTION .text,TEXT
	.TYPE _BL_Startup,function,.LFE1-_BL_Startup
_BL_Startup:
	.STACK _BL_Startup = 8
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 71
	movw de, #0x00F9
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 75
	mov a, [de]
	mov !LOWW(_g_bl_startup_status+0x00002), a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 78
	mov a, [de]
	cmp0 a
	bnz $.BB@LABEL@1_2
.BB@LABEL@1_1:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 0
	movw ax, #0x0014
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 81
	push ax
	movw de, #LOWW(_g_bl_info)
	clrw bc
	mov a, #0x0F
	call !!__COM_memset_f
	pop ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 84
	oneb !0x00F9
.BB@LABEL@1_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 88
	mov a, 0xFFFA8
	mov !LOWW(_g_bl_startup_status+0x00003), a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 90
	mov a, !0x0332
	mov1 CY, a.6
	clrb a
	bc $.BB@LABEL@1_5
.BB@LABEL@1_3:	; if_then_bb22
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 92
	call !_R_PORT_Create
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 98
	call !_BL_SFL_Init
	mov [sp+0x00], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 101
	cmp0 a
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_4:	; if_then_bb30
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 103
	call !_BL_RECOVERY_Init
	mov a, [sp+0x00]
.BB@LABEL@1_5:	; if_break_bb32
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 0
	pop bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 112
	ret
.LFE1:
	.TYPE _BL_StopPeripherals,function,.LFE2-_BL_StopPeripherals
_BL_StopPeripherals:
	.STACK _BL_StopPeripherals = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 125
	call !_R_UART2_Stop
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/startup/bl_startup.c", 126
	br !_R_TAU0_Channel0_Stop
.LFE2:
