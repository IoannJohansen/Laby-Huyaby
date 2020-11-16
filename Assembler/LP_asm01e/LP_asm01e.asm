.586														; ������� ������ (��������� Pentium)
.model flat, stdcall										; ������ ������, ���������� � �������
includelib kernel32.lib										; ������������: ����������� � kernel32
includelib libucrt.lib
includelib  ..\Debug\LP_asm01d.lib

ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 
GetStdHandle PROTO: DWORD									; �������� handle ������ �� ������� 
															; (��������� ����������� �������� -10 ����, -11 �����, -12 ������ ���������� ������)
WriteConsoleA PROTO: DWORD,: DWORD,: DWORD,: DWORD,: DWORD	; ����� �� ������� (����������� �-��)
SetConsoleTitleA PROTO: DWORD								; �������� �-�� ��������������� ��������� ����������� ���� (������� �����������)

EXTRN getmax: proc
EXTRN getmin: proc

.stack 4096													; ��������� ����� ������� 4 ���������

.const														; ���������
	consoleTitle db 'LP_asm01', 0							; ������, ������ ������� ������ + ������� ���
	array sdword 3, 5, 15, 71, 32, 14, 2, 10, 2, 4		; ������ ���������� 10-� ����������
	text byte 'getmax-getmin =', 0							; ������ ��� ������ ������	

.data
	consoleHandle dd 0h									; ��������� �������
	max sdword ?
	min sdword ?
	result sdword ?
	resultString byte 4 dup(0)
	stroka byte "Hello!", 0
.code

int_to_str PROC uses eax ebx ecx edi esi,
							  pstr: dword,      ; ����� ������ ��� ����������
							  intfield: sdword   ; ������������� ����a
push ebx
xor eax, eax					;�������� ��������
mov edi, pstr					;������� ����� ������ � �������
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
	mov [edi], edx     ;���������� ������� � ������
	inc edi         ;����������� ����� ������
	loop cycle2     ;���� ������������, ���� ECX>0

;�������������� �� �����
pop ebx
ret
int_to_str ENDP

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
	mov result, eax	
	
	push offset consoleTitle					        ; �������� � ���� �������� ������� SetConsoleTitle ������
	call SetConsoleTitleA						        ; �������� ������� �������� ��������� ����
														
	push -11											; �������� � ���� ��� ����������� �� ����� � �������
	call GetStdHandle							        ; �������� �-�� �������� ���������� �� �����
	mov consoleHandle, eax						        ; �������� ���������� ���������� �� �������� eax

	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push sizeof stroka									; ������ ������� � ����
	push offset stroka									; ��������� �� ������ ������ � ����
	push consoleHandle									; ���������� ����������
	call WriteConsoleA 



	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push 0												; ����� ���������� ����, ����� ��� �-�� ������ � �������
	push sizeof text									; ������ ������� � ����
	push offset text									; ��������� �� ������ ������ � ����
	push consoleHandle									; ���������� ����������
	call WriteConsoleA 

	push result
	push offset resultString 
	call int_to_str

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