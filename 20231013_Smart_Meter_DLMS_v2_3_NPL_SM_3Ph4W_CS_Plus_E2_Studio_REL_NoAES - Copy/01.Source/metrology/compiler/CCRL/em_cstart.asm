; Copyright (C) 2014 Renesas Electronics Corporation
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which
; it was furnished by Renesas Electronics Corporation. No part of this
; program may be reproduced or disclosed to others, in any
; form, without the prior written permission of Renesas Electronics
; Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE.

    .public _em_cstart
    .extern _EM_ForceLinking
;-----------------------------------------------------------------------------
;   RAM section
;-----------------------------------------------------------------------------
.SECTION .dataR, DATA
.SECTION .sdataR, DATA
; .SECTION .datafR, DATAF
; .SECTION .textfR, TEXTF

;-----------------------------------------------------------------------------
;   startup
;-----------------------------------------------------------------------------
.SECTION EMText_f, TEXTF

_em_cstart:
    ;--------------------------------------------------
    ; setting register bank
    ;--------------------------------------------------
;   SEL RB0

    ;--------------------------------------------------
    ; setting mirror area
    ;--------------------------------------------------
;   ONEB    !PMC        ; mirror area = 10000-1FFFFH
    
    ;--------------------------------------------------
    ; Force linking EM Symbol
    ;--------------------------------------------------
    CALL !!_EM_ForceLinking

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

    ;--------------------------------------------------
    ; call exit function
    ;--------------------------------------------------
    RET

