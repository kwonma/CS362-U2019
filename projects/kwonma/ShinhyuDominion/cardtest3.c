#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
	struct gameState state;
	//int maxHandCount = 5; 
	int seed = 75;
	int numPlayers = 4;
	int m[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};
	int i,j, temp,p;
	// initialize game 
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, m, seed, &state); 

	// check that player's hands are set up correctly
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
	}

	for(i = 0; i < numPlayers; i++) {
		int coin_ct = 0;
		temp = state.whoseTurn;
		updateCoins(temp, &state, 3);  // get some coins

		endTurn(&state); // call function
		// test 1 check that former player's hand is emptied
		assert(state.handCount[temp] == 0);
		printf("	test 1 passed: old player's hand is emptied\n");	
		// test 2 check that next player is correct	
		//printf("This player is %d next player should be %d\n", state.whoseTurn, (temp+1) % numPlayers);
		assert(state.whoseTurn == (temp + 1) % (numPlayers));
		printf("	test 2 passed: next player is correct\n");	
		// test 3 check that next player draws 5 cards from his deck 
		assert(state.handCount[state.whoseTurn] == 5);
		printf("	test 3 passed: next player has drawn 5 cards from his deck\n");	
		// test 4 check that next player's coin count is the sum of treasure in their hand and buys/actions updated
		for(j = 0; j < state.handCount[state.whoseTurn]; j++) {
			if(state.hand[p][j] == copper) {
				coin_ct += 1;		
			}
			else if(state.hand[p][j] == silver) {
				coin_ct += 2;	
			}
			else if(state.hand[p][j] == gold) {
				coin_ct += 3;
			}
			printf("		card %d\n", state.hand[p][j]);
		}
		printf("	state.coins %d coins counted %d\n", state.coins, coin_ct);
		assert(state.numBuys == 1);	
		assert(state.numActions == 1);
		printf("assertion coin_ct == state.coins failed");
		//assert(coin_ct == state.coins);
	//	printf("	test 4 passed: next player coin count is updated; numBuys and numActions are 1\n");	
	}
//	printf("	All tests passed for cardtest3.c \n");
	return 0;
}
