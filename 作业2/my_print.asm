segment .text
		global _printFile
		global _printDirectory
		global _clear

;传入参数为文件名字符数组所在位置
_printFile:
	enter 0,0
	;取光标位置
	mov bh,0
	mov ah,3h
	int 10h
	
	mov	ax,[ebp+12]
	mov	bp,ax		; ES:BP = 串地址
	mov	cx,[ebp+8]		; CX = 串长度
	mov	ax,01301h	; AH = 13,  AL = 01h
	mov	bx,0007h	; 页号为0(BH = 0) 黑底白字(BL = 07h)
	int	10h			; int 10h
	leave
	ret


;传入参数为文件夹名字符数组所在位置	
_printDirectory:
	enter 0,0
	;取光标位置
	mov bh,0
	mov ah,3h
	int 10h
	
	mov	ax,[ebp+12]
	mov	bp,ax		; ES:BP = 串地址
	mov	cx,[ebp+8]		; CX = 串长度
	mov	ax,01301h	; AH = 13,  AL = 01h
	mov	bx,000ch	; 页号为0(BH = 0) 黑底红字(BL = 0Ch,高亮)
	int	10h			; int 10h
	leave
	ret


;清屏
_clear:
	mov al,0
	mov bh,07h
	mov ch,0
	mov cl,0
	mov dh,24
	mov dl,79
	mov ah,6
	int 10h
	ret