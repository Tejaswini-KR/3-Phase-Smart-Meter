#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\serialflash\bl_serialflash.c
#@   -cpu=S3
#@   -cref=Release\bl_serialflash.cref
#@   -o Release\bl_serialflash.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_f9d95c49a14e464886cd7257403d8519jt41spxh.hgo
#@  compiled at Fri Aug 16 14:34:49 2024

	.EXTERN _MCU_Delay
	.EXTERN _WRP_SPI_SendReceive
	.PUBLIC _BL_SFL_Init
	.EXTERN _WRP_SPI_Init
	.EXTERN _WRP_SPI_Start
	.PUBLIC _BL_SFL_Stop
	.EXTERN _WRP_SPI_Stop
	.PUBLIC _BL_SFL_DeviceErase4KB
	.PUBLIC _BL_SFL_DeviceErase64KB
	.PUBLIC _BL_SFL_DeviceEraseAll
	.PUBLIC _BL_SFL_DeviceWriteProtectAll
	.PUBLIC _BL_SFL_DeviceWriteUnProtectAll
	.PUBLIC _BL_SFL_DeviceRead
	.PUBLIC _BL_SFL_DeviceWrite
	.PUBLIC _SFL_SendEndCallback
	.PUBLIC _SFL_ReceiveEndCallback

	.SECTION SFLTx_n,TEXT
	.TYPE _SFL_ClearFlagWaitBus@1,function,.LFE1-_SFL_ClearFlagWaitBus@1
_SFL_ClearFlagWaitBus@1:
	.STACK _SFL_ClearFlagWaitBus@1 = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 162
	clrb !LOWW(_g_is_receive_end@2)
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 163
	clrb !LOWW(_g_is_send_end@1)
	ret
.LFE1:
	.TYPE _SFL_WaitForBus@1,function,.LFE2-_SFL_WaitForBus@1
_SFL_WaitForBus@1:
	.STACK _SFL_WaitForBus@1 = 8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 174
	subw sp, #0x04
	movw ax, #0x0007
	movw [sp+0x02], ax
	movw ax, #0xFFF9
	movw [sp+0x00], ax
.BB@LABEL@2_1:	; bb9
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 186
	cmp0 !LOWW(_g_is_send_end@1)
	bz $.BB@LABEL@2_3
.BB@LABEL@2_2:	; bb14
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	cmp0 !LOWW(_g_is_receive_end@2)
	bnz $.BB@LABEL@2_9
.BB@LABEL@2_3:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 188
	onew ax
	call !_MCU_Delay
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 191
	addw ax, #0xFFFF
	movw [sp+0x00], ax
	movw ax, [sp+0x02]
	bc $.BB@LABEL@2_5
.BB@LABEL@2_4:	; bb
	decw ax
	movw [sp+0x02], ax
.BB@LABEL@2_5:	; bb
	clrw bc
	cmpw ax, bc
	movw ax, [sp+0x00]
	bnz $.BB@LABEL@2_7
.BB@LABEL@2_6:	; bb
	incw bc
	cmpw ax, bc
.BB@LABEL@2_7:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	bnz $.BB@LABEL@2_1
.BB@LABEL@2_8:	; bb.bb28_crit_edge
	mov a, #0x02
	br $.BB@LABEL@2_10
.BB@LABEL@2_9:	; bb14.bb28_crit_edge
	clrb a
.BB@LABEL@2_10:	; bb28
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 198
	addw sp, #0x04
	ret
.LFE2:
	.TYPE _SFL_WaitForWrite@1,function,.LFE3-_SFL_WaitForWrite@1
_SFL_WaitForWrite@1:
	.STACK _SFL_WaitForWrite@1 = 16
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 210
	subw sp, #0x0C
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 215
	movw hl, #0x0000
	movw de, #0x000A
	divwu
	movw [sp+0x08], ax
	movw ax, bc
	movw [sp+0x06], ax
	clrw ax
	movw [sp+0x04], ax
	movw [sp+0x02], ax
.BB@LABEL@3_1:	; bb21
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 217
	cmpw ax, bc
	movw ax, [sp+0x08]
	movw bc, ax
	movw ax, [sp+0x04]
	sknz
.BB@LABEL@3_2:	; bb21
	cmpw ax, bc
