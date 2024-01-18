#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\driver\bl_r_cg_tau_user.c
#@   -cpu=S3
#@   -cref=Release\bl_r_cg_tau_user.cref
#@   -o Release\bl_r_cg_tau_user.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_36da10b8dae2468982e43cd9ab52569dr52vlko2.l5l
#@  compiled at Thu Dec 28 12:19:47 2023

	.PUBLIC _r_tau0_channel0_interrupt
	.EXTERN _BL_RECOVERY_TimerEndCallBack

	.SECTION .text,TEXT
	.TYPE _r_tau0_channel0_interrupt,function,.LFE1-_r_tau0_channel0_interrupt
_r_tau0_channel0_interrupt:
	.STACK _r_tau0_channel0_interrupt = 4
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_tau_user.c", 60
	ei
	.LINE "E:/SM_3phase/New folder/20231013_Smart_Meter_DLMS_v2_3_NPL_SM_3Ph4W_CS_Plus_E2_Studio_REL_NoAES - Copy/01.Source/bootloader/driver/bl_r_cg_tau_user.c", 62
	br !_BL_RECOVERY_TimerEndCallBack
.LFE1:
