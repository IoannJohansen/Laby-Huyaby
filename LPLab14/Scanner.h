#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"


namespace Lex 
{
	struct Tables
	{
		LT::LexTable lexTable;
		IT::IdTable idenTable;
	};
	struct TempIT
	{
		bool flPar, flDec, flAssig, flPrint;
		int numLine = 0;
		int posNumber = 0;
		int numidIT;
		char lastID[ID_MAXSIZE+1];
		char parrentBlock[ID_MAXSIZE+1];
		int brBalance;
		TempIT() 
		{
			strcpy_s(this->parrentBlock, TI_BLOCK_DEFAULT);
			this->brBalance = 0;
		}
	};
	Tables lexAnalyse(Out::OUT out);
	bool tokenAnalyse(char* token);
	bool checkForInteger(char* token);
	bool checkForString(char* token);
	bool checkForFunction(char* token);
	bool checkForDeclare(char* token);
	bool checkForReturn(char* token);
	bool checkForPrint(char* token);
	bool checkForMain(char* token);
	char checkForArithmeticTokens(char* token);
	bool checkForId(char* token);
	bool checkForIntegerLiteral(char* token);
	bool checkForStringLiteral(char* token);
	void addIntLiteral(char* token);
	void addStrLiteral(char* token);
	void addLex(char lexem);
	void addIdent(char* token);
	void outLexAndIdenTables(const wchar_t* in, Tables tables);
}