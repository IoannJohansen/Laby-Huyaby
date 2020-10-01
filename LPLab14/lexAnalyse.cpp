#include "stdafx.h"

namespace Lex {
	void lexAnalyse(Out::OUT out) 
	{
		char buff[257] = "\0";
		int numLetter = 0;
		for (int i = 0; out.text[i] != '\0'; i++)
		{
			if (out.codeForOut[out.text[i]] == Out::OUT::S && out.text[i] != '\t')
			{
				buff[numLetter] = '\0';
				cout << buff << endl;
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
				cout << buff << endl;
				*buff = '\0';
				numLetter = 0;
				i--;
			}
			else if (numLetter == 1 &&(out.codeForOut[out.text[i-1]] == Out::OUT::P || out.codeForOut[out.text[i-1]] == Out::OUT::B))
			{
				buff[numLetter] = '\0';
				cout << buff << endl;
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
	bool checkForLexema()
	{


		return true;
	}
	bool checkForId()
	{



		return true;
	}
}