.BB@LABEL@3_3:	; bb21
	bnc $.BB@LABEL@3_8
.BB@LABEL@3_4:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 220
	movw ax, #0x000A
	call !_MCU_Delay
	movw ax, sp
	addw ax, #0x000A
	movw [sp+0x00], ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 223
	call !_SFL_DeviceReadStatusRegister@1
	pop hl
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 224
	bf [hl].0, $.BB@LABEL@3_9
.BB@LABEL@3_5:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 229
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x04]
	addw ax, #0x0001
	movw [sp+0x04], ax
	bnc $.BB@LABEL@3_7
.BB@LABEL@3_6:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x02]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 229
	incw ax
	movw [sp+0x02], ax
.BB@LABEL@3_7:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x06]
	movw bc, ax
	movw ax, [sp+0x02]
	br $.BB@LABEL@3_1
.BB@LABEL@3_8:	; bb21.bb29_crit_edge
	mov a, #0x02
	br $.BB@LABEL@3_10
.BB@LABEL@3_9:	; bb.bb29_crit_edge
	clrb a
.BB@LABEL@3_10:	; bb29
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 233
	addw sp, #0x0C
	ret
.LFE3:
	.TYPE _SFL_DeviceWriteEnable@1,function,.LFE4-_SFL_DeviceWriteEnable@1
_SFL_DeviceWriteEnable@1:
	.STACK _SFL_DeviceWriteEnable@1 = 6
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 243
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 247
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 249
	mov [sp+0x00], #0x06
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 250
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 251
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 252
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@4_2
.BB@LABEL@4_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 256
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 258
	clrb a
	pop bc
	ret
.BB@LABEL@4_2:	; bb12
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 259
	mov a, #0x02
	pop bc
	ret
.LFE4:
	.TYPE _SFL_DeviceWriteDisable@1,function,.LFE5-_SFL_DeviceWriteDisable@1
_SFL_DeviceWriteDisable@1:
	.STACK _SFL_DeviceWriteDisable@1 = 6
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 269
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 273
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 275
	mov [sp+0x00], #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 276
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 277
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 278
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@5_2
.BB@LABEL@5_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 282
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 284
	clrb a
	pop bc
	ret
.BB@LABEL@5_2:	; bb12
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 285
	mov a, #0x02
	pop bc
	ret
.LFE5:
	.TYPE _SFL_DevicePinBusyStatusDisable@1,function,.LFE6-_SFL_DevicePinBusyStatusDisable@1
_SFL_DevicePinBusyStatusDisable@1:
	.STACK _SFL_DevicePinBusyStatusDisable@1 = 6
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 322
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 326
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 327
	mov [sp+0x00], #0x80
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 329
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 330
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 331
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@6_2
.BB@LABEL@6_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 336
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 338
	clrb a
	pop bc
	ret
.BB@LABEL@6_2:	; bb12
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 339
	mov a, #0x02
	pop bc
	ret
.LFE6:
	.TYPE _SFL_DeviceReadStatusRegister@1,function,.LFE7-_SFL_DeviceReadStatusRegister@1
_SFL_DeviceReadStatusRegister@1:
	.STACK _SFL_DeviceReadStatusRegister@1 = 8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 349
	push ax
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 353
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 355
	mov [sp+0x00], #0x05
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 356
	mov [sp+0x01], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 357
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 358
	movw de, ax
	onew bc
	incw bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 359
	onew ax
	incw ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@7_2
.BB@LABEL@7_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 363
	set1 0xFFF05.0
	movw ax, [sp+0x02]
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 365
	mov a, [sp+0x01]
	mov [de], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 367
	clrb a
	br $.BB@LABEL@7_3
.BB@LABEL@7_2:	; bb20
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 368
	mov a, #0x02
.BB@LABEL@7_3:	; bb20
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 368
	ret
.LFE7:
	.TYPE _SFL_DeviceWriteStatusRegister@1,function,.LFE8-_SFL_DeviceWriteStatusRegister@1
