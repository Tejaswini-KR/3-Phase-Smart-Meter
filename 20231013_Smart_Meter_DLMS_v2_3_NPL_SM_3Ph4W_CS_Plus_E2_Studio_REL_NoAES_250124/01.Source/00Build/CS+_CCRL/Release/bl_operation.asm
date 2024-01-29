#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\core\bl_operation.c
#@   -cpu=S3
#@   -cref=Release\bl_operation.cref
#@   -o Release\bl_operation.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_2e73b912b5b949498b01df31396ca4a5yvpiavqs.2cg
#@  compiled at Thu Jan 25 17:43:00 2024

	.PUBLIC _g_bl_startup_status
	.PUBLIC _g_bl_info
	.PUBLIC _BL_OPERATION_ReadConfirmCode
	.PUBLIC _BL_OPERATION_ClearConfirmCode
	.PUBLIC _BL_OPERATION_SetConfirmCode
	.PUBLIC _BL_OPERATION_GetStartupStatus
	.PUBLIC _BL_OPERATION_GetProperties
	.PUBLIC _BL_OPERATION_RequestRecoveryMode
	.PUBLIC _BL_OPERATION_RequestUserReset
	.PUBLIC _BL_OPERATION_RequestImageActivation
	.PUBLIC _BL_OPERATION_RequestImageBackup
	.PUBLIC _BL_OPERATION_InformStartupOK
	.PUBLIC _BL_OPERATION_AcknowledgeImageUpdateStatus
	.PUBLIC _BL_OPERATION_UpdateOperatingClock
	.EXTERN _BL_R_CGC_UpdateCPUClock

	.SECTION .text,TEXT
	.TYPE _BL_OPERATION_ReadConfirmCode,function,.LFE1-_BL_OPERATION_ReadConfirmCode
_BL_OPERATION_ReadConfirmCode:
	.STACK _BL_OPERATION_ReadConfirmCode = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 96
	movw hl, #0x00F5
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 105
	sarw ax, 8+0x00000
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 102
	set1 [hl].7
	movw bc, ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 105
	shlw bc, 0x01
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 107
	movw ax, LOWW(_g_bl_info)[bc]
	cmpw ax, #0xA579
	oneb a
	skz
.BB@LABEL@1_1:	; bb10
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 0
	clrb a
.BB@LABEL@1_2:	; bb11
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 110
	clr1 [hl].0
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 111
	clr1 [hl].7
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 114
	ret
.LFE1:
	.TYPE _BL_OPERATION_ClearConfirmCode,function,.LFE2-_BL_OPERATION_ClearConfirmCode
_BL_OPERATION_ClearConfirmCode:
	.STACK _BL_OPERATION_ClearConfirmCode = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 122
	sarw ax, 8+0x00000
	movw bc, ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 125
	shlw bc, 0x01
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 126
	movw LOWW(_g_bl_info)[bc], ax
	ret
.LFE2:
	.TYPE _BL_OPERATION_SetConfirmCode,function,.LFE3-_BL_OPERATION_SetConfirmCode
_BL_OPERATION_SetConfirmCode:
	.STACK _BL_OPERATION_SetConfirmCode = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 135
	sarw ax, 8+0x00000
	movw bc, ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 138
	shlw bc, 0x01
	movw ax, #0xA579
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 139
	movw LOWW(_g_bl_info)[bc], ax
	ret
.LFE3:
	.SECTION BLShareTx_n,TEXT
	.TYPE _BL_OPERATION_GetStartupStatus,function,.LFE4-_BL_OPERATION_GetStartupStatus
_BL_OPERATION_GetStartupStatus:
	.STACK _BL_OPERATION_GetStartupStatus = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 157
	clrw bc
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 160
	cmpw ax, bc
	sknz
.BB@LABEL@4_1:	; return
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 167
	ret
.BB@LABEL@4_2:	; if_break_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 0
	movw de, ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 166
	incw ax
	incw ax
	movw hl, ax
	movw ax, !LOWW(_g_bl_startup_status+0x00002)
	movw [hl], ax
	movw ax, !LOWW(_g_bl_startup_status)
	movw [de], ax
	ret
.LFE4:
	.TYPE _BL_OPERATION_GetProperties,function,.LFE5-_BL_OPERATION_GetProperties
_BL_OPERATION_GetProperties:
	.STACK _BL_OPERATION_GetProperties = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 178
	clrw bc
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 181
	cmpw ax, bc
	sknz
