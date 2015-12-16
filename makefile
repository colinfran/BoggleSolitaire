P2.out: Proj2app.o SetLimits.o Game.o ShortWords.o
	g++ -g -o P2.out Proj2app.o SetLimits.o Game.o ShortWords.o

Proj2app.o: Proj2app.cpp SetLimits.h Game.h
	g++ -g -c Proj2app.cpp

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

Game.o: Game.cpp Game.h ShortWords.h
	g++ -g -c Game.cpp

ShortWords.o: ShortWords.cpp ShortWords.h
	g++ -g -c ShortWords.cpp

clean:
	rm *.o P2.out

run : P2.out
	clear
	./P2.out

submit : Proj2app.cpp Game.h Game.cpp makefile README.txt
	rm -rf franceschiniP2
	mkdir franceschiniP2
	cp Proj2app.cpp franceschiniP2
	cp Game.h franceschiniP2
	cp Game.cpp franceschiniP2
	cp makefile franceschiniP2
	cp README.txt franceschiniP2
	tar cfvz franceschiniP2.tgz franceschiniP2
	cp franceschiniP2.tgz ~tiawatts/cs215drop