_SFL_DeviceWriteStatusRegister@1:
	.STACK _SFL_DeviceWriteStatusRegister@1 = 8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 378
	push ax
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 383
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 385
	mov [sp+0x00], #0x50
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 386
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 387
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 388
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@8_3
.BB@LABEL@8_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 392
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 395
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 397
	mov [sp+0x00], #0x01
	mov a, [sp+0x03]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 398
	mov [sp+0x01], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 399
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 400
	movw de, ax
	onew bc
	incw bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 401
	onew ax
	incw ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@8_3
.BB@LABEL@8_2:	; if_break_bb28
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 405
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 408
	clrw bc
	movw ax, #0x000F
	call !_SFL_WaitForWrite@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@8_3:	; if_break_bb28
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@8_4:	; if_break_bb28
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 414
	ret
.LFE8:
	.TYPE _SFL_DeviceByteProgramming@1,function,.LFE9-_SFL_DeviceByteProgramming@1
_SFL_DeviceByteProgramming@1:
	.STACK _SFL_DeviceByteProgramming@1 = 16
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 425
	push de
	push ax
	subw sp, #0x06
	push bc
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 430
	call !_SFL_DeviceWriteEnable@1
	cmp0 a
	bnz $.BB@LABEL@9_3
.BB@LABEL@9_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 436
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 438
	mov [sp+0x02], #0x02
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 439
	mov [sp+0x03], a
	movw ax, [sp+0x08]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 440
	mov [sp+0x04], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 441
	mov a, c
	mov [sp+0x05], a
	mov a, [sp+0x0A]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 442
	mov [sp+0x06], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 444
	clr1 0xFFF05.0
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 445
	movw de, ax
	movw bc, #0x0005
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 446
	movw ax, #0x0005
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@9_3
.BB@LABEL@9_2:	; if_break_bb37
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 450
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 453
	clrw bc
	movw ax, #0x000A
	call !_SFL_WaitForWrite@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@9_3:	; if_break_bb37
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@9_4:	; if_break_bb37
	addw sp, #0x0C
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 459
	ret
.LFE9:
	.TYPE _BL_SFL_Init,function,.LFE10-_BL_SFL_Init
_BL_SFL_Init:
	.STACK _BL_SFL_Init = 8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 619
	subw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 624
	call !_WRP_SPI_Init
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 625
	call !_WRP_SPI_Start
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 629
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 632
	call !_SFL_DeviceWriteDisable@1
	cmp0 a
	bz $.BB@LABEL@10_2
.BB@LABEL@10_1:	; entry.bb94_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
	br $.BB@LABEL@10_11
.BB@LABEL@10_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 638
	call !_SFL_DeviceWriteEnable@1
	cmp0 a
	bnz $.BB@LABEL@10_1
.BB@LABEL@10_3:	; if_break_bb13
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, sp
	incw ax
	incw ax
	movw [sp+0x00], ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 644
	call !_SFL_DeviceReadStatusRegister@1
	cmp0 a
	bnz $.BB@LABEL@10_1
.BB@LABEL@10_4:	; if_break_bb21
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	pop hl
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 648
	bt [hl].1, $.BB@LABEL@10_6
.BB@LABEL@10_5:	; if_break_bb21.bb94_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	oneb a
	br $.BB@LABEL@10_11
.BB@LABEL@10_6:	; if_break_bb36
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 655
	call !_SFL_DevicePinBusyStatusDisable@1
	cmp0 a
	bnz $.BB@LABEL@10_1
.BB@LABEL@10_7:	; if_break_bb44
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 662
	mov [sp+0x02], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 663
	clrb a
	call !_SFL_DeviceWriteStatusRegister@1
	cmp0 a
	bnz $.BB@LABEL@10_1
.BB@LABEL@10_8:	; if_break_bb53
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 668
	movw ax, sp
	incw ax
	incw ax
	call !_SFL_DeviceReadStatusRegister@1
	cmp0 a
	bnz $.BB@LABEL@10_1
.BB@LABEL@10_9:	; if_break_bb61
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 674
	mov a, [sp+0x02]
	bt a.0, $.BB@LABEL@10_5
.BB@LABEL@10_10:	; bb73
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	shr a, 0x07
.BB@LABEL@10_11:	; bb94
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 681
	ret
.LFE10:
	.TYPE _BL_SFL_Stop,function,.LFE11-_BL_SFL_Stop
