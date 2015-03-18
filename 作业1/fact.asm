segment .text
	global _fact
_fact:
	enter   0,0
	mov eax,[ebp+8]   ;eax = n
	cmp eax,1
	jbe term_cond   ;if (n <= 1)
	dec eax    ;n -= 1
	push eax
	call _fact   ;eax = fact(n-1)
	pop ecx
	mul dword [ebp+8] ;edx:eax = eax * [ebp + 8]
	jmp short end_fact
term_cond:
	mov eax,1
end_fact:
	leave
	ret