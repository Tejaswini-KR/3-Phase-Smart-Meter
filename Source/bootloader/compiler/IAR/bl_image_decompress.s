
        #define SHT_PROGBITS 0x1
        #define SHT_IAR_NOINIT 0xabdc5467
        #define SHF_WRITE 0x1

        EXTERN ?UL_CMP_L03
        EXTERN _BL_FLASH_WriteBlock
        EXTERN _BL_HASHING_Calculate
        EXTERN _BL_HASHING_GetResult
        EXTERN _BL_HASHING_Init
        EXTERN _BL_IMAGE_EraseUserAppInROM
        EXTERN _BL_OPERATION_ClearConfirmCode
        EXTERN _BL_OPERATION_GetProperties
        EXTERN _BL_OPERATION_SetConfirmCode
        EXTERN _BL_SFL_DeviceRead
        EXTERN _BL_memcmp_nn
        EXTERN _BL_memcpy_nf
        EXTERN _g_bl_image_read_ROM_buffer

        PUBLIC _BL_IMAGE_TransferUserAppToROM
        PUBLIC __A_WDTE


        ASEGN `.bss.noinit`:DATA:NOROOT,0fffabH
        SECTION_TYPE SHT_IAR_NOINIT, SHF_WRITE
        SECTION_GROUP __A_WDTE
__A_WDTE:
        DS 1

        SECTION `.text`:CODE:NOROOT(0)
        CODE
_BL_IMAGE_TransferUserAppToROM:


        PUSH      AX                  

        SUBW      SP, #0x38           
        CLRB      A                   
        MOV       [SP], A             
        MOVW      AX, SP              
        ADDW      AX, #0x18           
        CALL      _BL_OPERATION_GetProperties   
        MOV       A, #0x8             
        CALL      _BL_OPERATION_SetConfirmCode   
        MOV       A, [SP+0x39]        
        CMP       A, #0x1             
        BZ        ??BL_IMAGE_TransferUserAppToROM_0   

        CMP       A, #0x2             
        BZ        ??BL_IMAGE_TransferUserAppToROM_0   

        MOV       A, #0x5             
        BR        N:??BL_IMAGE_TransferUserAppToROM_1   

??BL_IMAGE_TransferUserAppToROM_0:
        ONEW      AX                  
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0x3            
        MOVW      DE, AX              
        MOVW      AX, [SP+0x2C]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x2A]       
        CALL      _BL_SFL_DeviceRead   
        MOV       A, [SP+0x03]        
        MOV       X, A                
        CLRB      A                   
        SHLW      AX, 0x3             
        INCW      AX                  
        INCW      AX                  
        MOVW      BC, AX              
        SARW      AX, 0xF             
        XCHW      AX, BC              
        POP       HL                  
        MOVW      [SP+0x14], AX       
        MOVW      AX, BC              
        MOVW      [SP+0x16], AX       
        CALL      _BL_HASHING_Init    
        MOVW      AX, [SP+0x14]       
        PUSH      AX                  
        MOVW      DE, #LWRD(_g_bl_image_read_ROM_buffer)   
        MOVW      AX, [SP+0x2C]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x2A]       
        CALL      _BL_SFL_DeviceRead   
        MOVW      AX, [SP+0x16]       
        MOVW      BC, AX              
        MOVW      AX, #LWRD(_g_bl_image_read_ROM_buffer)   
        CALL      _BL_HASHING_Calculate   
        MOVW      AX, [SP+0x16]       
        MOVW      [SP+0x12], AX       
        MOVW      AX, [SP+0x18]       
        MOVW      [SP+0x14], AX       
        MOV       0xFFFAB, #0xAC      
        CLRB      A                   
        MOV       [SP+0x04], A        
        POP       AX                  
        BR        N:??BL_IMAGE_TransferUserAppToROM_2   

??BL_IMAGE_TransferUserAppToROM_3:
        CLRB      A                   
        SHLW      AX, 0x3             
        MOVW      BC, AX              
        SARW      AX, 0xF             
        XCHW      AX, BC              
        MOVW      [SP+0x14], AX       
        MOVW      AX, BC              
        MOVW      [SP+0x16], AX       
        MOVW      AX, #0x4            
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0xA            
        PUSH      AX                  
        MOVW      AX, [SP+0x2E]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2C]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x18]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        ADDW      AX, #0x1            
        SKNC
        INCW      BC                  
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        MOVW      AX, #0x4            
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0x10           
        PUSH      AX                  
        MOVW      AX, [SP+0x30]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2E]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x1C]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x1A]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        ADDW      AX, #0x5            
        SKNC
        INCW      BC                  
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        ADDW      SP, #0x4            
        MOVW      AX, [SP+0x1A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x1A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x0E]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x0C]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BC        ??BL_IMAGE_TransferUserAppToROM_4   

        PUSH      BC                  
        PUSH      AX                  
        MOVW      AX, [SP+0x22]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x20]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BNC       ??BL_IMAGE_TransferUserAppToROM_5   

        MOVW      AX, [SP+0x22]       
        PUSH      AX                  
        MOVW      AX, [SP+0x22]       
        PUSH      AX                  
        MOVW      AX, [SP+0x0E]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x0C]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BC        ??BL_IMAGE_TransferUserAppToROM_4   