_BL_SFL_Stop:
	.STACK _BL_SFL_Stop = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 691
	call !_WRP_SPI_Stop
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 693
	clrb a
	ret
.LFE11:
	.TYPE _BL_SFL_DeviceErase4KB,function,.LFE12-_BL_SFL_DeviceErase4KB
_BL_SFL_DeviceErase4KB:
	.STACK _BL_SFL_DeviceErase4KB = 12
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 703
	push ax
	subw sp, #0x04
	push bc
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 708
	cmpw ax, #0x0020
	mov a, #0x03
	bnc $.BB@LABEL@12_5
.BB@LABEL@12_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 714
	call !_SFL_DeviceWriteEnable@1
	cmp0 a
	bnz $.BB@LABEL@12_4
.BB@LABEL@12_2:	; if_break_bb13
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 720
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 722
	mov [sp+0x02], #0x20
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 723
	mov [sp+0x03], a
	movw ax, [sp+0x06]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 724
	mov [sp+0x04], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 725
	mov a, c
	mov [sp+0x05], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 727
	clr1 0xFFF05.0
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 728
	movw de, ax
	movw bc, #0x0004
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 729
	movw ax, #0x0004
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@12_4
.BB@LABEL@12_3:	; if_break_bb40
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 733
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 736
	clrw bc
	movw ax, #0x61A8
	call !_SFL_WaitForWrite@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@12_4:	; if_break_bb40
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@12_5:	; if_break_bb40
	addw sp, #0x08
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 742
	ret
.LFE12:
	.TYPE _BL_SFL_DeviceErase64KB,function,.LFE13-_BL_SFL_DeviceErase64KB
_BL_SFL_DeviceErase64KB:
	.STACK _BL_SFL_DeviceErase64KB = 12
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 752
	push ax
	subw sp, #0x04
	push bc
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 757
	cmpw ax, #0x0020
	mov a, #0x03
	bnc $.BB@LABEL@13_5
.BB@LABEL@13_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 763
	call !_SFL_DeviceWriteEnable@1
	cmp0 a
	bnz $.BB@LABEL@13_4
.BB@LABEL@13_2:	; if_break_bb13
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 769
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 771
	mov [sp+0x02], #0xD8
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 772
	mov [sp+0x03], a
	movw ax, [sp+0x06]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 773
	mov [sp+0x04], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 774
	mov a, c
	mov [sp+0x05], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 776
	clr1 0xFFF05.0
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 777
	movw de, ax
	movw bc, #0x0004
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 778
	movw ax, #0x0004
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@13_4
.BB@LABEL@13_3:	; if_break_bb40
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 782
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 785
	clrw bc
	movw ax, #0x61A8
	call !_SFL_WaitForWrite@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@13_4:	; if_break_bb40
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@13_5:	; if_break_bb40
	addw sp, #0x08
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 791
	ret
.LFE13:
	.TYPE _BL_SFL_DeviceEraseAll,function,.LFE14-_BL_SFL_DeviceEraseAll
_BL_SFL_DeviceEraseAll:
	.STACK _BL_SFL_DeviceEraseAll = 6
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 801
	push hl
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 806
	call !_SFL_DeviceWriteEnable@1
	cmp0 a
	bnz $.BB@LABEL@14_3
.BB@LABEL@14_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 812
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 814
	mov [sp+0x00], #0xC7
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 815
	clr1 0xFFF05.0
	movw ax, sp
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 816
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 817
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@14_3
.BB@LABEL@14_2:	; if_break_bb18
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 821
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 824
	clrw bc
	movw ax, #0xC350
	call !_SFL_WaitForWrite@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@14_3:	; if_break_bb18
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@14_4:	; if_break_bb18
	pop bc
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 830
	ret
.LFE14:
	.TYPE _BL_SFL_DeviceWriteProtectAll,function,.LFE15-_BL_SFL_DeviceWriteProtectAll
_BL_SFL_DeviceWriteProtectAll:
	.STACK _BL_SFL_DeviceWriteProtectAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 847
	mov a, #0xFF
	br !_SFL_DeviceWriteStatusRegister@1
.LFE15:
	.TYPE _BL_SFL_DeviceWriteUnProtectAll,function,.LFE16-_BL_SFL_DeviceWriteUnProtectAll
