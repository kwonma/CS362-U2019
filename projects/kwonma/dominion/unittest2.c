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
	int numPlayer = 4;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	G.supplyCount[ambassador] = 4;
	G.supplyCount[treasure_map] = 1;

	endTurn(&G); // set to the next player's (player 1) turn

	// test that ambassador can be played
	i = G.handCount[G.whoseTurn];
	G.hand[G.whoseTurn][i] = ambassador;  // give player ambassador
	playAmbassador(&G, i, 0, i, whoseTurn);
	for(j = 0; j < numPlayers; j++) {
		if(j != G.whoseTurn) {
			assert(G.hand[j][G.handCount-1] == ambassador); //verify last card is ambassador
		}
	}
	endTurn(&G); 
	
	// test that the curse card in the hand can be played
	i = G.handCount[G.whoseTurn];
	G.supplyCount[curse] = 3;
	G.hand[G.whoseTurn][i] = curse;
	G.hand[G.whoseTurn][i+1] = curse;
	G.hand[G.whoseTurn][i+2] = curse;
	
		
	// test that the treasure map card can be played
	return 0;
}


int playAmbassador(struct gameState * state, int choice1, int choice2, int handPos, int currentPlayer) {
