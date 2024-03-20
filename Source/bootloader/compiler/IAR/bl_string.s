
        #define SHT_PROGBITS 0x1

        PUBLIC _BL_memcmp_nn
        PUBLIC _BL_memcpy_nf
        PUBLIC _BL_memcpy_nn


        SECTION `.text`:CODE:NOROOT(0)
        CODE
_BL_memcmp_nn:
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
                 

        SECTION `.text`:CODE:NOROOT(0)
        CODE
_BL_memcpy_nf:
        PUSH      BC                  
        PUSH      DE                  
        SUBW      SP, #0x6            
        MOVW      HL, AX              
        MOVW      AX, [SP+0x0E]       
        MOVW      BC, AX              
        MOVW      AX, HL              
        MOVW      [SP], AX            
        MOV       A, [SP+0x08]        
        MOV       ES, A               
        MOV       A, ES               
        MOV       [SP+0x04], A        
        MOVW      AX, DE              
        MOVW      [SP+0x02], AX       
        BR        S:??BL_memcpy_nn_0   
??BL_memcpy_nf_0:
        MOV       A, [SP+0x04]        
        MOV       ES, A               
        MOVW      AX, [SP+0x02]       
        MOVW      HL, AX              
        MOV       A, ES:[HL]          
        MOV       D, A                
        MOVW      AX, [SP]            
        MOVW      HL, AX              
        MOV       A, D                
        MOV       [HL], A             
        MOVW      AX, HL              
        INCW      AX                  
        MOVW      [SP], AX            
        MOVW      AX, [SP+0x02]       
        MOVW      DE, AX              
        INCW      DE                  
        MOV       A, ES               
        MOV       [SP+0x04], A        
        MOVW      AX, DE              
        MOVW      [SP+0x02], AX       
        DECW      BC                  
??BL_memcpy_nn_0:
        MOVW      AX, BC              
        CLRW      BC                  
        CMPW      AX, BC              
        MOVW      BC, AX              
        BNZ       ??BL_memcpy_nf_0    
        ADDW      SP, #0xA            
        RET                           

        SECTION `.text`:CODE:NOROOT(0)
        CODE
_BL_memcpy_nn:
        PUSH      AX                  
        PUSH      AX                  
        PUSH      BC                  
        POP       HL                  
        PUSH      DE                  
        POP       BC                  
        PUSH      HL                  
        POP       DE                  
        MOVW      HL, AX              
        BR        S:??BL_memcpy_nn_1   
??BL_memcpy_nn_2:
        MOV       A, [DE]             
        MOV       [HL], A             
        INCW      HL                  
        INCW      DE                  
        DECW      BC                  
??BL_memcpy_nn_1:
        XCHW      AX, BC              
        CMPW      AX, #0x0            
        XCHW      AX, BC              
        BNZ       ??BL_memcpy_nn_2    
        ADDW      SP, #0x4            
        RET                           

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(1)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
