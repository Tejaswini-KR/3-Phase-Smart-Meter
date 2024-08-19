#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_port.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_port.cref
#@   -o Release\bl_r_cg_port.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_da6dff0db6a746758c247334109715ccxeecmpd0.dt4
#@  compiled at Fri Aug 16 14:34:49 2024

	.PUBLIC _R_PORT_Create
	.PUBLIC _R_PORT_StopCreate

	.SECTION .text,TEXT
	.TYPE _R_PORT_Create,function,.LFE1-_R_PORT_Create
_R_PORT_Create:
	.STACK _R_PORT_Create = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 54
	movw de, #0x0300
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 102
	mov [de+0x00], #0x0F
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 103
	mov [de+0x01], #0xFF
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 105
	mov [de+0x02], #0xFF
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 107
	mov [de+0x03], #0xFF
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 109
	mov [de+0x04], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 111
	mov [de+0x05], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 113
	mov [de+0x06], #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 117
	mov 0xFFF00, #0x5F
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 120
	clrb 0xFFF02
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 122
	clrb 0xFFF03
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 125
	mov 0xFFF04, #0x0D
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 127
	mov 0xFFF05, #0x68
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 130
	mov 0xFFF06, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 132
	clrb 0xFFF07
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 135
	clrb 0xFFF08
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 138
	mov 0xFFF0D, #0x81
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 140
	mov 0xFFF0F, #0x07
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 146
	mov 0xFFF20, #0x4B
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 149
	mov 0xFFF21, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 152
	mov 0xFFF22, #0x3D
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 155
	mov 0xFFF23, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 158
	mov 0xFFF24, #0x01
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 160
	mov 0xFFF25, #0x28
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 163
	mov 0xFFF26, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 165
	mov 0xFFF27, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 168
	mov 0xFFF28, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 171
	mov 0xFFF29, #0x00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 174
	mov 0xFFF2F, #0x07
	ret
.LFE1:
	.TYPE _R_PORT_StopCreate,function,.LFE2-_R_PORT_StopCreate
_R_PORT_StopCreate:
	.STACK _R_PORT_StopCreate = 4
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 194
	clrb 0xFFF03
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 195
	clrb 0xFFF05
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 197
	clrb 0xFFF00
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 198
	clrb 0xFFF01
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 199
	clrb 0xFFF02
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 200
	clrb 0xFFF03
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 201
	oneb 0xFFF04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 202
	clrb 0xFFF05
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 203
	mov 0xFFF06, #0x04
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 204
	clrb 0xFFF07
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 205
	clrb 0xFFF08
	.LINE "E:/Git/3-Phase-Smart-Meter/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/driver/bl_r_cg_port.c", 206
	oneb 0xFFF0D
	ret
.LFE2:
