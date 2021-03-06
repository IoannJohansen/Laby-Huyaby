#pragma once
#include "IT.h"
#include "LT.h"
#include <stack>

namespace Polska
{
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable);
	bool PolishNotation(int lexPos, LT::LexTable& lexTable, IT::IdTable& idenTable);
	int ArifmPriorities(LT::Entry entrit, IT::IdTable idenT);
}