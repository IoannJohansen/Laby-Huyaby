#include "stdafx.h"

namespace Polska
{
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable)		// TODO : ADD PROCESSING OF EXPRESSIONS WITH FUNCTION CALL'S
	{
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].lexema == LEX_EQUAL_SIGN && lexTable.table[i - 1].lexema == LEX_ID)
			{
				PolishNotation(++i, lexTable, idenTable);
			}

		}
	}
	bool PolishNotation(int lexPos, LT::LexTable& lexTable, IT::IdTable& idenTable)
	{
		//DETECKTING ERRORS
		if (lexTable.table[lexPos].lexema == LEX_ID && lexTable.table[lexPos + 1].lexema == LEX_LEFTHESIS)return false;	// we dont checking expressions with functions
		if ((lexTable.table[lexPos].lexema == LEX_ID|| lexTable.table[lexPos].lexema == LEX_LITERAL)&& lexTable.table[lexPos + 1].lexema == LEX_SEMICOLON)return false;
		if (lexTable.table[lexPos].lexema == LEX_ARITHMETIC && idenTable.table[lexTable.table[lexPos].idxTI].id[0]!=LEX_MINUS)throw ERROR_THROW(139);
		//DETECKTING ERRORS
		stack<LT::Entry> stack;
		LT::Entry resStr[200];
		int srcLen = 0, outLen = 0, semicolonId = 0, counter = 0;
		//for error checking
		int brBalance = 0, countOperands = 0, countOperations = 0;
		//for error checking
		for (int i = lexPos; (lexTable.table[i].lexema!=LEX_SEMICOLON); i++)		// read do semicolona
		{
			srcLen++;
			semicolonId = i + 1;
			if ((lexTable.table[i].lexema == LEX_ID) && (lexTable.table[i + 1].lexema == LEX_LEFTHESIS))throw ERROR_THROW(141);	 //----!!!!!!
			if (lexTable.table[i].lexema == LEX_ARITHMETIC && lexTable.table[i - 1].lexema == LEX_ARITHMETIC)throw ERROR_THROW(142);	 // bad interchange of operand - operation
		}
		srcLen++;					// чтоб выводилась ;

		for (int i = lexPos; i < lexPos + srcLen; i++)		// expression analyse
		{
			counter++;
			switch (lexTable.table[i].lexema)
			{
			case LEX_LITERAL:	//ЫАЫАЫАЫАЫЫАЫАЫЫЫЫЫЫЫЫЫЫЫЫААААААААЫАЫАЫАЫАЫАЫАЫАЫАЫАЫЫАЫАЫАЫАЫАЫАЫЫАЫАЫЫЫЫЫЫЫЫЫЫЫЫААААААААЫАЫАЫАЫАЫАЫАЫАЫАЫАЫЫАЫА
			case LEX_ID:	//операнды переносятся в результирующую строку в порядке их следования
			{
				countOperands++;
				resStr[outLen++] = lexTable.table[i];
				break;
			}
			case LEX_ARITHMETIC:
			{
				countOperations++;
				if (stack.empty() || stack.top().lexema == LEX_LEFTHESIS)// операция записывается в стек, если стек пуст или в вершине стека лежит открывающая скобка	
				{
					stack.push(lexTable.table[i]);
					break;
				}


				while ((ArifmPriorities(stack.top(), idenTable) >= ArifmPriorities(lexTable.table[i], idenTable)))
				{		// операция выталкивает все операции с большим или равным приоритетом в результирующую строку
					resStr[outLen++] = stack.top();
					stack.pop();
					if (stack.empty())break;		// -!!!
				}
				stack.push(lexTable.table[i]);		// push of arifm sign
				break;
			}
			

			case LEX_LEFTHESIS:		//  открывающая скобка помещается в стек
			{
				if (lexTable.table[i + 1].lexema == LEX_RIGHTHESIS)throw ERROR_THROW(137);
				brBalance++;
				stack.push(lexTable.table[i]);
				break;
			}

			case LEX_RIGHTHESIS:	// закрывающая скобка выталкивает все операции до открывающей скобки, после чего обе скобки уничтожаются
			{
				if (brBalance <= 0)throw ERROR_THROW(138);
				brBalance--;
				while (stack.top().lexema != LEX_LEFTHESIS)
				{
					resStr[outLen++] = stack.top();
					stack.pop();
				}
				stack.pop();
				break;
			}
			case LEX_SEMICOLON:break;		// bas symbol in expression

			default:						// UNCKNOWED SYMBOLS IN EXPRESSION
			{
				throw ERROR_THROW(140);
				break;
			}
			}

			if ((counter==srcLen)&&(!stack.empty()))	// по концу разбора исходной строки все операции, оставшиеся в стеке, выталкиваются в результирующую строку
			{
				while (!stack.empty())
				{
					resStr[outLen++] = stack.top();
					stack.pop();
				}
			}

			if (brBalance < 0)throw ERROR_THROW(138);

		}
		//------CHECKING FOR ERRORS

		if (brBalance != 0)throw ERROR_THROW(135);
		if (countOperations > countOperands)throw ERROR_THROW(134);
		if (outLen > srcLen)throw ERROR_THROW(136);
		//------CHECKING FOR ERRORS


		cout << "Польская нотаци выполнена" << endl;
		cout << "Исходное выражение: " << endl;
		for (int i = lexPos; i < lexPos + srcLen; i++)
		{
			cout << lexTable.table[i].lexema << ' ';
		}

		
		
		//EDIT THE TABLE
		for (int i = lexPos, k = 0; i < lexPos+outLen; i++, k++)
		{
			lexTable.table[i] = resStr[k];
		}
		int diff = srcLen-outLen-1;

		lexTable.table[semicolonId-diff].lexema = LEX_SEMICOLON;
		
		for (int i = 0; i < diff; i++)					// sdvig of table for offset because less skobocheck then bylo
		{
			for (int i = lexPos + outLen + 1; i < lexTable.size; i++)
			{
				lexTable.table[i] = lexTable.table[i + 1];
			}
			lexTable.size--;
		}
		//EDIT THE TABLE
		
		//-----OUT
		cout << endl;
		cout << "Результат: " << endl;
		for (int i = lexPos; i < lexPos+outLen; i++)
		{
			cout << lexTable.table[i].lexema << ' ';
		}
		cout << endl << endl;
		//-----OUT

		return true;
	}
	int ArifmPriorities(LT::Entry entrit, IT::IdTable idenT)
	{
		if (idenT.table[entrit.idxTI].id[0] == LEX_LEFTHESIS || idenT.table[entrit.idxTI].id[0] == LEX_RIGHTHESIS)
			return 1;
		if (idenT.table[entrit.idxTI].id[0] == LEX_PLUS || idenT.table[entrit.idxTI].id[0] == LEX_MINUS)
			return 2;
		if (idenT.table[entrit.idxTI].id[0] == LEX_STAR || idenT.table[entrit.idxTI].id[0] == LEX_DIRSLASH)
			return 3;
	}
}