#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\display\bl_r_drv_lcd_ext.c
#@   -cpu=S3
#@   -cref=Release\bl_r_drv_lcd_ext.cref
#@   -o Release\bl_r_drv_lcd_ext.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_cb28b33c06354dedb7120cbb08b91bd6r1p4kfed.5lk
#@  compiled at Mon Jun 10 17:42:25 2024

	.EXTERN _g_LCD_NumMap
	.EXTERN _g_LCD_NumType
	.PUBLIC _LCD_GetRamSize
	.PUBLIC _LCD_RamClearAll
	.PUBLIC _LCD_RamSetAll
	.PUBLIC _LCD_GetNumInfo
	.PUBLIC _LCD_WriteRAMDigitInfo
	.PUBLIC _LCD_ClearRAMDigitInfo

	.SECTION .text,TEXT
	.TYPE _LCD_GetRamSize,function,.LFE1-_LCD_GetRamSize
_LCD_GetRamSize:
	.STACK _LCD_GetRamSize = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 65
	movw ax, #0x0016
	ret
.LFE1:
	.TYPE _LCD_RamClearAll,function,.LFE2-_LCD_RamClearAll
_LCD_RamClearAll:
	.STACK _LCD_RamClearAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 73
	clrw ax
.BB@LABEL@2_1:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 0
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 81
	addw ax, #0x0404
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 79
	incw bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 81
	mov [de+0x00], #0x00
	movw ax, bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 79
	cmpw ax, #0x0018
	bnz $.BB@LABEL@2_1
.BB@LABEL@2_2:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 83
	ret
.LFE2:
	.TYPE _LCD_RamSetAll,function,.LFE3-_LCD_RamSetAll
_LCD_RamSetAll:
	.STACK _LCD_RamSetAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 91
	clrw ax
.BB@LABEL@3_1:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 0
	movw bc, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 99
	addw ax, #0x0404
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 97
	incw bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 99
	mov [de+0x00], #0xFF
	movw ax, bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 97
	cmpw ax, #0x0018
	bnz $.BB@LABEL@3_1
.BB@LABEL@3_2:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 101
	ret
.LFE3:
	.TYPE _LCD_GetNumInfo,function,.LFE4-_LCD_GetNumInfo
_LCD_GetNumInfo:
	.STACK _LCD_GetNumInfo = 8
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 116
	push bc
	push ax
	movw ax, [sp+0x02]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 122
	clrw bc
	cmpw ax, bc
	bz $.BB@LABEL@4_7
.BB@LABEL@4_1:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 0
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 128
	cmp0 a
	bz $.BB@LABEL@4_7
.BB@LABEL@4_2:	; if_break_bb
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 0
	mov a, [sp+0x01]
	cmp a, #0x0B
	bnc $.BB@LABEL@4_7
.BB@LABEL@4_3:	; if_break_bb
	mov a, [sp+0x00]
	cmp a, #0x08
	bnc $.BB@LABEL@4_7
.BB@LABEL@4_4:	; if_break_bb39
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 136
	mov x, #0x08
	mulu x
	addw ax, #LOWW(_g_LCD_NumMap)
	movw bc, ax
	addw ax, #0xFFFC
	mov es, #LOW(HIGHW(_g_LCD_NumMap))
	movw hl, ax
	movw ax, bc
	addw ax, #0xFFFA
	movw de, ax
	movw ax, es:[hl]
	movw ax, es:[de]
	movw de, ax
	movw ax, [sp+0x02]
	xchw ax, de
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 137
	decw bc
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 136
	movw [de], ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 137
	decw bc
	movw ax, bc
	movw hl, ax
	mov a, es:[hl]
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 139
	cmp0 a
	clrb a
	bnz $.BB@LABEL@4_6
.BB@LABEL@4_5:	; if_then_bb64
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 141
	mov es, #LOW(HIGHW(_g_LCD_NumType))
	pop bc
	push bc
	mov a, es:LOWW(_g_LCD_NumType)[b]
.BB@LABEL@4_6:	; if_break_bb71
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 149
	mov [de+0x02], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 151
	clrb a
	br $.BB@LABEL@4_8
.BB@LABEL@4_7:	; bb76
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 152
	mov a, #0x80
.BB@LABEL@4_8:	; bb76
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 0
	addw sp, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 152
	ret
.LFE4:
	.TYPE _LCD_WriteRAMDigitInfo,function,.LFE5-_LCD_WriteRAMDigitInfo
_LCD_WriteRAMDigitInfo:
	.STACK _LCD_WriteRAMDigitInfo = 6
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 163
	push ax
	movw hl, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 165
	mov a, c
	and a, #0x0F
	or a, [hl]
	mov b, a
	pop de
	push de
	mov a, b
	mov [de], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 166
	incw de
	movw ax, de
	movw [sp+0x00], ax
	movw hl, ax
	mov a, c
	shr a, 0x04
	or a, [hl]
	mov [hl], a
	pop ax
	ret
.LFE5:
	.TYPE _LCD_ClearRAMDigitInfo,function,.LFE6-_LCD_ClearRAMDigitInfo
_LCD_ClearRAMDigitInfo:
	.STACK _LCD_ClearRAMDigitInfo = 6
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 178
	push ax
	movw hl, ax
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 180
	mov a, c
	and a, [hl]
	and a, #0x0F
	mov b, a
	pop de
	push de
	mov a, b
	mov [de], a
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_drv_lcd_ext.c", 181
	incw de
	movw ax, de
	movw [sp+0x00], ax
	movw hl, ax
	mov a, c
	shr a, 0x04
	and a, [hl]
	mov [hl], a
	pop ax
	ret
.LFE6:
