.586
.model flat, stdcall
includelib kernel32.lib
ExitProcess PROTO : DWORD
.stack 4096
.data
nums        dd   4, 56, 13, -34, 0, 45, 6, 658, 196, 24
min         dd   ?
.code
call getmin
getmin proc arr:dword, len:dword
	mov esi, arr
	mov eax, DWORD PTR[esi]
	xor edi, edi
	jmp getminloop
getminloop:
	inc edi
	cmp edi, len
	jae getminend
	mov ebx, DWORD PTR[esi + edi * type arr]
	cmp ebx, eax
	jl assignmin
	loop getminloop
assignmin:
	mov eax, ebx
	jmp getminloop
getminend:
	ret
getmin endp

main PROC
invoke getmin, offset nums, lengthof nums
mov min, eax
push 0
call ExitProcess
main ENDP
end main
end