#include "Out.h"

namespace Out
{
	void preparationForOut(Out::OUT* out) {
		readInText(out);
		addSeparators(out);
	}
	void clearOutFile(wchar_t outfile[]) {
		ofstream f;
		f.open(outfile);
		f.close();
	}
	OUT getout(wchar_t outfile[], In::IN in)
	{
		OUT out;
		out.text = in.text;
		clearOutFile(outfile);
		out.stream = new ofstream(outfile, ofstream::trunc && ofstream::app);
		if (out.stream->fail()) throw ERROR_THROW(113);
		return out;
	}
	void addSeparators(Out::OUT* out)
	{
		unsigned char resultText[IN_MAX_LEN_TEXT] = "\0";
		for (int i = 0, j = 0; out->text[i] != '\0'; i++, j++)
		{
			if (out->codeForOut[out->text[i]] == OUT::N)
				resultText[j++] = '|';
			resultText[j] = out->text[i];
		}
		resultText[strlen((char*)resultText)] = '|';
		resultText[strlen((char*)resultText)] = '\0';
		strcpy((char*)out->text, (char*)resultText);
		cout << out->text;
	}
	void writeInsideTextTo_OutFile(Out::OUT out, Parm::PARM parm)
	{
		*out.stream << out.text;
	}
	void CloseOut(Out::OUT out) {
		out.stream->close();
		delete out.stream;
	}
	void readInText(Out::OUT* out){
		for (int i = 0; out->text[i] != '\0'; i++)
		{
			if (out->codeForOut[out->text[i]] == OUT::L) 
			{
				i = literalIgnore(out, ++i);
				continue;
			}
			if (checkSymbol(i, out))deleteSymbol(out, i--);
		}
	}
	bool checkSymbol(int i, Out::OUT* out) {
		//-----ÓÄÀËÅÍÈÅ ÏÐÅÔÈÊÑÍ. È ÏÎÑÒÔÈÊÑÍ. ÏÐÎÁÅËÜÍÛÕ ÑÈÌÂÎËÎÂ
		if ((out->codeForOut[out->text[i]] == OUT::S || out->codeForOut[out->text[i]] == OUT::N) && (out->codeForOut[out->text[i-1]] == OUT::P || out->codeForOut[out->text[i+1]] == OUT::P))return true;
		//-----ÓÄÀËÅÍÈÅ ËÈØÍÈÕ ÏÐÎÁÅËÎÂ
		if (out->codeForOut[out->text[i]] == OUT::S && (out->codeForOut[out->text[i+1]] == OUT::S || out->codeForOut[out->text[i+1]] == OUT::N))return true;
		//-----ËÈØÍÈÅ ÏÅÐÅÍÎÑÛ
		if (out->codeForOut[out->text[i]] == OUT::N && out->codeForOut[out->text[i+1]] == OUT::N)return true;
		//-----ÓÄÀËÅÍÈÅ ËÈØÍÈÕ ÏÐÎÁÅËÜÍÛÕ ÑÈÌÂÎËÎÂ ÂÎÇËÅ ÁÊÎËÎÎÁÐÀÇÓÞÙÈÕ ÑÈÌÂÎËÎÂ
		if (out->codeForOut[out->text[i]] == OUT::S && (out->codeForOut[out->text[i-1]] == OUT::B || out->codeForOut[out->text[i+1]] == OUT::B))return true;
		//-----ÏÐÎÁÅËÜÍÛÅ ÑÈÌÂÎËÛ Â ÊÎÍÖÅ ÑÒÐÎÊÈ
		if ((out->codeForOut[out->text[i]] == OUT::S || out->codeForOut[out->text[i]] == OUT::N) && (out->codeForOut[out->text[i+1]] == OUT::N || out->codeForOut[out->text[i+1]] == OUT::S) && (out->codeForOut[out->text[i+2]] == OUT::N || out->codeForOut[out->text[i+2]] == OUT::S))return true;
		if ((out->codeForOut[out->text[i]] == OUT::S || out->codeForOut[out->text[i]] == OUT::N) && out->codeForOut[out->text[i+1]] == OUT::E)return true;
		return false;
	}
	int literalIgnore(Out::OUT* out, int startIgnoreIndex) {
		while (out->codeForOut[out->text[startIgnoreIndex]] != OUT::L) {
			startIgnoreIndex++;
		}
		return startIgnoreIndex;
	}
	void deleteSymbol(Out::OUT* out, int deleteIndex) {
		for ( ; out->text[deleteIndex] != '\0'; deleteIndex++)
		{
			out->text[deleteIndex] = out->text[deleteIndex + 1];
		}
	}
}