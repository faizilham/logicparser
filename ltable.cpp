#include <iostream>
#include "LogicParser.h"

using namespace std;

int main(int argc, char** args){
	
	string sentence;
	if(argc==1){
		getline(cin,sentence);
	}else{
		sentence=args[1];
	}
	
	LogicParser L(sentence);
	cout<<(L.checkAllValue())<<endl;

	return 0;
}