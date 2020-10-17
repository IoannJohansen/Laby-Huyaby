#include "stdafx.h"
	Lex::TempIT tempIT;
	LT::LexTable lexTable = LT::Create(LT_MAXSIZE); // Создание таблицы лексем
	IT::IdTable idenTable = IT::Create(TI_MAXSIZE);        // создание таблицы индефикаторов размером 200
	IT::Entry entryIT = IT::GetEntry(idenTable, tempIT.numLine);
	bool static mainIsDeclared;


	namespace Lex
	{
		void textDivision(Out::OUT out)
		{
			char buff[257] = "\0";
			int numLetter = 0;
			for (int i = 0; out.text[i] != '\0'; i++)
			{
				if (out.text[i] == IN_CODE_ENDL)	//считаем строки
				{
					tempIT.numLine++;
					continue;
				}
				if (out.codeForOut[out.text[i]] == Out::OUT::S && out.text[i] != '\t')
				{
					buff[numLetter] = '\0';
					if (tokenAnalyse(buff))
					{
						*buff = '\0';
						numLetter = 0;
						
					}
				}
				else if (out.text[i] == '\t')
				{
					continue;
				}
				else if (numLetter != 0 && (out.codeForOut[out.text[i]] == Out::OUT::P || out.codeForOut[out.text[i]] == Out::OUT::B))
				{
					buff[numLetter] = '\0';
					if (tokenAnalyse(buff))
					{
						*buff = '\0';
						numLetter = 0;
						i--;

					}
				}
				else if (numLetter == 1 && (out.codeForOut[out.text[i - 1]] == Out::OUT::P || out.codeForOut[out.text[i - 1]] == Out::OUT::B))
				{
					buff[numLetter] = '\0';
					if (tokenAnalyse(buff))
					{
						*buff = '\0';
						numLetter = 0;
						i--;

					}
				}
				else if (out.text[i] == '|' || out.codeForOut[out.text[i]] == Out::OUT::N)
				{
					if (out.text[i] == IN_CODE_ENDL)
					{
						tempIT.numLine++;
					}
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
			if (!mainIsDeclared)
			{
				throw ERROR_THROW(133);
			}
		}

		bool tokenAnalyse(char* token)
		{
			if (checkForInteger(token)) {
				addLex(LEX_INTEGER);
				return true;
			}
			if (checkForString(token)) {
				addLex(LEX_STRING);
				return true;
			}
			if (checkForFunction(token)) {
				addLex(LEX_FUNCTION);
				return true;
			}
			if (checkForDeclare(token)) {
				addLex(LEX_DECLARE);
				return true;
			}
			if (checkForReturn(token)) {
				addLex(LEX_RETURN);
				return true;
			}
			if (checkForPrint(token)) {
				addLex(LEX_PRINT);
				return true;
			}
			if (checkForMain(token)) {
				addLex(LEX_MAIN);
				return true;
			}
			if ((token[0] == checkForArithmeticTokens(token)) && (strlen(token) == 1))
			{
				char symbol = checkForArithmeticTokens(token);
				addLex(symbol);
				return true;
			}
			if (checkForStringLiteral(token))
			{
				addLex(LEX_LITERAL);
				return true;
			}
			if (checkForIntegerLiteral(token))
			{
				addLex(LEX_LITERAL);
				return true;
			}
			if (checkForId(token)) {
				addLex(LEX_ID);
				return true;
			}
		}

		bool checkForInteger(char* token) {
			FST::FST* a_integer = new FST::FST(A_INTEGER(token));
			if (FST::execute(*a_integer))
			{
				entryIT.iddatatype = IT::INT;
				if (entryIT.iddatatype == IT::V)
				{
					entryIT.value.vint = TI_INT_DEFAULT;
				}
				delete a_integer;
				a_integer = nullptr;
				return true;
			}
			else
			{
				delete a_integer;
				a_integer = nullptr;
				return false;
			}
		}

		bool checkForString(char* token) {
			FST::FST* a_string = new FST::FST(A_STRING(token));
			if (FST::execute(*a_string))
			{
				entryIT.iddatatype = IT::STR;
				if (entryIT.iddatatype == IT::V)
				{
					entryIT.value.vstr.str[0] = TI_STR_DEFAULT;
					entryIT.value.vstr.len = 0;
				}
				delete a_string;
				a_string = nullptr;
				return true;
			}
			else
			{
				delete a_string;
				a_string = nullptr;
				return false;
			}
		}

		bool checkForFunction(char* token) {
			FST::FST* a_function = new FST::FST(A_FUNCTION(token));
			if (FST::execute(*a_function))
			{
				entryIT.idtype = IT::F;
				delete a_function;
				a_function = nullptr;
				return true;
			}
			else
			{
				delete a_function;
				a_function = nullptr;
				return false;
			}
		}

		bool checkForDeclare(char* token) {
			FST::FST* a_declare = new FST::FST(A_DECLARE(token));
			if (FST::execute(*a_declare))
			{
				tempIT.flDec = true;
				entryIT.idtype = IT::V;
				delete a_declare;
				a_declare = nullptr;
				return true;
			}
			else
			{
				delete a_declare;
				a_declare = nullptr;
				return false;
			}
		}

		bool checkForReturn(char* token) {
			FST::FST* a_return = new FST::FST(A_RETURN(token));
			if (FST::execute(*a_return))
			{
				delete a_return;
				a_return = nullptr;
				return true;
			}
			else
			{
				delete a_return;
				a_return = nullptr;
				return false;
			}
		}

		bool checkForPrint(char* token) {
			FST::FST* a_print = new FST::FST(A_PRINT(token));
			if (FST::execute(*a_print))
			{
				delete a_print;
				a_print = nullptr;
				return true;
			}
			else
			{
				delete a_print;
				a_print = nullptr;
				return false;
			}
		}

		bool checkForMain(char* token) {
			FST::FST* a_main = new FST::FST(A_MAIN(token));
			if (FST::execute(*a_main))
			{
				if (mainIsDeclared)throw ERROR_THROW(130);
				strcpy_s(tempIT.parrentBlock, TI_BLOCK_MAIN);
				mainIsDeclared = true;
				delete a_main;
				a_main = nullptr;
				return true;
			}
			else
			{
				delete a_main;
				a_main = nullptr;
				return false;
			}
		}

		char checkForArithmeticTokens(char* token) {
			switch (token[0])
			{
			case LEX_SEMICOLON: {return LEX_SEMICOLON; break; }
			case LEX_COMMA: {return LEX_COMMA; break; }
			case LEX_LEFTBRACE: {return LEX_LEFTBRACE; break; }
			case LEX_RIGHTBRACE: {return LEX_RIGHTBRACE; break; }
			case LEX_LEFTHESIS: {tempIT.flPar = true; return LEX_LEFTHESIS; break; }
			case LEX_RIGHTHESIS: {tempIT.flPar = false; return LEX_RIGHTHESIS; break; }
			case LEX_PLUS: {return LEX_PLUS; break; }
			case LEX_MINUS: {return LEX_MINUS; break; }
			case LEX_STAR: {return LEX_STAR; break; }
			case LEX_DIRSLASH: {return LEX_DIRSLASH; break; }
			case LEX_EQUAL_SIGN: {
				if (lexTable.table[lexTable.size - 1].lexema == LEX_ID)tempIT.flAssig = true;
				return LEX_EQUAL_SIGN;
				break;
			}
			}
		}

		bool checkForId(char* token) {
			if (strlen(token) > ID_MAXSIZE)throw ERROR_THROW(128);
			for (int i = 0; i < strlen(token); i++)
			{
				if (token[i] < 'a' || token[i] > 'z')throw ERROR_THROW(131);
			}
			if (tempIT.flPar)entryIT.idtype = IT::P;
			strcpy_s(tempIT.lastID, token);
			if (IT::IsId(idenTable, tempIT.lastID, entryIT.parrentBlock) == TI_NULLIDX)
				addIdent(token);
			return true;
		}

		bool checkForStringLiteral(char* token) {
			if (token[0] == '\'')
			{
				if (strlen(token) > TI_STR_MAXSIZE)throw ERROR_THROW(126);
				if (tempIT.flAssig)
				{
					tempIT.numidIT = IT::IsId(idenTable, tempIT.lastID, tempIT.parrentBlock);
					if (tempIT.numidIT != TI_NULLIDX)
					{
						strcpy_s(idenTable.table[tempIT.numidIT].value.vstr.str, token);
						idenTable.table[tempIT.numidIT].value.vstr.len = strlen(token);
					}
				}
				addStrLiteral(token);
				return true;	// LEX_LIteRAL
			}
			else
			{
				return false;
			}
		}

		bool checkForIntegerLiteral(char* token) {
			if (isdigit(token[0]))
			{
				if (atoi(token) < pow(-2, 31) || atoi(token) > (pow(2, 31) - 1))throw ERROR_THROW(132);
				strcpy_s(entryIT.id, "-");
				if (tempIT.flAssig)
				{
					tempIT.numidIT = IT::IsId(idenTable, tempIT.lastID, tempIT.parrentBlock);
					if (tempIT.numidIT != TI_NULLIDX)
						idenTable.table[tempIT.numidIT].value.vint = atoi(token);
				}
				addIntLiteral(token);
				return true;	// LEX_LITERAL
			}
		}

		void addIntLiteral(char* token) {
			entryIT.iddatatype = IT::INT;
			entryIT.value.vint = atoi(token);
			entryIT.idtype = IT::L;
			IT::Add(idenTable, entryIT);
			entryIT.value.vint = TI_INT_DEFAULT;
		}

		void addStrLiteral(char* token) {
			strcpy_s(entryIT.id, "-");
			entryIT.idtype = IT::L;
			entryIT.iddatatype = IT::STR;
			entryIT.value.vstr.len = strlen(token);
			strcpy_s(entryIT.value.vstr.str, token);
			IT::Add(idenTable, entryIT);
			entryIT.value.vstr.str[0] = TI_STR_DEFAULT;
			entryIT.value.vstr.len = 0;
		}

		void addLex(char lexem)
		{
			LT::Entry tempEntry;                             // временная лексема
			tempEntry.lexema = lexem;
			tempEntry.sn = tempIT.numLine;
			LT::Add(lexTable, tempEntry);
		}

		void addIdent(char* token)
		{
			if (entryIT.idtype == IT::F)
			{
				strcpy_s(entryIT.parrentBlock, TI_BLOCK_DEFAULT);
			}
			else
			{
				strcpy_s(entryIT.parrentBlock, tempIT.parrentBlock);
			}
			if (entryIT.iddatatype == IT::STR && entryIT.idtype != IT::F)
			{
				entryIT.value.vstr.str[0] = TI_STR_DEFAULT;
				entryIT.value.vstr.len = 0;
			}
			strcpy_s(entryIT.id, token);
			entryIT.idxfirstLE = tempIT.numLine;
			if (tempIT.flPar)entryIT.idtype = IT::P;
			IT::Add(idenTable, entryIT);
			if(entryIT.idtype == IT::F && !tempIT.flDec)
				strcpy_s(tempIT.parrentBlock, entryIT.id);
			tempIT.flDec = false;
		}

		void outLexAndIdenTables(Log::LOG log) {
			for (int i = 0; i < lexTable.size; i++)
			{
				if (lexTable.table[i].sn != lexTable.table[i - 1].sn) //вывод на новых строках
				{
					(*log.stream) << std::endl;
					(*log.stream) << lexTable.table[i].sn + 1 << " "; //нумерация
				}
				(*log.stream) << lexTable.table[i].lexema;
			}
			for (int i = 0; i < idenTable.size; i++)
			{
				cout << "Идентификатор: " << idenTable.table[i].id << endl;
				cout << "Родительский блок " << idenTable.table[i].parrentBlock << endl;
				if (idenTable.table[i].iddatatype == IT::INT)
					cout << "Тип данных: integer" << endl;
				else
					cout << "Тип данных: string" << endl;
				if (idenTable.table[i].idtype == IT::V)
					cout << "Тип Идентификатора: переменная" << endl;
				else if (idenTable.table[i].idtype == IT::F)
					cout << "Тип Идентификатора: функция" << endl;
				else if (idenTable.table[i].idtype == IT::P)
					cout << "Тип Идентификатора: параметр" << endl;
				else
					cout << "Тип Идентификатора: литерал" << endl;
				if ((idenTable.table[i].iddatatype == IT::INT && idenTable.table[i].idtype == IT::V) || (idenTable.table[i].iddatatype == IT::INT && idenTable.table[i].idtype == IT::L))
					cout << "Инициализированное значение: " << idenTable.table[i].value.vint << endl;
				else if ((idenTable.table[i].iddatatype == IT::STR && idenTable.table[i].idtype == IT::V)
					|| (idenTable.table[i].iddatatype == IT::STR && idenTable.table[i].idtype == IT::L))
				{
					if (idenTable.table[i].value.vstr.str[0] == NULL)
					{
						cout << "Инициализированное значение: NULL" << endl;
					}
					else
						cout << "Инициализированное значение: " << idenTable.table[i].value.vstr.str << endl;
					cout << "Длина строки: " << idenTable.table[i].value.vstr.len << endl;
				}

				cout << endl;
			}
		}
	}
	