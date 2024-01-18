#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_cgc.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_cgc.cref
#@   -o Release\bl_r_cg_cgc.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_05f4e2f20a4e4cc586a6ff92a54a6afey0azjkaj.dap
#@  compiled at Tue Jan 02 10:50:35 2024

	.PUBLIC _R_CGC_Create
	.PUBLIC _BL_R_CGC_OperateAtClock24M
	.PUBLIC _BL_R_CGC_OperateAtClock12M
	.PUBLIC _BL_R_CGC_OperateAtClock6M
	.PUBLIC _BL_R_CGC_UpdateCPUClock

	.SECTION .text,TEXT
	.TYPE _R_CGC_Create,function,.LFE1-_R_CGC_Create
_R_CGC_Create:
	.STACK _R_CGC_Create = 6
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 58
	push hl
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 62
	mov 0xFFFA0, #0x51
	movw hl, #0x00FC
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 65
	set1 [hl].0
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 66
	mov !0x0384, #0x12
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 68
	clr1 !0x0386.6
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 69
	clr1 0xFFFA1.6
.BB@LABEL@1_1:	; entry
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 0
	movw [sp+0x00], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 73
	movw ax, [sp+0x00]
	cmpw ax, #0x0169
	bnc $.BB@LABEL@1_3
.BB@LABEL@1_2:	; bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 75
	nop
	movw ax, [sp+0x00]
	incw ax
	br $.BB@LABEL@1_1
.BB@LABEL@1_3:	; bb7
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 0
	movw hl, #0xFFA4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 79
	clr1 0xFFFA1.0
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 82
	clr1 [hl].6
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 85
	clr1 [hl].4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 88
	clr1 [hl].0
	pop ax
	ret
.LFE1:
	.TYPE _BL_R_CGC_OperateAtClock24M,function,.LFE2-_BL_R_CGC_OperateAtClock24M
_BL_R_CGC_OperateAtClock24M:
	.STACK _BL_R_CGC_OperateAtClock24M = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 102
	clrb !0x00A8
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 103
	br $_BL_R_CGC_UpdateCPUClock
.LFE2:
	.TYPE _BL_R_CGC_OperateAtClock12M,function,.LFE3-_BL_R_CGC_OperateAtClock12M
_BL_R_CGC_OperateAtClock12M:
	.STACK _BL_R_CGC_OperateAtClock12M = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 116
	oneb !0x00A8
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 117
	br $_BL_R_CGC_UpdateCPUClock
.LFE3:
	.TYPE _BL_R_CGC_OperateAtClock6M,function,.LFE4-_BL_R_CGC_OperateAtClock6M
_BL_R_CGC_OperateAtClock6M:
	.STACK _BL_R_CGC_OperateAtClock6M = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 130
	mov !0x00A8, #0x02
.LFE4:
	.TYPE _BL_R_CGC_UpdateCPUClock,function,.LFE5-_BL_R_CGC_UpdateCPUClock
_BL_R_CGC_UpdateCPUClock:
	.STACK _BL_R_CGC_UpdateCPUClock = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_cgc.c", 137
	mov a, 0xFFFA1
	mov a, 0xFFFA4
	mov a, 0xFFFA4
	mov a, 0xFFFA4
	ret
.LFE5:
