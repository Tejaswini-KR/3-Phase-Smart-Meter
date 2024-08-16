#CC-RL Compiler RL78 Assembler Source
#@  CC-RL Version : V1.11.00 [24 Nov 2021]
#@  Commmand :
#@   ..\..\bootloader\display\bl_r_lcd_config.c
#@   -cpu=S3
#@   -cref=Release\bl_r_lcd_config.cref
#@   -o Release\bl_r_lcd_config.obj
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
#@   -exec_time=C:\Users\Tejaswini.kr\AppData\Local\Temp\CSPlusBuildTool_1f8481095a554bbda82f78a24d25342eggdneyix.rwm
#@  compiled at Mon Aug 12 12:54:20 2024

	.PUBLIC _g_LCD_NumMap
	.PUBLIC _g_LCD_NumType
	.PUBLIC _g_DecInfo
	.PUBLIC _g_DecInfo1

	.SECTION .constf,CONSTF
	.ALIGN 2
	.TYPE _g_LCD_NumMap,object,56
_g_LCD_NumMap:
	.DB 0x01
	.DS (1)
	.DB4 0x000F0419
	.DS (1)
	.DS (1)
	.DB 0x02
	.DS (1)
	.DB4 0x000F0417
	.DS (1)
	.DS (1)
	.DB 0x03
	.DS (1)
	.DB4 0x000F0415
	.DS (1)
	.DS (1)
	.DB 0x04
	.DS (1)
	.DB4 0x000F0413
	.DS (1)
	.DS (1)
	.DB 0x05
	.DS (1)
	.DB4 0x000F0411
	.DS (1)
	.DS (1)
	.DB 0x06
	.DS (1)
	.DB4 0x000F040D
	.DS (1)
	.DS (1)
	.DB 0x07
	.DS (1)
	.DB4 0x000F040B
	.DS (1)
	.DS (1)
	.TYPE _g_LCD_NumType,object,11
_g_LCD_NumType:
	.DB 0xBE
	.DB 0xDA
	.DB 0xEE
	.DB 0xF2
	.DB 0xB8
	.DB 0x76
	.DB 0xF8
	.DB 0xEC
	.DB 0xB6
	.DB 0xF0
	.DB 0x60
	.TYPE _g_DecInfo,object,2
_g_DecInfo:
	.DB 0x06
	.DB 0x19
	.TYPE _g_DecInfo1,object,2
_g_DecInfo1:
	.DB 0x05
	.DB 0x1A