.BB@LABEL@5_1:	; return
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 196
	ret
.BB@LABEL@5_2:	; if_break_bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 0
	movw de, ax
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 187
	movw [de+0x02], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 188
	movw [de+0x06], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 189
	movw [de+0x0A], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 192
	movw [de+0x10], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 194
	movw [de+0x18], ax
	mov a, #0x20
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 187
	movw [de], ax
	movw ax, #0x7BFF
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 188
	movw [de+0x04], ax
	incw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 189
	movw [de+0x08], ax
	movw ax, #0x0007
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 190
	movw [de+0x0E], ax
	movw ax, #0x4BFF
	movw [de+0x0C], ax
	movw ax, #0x0008
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 192
	movw [de+0x12], ax
	mov x, #0x0F
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 193
	movw [de+0x16], ax
	clrw ax
	decw ax
	movw [de+0x14], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 195
	movw [de+0x1C], ax
	movw ax, #0x0010
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 194
	movw [de+0x1A], ax
	mov x, #0x1F
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 195
	movw [de+0x1E], ax
	ret
.LFE5:
	.TYPE _BL_OPERATION_RequestRecoveryMode,function,.LFE6-_BL_OPERATION_RequestRecoveryMode
_BL_OPERATION_RequestRecoveryMode:
	.STACK _BL_OPERATION_RequestRecoveryMode = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 209
	oneb a
	br !_BL_OPERATION_SetConfirmCode
.LFE6:
	.TYPE _BL_OPERATION_RequestUserReset,function,.LFE7-_BL_OPERATION_RequestUserReset
_BL_OPERATION_RequestUserReset:
	.STACK _BL_OPERATION_RequestUserReset = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 224
	mov a, #0x02
	br !_BL_OPERATION_SetConfirmCode
.LFE7:
	.TYPE _BL_OPERATION_RequestImageActivation,function,.LFE8-_BL_OPERATION_RequestImageActivation
_BL_OPERATION_RequestImageActivation:
	.STACK _BL_OPERATION_RequestImageActivation = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 239
	mov a, #0x03
	call !_BL_OPERATION_SetConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 240
	mov a, #0x02
	call !_BL_OPERATION_SetConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 243
	mov 0xFFFAB, #0x00
	ret
.LFE8:
	.TYPE _BL_OPERATION_RequestImageBackup,function,.LFE9-_BL_OPERATION_RequestImageBackup
_BL_OPERATION_RequestImageBackup:
	.STACK _BL_OPERATION_RequestImageBackup = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 258
	mov a, #0x04
	br !_BL_OPERATION_SetConfirmCode
.LFE9:
	.TYPE _BL_OPERATION_InformStartupOK,function,.LFE10-_BL_OPERATION_InformStartupOK
_BL_OPERATION_InformStartupOK:
	.STACK _BL_OPERATION_InformStartupOK = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 270
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 272
	movw !LOWW(_g_bl_info), ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 275
	oneb a
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 276
	mov a, #0x02
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 277
	mov a, #0x03
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 278
	mov a, #0x04
	call !_BL_OPERATION_ClearConfirmCode
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 279
	mov a, #0x05
	br !_BL_OPERATION_ClearConfirmCode
.LFE10:
	.TYPE _BL_OPERATION_AcknowledgeImageUpdateStatus,function,.LFE11-_BL_OPERATION_AcknowledgeImageUpdateStatus
_BL_OPERATION_AcknowledgeImageUpdateStatus:
	.STACK _BL_OPERATION_AcknowledgeImageUpdateStatus = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 291
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 293
	movw !LOWW(_g_bl_startup_status), ax
	ret
.LFE11:
	.TYPE _BL_OPERATION_UpdateOperatingClock,function,.LFE12-_BL_OPERATION_UpdateOperatingClock
_BL_OPERATION_UpdateOperatingClock:
	.STACK _BL_OPERATION_UpdateOperatingClock = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_operation.c", 310
	br !_BL_R_CGC_UpdateCPUClock
.LFE12:
	.SECTION BLBss_n,BSS
	.ALIGN 2
	.TYPE _g_bl_startup_status,object,4
_g_bl_startup_status:
	.DS (4)
	.SECTION BLNoInit_n,BSS
	.ALIGN 2
	.TYPE _g_bl_info,object,20
_g_bl_info:
	.DS (20)
