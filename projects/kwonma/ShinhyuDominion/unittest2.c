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

	G.supplyCount[ambassador] = 4;
	G.supplyCount[treasure_map] = 1;

	endTurn(&G); // set to the next player's (player 1) turn

	// test that ambassador can be played
	i = G.handCount[G.whoseTurn];
	G.hand[G.whoseTurn][i] = ambassador;  // give player ambassador
	if(ambassadorCard(i, 0, &G, i-1)) {
		for(j = 0; j < numPlayers; j++) {
			if(j != G.whoseTurn) {

				if(G.hand[j][G.handCount[j]-1] != curse) {
					printf("	Test 1 failed: other players should have ambassador: %d\n",G.hand[j][G.handCount[j]-1]); //verify last card is ambassador
				}
			}
		}
	}
	endTurn(&G); // end player 1's turn now player 2

	// test that the curse card in the hand can be played
	i = G.handCount[G.whoseTurn];
	G.supplyCount[curse] = 3;
	G.hand[G.whoseTurn][i] = ambassador;
	G.hand[G.whoseTurn][i+1] = curse;
	G.hand[G.whoseTurn][i+2] = curse;
	G.hand[G.whoseTurn][i+3] = curse;
	if(ambassadorCard(i+1, 2, &G, i)) {
		//printf("	Test 2: send curse with 2 copies; Next player [3] should have curse added at the end of their hand: %d\n", G.hand[3][G.handCount[3]-1]);
		if(G.hand[3][G.handCount[3]-1] != curse) {
			printf("	test 2 failed: curse was not sent to other players\n");	
		}
		//printf("	Test 2: send curse with 2 copies; Next player [0] should have curse added at the end of their hand: %d\n", G.hand[0][G.handCount[0]-1]);
		if(G.hand[3][G.handCount[0]-1] != curse) {
			printf("	test 2 failed: curse was not sent to other players\n");	
		}
		for(j = 0; j < G.handCount[G.whoseTurn]; j++) {
			if(G.hand[3][G.handCount[2]-1] == curse) {
				printf("		test 2 failed: there should be no curses left in current player [2] hand: %d\n",G.hand[G.whoseTurn][j]);  // all curses given out
			}
		}
	}
	// test that the treasure map card can be played
	return 0;
}