??BL_IMAGE_TransferUserAppToROM_5:
        MOVW      AX, [SP+0x0A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x0A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x2A]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x28]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BNC       ??BL_IMAGE_TransferUserAppToROM_6   

??BL_IMAGE_TransferUserAppToROM_4:
        MOV       A, #0x4             
        MOV       [SP], A             

??BL_IMAGE_TransferUserAppToROM_6:
        MOVW      AX, [SP+0x1A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x1A]       
        PUSH      AX                  
        MOVW      AX, [SP+0x12]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x10]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BC        ??BL_IMAGE_TransferUserAppToROM_7   

        PUSH      BC                  
        PUSH      AX                  
        MOVW      AX, [SP+0x22]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x20]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BNC       ??BL_IMAGE_TransferUserAppToROM_8   

        MOVW      AX, [SP+0x22]       
        PUSH      AX                  
        MOVW      AX, [SP+0x22]       
        PUSH      AX                  
        MOVW      AX, [SP+0x12]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x10]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BC        ??BL_IMAGE_TransferUserAppToROM_7   

??BL_IMAGE_TransferUserAppToROM_8:
        MOVW      AX, [SP+0x0E]       
        PUSH      AX                  
        MOVW      AX, [SP+0x0E]       
        PUSH      AX                  
        MOVW      AX, [SP+0x2A]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x28]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BNC       ??BL_IMAGE_TransferUserAppToROM_9   

??BL_IMAGE_TransferUserAppToROM_7:
        MOV       A, #0x4             
        MOV       [SP], A             

??BL_IMAGE_TransferUserAppToROM_9:
        MOV       A, [SP+0x02]        
        INC       A                   
        MOV       [SP+0x02], A        

??BL_IMAGE_TransferUserAppToROM_2:
        MOV       A, [SP+0x02]        
        MOV       X, A                
        MOV       A, [SP+0x01]        
        CMP       X, A                
        SKNC                          
        BR        N:??BL_IMAGE_TransferUserAppToROM_3   

        MOV       A, [SP]             
        CMP0      A                   
        SKZ                           
        BR        N:??BL_IMAGE_TransferUserAppToROM_10   

        MOV       A, [SP+0x39]        
        CMP       A, #0x2             
        BNZ       ??BL_IMAGE_TransferUserAppToROM_11   

        CALL      _BL_IMAGE_EraseUserAppInROM   
        CMP       A, #0x1             
        BNZ       ??BL_IMAGE_TransferUserAppToROM_11   

        MOV       A, #0x2             

??BL_IMAGE_TransferUserAppToROM_1:
        MOV       [SP], A             
        BR        N:??BL_IMAGE_TransferUserAppToROM_10   

??BL_IMAGE_TransferUserAppToROM_11:
        CLRB      A                   
        BR        N:??BL_IMAGE_TransferUserAppToROM_12   

??BL_IMAGE_TransferUserAppToROM_13:
        MOVW      AX, #0x400          
        PUSH      AX                  
        MOVW      AX, [SP+0x0C]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x0A]       
        MOVW      DE, AX              
        MOVW      AX, #LWRD(_g_bl_image_read_ROM_buffer)   
        CALL      _BL_memcpy_nf       
        POP       AX                  

??BL_IMAGE_TransferUserAppToROM_14:
        MOVW      BC, #0x400          
        MOVW      AX, #LWRD(_g_bl_image_read_ROM_buffer)   
        CALL      _BL_HASHING_Calculate   
        MOVW      AX, [SP+0x0A]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x08]       
        ADDW      AX, #0x400          
        SKNC
        INCW      BC                  
        MOVW      [SP+0x08], AX       
        MOVW      AX, BC              
        MOVW      [SP+0x0A], AX       
        MOVW      AX, [SP+0x12]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x10]       
        ADDW      AX, #0x400          
        SKNC
        INCW      BC                  
        MOVW      [SP+0x10], AX       
        MOVW      AX, BC              
        MOVW      [SP+0x12], AX       
        MOV       0xFFFAB, #0xAC      

