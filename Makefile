#CXX=g++
#CPPFLAGS= -Wall -Werror

report: scanner cmos Plag
	./PlagarismDetector Examples

scanner: lex.yy.c
	g++ -o scanner lex.yy.c

lex.yy.c: cmos.l
	flex cmos.l

cmos: cmos.cpp	
	g++ -Wall -Werror -o cmos cmos.cpp

Plag:
	chmod +x PlagarismDetector

clean: 
	rm -f scanner_out.txt tokens.txt PlagarismReport.txt