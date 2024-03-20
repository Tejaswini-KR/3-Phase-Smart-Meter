
	.EXTERN _g_bl_image_read_ROM_buffer
	.PUBLIC _BL_IMAGE_TransferUserAppToROM
	.EXTERN _BL_OPERATION_GetProperties
	.EXTERN _BL_OPERATION_SetConfirmCode
	.EXTERN _BL_SFL_DeviceRead
	.EXTERN _BL_HASHING_Init
	.EXTERN _BL_HASHING_Calculate
	.EXTERN _BL_IMAGE_EraseUserAppInROM
	.EXTERN _BL_FLASH_WriteBlock
	.EXTERN _BL_memcpy_nf
	.EXTERN _BL_HASHING_GetResult
	.EXTERN _BL_OPERATION_ClearConfirmCode
	.EXTERN _BL_memcmp_nn

	.SECTION .text,TEXT
_BL_IMAGE_TransferUserAppToROM:
	.STACK _BL_IMAGE_TransferUserAppToROM = 66
	
	push ax
	subw sp, #0x3A
	movw ax, sp
	addw ax, #0x001A
	call !_BL_OPERATION_GetProperties
	mov a, #0x08
	call !_BL_OPERATION_SetConfirmCode
	mov a, [sp+0x3B]
	dec a
	cmp a, #0x02
	bc $.BB@LABEL@1_7
.BB@LABEL@1_1:
	mov [sp+0x06], #0x05
	movw [sp+0x08], ax
	movw [sp+0x0A], ax
.BB@LABEL@1_2:
	mov a, [sp+0x06]
	cmp0 a
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_3:
	mov a, [sp+0x3B]
	cmp a, #0x02
	bnz $.BB@LABEL@1_5
.BB@LABEL@1_4:
	call !_BL_IMAGE_EraseUserAppInROM
	dec a
.BB@LABEL@1_5:
	.bnz !.BB@LABEL@1_40
.BB@LABEL@1_6:
	mov a, #0x08
	call !_BL_OPERATION_ClearConfirmCode
	mov a, #0x02
	br !.BB@LABEL@1_72
.BB@LABEL@1_7:
	onew ax
	push ax
	movw ax, sp
	addw ax, #0x0009
	movw [sp+0x12], ax
	movw de, ax
	movw ax, [sp+0x2E]
	movw bc, ax
	movw ax, [sp+0x2C]
	call !_BL_SFL_DeviceRead
	pop ax
	mov a, [sp+0x07]
	mov [sp+0x00], a
	call !_BL_HASHING_Init
	mov a, [sp+0x00]
	mov x, #0x08
	mulu x
	incw ax
	incw ax
	movw [sp+0x08], ax
	push ax
	movw ax, [sp+0x2E]
	movw bc, ax
	movw ax, [sp+0x2C]
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x08]
	movw bc, ax
	movw ax, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_HASHING_Calculate
	mov 0xFFFAB, #0xAC
	clrw ax
	movw [sp+0x0A], ax
	clrb a
	mov [sp+0x06], a
.BB@LABEL@1_8:
	mov [sp+0x3A], a
	movw ax, [sp+0x10]
	movw hl, ax
	mov a, [sp+0x3A]
	cmp a, [hl]
	bnc $.BB@LABEL@1_2
.BB@LABEL@1_9:
	movw ax, [sp+0x2A]
	movw bc, ax
	movw ax, #0x0004
	push ax
	mov a, [sp+0x3C]
	mov x, #0x08
	mulu x
	movw [sp+0x02], ax
	incw ax
	addw ax, bc
	movw hl, ax
	movw ax, [sp+0x2E]
	movw bc, ax
	sknc
.BB@LABEL@1_10:
	incw bc
.BB@LABEL@1_11:
	movw ax, sp
	addw ax, #0x000E
	movw de, ax
	movw ax, hl
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x2A]
	movw bc, ax
	movw ax, #0x0004
	push ax
	movw ax, [sp+0x02]
	addw ax, #0x0005
	addw ax, bc
	movw hl, ax
	movw ax, [sp+0x2E]
	movw bc, ax
	sknc
.BB@LABEL@1_12:
	incw bc
.BB@LABEL@1_13:
	movw ax, sp
	addw ax, #0x0014
	movw de, ax
	movw ax, hl
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x1C]
	movw de, ax
	movw ax, [sp+0x1A]
	movw bc, ax
	movw ax, [sp+0x0E]
	movw [sp+0x04], ax
	cmpw ax, de
	movw ax, [sp+0x0C]
	movw [sp+0x02], ax
	sknz
