#pragma once
#include "stdafx.h"
#define	LT_MAXSIZE			1024		// ������������ ���������� ��-�� � ������� ������	
#define	LT_TI_NULLXDX		-1			// ��� �������� ������� ���������������				
#define	LEX_INTEGER			't'			// ������� ��� integer
#define	LEX_STRING			't'			// ������� ��� string
#define	LEX_TYPE			't'			// ������� ��� �����
#define	LEX_ID				'i'			// ������� ��� ��������������
#define	LEX_LITERAL			'l'			// ������� ��� ��������
#define	LEX_FUNCTION		'f'			// ������� ��� function
#define	LEX_DECLARE			'd'			// ������� ��� declare
#define	LEX_RETURN			'r'			// ������� ��� return
#define	LEX_PRINT			'p'			// ������� ��� print
#define	LEX_MAIN			'm'			// ������� ��� ������� �������
#define	LEX_SEMICOLON		';'			// ������� ��� ;
#define	LEX_COMMA			','			// ������� ��� ,
#define	LEX_LEFTBRACE		'{'			// ������� ��� {
#define	LEX_RIGHTBRACE		'}'			// ������� ��� }
#define	LEX_LEFTHESIS		'('			// ������� ��� (
#define	LEX_RIGHTHESIS		')'			// ������� ��� )
#define	LEX_PLUS			'+'			// ������� ��� +
#define	LEX_MINUS			'-'			// ������� ��� -
#define	LEX_STAR			'*'			// ������� ��� *
#define	LEX_DIRSLASH		'/'			// ������� ��� /
#define	LEX_EQUAL_SIGN		'='			// ������� ��� =
#define	LEX_ARITHMETIC		'v'			// ������� ��� �������������� ������
#define PARM_LEX_DEFAULT_EXT L".lex.txt" //��� ����� � ������ ������������ ������a


namespace LT
{
	struct Entry	//������ ������� ������
	{
		char lexema;	//�������
		int sn;			//����� ������ � �������� ������
		int idxTI;		//������ � ������� ��������������� ��� LT_TI_NULLIDX
	};

	struct LexTable		//��������� ������� ������
	{
		int maxsize;	//������� ������� ������ < LT_MAXSIZE
		int size;		//������� ������ ������� ������ < maxsize
		Entry* table;	//������ ����� ������� ������
		void writeLT(const wchar_t* in);
	};

	LexTable Create(	//������� ������� ������
		int size	//������� ������� ������ < LT_MAXSIZE
	);
	void Add(	//�������� ������ � ������� ������
		LexTable& lextable,		//��������� ������� ������
		Entry entry		//������ ������� ������
	);

	Entry GetEntry(		//�������� ������ ������� ������
		LexTable& lextable,		//��������� ������� ������
		int n		//����� ���������� ������
	);

	void Delete(LexTable& lextable);	//������� ������� ������ (���������� ������)
}
