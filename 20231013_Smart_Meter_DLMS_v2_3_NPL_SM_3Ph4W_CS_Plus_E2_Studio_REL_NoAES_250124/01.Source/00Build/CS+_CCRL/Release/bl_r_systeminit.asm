#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_systeminit.c
#@   -cpu=S3
#@   -cref=Release\bl_r_systeminit.cref
#@   -o Release\bl_r_systeminit.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_777ec430ac11483f85509861617a8d8at5qavg3l.g50
#@  compiled at Thu Jan 25 17:42:59 2024

	.EXTERN _RAM_ISR_Table
	.PUBLIC _R_Systeminit
	.EXTERN _MCU_Delay
	.EXTERN _R_CGC_Create
	.EXTERN _R_PORT_StopCreate
	.EXTERN _R_SAU1_Create
	.EXTERN _R_TAU0_Create
	.PUBLIC _R_DefaultInterrupHandler
	.PUBLIC _R_RAM_InterruptVectorInit
	.EXTERN _R_CSI30_Interrupt
	.EXTERN _r_uart2_interrupt_send
	.EXTERN _r_uart2_interrupt_receive
	.EXTERN _r_tau0_channel0_interrupt
	.EXTERN _r_lvd_vddinterrupt
	.PUBLIC _bl_hdwinit

	.SECTION .text,TEXT
	.TYPE _R_Systeminit,function,.LFE1-_R_Systeminit
_R_Systeminit:
	.STACK _R_Systeminit = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 85
	clrb !0x0077
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 86
	movw ax, #0xC350
	call !_MCU_Delay
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 88
	call !_R_CGC_Create
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 89
	call !_R_PORT_StopCreate
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 90
	call !_R_SAU1_Create
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 91
	call !_R_TAU0_Create
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 97
	mov !0x0078, #0x80
	ret
.LFE1:
	.TYPE _R_DefaultInterrupHandler,function,.LFE2-_R_DefaultInterrupHandler
_R_DefaultInterrupHandler:
	.STACK _R_DefaultInterrupHandler = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 106
	ret
.LFE2:
	.TYPE _R_RAM_InterruptVectorInit,function,.LFE3-_R_RAM_InterruptVectorInit
_R_RAM_InterruptVectorInit:
	.STACK _R_RAM_InterruptVectorInit = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 117
	clrb a
.BB@LABEL@3_1:	; bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 0
	mov d, a
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 124
	mov x, #0x02
	mulu x
	movw bc, ax
	movw ax, #LOWW(_R_DefaultInterrupHandler)
	movw LOWW(_RAM_ISR_Table)[bc], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 122
	inc d
	mov a, d
	cmp a, #0x80
	bnz $.BB@LABEL@3_1
.BB@LABEL@3_2:	; bb11
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 128
	movw ax, #LOWW(_R_CSI30_Interrupt)
	movw !LOWW(_RAM_ISR_Table+0x00080), ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 129
	movw ax, #LOWW(_r_uart2_interrupt_send)
	movw !LOWW(_RAM_ISR_Table+0x00028), ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 130
	movw ax, #LOWW(_r_uart2_interrupt_receive)
	movw !LOWW(_RAM_ISR_Table+0x0002C), ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 131
	movw ax, #LOWW(_r_tau0_channel0_interrupt)
	movw !LOWW(_RAM_ISR_Table+0x00058), ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 132
	movw ax, #LOWW(_r_lvd_vddinterrupt)
	movw !LOWW(_RAM_ISR_Table+0x000D8), ax
	ret
.LFE3:
	.TYPE _bl_hdwinit,function,.LFE4-_bl_hdwinit
_bl_hdwinit:
	.STACK _bl_hdwinit = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 145
	di
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 146
	call !_R_Systeminit
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 147
	call !_R_RAM_InterruptVectorInit
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_systeminit.c", 148
	ei
	ret
.LFE4:
