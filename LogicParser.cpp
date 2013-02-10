#include <cstdio>
#include "LogicParser.h"

//---TRUTH TABLE---


//------PARSER-----

//static vars & constants
const int LogicParser::MAX_VARIABLE = 15;
string LogicParser::opr[8] = {"<->", "<-", "->", "|", "&", "~", "(", ")"};

//methods

LogicParser::LogicParser(){
	word = new string[MAX_VARIABLE];
	setSentence("");
}

LogicParser::LogicParser(string sentence){
	word = new string[MAX_VARIABLE];
	setSentence(sentence);
}

LogicParser::LogicParser(const LogicParser& L){
	word = new string[MAX_VARIABLE];
	error = L.error;
	setSentence(L.display);
}

LogicParser::~LogicParser(){
	delete [] word;
}

LogicParser& LogicParser::operator= (const LogicParser& L){
	error = L.error;
	setSentence(L.display);
}

void LogicParser::setSentence(string s){
	sentence = s;
	display = s;
	while(sentence.find(' ')!=-1){
		sentence.erase(sentence.find(' '),1);
	}
	
	if (buildWords()==-1){
		error = true;
	}else{
		checkSyntax();
	}
}

string LogicParser::getSentence() const{
	return display;
}

bool LogicParser::isError() const{
	return error;
}

void LogicParser::printTable(){
	if (error){
		printf("Syntax Error\n");
		return;
	}
	
	for (int i = 0; i<n; i++){
		for (int j = 0; j<word[i].length(); j++){
			printf("%c", word[i][j]);
		}
		printf("\t");
	}
	
	for (int j = 0; j<display.length(); j++){
		printf("%c", display[j]);
	}
	printf("\n");
	
	for (int i = (1 << n) - 1; i >= 0; i--){
		for (int j = n-1; j>=0; j--){
			printf("%d\t",((i & (1 <<j)) == (1 << j)));
		}
		printf("%d\n", _parse(sentence, i));
	}
	
}

bool LogicParser::Parse(long interpretation){
	if (error) return false;
	return _parse(sentence, interpretation);
}

Validity LogicParser::checkAllValue(){
	if (error) return ERROR;
	
	bool check = _parse(sentence, 0);
	
	bool check2;
	for (long i = 1; i < (1<<n); i++){
		check2 = _parse(sentence, i);
		if (check!=check2) return UNCERTAIN;
	}
	
	return (check ? ALL_TRUE : ALL_FALSE);
}

//internal methods

void LogicParser::checkSyntax(){
	error = false;
	_parse(sentence, 0);
}

int LogicParser::buildWords(){
	//auto generate variables
	
	string temp = sentence;
	for (int i = 0; i<8;i++){
		while(temp.find(opr[i])!=-1){
			temp.replace(temp.find(opr[i]),opr[i].length()," ");
		}
	}
	
	n = 0;
	temp += " ";
	string w = "";
	for (int i = 0; i < temp.length(); i++){
		if (temp[i]!=' '){
			w+=temp[i];
		}else{
			if (w!=""){
				if(findbool(w)==-1){
					if (n==MAX_VARIABLE){
						n = 0;
						return -1; // too much variables
					}
					word[n]=w;
					n++;
				}
				w="";
			}
		}
	}
	
	return 0;
}

int LogicParser::findbool(string s){
//cari dari array constant
	for (int i = 0; i < n; ++i){
		if (s == word[i]) return (n-1)-i;
	}
	return -1;
}

int LogicParser::findrev(string str, string find){
// cari dari belakang, melewatkan yg di dalem kurung ()
	int level = 0;
	int n = str.length();
	int nf = find.length();
	string sub;
	for (int i = n-1; i>=0; --i){
		sub = str.substr(i, nf);
		if (sub.substr(0,1)==opr[7]){ // )
			level++;
		}else if(sub.substr(0,1)==opr[6]){ //(
			level--;
			if (level<0){
				error = true;
				return -1;
			}
		}else if(sub==find && level==0){
			return i;
		}
	}
	
	return -1;
}

bool LogicParser::_parse(string sentence, long interpretation){
	//parse kalimat logika
	
	if (error) return false;
	
	for (int i = 0; i < 5; i++){		
		int pos = findrev(sentence, opr[i]);
		if (pos!=-1){
			string left = sentence.substr(0, pos);
			int startright = pos + opr[i].length();
			string right = sentence.substr( startright, sentence.length() - startright);
			
			if(left==""||right==""){
				error = true;
				return false;
			}
			
			switch(i){
				case 0: // <->
					return _parse(left, interpretation) == _parse(right, interpretation); break;
				case 1: // <-
					return _parse(left, interpretation) || !_parse(right, interpretation); break;
				case 2: // ->
					return !_parse(left, interpretation) || _parse(right, interpretation); break;
				case 3: // | 
					return _parse(left, interpretation) || _parse(right, interpretation); break;
				case 4: //& 
					return _parse(left, interpretation) && _parse(right, interpretation); break;
			}
		}
	}
	
	bool negator = false;
	
	if (sentence.substr(0,1)==opr[5]){ // ~
		sentence = sentence.substr(1, sentence.length()-1);
		negator = true;
	}

	if (sentence.substr(0,1)==opr[6]){ // (
		return _parse(sentence.substr(1,sentence.length()-2), interpretation)!=negator;
	}else{
		int fb = findbool(sentence);
		
		if (fb==-1){
			error = true;
			return false;
		}
		return ((interpretation & (1 << fb)) == (1 << fb))!=negator;
	}

}