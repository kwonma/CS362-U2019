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
	int i,j, r = 0, p, next;
	int rand1, rand2, rand3;
	int error_flag;
	srand(time(0));
	int cards[10];

	for(i = 0; i < 1000; i++) {
		error_flag = 0;
		rand1 = (rand() % (INT_MAX));
		rand2 = (rand() % (INT_MAX));
		rand3 = (rand() % (INT_MAX));
		
		for(j = 0; j < sizeof(int); j++) {
			cards[j] = rand() % (treasure_map);
		}
		
		initializeGame(4, cards, rand3, &G1);
		
		printf("%d", i);
		/* START SETTING UP HAND */
		// adjust starting players
		p = (rand() % 4);
		next = (p + 1) % 4;
		G1.playedCardCount = rand() % 256;
		G1.deckCount[p] = (rand() % MAX_DECK);
		G1.discardCount[p] = (rand() % MAX_DECK);
		G1.handCount[p] = (rand() % MAX_HAND);
		if (i % 10 == 0) 
		{
			G1.deckCount[next] = 0;
		}
		else if(i % 15 == 0) 
		{
			G1.deckCount[next] = 1;
		}
		else {		
			G1.deckCount[next] = (rand() % MAX_DECK);
		}
		if (i % 20 == 0) {
			G1.discardCount[next] = 0;
		}
		else if(i % 5 == 0) 
		{
			G1.discardCount[next] = 1;
		}
		else {
			G1.discardCount[next] = (rand() % MAX_DECK);
		}
		if (i % 30 == 0) {
			G1.handCount[next] = 0;
		}
		else {
			G1.handCount[next] = (rand() % MAX_HAND);
		}

		// assign random cards to the next player's hand
		for (j = 0; j < G1.deckCount[next]; j++) {
			if (i < 250) {	// test all treasure cards
				G1.deck[next][j] = (rand() % 3) + copper;
			}
			else if(i < 500) { // test all victory cards
				G1.deck[next][j] = (rand() % 3) + estate;
			}
			else if(i < 750) { // test all action cards
				G1.deck[next][j] = (rand() % 5) + ambassador;
			}
			else {
				G1.deck[next][j] = rand() % (treasure_map + 1);
			}
		}
		for (j = 0; j < G1.deckCount[next]; j++) {
			if (i < 250) {	// test all treasure cards
				G1.discard[next][j] = (rand() % 3) + copper;
			}
			else if(i < 500) { // test all victory cards
				G1.discard[next][j] = (rand() % 3) + estate;
			}
			else if(i < 750) { // test all action cards
				G1.discard[next][j] = (rand() % 5) + ambassador;
			}
			else {
				G1.discard[next][j] = rand() % (treasure_map + 1);
			}
		}
		G1.numPlayers = 4;
		// assign hand
		G1.hand[p][0] = tribute;

		/* FINISHED SETTING UP HAND */
		memcpy(&G2, &G1, sizeof(struct gameState)); // make copy of gameState to compare G2 to G1


		r = playTribute(&G1, rand1, rand2, p);
		assert(r == 0);
		// test 1: case if only one card to pull from deck
		if(G2.deckCount[next] + G2.discardCount[next] == 1) {
			// prove that the discard or deck count matches 
			if(G1.deckCount[next] != G2.deckCount[next]-1 && G1.discardCount[next] != G2.discardCount[next]-1) {
				printf("	Test failed for deckcount + discardcount = 1\n");
				error_flag = 1;
			}
		}		
		// test 2: case if deck empty, discard full
		else if(G2.deckCount[next] == 0 && G2.discardCount[next] > 1) {
			// prove that deck count and discard count are the same as G2
			if(G1.discardCount[next] != G2.discardCount[next] && G1.deckCount[next] != G2.discardCount[next] - 2) {
				printf("	Test failed for deckcount = 0 and discardcount > 1\n");
				error_flag = 1;
			}
		}		
		// test 3: case if discard empty, deck full
		else if(G2.deckCount[next] > 1 && G2.discardCount[next] == 0) {
			// prove that deck is decremented by 2 and discount is the same
			if(G1.deckCount[next] != G2.deckCount[next] - 2) {
				printf("	Test failed for deckcount > 1 and discardcount = 0\n");
				error_flag = 1;
			}
		}		
		// test 4: case if no cards at all
		else if(G2.deckCount[next] == 0 && G2.discardCount[next] == 0) {
			// prove that nothing has changed
			if(G1.deckCount[next] != G2.deckCount[next]) {
				printf("	Test failed for deckcount = 0\n");
				error_flag = 1;
			}
			if(G1.discardCount[next] != G2.discardCount[next]) {
				printf("	Test failed for discardcount = 0\n");
				error_flag = 1;
			}
		}	
		// tests based on known values
		if (i < 250) {	// test all treasure cards
			if(G1.coins != G2.coins + 2 && G1.coins != G2.coins + 4) {
				printf("	Test all treasure cards failed for next player %d, %d\n", G1.coins, G2.coins);
			}		
#if STOP == 1
			exit(1);
#endif
		}
		else if(i < 500) { // test all victory cards
			if(G1.handCount[p] != G2.handCount[p] + 2 && G1.handCount[p] != G2.handCount[p] + 4) {
				printf("	Test all victory cards failed for next player %d, %d\n", G1.handCount[p], G2.handCount[p]);
			}			
#if STOP == 1
			exit(1);
#endif
		}
		else if(i < 750) { // test all action cards
			if(G1.numActions != G2.numActions + 2 && G1.numActions != G2.numActions + 4) {
				printf("	Test all action cards failed for next player %d, %d\n", G1.numActions, G2.numActions);
			}			
#if STOP == 1
			exit(1);
#endif
		}
		if(error_flag == 0){
			printf("	Tests passed for tribute\n");
		}
	}
}
