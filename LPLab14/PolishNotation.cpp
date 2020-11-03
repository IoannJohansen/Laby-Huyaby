#include "stdafx.h"
namespace Polska
{
	static bool inParameters = false;
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable) 
	{
		for (int i = 0; i < lexTable.size; i++)
		{
			if ((lexTable.table[i].lexema == LEX_ID) && (lexTable.table[i - 1].lexema == LEX_EQUAL_SIGN) && (lexTable.table[i + 1].lexema != LEX_LEFTHESIS))
			{													// just expression
				if (PolishNotation(i, lexTable, idenTable))
				{
					cout << endl << "Польская запись построена" << endl;
				}
				else
				{
					cout << "Польская запись не построена" << endl;
				}
			}
			else if ((lexTable.table[i].lexema == LEX_ID) && ((lexTable.table[i-1].lexema == LEX_LEFTHESIS)||(lexTable.table[i-1].lexema == LEX_COMMA))&&((lexTable.table[i + 1].lexema == LEX_PLUS)||(lexTable.table[i + 1].lexema == LEX_MINUS)||(lexTable.table[i + 1].lexema == LEX_DIRSLASH)||(lexTable.table[i + 1].lexema == LEX_STAR)))
			{// factic call of function
				inParameters = true;
				if (PolishNotation(i, lexTable, idenTable))
				{
					cout << endl << "Польская запись построена" << endl;
				}
				else
				{
					cout << "Польская запись не построена" << endl;
				}
				inParameters = false;
			}
		}

	}
	bool PolishNotation(int lexPos, LT::LexTable& lexTable, IT::IdTable& idenTable)
	{
		std::stack<LT::Entry> stack;
		LT::Entry outStr[200];
		int len = 0, lenOut = 0, countHesis = 0, semiColonId = 0, indexOfFuntion = 0;
		int countOfOperands = 0, countOfOperations = 0, brBalance = 0;		// FOR DETECKTING OF ERRORS
		char current, oper=NULL;


		for (int i = lexPos; (lexTable.table[i].lexema != LEX_SEMICOLON)&&(lexTable.table[i].lexema!=LEX_COMMA); i++)		// выражение до , либо до ; либо до ) если inPrameteres = true
		{
			if (inParameters&& (lexTable.table[i].lexema == LEX_RIGHTHESIS)&&(lexTable.table[i+1].lexema == LEX_SEMICOLON))
			{
				i--;
				break;
			}
			//-------------
			if ((lexTable.table[i].lexema == LEX_ID)||(lexTable.table[i].lexema == LEX_LITERAL))countOfOperands++;
			if ((lexTable.table[i].lexema == LEX_PLUS)||(lexTable.table[i].lexema == LEX_MINUS)||(lexTable.table[i].lexema == LEX_STAR)||(lexTable.table[i].lexema == LEX_DIRSLASH))countOfOperations++;
			if (lexTable.table[i].lexema == LEX_LEFTHESIS)brBalance++;
			if (lexTable.table[i].lexema == LEX_RIGHTHESIS)brBalance--;
			//-------------
			len = i;
			semiColonId = i + 1;
		}
		len++;

		//-------CHECK----------------
		if (countOfOperands < countOfOperations)throw ERROR_THROW(134);
		if (brBalance != 0)throw ERROR_THROW(135);
		if ((lexTable.table[lexPos].lexema == LEX_PLUS) || (lexTable.table[lexPos].lexema == LEX_MINUS) || (lexTable.table[lexPos].lexema == LEX_STAR) || (lexTable.table[lexPos].lexema == LEX_DIRSLASH))throw ERROR_THROW(137);


		//-------CHECK----------------

		for (int i = lexPos; i < len; i++)
		{
			current = lexTable.table[i].lexema;

			if ((lexTable.table[i].lexema == LEX_PLUS) || (lexTable.table[i].lexema == LEX_MINUS) || (lexTable.table[i].lexema == LEX_DIRSLASH) || (lexTable.table[i].lexema == LEX_STAR))
				oper = lexTable.table[i].lexema/*idenTable.table[lexTable.table[i].idxTI].id[0]*/;

			if (current == LEX_RIGHTHESIS)
			{
				while (stack.top().lexema != LEX_LEFTHESIS)
				{
					outStr[lenOut++] = stack.top();		// запись в стек символа между скобками
					countHesis++;
					stack.pop();	// снимаем вершину стека
				}
				stack.pop();		// удаляем (
			}

			if (current == LEX_ID || current == LEX_LITERAL)
			{
				if (lexTable.table[i + 1].lexema == LEX_LEFTHESIS)
				{
					indexOfFuntion = i;		// index of function
					i += 2;
					while (lexTable.table[i].lexema != LEX_RIGHTHESIS)
					{
						if (lexTable.table[i].lexema != LEX_COMMA)
						{
							outStr[lenOut++] = lexTable.table[i++];
						}
						else
						{
							countHesis++;
							i++;
						}
					}
					outStr[lenOut++] = lexTable.table[indexOfFuntion];
					outStr[lenOut - 1].lexema = LEX_NEWPROC;
					countHesis += 2;
				}
				else
					outStr[lenOut++] = lexTable.table[i];
			}

			if (current == LEX_LEFTHESIS)
			{
				stack.push(lexTable.table[i]);							//помещаем в стек левую скобку
				countHesis++;
			}

			if (oper == '+' || oper == '-' || oper == '*' || oper == '/')
			{
				if (!stack.size())
					stack.push(lexTable.table[i]);
				else
				{
					int pr, id;
					if (stack.top().lexema == '(' || stack.top().lexema == ')')
						pr = 1;
					else
					{
						id = stack.top().idxTI;
						pr = ArifmPriorities(idenTable.table[id].id[0]);
					}

					if (ArifmPriorities(oper) > pr)
						stack.push(lexTable.table[i]);
					else
					{
						while (stack.size() && ArifmPriorities(oper) <= ArifmPriorities(idenTable.table[id].id[0]))			//если меньше, то записываем в строку все операции с большим или равным приоритетом
						{
							outStr[lenOut] = stack.top();
							stack.pop();
							lenOut++;
						}
						stack.push(lexTable.table[i]);
					}
				}
			}
			oper = NULL;
		}

		while (stack.size())
		{
			outStr[lenOut++] = stack.top();												//вывод в строку всех знаков из стека
			stack.pop();
		}

		len = len - lexPos;
		if (lenOut > len)throw ERROR_THROW(136);

		for (int i = lexPos, k = 0; i < lexPos + lenOut; i++, k++)
		{
			lexTable.table[i] = outStr[k];												//запись в таблицу польской записи
		}
		
		
		lexTable.table[lexPos + lenOut] = lexTable.table[semiColonId];			//вставка элемента с точкой с запятой


		for (int i = 0; i < countHesis; i++)
		{
			for (int j = lexPos + lenOut + 1; j < lexTable.size; j++)				//сдвигаем на лишнее место
			{
				lexTable.table[j] = lexTable.table[j + 1];
			}
			lexTable.size--;
		}

		//--------------
		cout << "Запись выполнена: " << endl;
		for (int i = 0; i < lenOut; i++)
		{
			cout << outStr[i].lexema << ' ';
		}
		return true;
	}
	int ArifmPriorities(char symb)
	{
		if (symb == LEX_LEFTHESIS || symb == LEX_RIGHTHESIS)
			return 1;
		if (symb == LEX_PLUS || symb == LEX_MINUS)
			return 2;
		if (symb == LEX_STAR)
			return 3;
	}
}