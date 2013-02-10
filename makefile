all: LogicParser
LogicParser: ltable.o LogicParser.o
	g++ -o ltable ltable.o LogicParser.o
ltable.o : ltable.cpp
	g++ -c ltable.cpp
LogicParser.o : LogicParser.cpp
	g++ -c LogicParser.cpp
clean :
	rm -rf LogicParser *.o *~
run:
	./LogicParser
