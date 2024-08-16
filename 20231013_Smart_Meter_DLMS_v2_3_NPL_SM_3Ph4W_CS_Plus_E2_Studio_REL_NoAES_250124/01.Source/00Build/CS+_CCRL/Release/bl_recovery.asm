#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\core\bl_recovery.c
#@   -cpu=S3
#@   -cref=Release\bl_recovery.cref
#@   -o Release\bl_recovery.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_dcccdec68cf048f4935d08e08af6a379aua4kala.1qk
#@  compiled at Mon Aug 12 12:54:20 2024

	.PUBLIC _g_bl_recovery_data_buffer
	.PUBLIC _g_bl_recovery_frame_length
	.PUBLIC _g_bl_recovery_receive_count
	.PUBLIC _g_bl_recovery_response_error_code
	.PUBLIC _g_bl_recovery_is_key_press
	.PUBLIC _g_bl_recovery_is_mode_timeout
	.PUBLIC _g_bl_recovery_is_mode_finish
	.PUBLIC _g_bl_recovery_is_processing
	.PUBLIC _g_bl_recovery_is_sent
	.PUBLIC _g_bl_recovery_opr_state
	.PUBLIC _g_bl_recovery_timeout_counter
	.PUBLIC _BL_RECOVERY_Init
	.EXTERN _R_UART2_Start
	.EXTERN _R_TAU0_Channel0_Start
	.PUBLIC _BL_RECOVERY_SendFrameAck
	.EXTERN _R_UART2_Send
	.PUBLIC _BL_RECOVERY_PollingProcessing
	.EXTERN _R_CRC_Set
	.EXTERN _R_CRC_Calculate
	.EXTERN _R_CRC_GetResult
	.EXTERN _BL_FLASH_EraseBlock
	.EXTERN _BL_FLASH_WriteBlock
	.PUBLIC _BL_RECOVERY_UartSendEndCallBack
	.PUBLIC _BL_RECOVERY_UartReceivedEndCallBack
	.PUBLIC _BL_RECOVERY_TimerEndCallBack
	.PUBLIC _BL_RECOVERY_Processing
	.EXTERN _BL_OPERATION_ReadConfirmCode
	.EXTERN _BL_LCD_DisplayRecoveryMode
	.EXTERN _BL_OPERATION_InformStartupOK
	.EXTERN _BL_OPERATION_ClearConfirmCode

	.SECTION .text,TEXT
	.TYPE _BL_RECOVERY_Init,function,.LFE1-_BL_RECOVERY_Init
_BL_RECOVERY_Init:
	.STACK _BL_RECOVERY_Init = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 160
	call !_R_UART2_Start
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 163
	call !_R_TAU0_Channel0_Start
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 165
	clrb !LOWW(_g_bl_recovery_opr_state)
	ret
.LFE1:
	.TYPE _BL_RECOVERY_SendFrameAck,function,.LFE2-_BL_RECOVERY_SendFrameAck
_BL_RECOVERY_SendFrameAck:
	.STACK _BL_RECOVERY_SendFrameAck = 8
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 174
	subw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 179
	mov [sp+0x00], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 181
	dec a
	bz $.BB@LABEL@2_8
.BB@LABEL@2_1:	; entry
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	dec a
	bz $.BB@LABEL@2_7
.BB@LABEL@2_2:	; entry
	dec a
	clrb a
	bnz $.BB@LABEL@2_9
.BB@LABEL@2_3:	; switch_clause_bb13
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 192
	mov a, !LOWW(_g_bl_recovery_response_error_code)
	mov [sp+0x01], a
	mov a, #0x02
.BB@LABEL@2_4:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 203
	clrb !LOWW(_g_bl_recovery_is_sent)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 204
	shrw ax, 8+0x00000
	movw bc, ax
	movw ax, sp
	call !_R_UART2_Send
.BB@LABEL@2_5:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 206
	cmp0 !LOWW(_g_bl_recovery_is_sent)
	bz $.BB@LABEL@2_5
.BB@LABEL@2_6:	; bb31
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 207
	mov 0xFFFAB, #0xAC
	br $.BB@LABEL@2_10
.BB@LABEL@2_7:	; switch_clause_bb8
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 187
	mov [sp+0x01], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 188
	mov [sp+0x02], #0x04
	mov a, #0x03
	br $.BB@LABEL@2_9
.BB@LABEL@2_8:	; entry.switch_break_bb_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	oneb a
.BB@LABEL@2_9:	; switch_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 201
	cmp0 a
	bnz $.BB@LABEL@2_4
.BB@LABEL@2_10:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 209
	ret
