#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_crc.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_crc.cref
#@   -o Release\bl_r_cg_crc.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_70c5407556634a6ebaa58c3a8612cb9bhswsjiqp.5sp
#@  compiled at Fri Aug 16 14:34:49 2024

	.PUBLIC _R_CRC_Set
	.PUBLIC _R_CRC_GetResult
	.PUBLIC _R_CRC_Calculate

	.SECTION .text,TEXT
	.TYPE _R_CRC_Set,function,.LFE1-_R_CRC_Set
_R_CRC_Set:
	.STACK _R_CRC_Set = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 56
	movw !0x02FA, ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 58
	ret
.LFE1:
	.TYPE _R_CRC_GetResult,function,.LFE2-_R_CRC_GetResult
_R_CRC_GetResult:
	.STACK _R_CRC_GetResult = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 69
	movw ax, !0x02FA
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 70
	ret
.LFE2:
	.TYPE _R_CRC_Calculate,function,.LFE3-_R_CRC_Calculate
_R_CRC_Calculate:
	.STACK _R_CRC_Calculate = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 81
	movw de, ax
	incw bc
.BB@LABEL@3_1:	; bb8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 0
	movw ax, bc
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 83
	addw ax, #0xFFFF
	movw bc, ax
	bz $.BB@LABEL@3_3
.BB@LABEL@3_2:	; bb
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 85
	mov a, [de]
	mov 0xFFFAC, a
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 88
	incw de
	br $.BB@LABEL@3_1
.BB@LABEL@3_3:	; return
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_crc.c", 90
	ret
.LFE3:
