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
			for (int i = 0; out.text[i] != '\0'; i++, tempIT.posNumber++)
			{

				if (out.text[i+1] == '\0') 
				{
					if (tempIT.brBalance != 0)
					{
						throw ERROR_THROW_IN(117, tempIT.numLine+1, 0);					//--!!!
					}
				}
				if ((out.codeForOut[out.text[i]]==Out::OUT::S)&&(out.codeForOut[out.text[i-1]]==Out::OUT::I))
				{
					buff[numLetter] = '\0';
					tokenAnalyse(buff);
					//cout << "Лексема: " << buff << " распознана" << " Строка: " << tempIT.numLine <<  endl;
					*buff = '\0';
					numLetter = 0;
				}
				else if ((numLetter!=0)&&((out.codeForOut[out.text[i]]==Out::OUT::B)||(out.codeForOut[out.text[i]]==Out::OUT::P))&&(out.codeForOut[out.text[i-1]]==Out::OUT::I))
				{	
					buff[numLetter] = '\0';
					tokenAnalyse(buff);
					//cout << "Лексема: " << buff << " распознана" << " Строка: " << tempIT.numLine <<  endl;
					*buff = '\0';
					numLetter = 0;
					i--;			// откат на позицию назад т к текущ символ = OUT::B
				}
				else if ((numLetter==1)&&((out.codeForOut[out.text[i-1]]==Out::OUT::B)||(out.codeForOut[out.text[i-1]] == Out::OUT::P)))
				{					// check for arithmetic token
					buff[numLetter] = '\0';
					tokenAnalyse(buff);
					//cout << "Лексема: " << buff << " распознана" << " Строка: " << tempIT.numLine <<  endl;
					*buff = '\0';
					numLetter = 0;
					i--;			// откат на позицию назад т к текущ символ = OUT::B
				}
				else  if ((out.text[i]=='|')||(out.text[i]=='\t'))
				{
					if (strlen(buff) != 0)
					{
						buff[numLetter] = '\0';
						tokenAnalyse(buff);
						*buff = '\0';
						numLetter = 0;
					}
					tempIT.posNumber++;
				}
				else if (out.codeForOut[out.text[i]] == Out::OUT::L)		// literal
				{
					buff[numLetter++] = out.text[i++];
					while (out.codeForOut[out.text[i]] != Out::OUT::L)
					{
						buff[numLetter++] = out.text[i++];
					}
					buff[numLetter++] = out.text[i];
					buff[numLetter] = '\0';
					tokenAnalyse(buff);
					*buff = '\0';
					numLetter = 0;
				}
				else if ((out.text[i]==IN_CODE_ENDL)&&((out.codeForOut[out.text[i-2]]==Out::OUT::B)||(out.codeForOut[out.text[i-2]] == Out::OUT::I)))
				{
					
					numLetter = 0;
					tempIT.numLine++;
					tempIT.posNumber = 0;
				}
				else
				{
					buff[numLetter++] = out.text[i];
				}

			}

			if (!mainIsDeclared)
			{
				throw ERROR_THROW(133, tempIT.numLine+1, tempIT.posNumber);
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
			if (((token[0] == checkForArithmeticTokens(token)) || (checkForArithmeticTokens(token) == LEX_ARITHMETIC)) && strlen(token) == 1)
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

		bool checkIdNameForTokens(char* token)		//-----!!!!!!!!!!!!!!!!!!!
		{



			return true;
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
				tempIT.flPrint = true;
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
				if(tempIT.brBalance != 0)throw ERROR_THROW_IN(117, tempIT.numLine, 0);	//--!!!
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
			case LEX_SEMICOLON: { tempIT.flAssig = false; return LEX_SEMICOLON; break; }
			case LEX_COMMA: { return LEX_COMMA; break; }
			case LEX_LEFTBRACE: {tempIT.brBalance++; return LEX_LEFTBRACE; break; }
			case LEX_RIGHTBRACE: {tempIT.brBalance--; strcpy_s(tempIT.parrentBlock, TI_BLOCK_DEFAULT); return LEX_RIGHTBRACE; break; }
			case LEX_LEFTHESIS: 
			{ if (lexTable.table[lexTable.size-1].lexema==LEX_ID)tempIT.flPar = true;
			return LEX_LEFTHESIS; 
			break; 
			}
			case LEX_RIGHTHESIS: {tempIT.flPar = false; return LEX_RIGHTHESIS;break; }
			case LEX_PLUS: {return LEX_ARITHMETIC; break; }
			case LEX_MINUS: {return LEX_ARITHMETIC; break; }
			case LEX_STAR: {return LEX_ARITHMETIC; break; }
			case LEX_DIRSLASH: {return LEX_ARITHMETIC; break; }
			case LEX_EQUAL_SIGN: {
				tempIT.flAssig = true;
				return LEX_EQUAL_SIGN;
				break;
			}
			}
		}

		bool checkForId(char* token) {
			if (strlen(token) > ID_MAXSIZE)throw ERROR_THROW_IN(128, tempIT.numLine+1, tempIT.posNumber);
			for (int i = 0; i < strlen(token); i++)
			{
				if (token[i] < 'a' || token[i] > 'z')throw ERROR_THROW_IN(131, tempIT.numLine+1, tempIT.posNumber);
			}
			if (tempIT.flPar)entryIT.idtype = IT::P;
			strcpy_s(tempIT.lastID, token);

#pragma region Checking for lex errors

			if (tempIT.flPar && (tempIT.flAssig||tempIT.flPrint))					// CHECK FOR VALID DECLARATION OF FACTIC PARAMETERS IN CALL OF FUNCTION
			{
				if ((lexTable.table[lexTable.size-1].lexema!=LEX_LEFTHESIS) && (lexTable.table[lexTable.size-1].lexema!=LEX_COMMA))
				{
					throw ERROR_THROW_IN(119, tempIT.numLine+1, tempIT.posNumber);
				}
			}
			else if (tempIT.flPar)								// CHECK FOR VALID DECLARATION OF FORMAL PARAMETERS IN DECLARE OF FUNCTION
			{
				if ((lexTable.table[lexTable.size-1].lexema!=LEX_TYPE)&&(lexTable.table[lexTable.size-2].lexema!=LEX_COMMA)&&(lexTable.table[lexTable.size-2].lexema != LEX_LEFTHESIS))
				{
					throw ERROR_THROW_IN(119, tempIT.numLine+1, tempIT.posNumber);
				}
			}

			if (lexTable.table[lexTable.size-1].lexema==LEX_FUNCTION)	 // CHECK FOR INVALID DECLARATION OF FUNCTION
			{
				if (lexTable.table[lexTable.size-2].lexema!=LEX_TYPE)
				{
					throw ERROR_THROW_IN(118, tempIT.numLine+1, tempIT.posNumber);
				}
				else if (strcmp(tempIT.parrentBlock, TI_BLOCK_DEFAULT)==0)		// ext dec
				{
					if (lexTable.table[lexTable.size-3].lexema==LEX_DECLARE)
					{
						throw ERROR_THROW_IN(118, tempIT.numLine+1, tempIT.posNumber);
					}
				}
				else if (tempIT.parrentBlock != TI_BLOCK_DEFAULT)					// int dec
				{
					if (lexTable.table[lexTable.size-3].lexema!=LEX_DECLARE)
					{
						throw ERROR_THROW_IN(118, tempIT.numLine+1, tempIT.posNumber);
					}
				}
			}
			else if ((tempIT.flDec==false)&&(lexTable.table[lexTable.size-1].lexema!=LEX_TYPE)&&(lexTable.table[lexTable.size-1].lexema!=LEX_PRINT)&&(IT::IsId(idenTable, token, tempIT.parrentBlock)==TI_NULLIDX))			// CHECK FOR USING UNDECLARED VARIABLES
			{
				throw ERROR_THROW_IN(124, tempIT.numLine+1, tempIT.posNumber);
			}

			

			if ((IT::IsId(idenTable, token, tempIT.parrentBlock)!=TI_NULLIDX)&&((tempIT.flDec==true)||(lexTable.table[lexTable.size-1].lexema==LEX_FUNCTION)))						 // CHECK FOR OVERRIDING OF ID
			{
				throw ERROR_THROW_IN(123, tempIT.numLine+1, tempIT.posNumber);
			}
			
			
			if ((strcmp(tempIT.parrentBlock, TI_BLOCK_DEFAULT)!=0)&&(tempIT.flPar==false)&&(tempIT.flAssig==false)&&(IT::IsId(idenTable, token, tempIT.parrentBlock)==TI_NULLIDX)&&(lexTable.table[lexTable.size-1].lexema!=LEX_FUNCTION))			// CHECK FOR RIGHT SEQUENCE WHEN DECLARE OF VARIABLE
			{
				if (lexTable.table[lexTable.size-1].lexema == LEX_TYPE)
				{
					if (lexTable.table[lexTable.size-2].lexema != LEX_DECLARE)
					{
						throw ERROR_THROW_IN(121, tempIT.numLine + 1, tempIT.posNumber);
					}
				}
				else
				{
					throw ERROR_THROW_IN(121, tempIT.numLine + 1, tempIT.posNumber);
				}
			}


#pragma endregion	

			if (IT::IsId(idenTable, token, tempIT.parrentBlock) == TI_NULLIDX)
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
						if (idenTable.table[tempIT.numidIT].iddatatype == IT::INT)throw ERROR_THROW_IN(127, tempIT.numLine+1, tempIT.posNumber-3);
						strcpy_s(idenTable.table[tempIT.numidIT].value.vstr.str, token);
						idenTable.table[tempIT.numidIT].value.vstr.len = strlen(token)-2;
					}
				}
				addStrLiteral(token);
				return true;
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
					{
						if ((idenTable.table[tempIT.numidIT].iddatatype == IT::STR)&&(tempIT.flPar == false)&&(lexTable.table[lexTable.size-1].lexema!=LEX_RETURN))throw ERROR_THROW_IN(129, tempIT.numLine+1, tempIT.posNumber-3);
						idenTable.table[tempIT.numidIT].value.vint = atoi(token);
					}
				}
				addIntLiteral(token);
				return true;
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
			entryIT.value.vstr.len = strlen(token)-2;
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
			if (lexem == LEX_ID)
				tempEntry.idxTI = idenTable.size;
			else
				tempEntry.idxTI = LT_TI_NULLXDX;
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

		void outLexAndIdenTables(const wchar_t* in)
		{
			lexTable.writeLT(in);
			idenTable.writeIT(in);
		}
	}