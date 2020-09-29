#include "stdafx.h"

namespace Lex {
	void lexAnalyse(Out::OUT out) 
	{
		char buff[257] = "\0";
		int numLetter = 0;
		for (int i = 0; out.text[i] != '\0'; i++)
		{
			if (out.text[i] == ' ' || out.text[i] == '|')
			{
				
				buff[numLetter] = '\0';
				cout << buff << endl;
				*buff = '\0';
				numLetter = 0;



			}
			else
			{
				buff[numLetter++] = out.text[i];
			}
		}



	}
}