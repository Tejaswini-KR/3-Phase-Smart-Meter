#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\display\bl_r_lcd_display.c
#@   -cpu=S3
#@   -cref=Release\bl_r_lcd_display.cref
#@   -o Release\bl_r_lcd_display.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_5fec864fb9f542c6948cde67d01771eaf1u3zfok.kjf
#@  compiled at Fri Aug 16 14:34:48 2024

	.PUBLIC _LCD_DisplayAll
	.EXTERN _LCD_RamSetAll
	.PUBLIC _LCD_ClearAll
	.EXTERN _LCD_RamClearAll
	.PUBLIC _LCD_DisplayDigit
	.EXTERN _LCD_GetNumInfo
	.EXTERN _LCD_WriteRAMDigitInfo

	.SECTION .text,TEXT
	.TYPE _LCD_DisplayAll,function,.LFE1-_LCD_DisplayAll
_LCD_DisplayAll:
	.STACK _LCD_DisplayAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 64
	br !_LCD_RamSetAll
.LFE1:
	.TYPE _LCD_ClearAll,function,.LFE2-_LCD_ClearAll
_LCD_ClearAll:
	.STACK _LCD_ClearAll = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 76
	br !_LCD_RamClearAll
.LFE2:
	.TYPE _LCD_DisplayDigit,function,.LFE3-_LCD_DisplayDigit
_LCD_DisplayDigit:
	.STACK _LCD_DisplayDigit = 10
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 88
	subw sp, #0x04
	push ax
	mov a, [sp+0x00]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 95
	cmp a, #0x0B
	bnc $.BB@LABEL@3_5
.BB@LABEL@3_1:	; entry
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 0
	mov a, [sp+0x01]
	cmp a, #0x08
	bnc $.BB@LABEL@3_5
.BB@LABEL@3_2:	; if_break_bb
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 104
	movw bc, ax
	mov a, [sp+0x01]
	mov x, a
	mov a, [sp+0x00]
	call !_LCD_GetNumInfo
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 105
	cmp a, #0x80
	bz $.BB@LABEL@3_5
.BB@LABEL@3_3:	; if_break_bb32
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 110
	movw ax, [sp+0x02]
	movw de, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 111
	clrw bc
	cmpw ax, bc
	bz $.BB@LABEL@3_5
.BB@LABEL@3_4:	; if_break_bb41
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 117
	mov a, [sp+0x04]
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 118
	mov c, a
	movw ax, de
	call !_LCD_WriteRAMDigitInfo
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 120
	clrb a
	br $.BB@LABEL@3_6
.BB@LABEL@3_5:	; bb47
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 121
	mov a, #0x80
.BB@LABEL@3_6:	; bb47
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 0
	addw sp, #0x06
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/display/bl_r_lcd_display.c", 121
	ret
.LFE3:
