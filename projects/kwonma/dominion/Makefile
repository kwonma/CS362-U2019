CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

cardtest1: cardtest1.c rngs.o dominion.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c rngs.o dominion.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c rngs.o dominion.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c rngs.o dominion.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

cardtest5: cardtest5.c rngs.o dominion.o
	gcc -o cardtest5 -g cardtest5.c dominion.o rngs.o $(CFLAGS)

cardtestresults: cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 rngs.o dominion.o 
	echo "Results for card tests on dominion code " > unittestresults.out
	echo "cardtest1.c: " >> unittestresults.out
	./cardtest1 >> unittestresults.out 
	gcov cardtest1 >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	
	echo "cardtest2.c: " >> unittestresults.out
	./cardtest2 >> unittestresults.out 
	gcov cardtest2 >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	
	echo "cardtest3.c: " >> unittestresults.out
	./cardtest3 >> unittestresults.out 
	gcov cardtest3 >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	
	echo "cardtest4.c: " >> unittestresults.out
	./cardtest4 >> unittestresults.out 
	gcov cardtest4 >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	
	echo "cardtest5.c: " >> unittestresults.out
	./cardtest5 >> unittestresults.out 
	gcov cardtest5 >> unittestresults.out
	cat cardtest5.c.gcov >> unittestresults.out
	
unittest1: unittest1.c rngs.o dominion.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c rngs.o dominion.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c rngs.o dominion.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c rngs.o dominion.o
	gcc -o unittest4 -g unittest4.c rngs.o dominion.o $(CFLAGS)

unittest5: unittest5.c rngs.o dominion.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o  $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o cardtestresults
	echo "Results for unit tests on refactored code: " >> unittestresults.out
	echo "unittest1.c: " >> unittestresults.out
	./unittest1 >> unittestresults.out 
	gcov unittest1 >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out	
	
	echo "unittest2.c: " >> unittestresults.out
	./unittest2 >> unittestresults.out 
	gcov unittest2 >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out	
	
	echo "unittest3.c: " >> unittestresults.out
	./unittest3 >> unittestresults.out 
	gcov unittest3 >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out	
	
	echo "unittest4.c: " >> unittestresults.out
	./unittest4 >> unittestresults.out 
	gcov unittest4 >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out	
	
	echo "unittest5.c: " >> unittestresults.out
	./unittest5 >> unittestresults.out 
	gcov unittest5 >> unittestresults.out
	cat unittest5.c.gcov >> unittestresults.out	

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
