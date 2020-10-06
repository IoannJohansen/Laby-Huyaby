#include "stdafx.h"

namespace Lex {
	void textDivision(Out::OUT out) 
	{
		char buff[257] = "\0";
		int numLetter = 0;
		for (int i = 0; out.text[i] != '\0'; i++)
		{
			if (out.codeForOut[out.text[i]] == Out::OUT::S && out.text[i] != '\t')
			{
				buff[numLetter] = '\0';
				//cout << buff << endl;
				if (tokenAnalyse(buff))
				{
					cout << "Лексема " << buff << " распознана" << endl;
				}
				else
				{
					if (isIdentificator(buff))
					{
						// ИДЕНТИФИКАТОР
						// LT
						cout << "Лексема " << buff << " распознана" << endl;
					}
					else
					{
						cout << "Лексема " << buff << " не распознана" << endl;

					}
				}
				*buff = '\0';
				numLetter = 0;
			}
			else if(out.codeForOut[out.text[i]] == Out::OUT::N || out.text[i] == '\t')
			{
				continue;
			}
			else if (numLetter != 0 && (out.codeForOut[out.text[i]] == Out::OUT::P || out.codeForOut[out.text[i]] == Out::OUT::B))
			{
				buff[numLetter] = '\0';
				//cout << buff << endl;
				if (tokenAnalyse(buff))
				{
					cout << "Лексема " << buff << " распознана" << endl;
				}
				else
				{
					if (isIdentificator(buff))
					{
						// ИДЕНТИФИКАТОР
						// LT
						cout << "Лексема " << buff << " распознана" << endl;
					}
					else
					{
						cout << "Лексема " << buff << " не распознана" << endl;

					}
				}
				*buff = '\0';
				numLetter = 0;
				i--;
			}
			else if (numLetter == 1 &&(out.codeForOut[out.text[i-1]] == Out::OUT::P || out.codeForOut[out.text[i-1]] == Out::OUT::B))
			{
				buff[numLetter] = '\0';
				//cout << buff << endl;
				if (tokenAnalyse(buff)) 
				{
					cout << "Лексема " << buff << " распознана" << endl; 
				}
				else
				{
					if (isIdentificator(buff))
					{
						// LT
						// ИДЕНТИФИКАТОР
						cout << "Лексема " << buff << " распознана" << endl;
					}
					else
					{
						cout << "Лексема " << buff << " не распознана" << endl;

					}
				}
				*buff = '\0';
				numLetter = 0;
				i--;
			}
			else if (out.text[i] == '|')	
			{
				continue;
			}
			else if (out.codeForOut[out.text[i]] == Out::OUT::L)
			{
				buff[numLetter++] = out.text[i++];
				while (out.codeForOut[out.text[i]] != Out::OUT::L)
				{
					buff[numLetter++] = out.text[i++];
				}
				buff[numLetter++] = out.text[i];
			}
			else
			{
				buff[numLetter++] = out.text[i];
			}
			
		}
	}

	bool tokenAnalyse(char* token) {		//TODO: Add LT and IT with checking
		switch (token[0])
		{
		case LEX_SEMICOLON:
		{
			// запись в LT
			return true;
		}
		case LEX_COMMA:
		{
			// запись в LT
			return true;
		}

		case LEX_LEFTBRACE:
		{
			// запись в LT
			return true;
		}

		case LEX_RIGHTBRACE:
		{
			// запись в LT
			return true;
		}

		case LEX_LEFTHESIS:
		{
			// запись в LT
			return true;
		}

		case LEX_RIGHTHESIS:
		{
			// запись в LT
			return true;
		}

		case LEX_PLUS:
		{
			// запись в LT
			return true;
		}

		case LEX_MINUS:
		{
			// запись в LT
			return true;
		}

		case LEX_STAR:
		{
			// запись в LT
			return true;
		}

		case LEX_DIRSLASH:
		{
			// запись в LT
			return true;
		}

		case LEX_MAIN: 
		{
			// запись в LT
			return true;
		}

		case 'f': {
			FST::FST* a_function = new FST::FST(A_FUNCTION(token));
			if (FST::execute(*a_function))
			{
				// запись в LT
				delete a_function;
				a_function = nullptr;
				return true;
			}
			else
			{
				delete a_function;
				a_function = nullptr;

			}
			break;
		}

		case 'i': {
			FST::FST* a_integer = new FST::FST(A_INTEGER(token));
			if (FST::execute(*a_integer))
			{
				// запись в LT
				delete a_integer;
				a_integer = nullptr;
				return true;
			}
			else
			{
				delete a_integer;
				a_integer = nullptr;
				//--
			}
			break;
		}

		case 's': {
			FST::FST* a_string = new FST::FST(A_STRING(token));
			if (FST::execute(*a_string))
			{
				// запись в LT
				delete a_string;
				a_string = nullptr;
				return true;
			}
			else
			{
				delete a_string;
				a_string = nullptr;

			}
			break;
		}

		case 'd': {
			FST::FST* a_declare = new FST::FST(A_DECLARE(token));
			if (FST::execute(*a_declare))
			{
				// запись в LT
				delete a_declare;
				a_declare = nullptr;
				return true;
			}
			else
			{
				delete a_declare;
				a_declare = nullptr;

			}
			break;
		}

		case 'r': {
			FST::FST* a_return = new FST::FST(A_RETURN(token));
			if (FST::execute(*a_return))
			{
				// запись в LT
				delete a_return;
				a_return = nullptr;
				return true;
			}
			else
			{
				delete a_return;
				a_return = nullptr;

			}
			break;
		}

		case 'p': {
			FST::FST* a_print = new FST::FST(A_PRINT(token));
			
			if (FST::execute(*a_print))
			{
				// запись в LT
				delete a_print;
				a_print = nullptr;
				return true;
			}
			else
			{
				delete a_print;
				a_print = nullptr;

			}
			break;
		}
		default:
			// check for literal
			if (isStringLiteral(token)) 
			{
				// add to lt
				return true;
			}
			if (isIdentificator(token)) 
			{ 
				// add to lt
				return true; 
			}
			//-------------
			return false;
		}


	}

	bool isStringLiteral(char* token) {
		if ((strlen(token) <= 258) && token[0] == (char)39 && token[strlen(token)-1] == (char)39)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isIdentificator(char* buff) {
		int identLen = strlen(buff)-1;
		if (identLen <= 5)
		{
			for (int i = 0; i < identLen; i++)
			{
				if (buff[i] <= 'a' || (buff[i] >= 'z') && (buff[i] <= '0' || buff[i] >= '9'))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool checkForLexema()
	{

		return true;
	}
	bool checkForId()
	{

		return true;
	}
}