_BL_SFL_DeviceWriteUnProtectAll:
	.STACK _BL_SFL_DeviceWriteUnProtectAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 862
	clrb a
	br !_SFL_DeviceWriteStatusRegister@1
.LFE16:
	.TYPE _BL_SFL_DeviceRead,function,.LFE17-_BL_SFL_DeviceRead
_BL_SFL_DeviceRead:
	.STACK _BL_SFL_DeviceRead = 14
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 875
	push de
	push ax
	subw sp, #0x04
	movw hl, ax
	push bc
	movw ax, [sp+0x08]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 880
	or a, x
	movw ax, [sp+0x0E]
	bnz $.BB@LABEL@17_2
.BB@LABEL@17_1:	; entry.bb69_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	oneb a
	br $.BB@LABEL@17_13
.BB@LABEL@17_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 886
	cmpw ax, #0x0000
	bnz $.BB@LABEL@17_4
.BB@LABEL@17_3:	; if_break_bb.bb69_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x03
	br $.BB@LABEL@17_13
.BB@LABEL@17_4:	; bb11
	addw ax, hl
	movw de, ax
	movw ax, bc
	sknc
.BB@LABEL@17_5:	; bb11
	incw ax
.BB@LABEL@17_6:	; bb11
	cmpw ax, #0x0020
	movw ax, de
	bnz $.BB@LABEL@17_8
.BB@LABEL@17_7:	; bb11
	onew bc
	cmpw ax, bc
.BB@LABEL@17_8:	; bb11
	bnc $.BB@LABEL@17_3
.BB@LABEL@17_9:	; if_break_bb27
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 893
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 895
	mov [sp+0x02], #0x03
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 896
	mov [sp+0x03], a
	movw ax, [sp+0x06]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 897
	mov [sp+0x04], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 898
	mov a, c
	mov [sp+0x05], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 900
	clr1 0xFFF05.0
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 901
	movw de, ax
	movw bc, #0x0004
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 902
	movw ax, #0x0004
	call !_SFL_WaitForBus@1
	cmp0 a
	bz $.BB@LABEL@17_11
.BB@LABEL@17_10:	; if_break_bb27.bb69_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
	br $.BB@LABEL@17_13
.BB@LABEL@17_11:	; if_break_bb54
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 907
	call !_SFL_ClearFlagWaitBus@1
	movw ax, [sp+0x08]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 908
	movw de, ax
	movw ax, [sp+0x0E]
	movw bc, ax
	movw ax, [sp+0x08]
	call !_WRP_SPI_SendReceive
	movw ax, [sp+0x0E]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 909
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@17_10
.BB@LABEL@17_12:	; if_break_bb67
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 913
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 915
	clrb a
.BB@LABEL@17_13:	; bb69
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	addw sp, #0x0A
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 916
	ret
.LFE17:
	.TYPE _BL_SFL_DeviceWrite,function,.LFE18-_BL_SFL_DeviceWrite
_BL_SFL_DeviceWrite:
	.STACK _BL_SFL_DeviceWrite = 28
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 926
	push de
	push bc
	push ax
	subw sp, #0x10
	movw hl, ax
	movw ax, [sp+0x14]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 929
	or a, x
	movw ax, [sp+0x1A]
	movw [sp+0x08], ax
	bz $.BB@LABEL@18_16
.BB@LABEL@18_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 935
	cmpw ax, #0x0000
	bnz $.BB@LABEL@18_3
.BB@LABEL@18_2:	; if_break_bb.bb33_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x03
	br $.BB@LABEL@18_17
.BB@LABEL@18_3:	; bb10
	addw ax, hl
	movw de, ax
	movw ax, bc
	sknc
.BB@LABEL@18_4:	; bb10
	incw ax
.BB@LABEL@18_5:	; bb10
	cmpw ax, #0x0020
	movw ax, de
	sknz
.BB@LABEL@18_6:	; bb10
	cmpw ax, #0x0001
.BB@LABEL@18_7:	; bb10
	clrw ax
	movw [sp+0x06], ax
	bnc $.BB@LABEL@18_2
.BB@LABEL@18_8:	; if_break_bb26
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 479
	mov a, l
	bf a.0, $.BB@LABEL@18_15
