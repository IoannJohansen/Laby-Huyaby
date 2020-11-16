.586														; система команд (процессор Pentium)
.model flat, stdcall										; модель памяти, соглашение о вызовах
includelib kernel32.lib										; компановщику: компоновать с kernel32
includelib libucrt.lib
includelib  ..\Debug\LP_asm01d.lib

ExitProcess PROTO: DWORD									; прототип функции для завершения процесса Windows 
GetStdHandle PROTO: DWORD									; получить handle вывода на консоль 
															; (принимает константное значение -10 ввод, -11 вывод, -12 ошибка устройства вывода)
WriteConsoleA PROTO: DWORD,: DWORD,: DWORD,: DWORD,: DWORD	; вывод на консоль (стандартная ф-ия)
SetConsoleTitleA PROTO: DWORD								; прототип ф-ии устанавливающей заголовок консольного окна (функция стандартная)

EXTRN getmax: proc
EXTRN getmin: proc

.stack 4096													; выделение стека объёмом 4 мегабайта

.const														; константы
	consoleTitle db 'LP_asm01', 0							; строка, первый элемент данные + нулевой бит
	array sdword 3, 5, 15, 71, 32, 14, 2, 10, 2, 4		; массив заполненый 10-ю значениями
	text byte 'getmax-getmin =', 0							; строка для вывода ответа	

.data
	consoleHandle dd 0h									; состояние консоли
	max sdword ?
	min sdword ?
	result sdword ?
	resultString byte 4 dup(0)
	stroka byte "Hello!", 0
.code

int_to_str PROC uses eax ebx ecx edi esi,
							  pstr: dword,      ; адрес строки для результата
							  intfield: sdword   ; преобразуемое числa
push ebx
xor eax, eax					;очищение регистра
mov edi, pstr					;заносим адрес строки в регистр
mov eax, [intfield]				;заносим число в регистр для дальнейшего деления
test eax, eax					;проверка знака числа в EAX
jns unum_to_str					;переход, если число без знака или равно нулю
mov edi, '-'				;добавление знака в начало строки
inc edi
neg eax             ;инвертирование двоичного числа в EAX (дополнительный        код и прочее)

;Преобразование беззнакового числа
unum_to_str:
	xor ecx, ecx        ;обнуление счетчика
	mov ebx, 10     ;помещаем в регистр EBX делитель
	cycle1:
	xor edx, edx        ;обнуление старшей части двойного слова (остатка)
	div ebx         ;деление (EDX:EAX)/EBX, остаток в EDX
	add edx, '0'        ;Преобразование остатка в код символа
	push edx        ;сохраняем остаток в стеке
	inc ecx         ;увеличиваем счетчик цикла (для второго цикла)  
	test eax, eax       ;проверка EAX
	jnz cycle1      ;переход к началу цикла, если частное не ноль

cycle2:
	pop edx         ;восстановление символа из стека
	mov [edi], edx     ;сохранение символа в строку
	inc edi         ;увеличиваем адрес строки
	loop cycle2     ;цикл продолжается, пока ECX>0

;Восстановление из стека
pop ebx
ret
int_to_str ENDP

main PROC										        ; точка входа main
														
	push lengthof array                                 ;
	push offset array                                   ; помещаем массив в стек
	call getmin											; вызов процедуры getmin
	mov min, eax										; результат в min

	push lengthof array									;
	push offset array									; помещаем массив в стек
	call getmax											; вызов процедуры getmax
	mov max, eax										; результат в max

	sub eax, min										; 
	mov result, eax	
	
	push offset consoleTitle					        ; помещаем в стек параметр функции SetConsoleTitle строку
	call SetConsoleTitleA						        ; вызываем функцию устанвки заголовка окна
														
	push -11											; помещаем в стек код ращзрешения на вывод в консоли
	call GetStdHandle							        ; вызываем ф-ию проверки разрешения на вывод
	mov consoleHandle, eax						        ; копируем полученное разрешение из регистра eax

	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push sizeof stroka									; размер массива в стек
	push offset stroka									; указатель на начало строки в стек
	push consoleHandle									; полученное разрешение
	call WriteConsoleA 



	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push sizeof text									; размер массива в стек
	push offset text									; указатель на начало строки в стек
	push consoleHandle									; полученное разрешение
	call WriteConsoleA 

	push result
	push offset resultString 
	call int_to_str

	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push 0												; можно отправлять нули, нужно для ф-ии вывода в консоль
	push sizeof resultString 							; размер массива в стек
	push offset resultString							; указатель на начало строки в стек
	push consoleHandle									; полученное разрешение
	call WriteConsoleA 

	push 0												; помещаем в стек код завершения процесса Windows
	call ExitProcess									; завершение процесса Windows
main ENDP												; конец процедуры
end main		