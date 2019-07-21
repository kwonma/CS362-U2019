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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 5;

	// test a - assert that cards from any position in hand can be used for choice1
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.handCount[p] = handCount;                 // set the number of cards on hand
	memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper

	for (p = 0; p < numPlayer; p++) {
		for (i = 0; i < handCount; i++) {

		}
	}

	// test b - only treasure cards can be used as choice1
	// test c - the requested card choice2 should be a treasure card
	// test d - the requested card choice2 should be no more than +3 value than the choice1
	/*
	// arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++)
	{
	coppers[i] = copper;
	silvers[i] = silver;
	golds[i] = gold;
	}

	printf ("TESTING updateCoins():\n");
	for (p = 0; p < numPlayer; p++)
	{
	for (handCount = 1; handCount <= maxHandCount; handCount++)
	{
	for (bonus = 0; bonus <= maxBonus; bonus++)
	{
#if (NOISY_TEST == 1)
printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
}
}
}
*/
printf("All tests passed!\n");

return 0;
}

int playMine(struct gameState * state, int choice1, int choice2, int handPos, int currentPlayer) {
	int j;
	j = state->hand[currentPlayer][choice1];  //store card we will trash

	if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	{
		return -1;
	}

	if (choice2 > treasure_map || choice2 < curse)
	{
		return -1;
	}

	if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
	{
		return -1;
	}

	gainCard(choice2, state, 2, currentPlayer);

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	//discard trashed card
	for (int i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard(i, currentPlayer, state, 0);			
			/*	MINE BUG#1 REMOVAL OF THE BREAK STATEMENT WHEN CARD FOUND 	*/
			//break;
		}
	}
	/*	MINE BUG#2 USER REGAINS 3 CARDS OF THE ONE SELECTED TO TRASH INTO DECK		*/
	for (int i = 0; i < 3; i++) {
		gainCard(j, state, 1, currentPlayer);
	} //END OF BUG

	return 0;
}