.BB@LABEL@18_9:	; if_then_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x14]
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 482
	mov a, [de]
	mov e, a
	movw ax, [sp+0x10]
	call !_SFL_DeviceByteProgramming@1
	cmp0 a
	.bnz !.BB@LABEL@18_46
.BB@LABEL@18_10:	; if_break_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x08]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 490
	addw ax, #0xFFFF
	movw [sp+0x08], ax
	clrw ax
	skc
.BB@LABEL@18_11:	; if_break_bb.i
	decw ax
.BB@LABEL@18_12:	; if_break_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw [sp+0x06], ax
	movw ax, [sp+0x10]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 488
	addw ax, #0x0001
	movw [sp+0x10], ax
	bnc $.BB@LABEL@18_14
.BB@LABEL@18_13:	; if_break_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x12]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 488
	incw ax
	movw [sp+0x12], ax
.BB@LABEL@18_14:	; if_break_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x14]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 489
	incw ax
	movw [sp+0x14], ax
.BB@LABEL@18_15:	; if_break_bb29.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 299
	call !_SFL_ClearFlagWaitBus@1
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 300
	mov [sp+0x05], #0x70
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 302
	clr1 0xFFF05.0
	movw ax, sp
	addw ax, #0x0005
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 303
	movw de, ax
	onew bc
	call !_WRP_SPI_SendReceive
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 304
	onew ax
	call !_SFL_WaitForBus@1
	cmp0 a
	bz $.BB@LABEL@18_18
.BB@LABEL@18_16:	; if_break_bb29.i.SFL_DeviceAAIWordProgramming@1.exit_crit_edge
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	oneb a
.BB@LABEL@18_17:	; if_break_bb29.i.SFL_DeviceAAIWordProgramming@1.exit_crit_edge
	br !.BB@LABEL@18_47
.BB@LABEL@18_18:	; if_break_bb.i.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 309
	set1 0xFFF05.0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 502
	call !_SFL_DeviceWriteEnable@1
	oneb a
	mov [sp+0x04], a
.BB@LABEL@18_19:	; bb136.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x06]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 507
	clrw bc
	cmpw ax, bc
	movw ax, [sp+0x08]
	sknz
.BB@LABEL@18_20:	; bb136.i
	cmpw ax, #0x0002
.BB@LABEL@18_21:	; bb136.i
	.bc !.BB@LABEL@18_40
.BB@LABEL@18_22:	; bb39.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 509
	mov [sp+0x0A], #0xAD
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 512
	call !_SFL_ClearFlagWaitBus@1
	mov a, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 513
	cmp0 a
	bnz $.BB@LABEL@18_24
.BB@LABEL@18_23:	; if_else_bb.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x14]
	movw de, ax
	mov b, #0x03
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 525
	mov a, [de]
	mov [sp+0x0B], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 526
	mov a, [de+0x01]
	mov [sp+0x0C], a
	br $.BB@LABEL@18_25
.BB@LABEL@18_24:	; if_then_bb47.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, [sp+0x12]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 515
	mov [sp+0x0B], a
	movw ax, [sp+0x10]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 516
	mov [sp+0x0C], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 517
	mov a, c
	mov [sp+0x0D], a
	movw ax, [sp+0x14]
	movw de, ax
	clrb a
	mov [sp+0x04], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 518
	mov a, [de]
	mov [sp+0x0E], a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 519
	mov a, [de+0x01]
	mov [sp+0x0F], a
	mov b, #0x06
.BB@LABEL@18_25:	; if_break_bb80.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 530
	clr1 0xFFF05.0
	movw ax, sp
	addw ax, #0x000A
	movw hl, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 531
	push hl
	pop de
	mov a, b
	shrw ax, 8+0x00000
	movw [sp+0x00], ax
	movw bc, ax
	movw ax, hl
	call !_WRP_SPI_SendReceive
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 532
	call !_SFL_WaitForBus@1
	cmp0 a
	bnz $.BB@LABEL@18_34
.BB@LABEL@18_26:	; if_break_bb95.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw hl, #0xFF05
	clrw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 537
	set1 [hl].0
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 545
	clr1 [hl].0
	movw [sp+0x00], ax
	incw ax
	movw [sp+0x02], ax
