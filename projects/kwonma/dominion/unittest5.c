/* -----------------------------------------------------------------------
 * Tests refactored code based off of the example demonstration code:
 * "How to write unit tests for dominion-base"
 * 	unittest1 - playMine refactored code
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int i;
	int seed = 1000;
	int numPlayer = 4;
	int p = 1, r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;

	// test a - assert that cards from any position in hand can be used for choice1
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	// test that mine only accepts inputs that are 
		G.handCount[p] = maxHandCount;                 // set the number of cards on hand
		// tests assuming choice1 is copper
		G.hand[p][0] = mine; // set cards
		for(i = 1; i < maxHandCount; i++) {
			G.hand[p][i] = copper;
		}	
	
		playMine(&G, 4, 4, 0, p); // limited to treasure cards should return 1	
	//	printf("Swapped copper at %d and gained: %d\n", 4, G.hand[p][4]);
		assert(G.hand[p][4] == 4);
		playMine(&G, 3, 8, 0, p); // not treasure card should return -1	
	//	printf("Swapped copper at %d and gained: %d\n", 3, G.hand[p][3]);
		assert(G.hand[p][3] == -1);
		playMine(&G, 3, 6, 0, p); // not treasure card should return -1	
	//	printf("Swapped copper at %d and gained: %d\n", 3, G.hand[p][3]);
		assert(G.hand[p][3] == -1);
		
		// tests assuming choice1 is silver
		G.hand[p][0] = mine; // set cards
		for(i = 1; i < maxHandCount; i++) {
			G.hand[p][i] = silver;
		}	
	
		playMine(&G, 4, 4, 0, p); // limited to treasure cards should return 1	
		printf("	Swapped silver at %d and gained: %d\n", 4, G.hand[p][4]);
	//	assert(G.hand[p][4] == 4);
		playMine(&G, 3, 5, 0, p); // not treasure card should return -1	
		printf("	Swapped silver at %d and gained: %d\n", 3, G.hand[p][3]);
		//assert(G.hand[p][3] == 5);
		playMine(&G, 3, 9, 0, p); // not treasure card should return -1	
		printf("	Swapped silver at %d and gained: %d\n", 3, G.hand[p][3]);
	//	assert(G.hand[p][3] == -1);


		// tests assuming choice1 is gold
		G.hand[p][0] = mine; // set cards
		for(i = 1; i < maxHandCount; i++) {
			G.hand[p][i] = gold;
		}	
	
	//	playMine(&G, 4, 4, 0, p); // limited to treasure cards should return 1	
		printf("	Swapped gold at %d and gained: %d\n", 4, G.hand[p][4]);
	//	assert(G.hand[p][4] == 4);
		playMine(&G, 3, 8, 0, p); // not treasure card should return -1	
		printf("	Swapped gold at %d and gained: %d\n", 3, G.hand[p][3]);
	//	assert(G.hand[p][3] == -1);
		playMine(&G, 3, 6, 0, p); // not treasure card should return -1	
	//	printf("Swapped gold at %d and gained: %d\n", 3, G.hand[p][3]);
		assert(G.hand[p][3] == 6);
	printf("	Tests 2 and 3 failed: segmentation fault created\n");

	return 0;
}

