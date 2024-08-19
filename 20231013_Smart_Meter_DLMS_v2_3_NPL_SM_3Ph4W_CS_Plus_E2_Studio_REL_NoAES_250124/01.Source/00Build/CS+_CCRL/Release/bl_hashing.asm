#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\core\bl_hashing.c
#@   -cpu=S3
#@   -cref=Release\bl_hashing.cref
#@   -o Release\bl_hashing.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_caf1fd5b23b1457f83b05fca17d864a9yxte2upl.xtt
#@  compiled at Fri Aug 16 14:34:50 2024

	.PUBLIC _BL_HASHING_Init
	.EXTERN _R_CRC_Set
	.PUBLIC _BL_HASHING_Calculate
	.EXTERN _R_CRC_Calculate
	.PUBLIC _BL_HASHING_GetResult
	.EXTERN _R_CRC_GetResult
	.EXTERN _BL_memcpy_nn
	.PUBLIC _BL_HASHING_DigestUserAppBackupSFL
	.PUBLIC _BL_HASHING_DigestUserAppROM

	.SECTION .text,TEXT
	.TYPE _BL_HASHING_Init,function,.LFE1-_BL_HASHING_Init
_BL_HASHING_Init:
	.STACK _BL_HASHING_Init = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 81
	clrw ax
	decw ax
	br !_R_CRC_Set
.LFE1:
	.TYPE _BL_HASHING_Calculate,function,.LFE2-_BL_HASHING_Calculate
_BL_HASHING_Calculate:
	.STACK _BL_HASHING_Calculate = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 91
	br !_R_CRC_Calculate
.LFE2:
	.TYPE _BL_HASHING_GetResult,function,.LFE3-_BL_HASHING_GetResult
_BL_HASHING_GetResult:
	.STACK _BL_HASHING_GetResult = 8
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 102
	push hl
	push ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 107
	call !_R_CRC_GetResult
	movw bc, ax
	clrw ax
	decw ax
	subw ax, bc
	movw [sp+0x02], ax
	movw ax, sp
	incw ax
	incw ax
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 110
	movw bc, ax
	movw ax, [sp+0x00]
	movw de, #0x0002
	call !_BL_memcpy_nn
	addw sp, #0x04
	ret
.LFE3:
	.SECTION BLShareTx_n,TEXT
	.TYPE _BL_HASHING_DigestUserAppBackupSFL,function,.LFE4-_BL_HASHING_DigestUserAppBackupSFL
_BL_HASHING_DigestUserAppBackupSFL:
	.STACK _BL_HASHING_DigestUserAppBackupSFL = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 139
	ret
.LFE4:
	.TYPE _BL_HASHING_DigestUserAppROM,function,.LFE5-_BL_HASHING_DigestUserAppROM
_BL_HASHING_DigestUserAppROM:
	.STACK _BL_HASHING_DigestUserAppROM = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/core/bl_hashing.c", 153
	ret
.LFE5:
