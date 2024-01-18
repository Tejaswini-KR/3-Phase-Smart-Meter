#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_lcd.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_lcd.cref
#@   -o Release\bl_r_cg_lcd.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_e46fd9199bb8478584dbfcaf3d1b2fa7jgm0zaoa.pyn
#@  compiled at Tue Jan 16 17:12:05 2024

	.PUBLIC _R_LCD_Create
	.PUBLIC _R_LCD_Start
	.PUBLIC _R_LCD_Stop
	.PUBLIC _R_LCD_Set_VoltageOn
	.PUBLIC _R_LCD_Set_VoltageOff
	.PUBLIC _R_LCD_PowerOff
	.PUBLIC _R_LCD_PowerOn

	.SECTION .text,TEXT
	.TYPE _R_LCD_Create,function,.LFE1-_R_LCD_Create
_R_LCD_Create:
	.STACK _R_LCD_Create = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 60
	ret
.LFE1:
	.TYPE _R_LCD_Start,function,.LFE2-_R_LCD_Start
_R_LCD_Start:
	.STACK _R_LCD_Start = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 101
	set1 0xFFF41.7
	ret
.LFE2:
	.TYPE _R_LCD_Stop,function,.LFE3-_R_LCD_Stop
_R_LCD_Stop:
	.STACK _R_LCD_Stop = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 112
	clr1 0xFFF41.7
	ret
.LFE3:
	.TYPE _R_LCD_Set_VoltageOn,function,.LFE4-_R_LCD_Set_VoltageOn
_R_LCD_Set_VoltageOn:
	.STACK _R_LCD_Set_VoltageOn = 8
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 121
	subw sp, #0x04
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 125
	set1 0xFFF41.5
	clrw ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 128
	movw [sp+0x02], ax
.BB@LABEL@4_1:	; entry
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 0
	movw [sp+0x00], ax
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 128
	movw ax, [sp+0x02]
	clrw bc
	cmpw ax, bc
	movw ax, [sp+0x00]
	sknz
.BB@LABEL@4_2:	; bb3
	cmpw ax, #0x0065
.BB@LABEL@4_3:	; bb3
	bnc $.BB@LABEL@4_7
.BB@LABEL@4_4:	; bb
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 130
	nop
	movw ax, [sp+0x02]
	movw de, ax
	movw ax, [sp+0x00]
	addw ax, #0x0001
	movw bc, ax
	movw ax, de
	sknc
.BB@LABEL@4_5:	; bb
	incw ax
.BB@LABEL@4_6:	; bb
	movw [sp+0x02], ax
	movw ax, bc
	br $.BB@LABEL@4_1
.BB@LABEL@4_7:	; bb7
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 133
	set1 0xFFF41.6
	addw sp, #0x04
	ret
.LFE4:
	.TYPE _R_LCD_Set_VoltageOff,function,.LFE5-_R_LCD_Set_VoltageOff
_R_LCD_Set_VoltageOff:
	.STACK _R_LCD_Set_VoltageOff = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 142
	movw hl, #0xFF41
	mov a, #0x3F
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 144
	clr1 [hl].6
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 145
	clr1 [hl].5
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 146
	and a, !0xFF40
	mov 0xFFF40, a
	ret
.LFE5:
	.TYPE _R_LCD_PowerOff,function,.LFE6-_R_LCD_PowerOff
_R_LCD_PowerOff:
	.STACK _R_LCD_PowerOff = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 112
	clr1 0xFFF41.7
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 158
	br $_R_LCD_Set_VoltageOff
.LFE6:
	.TYPE _R_LCD_PowerOn,function,.LFE7-_R_LCD_PowerOn
_R_LCD_PowerOn:
	.STACK _R_LCD_PowerOn = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 101
	set1 0xFFF41.7
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_lcd.c", 170
	br $_R_LCD_Set_VoltageOn
.LFE7:
