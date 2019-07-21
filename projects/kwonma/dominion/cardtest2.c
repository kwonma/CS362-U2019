#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
	struct gameState state;
	int i,l,j = 0, k = 0;
	//int maxHandCount = 5; 
	int seed = 75;
	int numPlayers = 2;
	//int start = -1;
	int m[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	// initialize game 
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, m, seed, &state); 

	// test shuffle for Player one's deck
	i = shuffle(0, &state);
	//printf("User with nonempty deck should shuffle and exit with 0: deck count %d\n", state.deckCount[0]);
	assert(i == 0);
	printf("	test 1 passed: shuffle nonempty deck returns 0 \n");

	// test shuffle randomness for both players
	shuffle(0, &state);
	shuffle(1, &state);

	// draw 5 cards and determine that the order of the values is different
	for(l = 0; l < 5; l++) {
		drawCard(1, &state);
	}	
	//printf("handcount 2 %d handcount 1 %d", state.handCount[1], state.handCount[0]);
	// first draw * 1
	k = state.hand[0][0];
	j = state.hand[1][0];
	// second draw * 2
	k = k + state.hand[0][1] * 2;
	j += state.hand[1][1] * 2;
	// third draw * 4
	k += state.hand[0][2] * 4;
	j += state.hand[1][2] * 4;
	// fourth draw * 8
	k += state.hand[0][3] * 8;
	j += state.hand[1][4] * 8;
	// fifth drawy * 16 
	k += state.hand[0][4] * 16;
	j += state.hand[1][4] * 16;
	assert(k != j);	
	printf("	test 2 passed: shuffle produces a different combination of drawn cards\n");

	// test shuffle for Player Two's deck (empty)
	while(state.deckCount[1] > 0) {
		drawCard(1, &state); // remove cards from deck
	}
	//printf("User with empty deck should shuffle and exit with an error: deck count %d\n", state.deckCount[1]);	
	i = shuffle(1, &state);
	assert(i == -1);
	printf("	test 3 passed: shuffle empty deck returns -1 \n");

	printf("	All tests passed for cardtest2.c \n");
	return 0;
}