.LFE2:
	.TYPE _BL_RECOVERY_PollingProcessing,function,.LFE3-_BL_RECOVERY_PollingProcessing
_BL_RECOVERY_PollingProcessing:
	.STACK _BL_RECOVERY_PollingProcessing = 10
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 217
	subw sp, #0x06
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 219
	cmp !LOWW(_g_bl_recovery_opr_state), #0x04
	.bnz !.BB@LABEL@3_18
.BB@LABEL@3_1:	; switch_clause_bb11
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 239
	mov x, !LOWW(_g_bl_recovery_data_buffer)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 240
	mov a, !LOWW(_g_bl_recovery_data_buffer+0x00001)
	movw [sp+0x04], ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 245
	addw ax, #LOWW(_g_bl_recovery_data_buffer)
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 243
	mov a, !LOWW(_g_bl_recovery_data_buffer+0x00002)
	mov [sp+0x02], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 245
	mov a, [de]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 246
	incw de
	mov [sp+0x01], a
	mov a, [de]
	mov [sp+0x00], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 249
	clrw ax
	decw ax
	call !_R_CRC_Set
	movw ax, [sp+0x04]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 250
	movw ax, #LOWW(_g_bl_recovery_data_buffer)
	call !_R_CRC_Calculate
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 253
	call !_R_CRC_GetResult
	movw bc, ax
	clrw ax
	decw ax
	subw ax, bc
	movw bc, ax
	mov a, [sp+0x01]
	mov x, a
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 246
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 255
	cmpw ax, bc
	bnz $.BB@LABEL@3_15
.BB@LABEL@3_2:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	mov a, [sp+0x02]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 264
	cmp0 a
	bnz $.BB@LABEL@3_4
.BB@LABEL@3_3:	; if_then_bb51
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 267
	oneb !LOWW(_g_bl_recovery_is_mode_finish)
	br $.BB@LABEL@3_11
.BB@LABEL@3_4:	; if_else_bb52
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 270
	cmp a, #0x01
	bnz $.BB@LABEL@3_6
.BB@LABEL@3_5:	; if_else_bb52.if_break_bb120_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	mov a, #0x02
	br $.BB@LABEL@3_17
.BB@LABEL@3_6:	; if_else_bb59
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 274
	cmp a, #0x02
	bnz $.BB@LABEL@3_14
.BB@LABEL@3_7:	; if_then_bb65
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 277
	mov x, !LOWW(_g_bl_recovery_data_buffer+0x00003)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 278
	mov a, !LOWW(_g_bl_recovery_data_buffer+0x00004)
	movw [sp+0x00], ax
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 281
	addw ax, #0xFFF8
	cmpw ax, #0x01F8
	bc $.BB@LABEL@3_9
.BB@LABEL@3_8:	; if_then_bb86
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 286
	mov !LOWW(_g_bl_recovery_response_error_code), #0x04
	br $.BB@LABEL@3_16
.BB@LABEL@3_9:	; if_else_bb87
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	movw ax, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 289
	cmpw ax, #0x0405
	bnz $.BB@LABEL@3_13
.BB@LABEL@3_10:	; if_else_bb94
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 301
	movw ax, bc
	call !_BL_FLASH_EraseBlock
	mov [sp+0x02], a
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 302
	shrw ax, 0x06
	movw bc, ax
	movw ax, [sp+0x00]
	shlw ax, 0x0A
	movw de, #LOWW(_g_bl_recovery_data_buffer+0x00005)
	call !_BL_FLASH_WriteBlock
	mov x, a
	mov a, [sp+0x02]
	or a, x
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 304
	bnz $.BB@LABEL@3_12
.BB@LABEL@3_11:	; if_else_bb94.if_break_bb120_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	oneb a
	br $.BB@LABEL@3_17
.BB@LABEL@3_12:	; if_then_bb112
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 308
	mov !LOWW(_g_bl_recovery_response_error_code), #0x06
	br $.BB@LABEL@3_16
.BB@LABEL@3_13:	; if_then_bb93
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 293
	mov !LOWW(_g_bl_recovery_response_error_code), #0x05
	br $.BB@LABEL@3_16
.BB@LABEL@3_14:	; if_else_bb116
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 320
	mov !LOWW(_g_bl_recovery_response_error_code), #0x02
	br $.BB@LABEL@3_16
.BB@LABEL@3_15:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 259
	mov !LOWW(_g_bl_recovery_response_error_code), #0x03
.BB@LABEL@3_16:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	mov a, #0x03
.BB@LABEL@3_17:	; if_break_bb120
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 325
	call !_BL_RECOVERY_SendFrameAck
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 328
	clrb !LOWW(_g_bl_recovery_opr_state)
