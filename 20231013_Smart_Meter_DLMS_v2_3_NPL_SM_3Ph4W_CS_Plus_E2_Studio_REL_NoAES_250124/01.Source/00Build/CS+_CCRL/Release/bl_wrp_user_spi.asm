#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\wrapper\bl_wrp_user_spi.c
#@   -cpu=S3
#@   -cref=Release\bl_wrp_user_spi.cref
#@   -o Release\bl_wrp_user_spi.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_9da69feddc5b4e468dede3adc87d5235imvd2s12.xx1
#@  compiled at Mon Aug 12 12:54:20 2024

	.PUBLIC _WRP_SPI_Init
	.PUBLIC _WRP_SPI_Start
	.EXTERN _R_CSI30_Start
	.PUBLIC _WRP_SPI_Stop
	.EXTERN _R_CSI30_Stop
	.PUBLIC _WRP_SPI_SendReceive
	.EXTERN _R_CSI30_Send_Receive
	.PUBLIC _WRP_SPI_SendEndCallback
	.EXTERN _SFL_SendEndCallback
	.PUBLIC _WRP_SPI_ReceiveEndCallback
	.EXTERN _SFL_ReceiveEndCallback

	.SECTION .text,TEXT
	.TYPE _WRP_SPI_Init,function,.LFE1-_WRP_SPI_Init
_WRP_SPI_Init:
	.STACK _WRP_SPI_Init = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 74
	ret
.LFE1:
	.TYPE _WRP_SPI_Start,function,.LFE2-_WRP_SPI_Start
_WRP_SPI_Start:
	.STACK _WRP_SPI_Start = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 88
	br !_R_CSI30_Start
.LFE2:
	.TYPE _WRP_SPI_Stop,function,.LFE3-_WRP_SPI_Stop
_WRP_SPI_Stop:
	.STACK _WRP_SPI_Stop = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 100
	br !_R_CSI30_Stop
.LFE3:
	.TYPE _WRP_SPI_SendReceive,function,.LFE4-_WRP_SPI_SendReceive
_WRP_SPI_SendReceive:
	.STACK _WRP_SPI_SendReceive = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 113
	call !_R_CSI30_Send_Receive
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 115
	clrw bc
	cmpw ax, bc
	oneb a
	sknz
.BB@LABEL@4_1:	; entry
	clrb a
.BB@LABEL@4_2:	; entry
	ret
.LFE4:
	.TYPE _WRP_SPI_SendEndCallback,function,.LFE5-_WRP_SPI_SendEndCallback
_WRP_SPI_SendEndCallback:
	.STACK _WRP_SPI_SendEndCallback = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 135
	br !_SFL_SendEndCallback
.LFE5:
	.TYPE _WRP_SPI_ReceiveEndCallback,function,.LFE6-_WRP_SPI_ReceiveEndCallback
_WRP_SPI_ReceiveEndCallback:
	.STACK _WRP_SPI_ReceiveEndCallback = 4
	.LINE "E:/Git/3-Phase-Smart-Meter-1/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES_250124/01.Source/bootloader/wrapper/bl_wrp_user_spi.c", 148
	br !_SFL_ReceiveEndCallback
.LFE6:
