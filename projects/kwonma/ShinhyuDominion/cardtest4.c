#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
	struct gameState state;
	int i, player;
	int temp;
	//int maxHandCount = 5; 
	int seed = 75;
	int numPlayers = 2;
	//int start = -1;
	int m[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};
	int players[MAX_PLAYERS];
	// test what happens if there is 1 winner
	// initialize game 
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, m, seed, &state); 	
	// give player one +3 more estates
	for (i = 0; i < 3; i++) {
		temp = state.deckCount[0]; 
		state.deck[0][temp] = estate;
		state.deckCount[0]++;
	}
	for(i = 0; i < MAX_PLAYERS; i++) {
		players[i] = 0;
	}
	getWinners(players, &state);
	assert(players[0] == 1);
	assert(players[1] == 0);

	printf("	test 1: passed for cardtest4.c \n");
	// test what happens if there is all winners
	// initialize game 
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, m, seed, &state); 
	//endTurn(&state);
	// give player two the same cards as player 1
	/*	for(i = 0; i < numPlayers; i++) {	
		temp = state.deckCount[1]; 
		state.deck[1][temp] = estate;
		state.deckCount[1]++;
		temp = state.deckCount[0]; 
		state.deck[0][temp] = estate;
		state.deckCount[0]++;
		}
		*/	
	for(i = 0; i < MAX_PLAYERS; i++) {
		players[i] = 0;
	}
	getWinners(players, &state);
	printf("		players 1 handCount %d, deckCount %d, discardCount %d\n", state.handCount[0], state.deckCount[0], state.discardCount[0]);
	printf("		players 2 handCount %d, deckCount %d, discardCount %d\n", state.handCount[1], state.deckCount[1], state.discardCount[1]);

	int score;
	//score from handi
	for (player = 0; player < numPlayers; player++) {
		score = 0;
		for (i = 0; i < state.handCount[player]; i++)
		{
			if (state.hand[player][i] == curse) { score = score - 1; };
			if (state.hand[player][i] == estate) { score = score + 1; };
			if (state.hand[player][i] == duchy) { score = score + 3; };
			if (state.hand[player][i] == province) { score = score + 6; };
			if (state.hand[player][i] == great_hall) { score = score + 1; };
			//				if (state.hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
			//	printf("%d\n", state.hand[player][i]);
		}

		//score from discard
		for (i = 0; i < state.discardCount[player]; i++)
		{
			if (state.discard[player][i] == curse) { score = score - 1; };
			if (state.discard[player][i] == estate) { score = score + 1; };
			if (state.discard[player][i] == duchy) { score = score + 3; };
			if (state.discard[player][i] == province) { score = score + 6; };
			if (state.discard[player][i] == great_hall) { score = score + 1; };
			//				if (state.discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
			//	printf("%d\n", state.discard[player][i]);
		}

		//score from deck
		for (i = 0; i < state.deckCount[player]; i++)
		{
			if (state.deck[player][i] == curse) { score = score - 1; };
			if (state.deck[player][i] == estate) { score = score + 1; };
			if (state.deck[player][i] == duchy) { score = score + 3; };
			if (state.deck[player][i] == province) { score = score + 6; };
			if (state.deck[player][i] == great_hall) { score = score + 1; };
			//				if (state.deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
			//	printf("%d\n", state.deck[player][i]);
		}
		printf("		score: %d \n", score);
	}
	printf("		players 1 - %d, players 2 - %d\n", players[0], players[1]);
	printf(" Assertion failed for test 2: players 1 == players 2\n");
//	assert(players[0] == 1);
//	assert(players[1] == 1);
	/*	for(k = 0; k < numPlayers; k++) {
		assert(players[k] == 1);
		}
		*/
	//printf("	test 2: passed for cardtest4.c \n");
	// test what happens if there is no users
	// initialize game 
/*	numPlayers = 1;
	memset(&state, 'z', sizeof(struct gameState)); // clear the gamestate
	initializeGame(numPlayers, 0, seed, &state); 
	for(i = 0; i < MAX_PLAYERS; i++) {
		players[i] = 0;
	}
	getWinners(players, &state);
	for(l = 1; l < MAX_PLAYERS; l++) {
		assert(players[l] == -9999);
	}
	printf("	test 3: passed for cardtest4.c \n");
	//printf("	All tests passed for cardtest4.c \n");
*/	return 0;
}