.BB@LABEL@1_14:
	cmpw ax, bc
.BB@LABEL@1_15:
	bc $.BB@LABEL@1_25
.BB@LABEL@1_16:
	movw ax, [sp+0x20]
	movw hl, ax
	movw ax, [sp+0x1E]
	movw [sp+0x00], ax
	movw ax, [sp+0x04]
	cmpw ax, hl
	pop hl
	push hl
	movw ax, [sp+0x02]
	sknz
.BB@LABEL@1_17:
	cmpw ax, hl
.BB@LABEL@1_18:
	bnh $.BB@LABEL@1_22
.BB@LABEL@1_19:
	movw ax, [sp+0x24]
	movw hl, ax
	movw ax, [sp+0x22]
	movw [sp+0x00], ax
	movw ax, [sp+0x04]
	cmpw ax, hl
	pop hl
	push hl
	movw ax, [sp+0x02]
	sknz
.BB@LABEL@1_20:
	cmpw ax, hl
.BB@LABEL@1_21:
	bc $.BB@LABEL@1_25
.BB@LABEL@1_22:
	movw ax, [sp+0x28]
	movw hl, ax
	movw ax, [sp+0x26]
	movw [sp+0x00], ax
	movw ax, [sp+0x04]
	cmpw ax, hl
	pop hl
	push hl
	movw ax, [sp+0x02]
	sknz
.BB@LABEL@1_23:
	cmpw ax, hl
.BB@LABEL@1_24:
	sknh
.BB@LABEL@1_25:
	mov [sp+0x06], #0x04
.BB@LABEL@1_26:
	movw ax, [sp+0x14]
	movw [sp+0x00], ax
	cmpw ax, de
	movw ax, [sp+0x12]
	movw hl, ax
	sknz
.BB@LABEL@1_27:
	cmpw ax, bc
.BB@LABEL@1_28:
	bc $.BB@LABEL@1_38
.BB@LABEL@1_29:
	movw ax, [sp+0x20]
	movw bc, ax
	movw ax, [sp+0x1E]
	movw de, ax
	movw ax, [sp+0x00]
	cmpw ax, bc
	movw ax, hl
	sknz
.BB@LABEL@1_30:
	cmpw ax, de
.BB@LABEL@1_31:
	bnh $.BB@LABEL@1_35
.BB@LABEL@1_32:
	movw ax, [sp+0x24]
	movw bc, ax
	movw ax, [sp+0x22]
	movw de, ax
	movw ax, [sp+0x00]
	cmpw ax, bc
	movw ax, hl
	sknz
.BB@LABEL@1_33:
	cmpw ax, de
.BB@LABEL@1_34:
	bc $.BB@LABEL@1_38
.BB@LABEL@1_35:
	movw ax, [sp+0x28]
	movw bc, ax
	movw ax, [sp+0x26]
	movw de, ax
	movw ax, [sp+0x00]
	cmpw ax, bc
	movw ax, hl
	sknz
.BB@LABEL@1_36:
	cmpw ax, de
.BB@LABEL@1_37:
	sknh
.BB@LABEL@1_38:
	mov [sp+0x06], #0x04
.BB@LABEL@1_39:
	mov a, [sp+0x3A]
	inc a
	br !.BB@LABEL@1_8
.BB@LABEL@1_40:
	mov a, [sp+0x06]
	cmp0 a
	.bnz !.BB@LABEL@1_68
.BB@LABEL@1_41:
	clrb a
.BB@LABEL@1_42:
	mov [sp+0x3A], a
	movw ax, sp
	addw ax, #0x0007
	movw hl, ax
	mov a, [sp+0x3A]
	cmp a, [hl]
	movw ax, [sp+0x2C]
	movw [sp+0x00], ax
	movw ax, [sp+0x2A]
	movw bc, ax
	.bnc !.BB@LABEL@1_65
.BB@LABEL@1_43:
	movw ax, #0x0004
	push ax
	mov a, [sp+0x3C]
	mov x, #0x08
	mulu x
	movw [sp+0x04], ax
	incw ax
	addw ax, bc
	movw hl, ax
	movw ax, [sp+0x02]
	movw bc, ax
	sknc
.BB@LABEL@1_44:
	incw bc
.BB@LABEL@1_45:
	movw ax, sp
	addw ax, #0x000E
	movw de, ax
	movw ax, hl
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, [sp+0x2A]
	movw bc, ax
	movw ax, #0x0004
	push ax
	movw ax, [sp+0x04]
	addw ax, #0x0005
	addw ax, bc
	movw hl, ax
	movw ax, [sp+0x2E]
	movw bc, ax
	sknc
