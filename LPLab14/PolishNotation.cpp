#include "stdafx.h"

namespace Polska
{
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable) 
	{
		//PolishNotation(17, lexTable, idenTable);
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
		if (lexTable.table[lexPos].lexema == LEX_ID && lexTable.table[lexPos + 1].lexema == LEX_LEFTHESIS)return false;
		if ((lexTable.table[lexPos].lexema == LEX_ID|| lexTable.table[lexPos].lexema == LEX_LITERAL)&& lexTable.table[lexPos + 1].lexema == LEX_SEMICOLON)return false;
		if (lexTable.table[lexPos].lexema == LEX_PLUS || lexTable.table[lexPos].lexema == LEX_MINUS || lexTable.table[lexPos].lexema == LEX_DIRSLASH || lexTable.table[lexPos].lexema == LEX_STAR)throw ERROR_THROW(139);
		//DETECKTING ERRORS
		stack<LT::Entry> stack;
		LT::Entry resStr[200];
		int srcLen = 0, outLen = 0, semicolonId = 0, counter = 0;
		//for error checking
		int brBalance = 0, countOperands = 0, countOperations = 0;
		//for error checking
		for (int i = lexPos; lexTable.table[i].lexema!=LEX_SEMICOLON; i++)		// read do semicolona
		{
			srcLen++;
			semicolonId = i + 1;
		}
		srcLen++;					// чтоб выводилась ;

		for (int i = lexPos; i < lexPos + srcLen; i++)		// expression analyse
		{
			counter++;
			switch (lexTable.table[i].lexema)
			{
			case LEX_LITERAL://џјџјџјџјџџјџјџџџџџџџџџџџџјјјјјјјјџјџјџјџјџјџјџјџјџјџџјџј
			case LEX_ID:	//операнды перенос€тс€ в результирующую строку в пор€дке их следовани€
			{
				countOperands++;
				resStr[outLen++] = lexTable.table[i];
				break;
			}
			case LEX_PLUS:
			case LEX_MINUS:
			case LEX_STAR:
			case LEX_DIRSLASH:
			{
				countOperations++;
				if (stack.empty() || stack.top().lexema == LEX_LEFTHESIS)// операци€ записываетс€ в стек, если стек пуст или в вершине стека лежит открывающа€ скобка	
				{
					stack.push(lexTable.table[i]);
					break;
				}


				while ((ArifmPriorities(stack.top().lexema) >= ArifmPriorities(lexTable.table[i].lexema)))
				{		// операци€ выталкивает все операции с большим или равным приоритетом в результирующую строку
					resStr[outLen++] = stack.top();
					stack.pop();
					if (stack.empty())break;		// -!!!
				}
				stack.push(lexTable.table[i]);		// push of arifm sign
				break;
			}
			

			case LEX_LEFTHESIS:		//  открывающа€ скобка помещаетс€ в стек
			{
				if (lexTable.table[i + 1].lexema == LEX_RIGHTHESIS)throw ERROR_THROW(137);
				brBalance++;
				stack.push(lexTable.table[i]);
				break;
			}

			case LEX_RIGHTHESIS:	// закрывающа€ скобка выталкивает все операции до открывающей скобки, после чего обе скобки уничтожаютс€
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
			default:
			{
				throw ERROR_THROW(140);
				break;
			}
			}

			if ((counter==srcLen)&&(!stack.empty()))	// по концу разбора исходной строки все операции, оставшиес€ в стеке, выталкиваютс€ в результирующую строку
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
		if (countOperations >= countOperands)throw ERROR_THROW(134);
		if (outLen > srcLen)throw ERROR_THROW(136);
		//------CHECKING FOR ERRORS


		cout << "ѕольска€ нотаци выполнена" << endl;
		cout << "»сходное выражение: " << endl;
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
		cout << "–езультат: " << endl;
		for (int i = lexPos; i < lexPos+outLen; i++)
		{
			cout << lexTable.table[i].lexema << ' ';
		}
		cout << endl << endl;
		//-----OUT

		return true;
	}
	int ArifmPriorities(char symb)
	{
		if (symb == LEX_LEFTHESIS || symb == LEX_RIGHTHESIS)
			return 1;
		if (symb == LEX_PLUS || symb == LEX_MINUS)
			return 2;
		if (symb == LEX_STAR || symb == LEX_DIRSLASH)
			return 3;
	}
}