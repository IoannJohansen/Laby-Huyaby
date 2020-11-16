.586
.model flat, stdcall
.code
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

getmax proc arr:dword, len:dword
	mov esi, arr
	mov eax, DWORD PTR[esi]
	xor edi, edi
	jmp getmaxloop
getmaxloop:
	inc edi
	cmp edi, len
	jae getmaxend
	mov ebx, DWORD PTR[esi + edi * type arr]
	cmp ebx, eax
	jg assignmax
	loop getmaxloop
assignmax:
	mov eax, ebx
	jmp getmaxloop
getmaxend:
	ret
getmax endp
end