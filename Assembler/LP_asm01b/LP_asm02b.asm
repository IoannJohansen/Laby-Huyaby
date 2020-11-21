.586														; ������� ������ (��������� Pentium)
.model flat, stdcall										; ������ ������, ���������� � �������
includelib kernel32.lib										; ������������: ����������� � kernel32
includelib ..\Debug\LP_asm01a.lib

ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 
GetStdHandle PROTO: DWORD									; �������� handle ������ �� ������� 
															; (��������� ����������� �������� -10 ����, -11 �����, -12 ������ ���������� ������)
WriteConsoleA PROTO: DWORD,: DWORD,: DWORD,: DWORD,: DWORD	; ����� �� ������� (����������� �-��)
SetConsoleTitleA PROTO: DWORD								; �������� �-�� ��������������� ��������� ����������� ���� (������� �����������)

getmin PROTO :DWORD, :DWORD
getmax PROTO :DWORD, :DWORD

.stack 4096													; ��������� ����� ������� 4 ���������

.const														; ���������
	consoleTitle byte 'LP_asm01', 0							; ������, ������ ������� ������ + ������� ���
	handleOutput sdword -11									; ��� �� ������ ���������� ������ � �������
	array sdword -3, 5, 15, 71, 32, 14, 2, 10, 2, 4		; ������ ���������� 10-� ����������
	text byte 'getmax-getmin =', 0							; ������ ��� ������ ������	

.data
	consoleHandle dword 0h									; ��������� �������
	max sdword ?
	min sdword ?
	result sdword ?
	resultString byte 4 dup(0)

.code

int_to_char PROC uses eax ebx ecx edi esi,
							  pstr: dword,      ; ����� ������ ��� ����������
							  intfield: sdword   ; ������������� ����a
push ebx
xor eax, eax					;�������� ��������
mov edi, [pstr]					;������� ����� ������ � �������
mov eax, [intfield]				;������� ����� � ������� ��� ����������� �������
test eax, eax					;�������� ����� ����� � EAX
jns unum_to_str					;�������, ���� ����� ��� ����� ��� ����� ����
mov edi, '-'				;���������� ����� � ������ ������
inc edi
neg eax             ;�������������� ��������� ����� � EAX (��������������        ��� � ������)

					;�������������� ������������ �����
unum_to_str:
	xor ecx, ecx        ;��������� ��������
	mov ebx, 10     ;�������� � ������� EBX ��������
	cycle1:
	xor edx, edx        ;��������� ������� ����� �������� ����� (�������)
	div ebx         ;������� (EDX:EAX)/EBX, ������� � EDX
	add edx, '0'        ;�������������� ������� � ��� �������
	push edx        ;��������� ������� � �����
	inc ecx         ;����������� ������� ����� (��� ������� �����)  
	test eax, eax       ;�������� EAX
	jnz cycle1      ;������� � ������ �����, ���� ������� �� ����

cycle2:
	pop edx         ;�������������� ������� �� �����
	mov [edi], edx      ;���������� ������� � ������
	inc edi         ;����������� ����� ������
	loop cycle2     ;���� ������������, ���� ECX>0

;�������������� �� �����
pop ebx
ret
int_to_char ENDP

main PROC										        ; ����� ����� main
														
	push lengthof array                                 ;
	push offset array                                   ; �������� ������ � ����
	call getmin											; ����� ��������� getmin
	mov min, eax										; ��������� � min

	push lengthof array									;
	push offset array									; �������� ������ � ����
	call getmax											; ����� ��������� getmax
	mov max, eax										; ��������� � max
	sub eax, min										; 
	mov result, eax										;
	
	push offset consoleTitle					        ; �������� � ���� �������� ������� SetConsoleTitle ������
	call SetConsoleTitleA						        ; �������� ������� �������� ��������� ����
														
	push handleOutput							        ; �������� � ���� ��� ����������� �� ����� � �������
	call GetStdHandle							        ; �������� �-�� �������� ���������� �� �����
	mov consoleHandle, eax						        ; �������� ���������� ���������� �� �������� eax

	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push sizeof text									; ������ ������� � ����
	push offset text									; ��������� �� ������ ������ � ����
	push consoleHandle									; ���������� ����������
	call WriteConsoleA 

	push result
	push offset resultString 
	call int_to_char

	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push sizeof resultString 							; ������ ������� � ����
	push offset resultString							; ��������� �� ������ ������ � ����
	push consoleHandle									; ���������� ����������
	call WriteConsoleA 

	push 0												; �������� � ���� ��� ���������� �������� Windows
	call ExitProcess									; ���������� �������� Windows
main ENDP												; ����� ���������
end main		