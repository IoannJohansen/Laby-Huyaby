#pragma once
#include "IT.h"
#include "LT.h"
#define LEX_NEWPROC '@'
#include <stack>

namespace Polska
{
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable);
	bool PolishNotation(int lexPos, LT::LexTable& lexTable, IT::IdTable& idenTable);
	int ArifmPriorities(char symb);

}

