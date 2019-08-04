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
	int error_flag = 0;
	int seed = 1000;
	int numPlayer = 4;
	int p = 0, r;
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
	mineCard(4, 4, &G, 0); // limited to treasure cards should return 1	
	if(G.hand[p][4] == 4) {
	}
	else{
		error_flag = 1;
		printf("	test 1 failed\n");
		printf("	Swapped copper at %d and gained: %d\n", 4, G.hand[p][4]);
	}
	mineCard(3, 8, &G, 0); // not treasure card should return -1	
	if(G.hand[p][3] == -1) {
	}
	else{
		error_flag = 1;
		printf("	test 1 failed\n");
		printf("	Swapped copper at %d and gained: %d\n", 3, G.hand[p][3]);
	}
	mineCard(3, 6, &G, 0); // not treasure card should return -1	
	if(G.hand[p][3] == -1) {
	}
	else{
		error_flag = 1;
		printf("	test 1 failed\n");
		printf("	Swapped copper at %d and gained: %d\n", 3, G.hand[p][3]);
	}

	// tests assuming choice1 is silver
	G.hand[p][0] = mine; // set cards
	for(i = 1; i < maxHandCount; i++) {
		G.hand[p][i] = silver;
	}	

	mineCard(4, 4,&G, 0); // limited to treasure cards should return 1	
	if(G.hand[p][4] == 4) {
	}
	else{
		error_flag = 1;
		printf("	test 1 failed\n");
		printf("	Swapped silver at %d and gained: %d\n", 4, G.hand[p][4]);
	}
	mineCard(3, 5, &G, 0); // not treasure card should return -1	
	if(G.hand[p][3] == 5) {
	}
	else{
		error_flag = 1;
		printf("	test 2 failed\n");
		printf("	Swapped silver at %d and gained: %d\n", 3, G.hand[p][3]);
	}
	//assert(G.hand[p][3] == 5);
	mineCard(3, 9, &G, 0); // not treasure card should return -1	
	if(G.hand[p][3] == -1) {
	}
	else{
		error_flag = 1;
		printf("	test 2 failed\n");
		printf("	Swapped silver at %d and gained: %d\n", 3, G.hand[p][3]);
	}

	// tests assuming choice1 is gold
	G.hand[p][0] = mine; // set cards
	for(i = 1; i < maxHandCount; i++) {
		G.hand[p][i] = gold;
	}	

	mineCard(3, 8, &G, 0); // not treasure card should return -1	
	if(G.hand[p][3] == -1) {
	}
	else{
		error_flag = 1;
		printf("	test 3 failed\n");
		printf("	Swapped gold at %d and gained: %d\n", 3, G.hand[p][3]);
	}
	mineCard(4, 6, &G, 0); // not treasure card should return -1	
	if(G.hand[p][4] == -1) {
	}
	else{
		error_flag = 1;
		printf("	test 3 failed\n");
		printf("	Swapped gold at %d and gained: %d\n", 3, G.hand[p][3]);
	}

	if(error_flag == 0) {
		printf("	All tests passed\n");
	}
	return 0;
}

