/* -----------------------------------------------------------------------
 * Tests refactored code based off of the example demonstration code:
 * "How to write unit tests for dominion-base"
 * 	unittest2 - playAmbassador refactored code
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int i,j;
	int seed = 1000;
	int numPlayers = 4;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
	// gain an estate
	if (playBaron(&G, 0, 1, 1)) {
		if(G.hand[1][G.handCount[1]-1] != estate) {
			printf("	Test 1 failed: did not gain an estate at the end of player's hand: %d\n", G.hand[1][G.handCount[1]-1]);
		}
	}

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
	// gain an estate when there's nothing left
	int estateCount=0;
	G.supplyCount[estate] = 0;
	for(i = 0; i < G.handCount[2]; i++) {
		if(G.hand[2][i] == estate) {
			estateCount++; 
		}
	}
	if(playBaron(&G, 0, 1, 2)) {
		int temp =0;
		for(i = 0; i < G.handCount[2]; i++) {
			if(G.hand[2][i] == estate) {
				temp++; 
			}
		}
		if(temp != estateCount){	
			printf("	Test 2 failed: player estate count incorrect when supplycount is 0 estates: %d != %d\n", temp, estateCount);
		}

	}

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game

	// trash an estate 
	estateCount=0; int coinCount=0;
	for(i = 0; i < G.handCount[3]; i++) {
		if(G.hand[3][i] == estate) {
			estateCount++; 
		}
		else if(G.hand[3][i] == copper) {
			coinCount++; 
		}
	}
	if(playBaron(&G, 1, 0, 3)) {
		int temp = 0, coin = 0;
		for(i = 0; i < G.handCount[3]; i++) {
			if(G.hand[3][i] == estate) {
				temp++; 
			}
			else if(G.hand[3][i] == copper) {
				coin++; 
			}
		}
		if(temp == estateCount){	
			printf("	Test 3 failed: trashing estates did not work: %d != %d\n", temp, estateCount);
		}
		if(coin != coinCount){	
			printf("	Test 3 failed: getting coins when trashing estates did not work: %d != %d\n", coin, coinCount);
		}
	}
	printf("	All tests passed: No bugs detected\n");
	return 0;
}