.BB@LABEL@18_27:	; bb127.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 548
	mov a, 0xFFF08
	bt a.4, $.BB@LABEL@18_35
.BB@LABEL@18_28:	; bb102.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 550
	mov 0xFFFAB, #0xAC
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 552
	onew ax
	call !_MCU_Delay
	movw ax, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 554
	cmpw ax, #0x000F
	movw ax, [sp+0x02]
	sknz
.BB@LABEL@18_29:	; bb102.i
	cmpw ax, #0x4240
.BB@LABEL@18_30:	; bb102.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	bnc $.BB@LABEL@18_34
.BB@LABEL@18_31:	; bb108.i
	addw ax, #0x0001
	movw [sp+0x02], ax
	bnc $.BB@LABEL@18_33
.BB@LABEL@18_32:	; bb108.i
	movw ax, [sp+0x00]
	incw ax
	movw [sp+0x00], ax
.BB@LABEL@18_33:	; bb108.i
	mov a, !0x0332
	bf a.6, $.BB@LABEL@18_27
.BB@LABEL@18_34:	; bb108.i
	br $.BB@LABEL@18_46
.BB@LABEL@18_35:	; bb135.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 559
	set1 0xFFF05.0
	movw ax, [sp+0x08]
	addw ax, #0xFFFE
	movw [sp+0x08], ax
	bc $.BB@LABEL@18_37
.BB@LABEL@18_36:	; bb135.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x06]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 559
	decw ax
	movw [sp+0x06], ax
.BB@LABEL@18_37:	; bb135.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x10]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 559
	addw ax, #0x0002
	movw [sp+0x10], ax
	bnc $.BB@LABEL@18_39
.BB@LABEL@18_38:	; bb135.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x12]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 559
	incw ax
	movw [sp+0x12], ax
.BB@LABEL@18_39:	; bb135.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x14]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 559
	incw ax
	incw ax
	movw [sp+0x14], ax
	br !.BB@LABEL@18_19
.BB@LABEL@18_40:	; bb141.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 572
	call !_SFL_DeviceWriteDisable@1
	cmp0 a
	bnz $.BB@LABEL@18_46
.BB@LABEL@18_41:	; if_break_bb149.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 579
	call !_SFL_DevicePinBusyStatusDisable@1
	cmp0 a
	.bnz !.BB@LABEL@18_16
.BB@LABEL@18_42:	; if_break_bb157.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	movw ax, [sp+0x06]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 598
	clrw bc
	cmpw ax, bc
	movw ax, [sp+0x08]
	bnz $.BB@LABEL@18_44
.BB@LABEL@18_43:	; if_break_bb157.i
	incw bc
	cmpw ax, bc
.BB@LABEL@18_44:	; if_break_bb157.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	clrb a
	bnz $.BB@LABEL@18_47
.BB@LABEL@18_45:	; if_then_bb162.i
	movw ax, [sp+0x14]
	movw de, ax
	movw ax, [sp+0x12]
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 601
	mov a, [de]
	mov e, a
	movw ax, [sp+0x10]
	call !_SFL_DeviceByteProgramming@1
	cmp0 a
	clrb a
	skz
.BB@LABEL@18_46:	; if_then_bb162.i
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 0
	mov a, #0x02
.BB@LABEL@18_47:	; if_then_bb162.i
	addw sp, #0x16
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 942
	ret
.LFE18:
	.SECTION .text,TEXT
	.TYPE _SFL_SendEndCallback,function,.LFE19-_SFL_SendEndCallback
_SFL_SendEndCallback:
	.STACK _SFL_SendEndCallback = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 959
	oneb !LOWW(_g_is_send_end@1)
	ret
.LFE19:
	.TYPE _SFL_ReceiveEndCallback,function,.LFE20-_SFL_ReceiveEndCallback
_SFL_ReceiveEndCallback:
	.STACK _SFL_ReceiveEndCallback = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/serialflash/bl_serialflash.c", 970
	oneb !LOWW(_g_is_receive_end@2)
	ret
.LFE20:
	.SECTION BLData_n,DATA
	.TYPE _g_is_send_end@1,object,1
_g_is_send_end@1:
	.DS (1)
	.TYPE _g_is_receive_end@2,object,1
_g_is_receive_end@2:
	.DS (1)