.BB@LABEL@3_18:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	addw sp, #0x06
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 336
	ret
.LFE3:
	.TYPE _BL_RECOVERY_UartSendEndCallBack,function,.LFE4-_BL_RECOVERY_UartSendEndCallBack
_BL_RECOVERY_UartSendEndCallBack:
	.STACK _BL_RECOVERY_UartSendEndCallBack = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 346
	oneb !LOWW(_g_bl_recovery_is_sent)
	ret
.LFE4:
	.TYPE _BL_RECOVERY_UartReceivedEndCallBack,function,.LFE5-_BL_RECOVERY_UartReceivedEndCallBack
_BL_RECOVERY_UartReceivedEndCallBack:
	.STACK _BL_RECOVERY_UartReceivedEndCallBack = 6
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 355
	push hl
	mov [sp+0x00], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 357
	mov a, !LOWW(_g_bl_recovery_opr_state)
	cmp0 a
	bz $.BB@LABEL@5_6
.BB@LABEL@5_1:	; entry
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	dec a
	bz $.BB@LABEL@5_8
.BB@LABEL@5_2:	; entry
	dec a
	bz $.BB@LABEL@5_10
.BB@LABEL@5_3:	; entry
	dec a
	bnz $.BB@LABEL@5_13
.BB@LABEL@5_4:	; switch_clause_bb45
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 397
	cmp a, #0x23
	bnz $.BB@LABEL@5_13
.BB@LABEL@5_5:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 404
	mov !LOWW(_g_bl_recovery_opr_state), #0x04
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 405
	movw !LOWW(_g_bl_recovery_timeout_counter), ax
	br $.BB@LABEL@5_14
.BB@LABEL@5_6:	; switch_clause_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 360
	cmp a, #0x7E
	bnz $.BB@LABEL@5_14
.BB@LABEL@5_7:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 362
	movw !LOWW(_g_bl_recovery_receive_count), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 363
	oneb !LOWW(_g_bl_recovery_opr_state)
	br $.BB@LABEL@5_14
.BB@LABEL@5_8:	; switch_clause_bb7
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 368
	movw bc, !LOWW(_g_bl_recovery_receive_count)
	mov a, [sp+0x00]
	mov LOWW(_g_bl_recovery_data_buffer)[bc], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 369
	incw bc
	movw ax, bc
	movw !LOWW(_g_bl_recovery_receive_count), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 371
	cmpw ax, #0x0002
	bc $.BB@LABEL@5_14
.BB@LABEL@5_9:	; if_then_bb18
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 373
	mov a, !LOWW(_g_bl_recovery_data_buffer)
	mov !LOWW(_g_bl_recovery_frame_length), a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 374
	mov a, !LOWW(_g_bl_recovery_data_buffer+0x00001)
	mov !LOWW(_g_bl_recovery_frame_length+0x00001), a
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 375
	movw !LOWW(_g_bl_recovery_receive_count), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 376
	mov !LOWW(_g_bl_recovery_opr_state), #0x02
	br $.BB@LABEL@5_14
.BB@LABEL@5_10:	; switch_clause_bb22
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 382
	movw bc, !LOWW(_g_bl_recovery_frame_length)
	movw ax, !LOWW(_g_bl_recovery_receive_count)
	cmpw ax, bc
	bnc $.BB@LABEL@5_14
.BB@LABEL@5_11:	; if_then_bb28
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 384
	addw ax, #LOWW(_g_bl_recovery_data_buffer+0x00002)
	movw hl, ax
	mov a, [sp+0x00]
	mov [hl], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 385
	incw de
	movw ax, de
	movw !LOWW(_g_bl_recovery_receive_count), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 387
	cmpw ax, bc
	bc $.BB@LABEL@5_14
.BB@LABEL@5_12:	; if_then_bb42
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 389
	mov !LOWW(_g_bl_recovery_opr_state), #0x03
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 390
	movw !LOWW(_g_bl_recovery_receive_count), ax
	br $.BB@LABEL@5_14
.BB@LABEL@5_13:	; if_then_bb51
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	clrb !LOWW(_g_bl_recovery_opr_state)
.BB@LABEL@5_14:	; return
	pop ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 412
	ret
.LFE5:
	.TYPE _BL_RECOVERY_TimerEndCallBack,function,.LFE6-_BL_RECOVERY_TimerEndCallBack
_BL_RECOVERY_TimerEndCallBack:
	.STACK _BL_RECOVERY_TimerEndCallBack = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 422
	cmp0 !LOWW(_g_bl_recovery_is_processing)
	bz $.BB@LABEL@6_6
