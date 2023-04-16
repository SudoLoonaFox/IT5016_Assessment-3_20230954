; A poorly written integer reversing program in x86 assesembly
section .data
	num db 23

section .text
global _start

_start:
	;remainder = x % 10;
    ;rev = 10 * rev + remainder;
    ;x /=10;
	mov eax, [num]
reverse:
	cmp eax, 0
	je exit
	; The idiv instruction divides the contents of the 64 bit integer EDX:EAX (constructed by viewing EDX as the most significant four bytes and EAX as the least significant four bytes) by the specified operand value. The quotient result of the division is stored into EAX, while the remainder is placed in EDX. 
	mov edx, 0; set upper bytes. lower are set by eax
	mov ecx, 10
	idiv ecx
	; ebx = ebx * 10 + edx
	imul ebx, 10
	add ebx, edx; adds remainder
	jmp reverse

exit:
	mov eax, 1
	; xor ebx, ebx
	int 0x80

