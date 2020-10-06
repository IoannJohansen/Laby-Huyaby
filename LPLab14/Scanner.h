#pragma once
#include "stdafx.h"
namespace Lex {

	void textDivision(Out::OUT out);
	bool tokenAnalyse(char* token);
	bool checkForLexema();
	bool checkForId();
	bool isIdentificator(char* buff);
	bool isStringLiteral(char* token);

	
}