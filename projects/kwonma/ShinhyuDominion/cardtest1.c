#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
	struct gameState state;
	int i, p;
	//int maxHandCount = 5; 
	int seed = 75;
	int numPlayers = 4;
	//int start = -1;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	// testing initialize game for 4 players
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, k, seed, &state); 

	for (p = 0; p < numPlayers; p++) { 
		// test hand is 5 for the first player
		if(p == 0) { 
		//	printf("First player hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 5);
		}
		// test hand is 0 for all other players
		else {
		//	printf("Players hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 0);
		}
		// test discard pile number is 0 for all players
		//printf("Player's discard count should be 0: %d\n", state.discardCount[p]);
		assert(state.discardCount[p] == 0);
	}

	for(i = 0; i <= treasure_map; i++) {
		// test embargo tokens were set to 0 for all cards
		// printf("embargo tokens for ENUM %d should be 0: %d\n", i, state.embargoTokens[i]);
		assert(state.embargoTokens[i] == 0);
		// test supply count was initialzed and nonzero for all cards
		// printf("supply count for ENUM %d should be nonzero: %d\n", i, state.supplyCount[i]);
		assert(state.supplyCount[i] != 0);
	}	
	printf("	test passed for 4 players\n");
	// testing initialize game for 3 players
	numPlayers = 3;
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, k, seed, &state); 

	for (p = 0; p < numPlayers; p++) { 
		// test hand is 5 for the first player
		if(p == 0) { 
	//		printf("First player hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 5);
		}
		// test hand is 0 for all other players
		else {
	//		printf("Players hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 0);
		}
		// test discard pile number is 0 for all players
	//	printf("Players discard count should be 0: %d\n", state.discardCount[p]);
		assert(state.discardCount[p] == 0);
	}

	for(i = 0; i <= treasure_map; i++) {
		// test embargo tokens were set to 0 for all cards
	//	printf("embargo tokens for ENUM %d should be 0: %d\n", i, state.embargoTokens[i]);
		assert(state.embargoTokens[i] == 0);
		// test supply count was initialzed and nonzero for all cards
	//	printf("supply count for ENUM %d should be nonzero: %d\n", i, state.supplyCount[i]);
		assert(state.supplyCount[i] != 0);
	}	
	printf("	test passed for 3 players\n");

	// testing initialize game for 2 players
	numPlayers = 2;
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, k, seed, &state); 

	for (p = 0; p < numPlayers; p++) { 
		// test hand is 5 for the first player
		if(p == 0) { 
	//		printf("First player hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 5);
		}
		// test hand is 0 for all other players
		else {
	//		printf("Players hand count should be 5: %d\n", state.handCount[p]);
			assert(state.handCount[p] == 0);
		}
		// test discard pile number is 0 for all players
	//	printf("Players discard count should be 0: %d\n", state.discardCount[p]);
		assert(state.discardCount[p] == 0);
	}

	for(i = 0; i <= treasure_map; i++) {
		// test embargo tokens were set to 0 for all cards
	//	printf("embargo tokens for ENUM %d should be 0: %d\n", i, state.embargoTokens[i]);
		assert(state.embargoTokens[i] == 0);
		// test supply count was initialzed and nonzero for all cards
	//	printf("supply count for ENUM %d should be nonzero: %d\n", i, state.supplyCount[i]);
		assert(state.supplyCount[i] != 0);
	}	
	printf("	test passed for 2 players\n");
	printf("	All tests passed for cardtest1.c \n");
	return 0;
}
