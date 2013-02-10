#include <string>

#ifndef LOGICPARSER_H
#define LOGICPARSER_H

using namespace std;

enum Validity {ALL_TRUE, ALL_FALSE, UNCERTAIN, ERROR};

class LogicParser{
	private:
		//vars
		string sentence;
		string display;
		string *word;
		int n;
		bool error;
		
		//statics
		static string opr[8];
		static const int MAX_VARIABLE;
		
		//internal methods
		int buildWords();
		int findbool(string);
		int findrev(string,string);
		bool _parse(string, long);
		void checkSyntax();
		
	public:
		LogicParser();
		LogicParser(string);
		LogicParser(const LogicParser&);
		~LogicParser();
		
		LogicParser& operator= (const LogicParser&);
		
		//setter & getter
		void setSentence(string);
		string getSentence() const;
		
		//error status
		bool isError() const;
		
		//value related
		bool Parse(long);
		Validity checkAllValue();
		void printTable();
		//TruthTable* buildTable();
};

#endif