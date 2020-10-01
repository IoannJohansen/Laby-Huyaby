#pragma once
#include "stdafx.h"
#define	LT_MAXSIZE			2000		// ������������ ���������� ��-�� � ������� ������	
#define	LT_TI_NULLXDX		-1			// ��� �������� ������� ���������������				
#define	LEX_TYPE			't'			// ������� ��� ��� ������
#define	LEX_ID				'i'			// ������� ��� ��������������
#define	LEX_LITERAL			'l'			// ������� ��� ��������
#define	LEX_FUNCTION		'f'			// ������� ��� function
#define	LEX_LITERAL			'd'			// ������� ��� declare
#define	LEX_RETURN			'r'			// ������� ��� return
#define	LEX_PRINT			'p'			// ������� ��� print
#define	LEX_MAIN			'm'			// ������� ��� ������� �������
#define	LEX_SEMICOLON		';'			// ������� ��� ;
#define	LEX_COMMA			','			// ������� ��� ,
#define	LEX_LEFTBRACE		'{'			// ������� ��� {
#define	LEX_RIGHTBRACE		'}'			// ������� ��� }
#define	LEX_LEFTHESIS		'('			// ������� ��� (
#define	LEX_RIGHTHESIS		')'			// ������� ��� )
#define	LEX_PLUS			'v'			// ������� ��� +
#define	LEX_MINUS			'v'			// ������� ��� -
#define	LEX_STAR			'v'			// ������� ��� *
#define	LEX_DIRSLASH		'v'			// ������� ��� /
#define PARM_LEX_DEFAULT_EXT L".lex.txt" //��� ����� � ����������� ������������ ������a



namespace LT
{
	struct Entry						// ������ ������� ������
	{
		char lexema;					// ������
		int sn;							// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int current_size;				// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������

		LexTable();
		void Add(Entry entry);					// ���������� ������
		Entry GetEntry(int n);					// �������� ������ ������� ������
		void PrintLexTable(const wchar_t* in);		// ����� ������ � ����
		void Delete();							// ������� ������� ������ (���������� ������)
	};
}