??BL_IMAGE_TransferUserAppToROM_15:
        MOVW      AX, [SP+0x0E]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x0C]       
        ADDW      AX, #0x1            
        SKNC
        INCW      BC                  
        PUSH      BC                  
        PUSH      AX                  
        MOVW      AX, [SP+0x0E]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x0C]       
        CALL      N:?UL_CMP_L03       
        ADDW      SP, #0x4            
        BNC       ??BL_IMAGE_TransferUserAppToROM_16   

        MOVW      AX, #0x400          
        PUSH      AX                  
        MOVW      DE, #LWRD(_g_bl_image_read_ROM_buffer)   
        PUSH      DE                  
        MOVW      AX, [SP+0x2E]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2C]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x16]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x14]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        MOV       A, [SP+0x3B]        
        POP       HL                  
        CMP       A, #0x2             
        BNZ       ??BL_IMAGE_TransferUserAppToROM_14   

        MOVW      DE, #LWRD(_g_bl_image_read_ROM_buffer)   
        MOVW      AX, [SP+0x0A]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x08]       
        CALL      _BL_FLASH_WriteBlock   
        CMP0      A                   
        SKNZ                          
        BR        N:??BL_IMAGE_TransferUserAppToROM_13   

        MOV       A, #0x3             
        MOV       [SP], A             

??BL_IMAGE_TransferUserAppToROM_16:
        MOV       A, [SP+0x02]        
        INC       A                   

??BL_IMAGE_TransferUserAppToROM_12:
        MOV       [SP+0x02], A        
        MOV       A, [SP+0x02]        
        MOV       X, A                
        MOV       A, [SP+0x01]        
        CMP       X, A                
        BNC       ??BL_IMAGE_TransferUserAppToROM_17   

        CLRB      A                   
        SHLW      AX, 0x3             
        MOVW      BC, AX              
        SARW      AX, 0xF             
        XCHW      AX, BC              
        MOVW      [SP+0x14], AX       
        MOVW      AX, BC              
        MOVW      [SP+0x16], AX       
        MOVW      AX, #0x4            
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0xA            
        PUSH      AX                  
        MOVW      AX, [SP+0x2E]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2C]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x18]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        ADDW      AX, #0x1            
        SKNC
        INCW      BC                  
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        MOVW      AX, #0x4            
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0x10           
        PUSH      AX                  
        MOVW      AX, [SP+0x30]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2E]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x1C]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x1A]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        ADDW      AX, #0x5            
        SKNC
        INCW      BC                  
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        ADDW      SP, #0x4            
        BR        N:??BL_IMAGE_TransferUserAppToROM_15   

??BL_IMAGE_TransferUserAppToROM_17:
        MOVW      AX, #0x2            
        PUSH      AX                  
        MOVW      AX, SP              
        ADDW      AX, #0x5            
        PUSH      AX                  
        MOVW      AX, [SP+0x2E]       
        MOVW      HL, AX              
        MOVW      AX, [SP+0x2C]       
        MOVW      DE, AX              
        MOVW      AX, [SP+0x16]       
        MOVW      BC, AX              
        MOVW      AX, [SP+0x14]       
        ADDW      AX, DE              
        SKNC
        INCW      BC                  
        XCHW      AX, BC              
        ADDW      AX, HL              
        XCHW      AX, BC              
        POP       DE                  
        CALL      _BL_SFL_DeviceRead   
        MOVW      AX, SP              
        ADDW      AX, #0x7            
        CALL      _BL_HASHING_GetResult   
        POP       AX                  

??BL_IMAGE_TransferUserAppToROM_10:
        MOV       A, #0x8             
        CALL      _BL_OPERATION_ClearConfirmCode   
        MOV       A, [SP]             
        CMP0      A                   
        BNZ       ??BL_IMAGE_TransferUserAppToROM_18   

        MOVW      DE, #0x2            
        MOVW      AX, SP              
        ADDW      AX, #0x3            
        MOVW      BC, AX              
        INCW      AX                  
        INCW      AX                  
        CALL      _BL_memcmp_nn       
        CLRW      BC                  
        CMPW      AX, BC              
        BZ        ??BL_IMAGE_TransferUserAppToROM_18   

        ONEB      A                   
        MOV       [SP], A             

??BL_IMAGE_TransferUserAppToROM_18:
        MOV       A, [SP]             
        ADDW      SP, #0x3A           
        RET                           


        REQUIRE __A_WDTE

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(1)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
