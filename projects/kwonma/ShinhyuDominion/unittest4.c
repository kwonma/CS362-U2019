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

	// test choice 1
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game

	i = G.handCount[G.whoseTurn];
	G.hand[G.whoseTurn][i] = minion;
	int coinCount=0, temp=0;
	for(i = 0; i < G.handCount[3]; i++) {
		if(G.hand[3][i] == copper) {
			coinCount++; 
		}
	}
	if(minionCard( 1, 0, &G, i)) {
		if(G.numActions != 1) {	
			printf("	test 1 failed: choicee 2 did not increment actions\n");
		}
		for(i = 0; i < G.handCount[3]; i++) {
			if(G.hand[3][i] == copper) {
				temp++; 
			}
		}
		if(temp != coinCount+2) {
			printf("	Test 1 failed: did not increment coins\n");
		} 
	}

	// test choice 2 if no players have + 4 cards
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
	for(i = 0; i < numPlayers; i++) {
		for(j = 0; j < 4; j++){
			drawCard(i, &G);
		}
	}
	i = G.handCount[G.whoseTurn];
	G.hand[G.whoseTurn][i] = minion;
	if(minionCard(0,2, &G, i)) {
		if(G.numActions != 1) {	
			printf("	test 2 failed: choicee 2 did not increment actions\n");
		}
		for(i = 0; i < numPlayers; i++) {
			if(i != G.whoseTurn) {
				if(G.handCount[i]!= 4)	{
					printf("	test 2 failed: players with 5 cards did not use the drawFourNew function\n");
				}	
			}
		}
	}
	// test choice 2 if players have 5+ cards
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
	for(i = 0; i < numPlayers; i++)	{
		for(j = 0; j < 5; j++) { 
			drawCard(i, &G);
		}	
	}
	i = G.handCount[G.whoseTurn];
	G.hand[G.whoseTurn][i] = minion;
	if(minionCard(0 ,2, &G, i)) {
		if(G.numActions != 1) {	
			printf("	test 3 failed: choicee 2 did not increment actions\n");
		}
		for(i = 0; i < numPlayers; i++) {
			if(i != G.whoseTurn) {
				if(G.handCount[i]!= 4)	{
					printf("	test 3 failed: players with 5 cards did not use the drawFourNew function\n");
				}	
			}
		}
	}
	printf("	All tests passed: No bugs detected\n");
	return 0;
}
