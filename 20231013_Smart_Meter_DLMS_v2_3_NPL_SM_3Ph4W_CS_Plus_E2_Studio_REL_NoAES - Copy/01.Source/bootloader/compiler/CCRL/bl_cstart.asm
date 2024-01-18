; Copyright (C) 2014 Renesas Electronics Corporation
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which
; it was furnished by Renesas Electronics Corporation. No part of this
; program may be reproduced or disclosed to others, in any
; form, without the prior written permission of Renesas Electronics
; Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE.

$IFNDEF __RENESAS_VERSION__
__RENESAS_VERSION__ .EQU    0x01000000
$ENDIF

    .public _bl_start
    
;-----------------------------------------------------------------------------
;   RAM section
;-----------------------------------------------------------------------------
.SECTION .dataR, DATA
;.SECTION .sdataR, DATA
; .SECTION .datafR, DATAF
; .SECTION .textfR, TEXTF

SETUP_CPU_REGISTERS .MACRO
	;--------------------------------------------------
	; setting register bank
	;--------------------------------------------------
;	SEL	RB0

	;--------------------------------------------------
	; setting mirror area
	;--------------------------------------------------
;	ONEB    !PMC		; mirror area = 10000-1FFFFH

	;--------------------------------------------------
	; setting the stack pointer
	;--------------------------------------------------
	MOVW    SP, #0xFE20

.ENDM

;-----------------------------------------------------------------------------
;   stack area
;-----------------------------------------------------------------------------
; !!! [CAUTION] !!!
; Set up stack size suitable for a project.
.SECTION .stack_bss, BSS
_stackend:
    .DS     0xe60
_stacktop:

;-----------------------------------------------------------------------------
;   RESET vector
;-----------------------------------------------------------------------------
_bl_start .VECTOR 0

;-----------------------------------------------------------------------------
;   startup
;-----------------------------------------------------------------------------
.SECTION BStaTx_n, TEXT

_bl_start:
    SETUP_CPU_REGISTERS         ;Macro call due to SP setting
    

_bl_stack_init:
    ;--------------------------------------------------
    ; initializing stack area
    ;--------------------------------------------------
    MOVW    AX,#LOWW(STARTOF(.stack_bss))
    
    CALL    !_bl_stkinit

    ;--------------------------------------------------
    ; hardware initialization
    ;--------------------------------------------------
    CALL    !_bl_hdwinit
    
_bl__section_init:
    ;--------------------------------------------------
    ; initializing BSS
    ;--------------------------------------------------
    ; clear external variables which doesn't have initial value (near)
    MOVW    HL,#LOWW(STARTOF(.bss))
    MOVW    AX,#LOWW(STARTOF(.bss) + SIZEOF(.bss))
    BR  $.L2_BSS
.L1_BSS:
    MOV [HL+0],#0
    INCW    HL
.L2_BSS:
    CMPW    AX,HL
    BNZ $.L1_BSS
    
    ; clear BLBss_n
    MOVW    HL,#LOWW(STARTOF(BLBss_n))
    MOVW    AX,#LOWW(STARTOF(BLBss_n) + SIZEOF(BLBss_n))
    BR  $.L2_BLBSS
.L1_BLBSS:
    MOV [HL+0],#0
    INCW    HL
.L2_BLBSS:
    CMPW    AX,HL
    BNZ $.L1_BLBSS

    ;--------------------------------------------------
    ; ROM data copy
    ;--------------------------------------------------
    ; copy external variables having initial value (near)
    MOV ES,#HIGHW(STARTOF(.data))
    MOVW    BC,#LOWW(SIZEOF(.data))
    BR  $.L2_DATA
.L1_DATA:
    DECW    BC
    MOV A,ES:LOWW(STARTOF(.data))[BC]
    MOV LOWW(STARTOF(.dataR))[BC],A
.L2_DATA:
    CLRW    AX
    CMPW    AX,BC
    BNZ $.L1_DATA
    
    ; romization for BLData
    MOV ES,#HIGHW(STARTOF(BLData_n))
    MOVW    BC,#LOWW(SIZEOF(BLData_n))
    BR  $.L2_BLDATA
.L1_BLDATA:
    DECW    BC
    MOV A,ES:LOWW(STARTOF(BLData_n))[BC]
    MOV LOWW(STARTOF(BLDataR_n))[BC],A
.L2_BLDATA:
    CLRW    AX
    CMPW    AX,BC
    BNZ $.L1_BLDATA
    
    ;--------------------------------------------------
    ; call main function
    ;--------------------------------------------------
    CALL    !!_bl_main ; bl_main();
    
    ;--------------------------------------------------
    ; call exit function
    ;--------------------------------------------------
    CLRW    AX      ; exit(0)
_exit:
    BR  $_exit
    
;-----------------------------------------------------------------------------
;   section
;-----------------------------------------------------------------------------
$IF (__RENESAS_VERSION__ >= 0x01010000)
.SECTION .RLIB, TEXTF
.L_section_RLIB:
.SECTION .SLIB, TEXTF
.L_section_SLIB:
$ENDIF
.SECTION .textf, TEXTF
.L_section_textf:
;.SECTION .const, CONST
;.L_section_const:
.SECTION .constf, CONSTF
.L_section_constf:
.SECTION .data, DATA
.L_section_data:
;.SECTION .dataf, DATAF
;.L_section_dataf:
;.SECTION .sdata, SDATA
;.L_section_sdata:
.SECTION .bss, BSS
.L_section_bss:
;.SECTION .bssf, BSSF
;.L_section_bssf:
;.SECTION .sbss, SBSS
;.L_section_sbss:
