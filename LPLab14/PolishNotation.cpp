#include "stdafx.h"

namespace Polska
{
	void findForExpressions(LT::LexTable& lexTable, IT::IdTable& idenTable) 
	{
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].lexema==LEX_ID)
			{
				PolishNotation(++i, lexTable, idenTable);
			}
		}

	}
	bool PolishNotation(int lexPos, LT::LexTable& lexTable, IT::IdTable& idenTable)
	{
		std::stack<LT::Entry> stack;
		LT::Entry outStr[200];
		int len = 0, lenOut = 0, countHesis = 0, semiColonId = 0, indexOfFuntion = 0;
		char current, oper=NULL;
		for (int i = lexPos; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
		{
			len = i;
			semiColonId = i + 1;
		}
		len++;

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

		for (int i = 0; i < lenOut; i++)
		{
			cout << outStr[i].lexema << endl;
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