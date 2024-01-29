.PUBLIC _BL_memcmp_nn
.PUBLIC _BL_memcpy_nn
.PUBLIC _BL_memcpy_nf

.SECTION .text, TEXT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Function Name: _BL_memcmp_nn
; Interface    : int16_t _BL_memcmp_nn(const void __near *s1, const void __near *s2, uint16_t n)
; Description  : Same like memcmp
;              : But fixed compare near to near region (RAM), not depend on memory model
; Arguments    : s1: pointer to object1
;              : s2: pointer to object2
;              : n: number of bytes to compare
; Return Value : int: a value >0, =0 or <0, depend on s1>s2, s1=s2 or s1<s2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_BL_memcmp_nn:
    ; Arguments allocation on registers:
    ; AX: s1 near pointer
    ; BC: s2 near pointer
    ; DE: size
    
    ; Please note other compiler may require
    ; HL, DE, or BC value to be same value before and after called
    ; This implementation only work best with CCRL
    PUSH    BC
    POP     HL      ;HL holding BC: s2 pointer
    XCHW    AX, DE  ;DE holding AX: s1 pointer
    MOVW    BC, AX  ;BC holding DE: size
    
LOOP_CMP_NN:
    ;while (size > 0)
    CLRW    AX
    CMPW    AX, BC
    BZ      $LOOP_END_CMP_NN
    
    MOV     A, [DE]
    SUB     A, [HL]
    
    INCW    HL
    INCW    DE
    DECW    BC
    
    BZ      $LOOP_CMP_NN
    
LOOP_END_CMP_NN:
    ;A holding substract value when compare
    MOV     X, A
    SAR     A, 0x07
    RET
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Function Name: _BL_memcpy_nn
; Interface    : void _BL_memcpy_nn(const void __near *s1, const void __near *s2, uint16_t n)
; Description  : Same like memcpy except return value
;              : But fixed copy near to near region (RAM), not depend on memory model
; Arguments    : s1: pointer to object1
;              : s2: pointer to object2
;              : n: number of bytes to copy
; Return Value : None
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_BL_memcpy_nn:
    ; Arguments allocation on registers:
    ; AX: dest near pointer
    ; BC: src near pointer
    ; DE: size
    
    ; Please note other compiler may require
    ; HL, DE, or BC value to be same value before and after called
    ; This implementation only work best with CCRL
    PUSH    HL
    PUSH    AX
    POP     HL      ;HL holding AX --> dest near pointer
    PUSH    BC
    PUSH    DE
    POP     BC      ;BC holding DE --> size
    POP     DE      ;DE holding BC --> src near pointer
    
LOOP_NN:
    ;while (size > 0)
    CLRW    AX
    CMPW    AX, BC
    BZ      $LOOP_END_NN
    
    ;*dest = *src;
    MOV     A, [DE]
    MOV     [HL], A
    
    ;dest++;
    INCW    HL
    ;src++;
    INCW    DE
    
    ;size--;
    DECW    BC
    BR      $LOOP_NN
    
LOOP_END_NN:
    ADDW  SP, #0x02
    RET
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Function Name: _BL_memcpy_nf
; Interface    : void _BL_memcpy_nf(const void __near *s1, const void __near *s2, uint16_t n)
; Description  : Same like far memcpy except return value is void and copy destination is near not far
;              : But fixed copy far to near region (RAM), not depend on memory model
; Arguments    : s1: pointer to object1
;              : s2: pointer to object2
;              : n: number of bytes to copy
; Return Value : None
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_BL_memcpy_nf:
    ; AX: dest near pointer
    ; C-DE: src far pointer
    ; [SP+0x00]            : src pointer high byte
    ; [SP+0x02] - [SP+0x03]: dest pointer
    ; [SP+0x04] - [SP+0x05]: HL backup
    ; [SP+0x06] - [SP+0x09]: PC
    ; [SP+0x0A] - [SP+0x0B]: size
    
    ;This implementation reserve HL and BC.
    PUSH    HL
    PUSH    AX
    PUSH    BC
    
    MOVW    HL, AX          ;HL holding dest near pointer
    MOVW    AX, [SP+0x0A]   
    MOVW    BC, AX          ;BC holding size
    
    MOV     A, [SP+0x00]
    MOV     ES, A
    
LOOP_NF:
    ;while (size > 0)
    CLRW    AX
    CMPW    AX, BC
    BZ      $LOOP_END_NF
    
    ;*dest = *src;
    MOV     A, ES:[DE]
    MOV     [HL], A
    
    ;dest++;
    INCW    DE
    INCW    HL
    
    ;size--;
    DECW    BC
    BR      $LOOP_NF
    
LOOP_END_NF:
    POP     BC
    POP     AX
    POP     HL

    RET