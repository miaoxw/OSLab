segment .text
	global _isEmpty
	
;int _cdecl isEmpty(unsigned char *buffer,int length)
_isEmpty:
	push	ebp
	mov	ebp,esp
	sub	esp,10h
	mov	dword [ebp-8],0	;temp=0
	mov	dword [ebp-4],0	;i=0
	jmp	_cond	;进入循环
_loop:
	mov	edx,dword [ebp-4]	;edx=i
	mov	eax,dword [ebp+8]	;eax=buffer
	add	eax,edx	;基址+偏移量
	movzx	eax,byte [eax]	;eax=buffer+i
	movzx	eax,al
	or	dword [ebp-8],eax	;temp|=buffer[i]
	inc	dword [ebp-4]	;i++
_cond:
	mov	eax,dword [ebp-4]	;eax=i
	cmp	eax,dword [ebp+0xC]	;if(i<length)
	jl	_loop	;goto _loop
	cmp	dword [ebp-8],0
	sete	al	;if(al==0) al=1
	movzx	eax,al	;结果的无符号扩展
	leave
	ret