.BB@LABEL@1_46:
	incw bc
.BB@LABEL@1_47:
	movw ax, sp
	addw ax, #0x0014
	movw de, ax
	movw ax, hl
	call !_BL_SFL_DeviceRead
	pop ax
.BB@LABEL@1_48:
	movw ax, [sp+0x12]
	addw ax, #0x0001
	movw hl, ax
	movw ax, [sp+0x0E]
	movw bc, ax
	movw ax, [sp+0x0C]
	movw de, ax
	movw ax, [sp+0x14]
	sknc
.BB@LABEL@1_49:
	incw ax
.BB@LABEL@1_50:
	cmpw ax, bc
	movw ax, hl
	sknz
.BB@LABEL@1_51:
	cmpw ax, de
.BB@LABEL@1_52:
	bnh $.BB@LABEL@1_64
.BB@LABEL@1_53:
	movw ax, #0x0400
	push ax
	movw ax, [sp+0x0A]
	movw bc, ax
	movw ax, [sp+0x2C]
	addw ax, bc
	movw de, ax
	movw ax, [sp+0x0C]
	movw bc, ax
	movw ax, [sp+0x2E]
	sknc
.BB@LABEL@1_54:
	incw ax
.BB@LABEL@1_55:
	addw ax, bc
	movw bc, ax
	movw ax, de
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_SFL_DeviceRead
	pop ax
	mov a, [sp+0x3B]
	cmp a, #0x02
	bnz $.BB@LABEL@1_58
.BB@LABEL@1_56:
	movw ax, [sp+0x0E]
	movw bc, ax
	movw ax, [sp+0x0C]
	movw de, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_FLASH_WriteBlock
	cmp0 a
	bnz $.BB@LABEL@1_63
.BB@LABEL@1_57:
	movw ax, #0x0400
	push ax
	mov a, [sp+0x10]
	mov c, a
	movw ax, [sp+0x0E]
	movw de, ax
	movw ax, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_memcpy_nf
	pop ax
.BB@LABEL@1_58:
	movw bc, #0x0400
	movw ax, #LOWW(_g_bl_image_read_ROM_buffer)
	call !_BL_HASHING_Calculate
	movw ax, [sp+0x0C]
	addw ax, #0x0400
	movw [sp+0x0C], ax
	movw ax, [sp+0x0E]
	sknc
.BB@LABEL@1_59:
	incw ax
.BB@LABEL@1_60:
	movw [sp+0x0E], ax
	mov 0xFFFAB, #0xAC
	movw ax, [sp+0x08]
	addw ax, #0x0400
	movw [sp+0x08], ax
	movw ax, [sp+0x0A]
	sknc
.BB@LABEL@1_61:
	incw ax
.BB@LABEL@1_62:
	movw [sp+0x0A], ax
	br !.BB@LABEL@1_48
.BB@LABEL@1_63:
	mov [sp+0x06], #0x03
.BB@LABEL@1_64:
	mov a, [sp+0x3A]
	inc a
	br !.BB@LABEL@1_42
.BB@LABEL@1_65:
	onew ax
	incw ax
	push ax
	movw ax, [sp+0x0A]
	addw ax, bc
	movw hl, ax
	movw ax, [sp+0x0C]
	movw bc, ax
	movw ax, [sp+0x02]
	sknc
.BB@LABEL@1_66:
	incw ax
.BB@LABEL@1_67:
	addw ax, bc
	movw bc, ax
	movw ax, sp
	addw ax, #0x0018
	movw de, ax
	movw ax, hl
	call !_BL_SFL_DeviceRead
	pop ax
	movw ax, sp
	addw ax, #0x0018
	call !_BL_HASHING_GetResult
.BB@LABEL@1_68:
	mov a, #0x08
	call !_BL_OPERATION_ClearConfirmCode
	mov a, [sp+0x06]
	cmp0 a
	bnz $.BB@LABEL@1_72
.BB@LABEL@1_69:
	movw ax, sp
	addw ax, #0x0016
	movw bc, ax
	movw de, #0x0002
	incw ax
	incw ax
	call !_BL_memcmp_nn
	clrw bc
	cmpw ax, bc
	oneb a
	skz
.BB@LABEL@1_70:
	mov [sp+0x06], a
.BB@LABEL@1_71:
	mov a, [sp+0x06]
.BB@LABEL@1_72:
	addw sp, #0x3C
	ret
