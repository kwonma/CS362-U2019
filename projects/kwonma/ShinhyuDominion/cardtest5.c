#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
	struct gameState state;
	int i,p;
	//int maxHandCount = 5; 
	int seed = 75;
	int numPlayers = 4;
	//int start = -1;
	int m[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	// initialize game 
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, m, seed, &state); 

	for (p = 0; p < numPlayers; p++) { 
		// check that drawCard works when moving all cards to the hand pile
		for (i = 0; i < 5; i++) {
			drawCard(state.whoseTurn, &state);
		}
		//printf("		players 1 handCount %d, deckCount %d, discardCount %d\n", state.handCount[0], state.deckCount[0], state.discardCount[0]);
		assert(state.handCount[state.whoseTurn] == 10);
		assert(state.discardCount[state.whoseTurn] == 0);
		assert(state.deckCount[state.whoseTurn] == 0);
		printf("	test 1: passed drawing a card\n");

		// check that drawCard works when there is 10 cards in the hand and must pull from in discard
		// add item to discard pile
		for(i = 0; i < 5; i++) {
			state.discard[state.whoseTurn][i] = copper;
			state.discardCount[state.whoseTurn]++;
		}
		for (i = 0; i < 5; i++) {
			drawCard(state.whoseTurn, &state);
		}
		//printf("		players 1 handCount %d, deckCount %d, discardCount %d\n", state.handCount[0], state.deckCount[0], state.discardCount[0]);
		assert(state.handCount[state.whoseTurn] == 15);
		assert(state.discardCount[state.whoseTurn] == 0);
		assert(state.deckCount[state.whoseTurn] == 0);
		printf("	test 2: passed drawing from emtpy deck and full discard\n");
		
		// draw when deck and discard are empty
		for (i = 0; i < 5; i++) {
			drawCard(state.whoseTurn, &state);
		}
		//printf("		players 1 handCount %d, deckCount %d, discardCount %d\n", state.handCount[0], state.deckCount[0], state.discardCount[0]);
		assert(state.handCount[state.whoseTurn] == 15);
		assert(state.discardCount[state.whoseTurn] == 0);
		assert(state.deckCount[state.whoseTurn] == 0);
		printf("	test 3: passed drawing from empty deck and discard\n");
		endTurn(&state);
	}
	printf("	All tests passed for cardtest5.c \n");
	return 0;
}
