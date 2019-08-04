#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include <time.h>

#define STOP 0 // run asserts

// minion random test

int main() {
	struct gameState G1, G2; // define generic game state
	int i,j, r = 0, p;
	int rand1, rand2, rand3, rand4;
	int error_flag = 0;
	srand(time(0));
	int cards[10];

	for(i = 0; i < 1000; i++) {
		for(j = 0; j < sizeof(int); j++) {
			cards[j] = rand() % (treasure_map);
		}
		rand3 = (rand() % INT_MAX);	
		initializeGame(4, cards, rand3, &G1);
		G1.whoseTurn = 0;
		error_flag = 0;
		printf("%d", i);
		/* START SETTING UP HAND */
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G1)[j] = rand() % 256; 		
		}
		// adjust starting players
		p = (rand() % 4);
		G1.deckCount[p] = (rand() % MAX_DECK);
		G1.discardCount[p] = (rand() % MAX_DECK);
		G1.handCount[p] = (rand() % MAX_HAND);
		if (i % 100 == 0) {	// sets numBuys to 0 once every 100 times
			G1.numActions = 0;
		}
		else {
			G1.numActions = (rand() % INT_MAX);
		}
		G1.numPlayers = 4;
		// assign hand
		G1.hand[p][0] = minion;
		/* FINISHED SETTING UP HAND */
		memcpy(&G2, &G1, sizeof(struct gameState)); // make copy of gameState to compare G2 to G1

		rand1 = (rand() % 2); // 50% change of entering in yes or no for choice1 and choice2
		rand2 = (rand() % 2);
		rand3 = rand() % (INT_MAX);
		rand4 = rand() % (INT_MAX);

		if (i % 3 == 0) { // run test 1
			// test for either option that function returns 0
			r = minionCard(rand1, rand2, &G1, 0);
			//	printf("	Minion output for random test 1: %d\n", r);
			printf("	G1 (%d) num actions %d, G2 (%d) num actions %d\n", G1.whoseTurn, G1.numActions, G2.whoseTurn, G2.numActions);
			assert(r==0);
			assert(G1.numActions == G2.numActions + 1);
			assert(G1.handCount[p] == G2.handCount[p]-1);
			printf("	Test 1 passed\n");
		}
		else if( i % 3 == 1 ) { // run test 2
			// test for discard card form hand and +2 coins for choice 1
			r = minionCard(rand3, 0, &G1, 0);
			//printf("	Minion output for random test 2: %d\n", r);
			if(G1.coins != G2.coins + 2) { 
				error_flag = 1;
				printf("     Test 2 failed: Coins for G1 (%d) != G2 + 2 (%d)\n", G1.coins, G2.coins + 2); }
			else if(G1.handCount[p] != (G2.handCount[p] - 1)) { 
				error_flag = 1;
				printf("	Test 2 failed: handCount for G1 (%d) != G2 - 1 (%d)\n", G1.handCount[p], (G2.handCount[p] - 1)); }
			for(j = 0; j < 4; j++) {
				if(j != p) {
#if STOP == 1
					assert(G1.handCount[p] == G2.handCount[p]);
#endif
					if(G1.handCount[p] != G2.handCount[p]) {
						error_flag = 1;
						printf("	Test 2 failed: players should not have to drawfournew() if choice 1\n");
						break;
					}
				}
			}
#if STOP == 1
			assert(r==0);
			assert(G1.numActions == G2.numActions + 1);
			assert(G1.coins == G2.coins + 2);
			assert(G1.handCount[p] == G2.handCount[p]-1);
#endif
			if(error_flag == 0) { printf("        Test 2 passed\n"); }
		}
		else if(i % 3 == 2) { // run test 3
			// test for any integer value > 0 for choice 2
			r = minionCard(0, rand4, &G1, 0);
			//printf("	Minion output for random test 3: %d\n", r);
			if(G1.coins != G2.coins) { 
				error_flag = 1;
				printf("     Test 3 failed: Coins for G1 (%d) != G2 (%d)\n", G1.coins, G2.coins); }
			else if(G1.handCount[p] != (G2.handCount[p] - 1)) { 
				error_flag = 1;
				printf("	Test 3 failed: handCount for G1 (%d) != G2 - 1 (%d)\n", G1.handCount[p], (G2.handCount[p] - 1)); }
#if STOP == 1
			assert(r==0);
			assert(G1.numActions == G2.numActions + 1);
			assert(G1.coins == G2.coins);
			assert(G1.handCount[p] == G2.handCount[p]-1);
#endif
			for(j = 0; j < 4; j++) {
				if(j != p) {
#if STOP == 1
					assert(G1.handCount[p] <= 4);
#endif
					if(G1.handCount[p] > 4) {
						error_flag = 1;
						printf("	Test 3 failed: players should drawfournew() if choice 2\n");
						break;
					}
				}
			}
			if(error_flag == 0) { printf("      Test 3 passed\n"); }
		}
	}
}