.BB@LABEL@6_1:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	onew ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 424
	addw ax, !LOWW(_g_bl_recovery_timeout_counter)
	movw !LOWW(_g_bl_recovery_timeout_counter), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 427
	cmp0 !LOWW(_g_bl_recovery_opr_state)
	bnz $.BB@LABEL@6_4
.BB@LABEL@6_2:	; if_then_bb11
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 430
	cmpw ax, #0x003C
	bc $.BB@LABEL@6_6
.BB@LABEL@6_3:	; if_then_bb16
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 432
	oneb !LOWW(_g_bl_recovery_is_mode_timeout)
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 433
	movw !LOWW(_g_bl_recovery_timeout_counter), ax
	ret
.BB@LABEL@6_4:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 439
	cmpw ax, #0x0004
	bc $.BB@LABEL@6_6
.BB@LABEL@6_5:	; if_then_bb21
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 441
	movw !LOWW(_g_bl_recovery_frame_length), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 442
	movw !LOWW(_g_bl_recovery_receive_count), ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 443
	clrb !LOWW(_g_bl_recovery_opr_state)
.BB@LABEL@6_6:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 448
	ret
.LFE6:
	.TYPE _BL_RECOVERY_Processing,function,.LFE7-_BL_RECOVERY_Processing
_BL_RECOVERY_Processing:
	.STACK _BL_RECOVERY_Processing = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 464
	oneb a
	call !_BL_OPERATION_ReadConfirmCode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 466
	cmp0 a
	bz $.BB@LABEL@7_10
.BB@LABEL@7_1:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 472
	call !_BL_LCD_DisplayRecoveryMode
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 475
	oneb !LOWW(_g_bl_recovery_is_processing)
.BB@LABEL@7_2:	; bb47
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 477
	cmp0 !LOWW(_g_bl_recovery_is_processing)
	bz $.BB@LABEL@7_10
.BB@LABEL@7_3:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 479
	call !_BL_RECOVERY_PollingProcessing
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 483
	cmp !LOWW(_g_bl_recovery_is_key_press), #0x01
	bz $.BB@LABEL@7_6
.BB@LABEL@7_4:	; bb15
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 0
	cmp !LOWW(_g_bl_recovery_is_mode_timeout), #0x01
	bz $.BB@LABEL@7_6
.BB@LABEL@7_5:	; bb26
	cmp !LOWW(_g_bl_recovery_is_mode_finish), #0x01
	bnz $.BB@LABEL@7_9
.BB@LABEL@7_6:	; if_then_bb39
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 490
	cmp !LOWW(_g_bl_recovery_is_mode_finish), #0x01
	sknz
.BB@LABEL@7_7:	; if_then_bb45
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 492
	call !_BL_OPERATION_InformStartupOK
.BB@LABEL@7_8:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 494
	clrb !LOWW(_g_bl_recovery_is_processing)
.BB@LABEL@7_9:	; if_break_bb46
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 496
	mov 0xFFFAB, #0xAC
	br $.BB@LABEL@7_2
.BB@LABEL@7_10:	; if_break_bb54
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_recovery.c", 504
	oneb a
	br !_BL_OPERATION_ClearConfirmCode
.LFE7:
	.SECTION .bss,BSS
	.TYPE _g_bl_recovery_data_buffer,object,1056
_g_bl_recovery_data_buffer:
	.DS (1056)
	.ALIGN 2
	.TYPE _g_bl_recovery_frame_length,object,2
_g_bl_recovery_frame_length:
	.DS (2)
	.ALIGN 2
	.TYPE _g_bl_recovery_receive_count,object,2
_g_bl_recovery_receive_count:
	.DS (2)
	.TYPE _g_bl_recovery_response_error_code,object,1
_g_bl_recovery_response_error_code:
	.DS (1)
	.TYPE _g_bl_recovery_is_key_press,object,1
_g_bl_recovery_is_key_press:
	.DS (1)
	.TYPE _g_bl_recovery_is_mode_timeout,object,1
_g_bl_recovery_is_mode_timeout:
	.DS (1)
	.TYPE _g_bl_recovery_is_mode_finish,object,1
_g_bl_recovery_is_mode_finish:
	.DS (1)
	.TYPE _g_bl_recovery_is_processing,object,1
_g_bl_recovery_is_processing:
	.DS (1)
	.TYPE _g_bl_recovery_is_sent,object,1
_g_bl_recovery_is_sent:
	.DS (1)
	.TYPE _g_bl_recovery_opr_state,object,1
_g_bl_recovery_opr_state:
	.DS (1)
	.SECTION .data,DATA
	.ALIGN 2
	.TYPE _g_bl_recovery_timeout_counter,object,2
_g_bl_recovery_timeout_counter:
	.DS (2)
