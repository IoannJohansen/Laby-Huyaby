#pragma once
#define IN_MAX_LEN_TEXT 1024
#define IN_CODE_ENDL '\n'
namespace In
{
#define IN_CODE_TABLE {\
	/*0		  1		  2		  3		  4		  5		  6		  7		  8		  9	     A		  B	      C	      D	      E		  F*/\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::T,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::L,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::F,	IN::F,	IN::F,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::F,	IN::T,	IN::F,	IN::T,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::F,	IN::T,	IN::F,	IN::F,\
	\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F \
	};
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, L = 5120 };
		int size = 0;
		int lines = 1;
		int ignor = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];
		int code[256] = IN_CODE_TABLE;
	};
	IN getin(wchar_t* infile);
}