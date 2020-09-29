#pragma once
#include "stdafx.h"
#include "In.h"
#include "Parm.h"
#include <string>
#include <cstring>
namespace Out
{
	#define UNNECESSARY_SYMBOLS\
	{\
	/*0			1		2		3		4		5		6		7		8		9	  A		   B	   C	   D	  E		  F*/\
	OUT::E,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::S,	OUT::N,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::S,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::L,	OUT::B,	OUT::B,	OUT::P,	OUT::P,	OUT::P,	OUT::P,	OUT::I,	OUT::P,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::B,	OUT::I,	OUT::P,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::B,	OUT::I,	OUT::B,	OUT::I,	OUT::I,\
	\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,\
	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I,	OUT::I \
	};
	//	I(ignored) - обычные символы / буквы	/ НЕ ТРОГАТ
	//	S(space) - пробельные  символы	/	пробел / табуляция
	//	N(New string) - символ переноса строки	\n
	//	B(block) - символы блокообразующие () {} 
	//  P(post pref chars) - для удаления постфикс и префикс пробелов
	//	E(TERMINATOR) - нуль терминатор / конец строки
	//	L(Literal) - строка в скобочках 'dfgdfgdfg	 dhdfgdf'
	struct OUT
	{
		enum
		{
			I = -1, S = -2, N = -3, B = -4, P = -5, E = -6, L = -7
		};
		unsigned char* text = nullptr;
		std::ofstream* stream = nullptr;
		int codeForOut[256] = UNNECESSARY_SYMBOLS;
	};
	void writeInsideTextTo_OutFile(Out::OUT out, Parm::PARM parm);
	void readInText(Out::OUT* out);
	void deleteSymbol(Out::OUT* out, int deleteIndex);
	int literalIgnore(Out::OUT* out, int startIgnoreIndex);
	bool checkSymbol(int i, Out::OUT* out);
	OUT getout(wchar_t outfile[], In::IN in);
	void addSeparators(OUT* out);
	void preparationForOut(Out::OUT* out);
	void CloseOut(Out::OUT out);
	void clearOutFile(wchar_t outfile[]);
}