#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_sau_user.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_sau_user.cref
#@   -o Release\bl_r_cg_sau_user.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_c7dcd76aac1b4591908f63f84403bb74lw4ynbow.1y2
#@  compiled at Mon Aug 12 12:54:18 2024

	.EXTERN _gp_Csi30RxAddress
	.EXTERN _gp_Csi30TxAddress
	.EXTERN _g_Csi30TxCnt
	.EXTERN _gp_uart2_tx_address
	.EXTERN _g_uart2_tx_count
	.PUBLIC _R_CSI30_Interrupt
	.PUBLIC _R_CSI30_Callback_ReceiveEnd
	.PUBLIC _R_CSI30_Callback_SendEnd
	.EXTERN _WRP_SPI_SendEndCallback
	.EXTERN _WRP_SPI_ReceiveEndCallback
	.PUBLIC _r_uart2_interrupt_send
	.EXTERN _BL_RECOVERY_UartSendEndCallBack
	.PUBLIC _r_uart2_interrupt_receive
	.EXTERN _BL_RECOVERY_UartReceivedEndCallBack

	.SECTION .text,TEXT
	.TYPE _R_CSI30_Interrupt,function,.LFE1-_R_CSI30_Interrupt
_R_CSI30_Interrupt:
	.STACK _R_CSI30_Interrupt = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 79
	movw ax, !0x0144
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 80
	shlw ax, 0x0D
	shrw ax, 0x0D
	movw !0x014C, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 79
	mov a, c
	and a, #0x07
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 81
	dec a
	sknz
.BB@LABEL@1_1:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 101
	ret
.BB@LABEL@1_2:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 83
	movw ax, !LOWW(_g_Csi30TxCnt)
	clrw bc
	cmpw ax, bc
	bnz $.BB@LABEL@1_6
.BB@LABEL@1_3:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 93
	movw ax, !LOWW(_g_Csi30TxCnt)
	cmpw ax, bc
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_4:	; if_then_bb30
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 95
	movw de, !LOWW(_gp_Csi30RxAddress)
	mov a, 0xFFF14
	mov [de], a
.BB@LABEL@1_5:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 139
	call !_WRP_SPI_ReceiveEndCallback
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 119
	br !_WRP_SPI_SendEndCallback
.BB@LABEL@1_6:	; if_then_bb14
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 85
	movw de, !LOWW(_gp_Csi30RxAddress)
	mov a, 0xFFF14
	mov [de], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 87
	movw de, !LOWW(_gp_Csi30TxAddress)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 86
	incw !LOWW(_gp_Csi30RxAddress)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 87
	mov a, [de]
	mov 0xFFF14, a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 88
	incw !LOWW(_gp_Csi30TxAddress)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 89
	decw !LOWW(_g_Csi30TxCnt)
	ret
.LFE1:
	.TYPE _R_CSI30_Callback_ReceiveEnd,function,.LFE2-_R_CSI30_Callback_ReceiveEnd
_R_CSI30_Callback_ReceiveEnd:
	.STACK _R_CSI30_Callback_ReceiveEnd = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 119
	br !_WRP_SPI_SendEndCallback
.LFE2:
	.TYPE _R_CSI30_Callback_SendEnd,function,.LFE3-_R_CSI30_Callback_SendEnd
_R_CSI30_Callback_SendEnd:
	.STACK _R_CSI30_Callback_SendEnd = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 139
	br !_WRP_SPI_ReceiveEndCallback
.LFE3:
	.TYPE _r_uart2_interrupt_send,function,.LFE4-_r_uart2_interrupt_send
_r_uart2_interrupt_send:
	.STACK _r_uart2_interrupt_send = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 151
	ei
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 152
	movw ax, !LOWW(_g_uart2_tx_count)
	clrw bc
	cmpw ax, bc
	sknz
.BB@LABEL@4_1:	; if_else_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 160
	br !_BL_RECOVERY_UartSendEndCallBack
.BB@LABEL@4_2:	; if_then_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 154
	movw de, !LOWW(_gp_uart2_tx_address)
	mov a, [de]
	mov 0xFFF48, a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 155
	incw !LOWW(_gp_uart2_tx_address)
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 156
	decw !LOWW(_g_uart2_tx_count)
	ret
.LFE4:
	.TYPE _r_uart2_interrupt_receive,function,.LFE5-_r_uart2_interrupt_receive
_r_uart2_interrupt_receive:
	.STACK _r_uart2_interrupt_receive = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 174
	ei
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 176
	movw ax, !0x0142
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 177
	shlw ax, 0x0D
	shrw ax, 0x0D
	movw !0x014A, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_sau_user.c", 184
	mov a, 0xFFF4A
	br !_BL_RECOVERY_UartReceivedEndCallBack
.LFE5:
