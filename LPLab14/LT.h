#pragma once
#define	LT_MAXSIZE			2000		// максимальное количество эл-ов в таблице лексем	
#define	LT_TI_NULLXDX		-1			// нет элемента таблицы идентификаторов				
#define	LEX_TYPE			't'			// лексема дл€ тип данных
#define	LEX_ID				'i'			// лексема дл€ идентификатора
#define	LEX_MAIN			'm'			// лексема дл€ главной функции
#define	LEX_LITERAL			'l'			// лексема дл€ литерала
#define	LEX_LITERAL			'd'			// лексема дл€ declare
#define	LEX_FUNCTION		'f'			// лексема дл€ function
#define	LEX_RETURN			'r'			// лексема дл€ return
#define	LEX_SEMICOLON		';'			// лексема дл€ ;
#define	LEX_COMMA			','			// лексема дл€ ,
#define	LEX_LEFTBRACE		'{'			// лексема дл€ {
#define	LEX_RIGHTBRACE		'}'			// лексема дл€ }
#define	LEX_LEFTHESIS		'('			// лексема дл€ (
#define	LEX_RIGHTHESIS		')'			// лексема дл€ )
#define	LEX_PLUS			'+'			// лексема дл€ +
#define	LEX_MINUS			'-'			// лексема дл€ -
#define	LEX_STAR			'*'			// лексема дл€ *
#define	LEX_DIRSLASH		'/'			// лексема дл€ /

#define PARM_LEX_DEFAULT_EXT L".lex.txt" //дл€ файла с результатом лексического анализa


namespace LT
{
	struct Entry						// строка таблицы лексем
	{
		char lexema;					// лесема
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable						// экземпл€р таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int current_size;				// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем

		LexTable();
		void Add(Entry entry);					// добавление лексем
		Entry GetEntry(int n);					// получить строку таблицы лексем
		void PrintLexTable(const wchar_t* in);		// вывод лексем в файл
		void Delete();							// удалить таблицу лексем (освободить пам€ть)
	};
}