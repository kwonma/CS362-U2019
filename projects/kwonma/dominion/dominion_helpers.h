#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

// added functions from assignment 2
int whoIsNext(struct gameState *state);
int errorCheck(int a, int b, int c); // choices a and b are fields to compare, int c gives the operation
int drawFourNew(struct gameState * state, int handpos, int currentplayer);

int playMinion(struct gameState * state, int choice1, int choice2, int handPos, int currentPlayer);
int playBaron(struct gameState * state, int choice1, int choice2, int currentPlayer);
int playTribute(struct gameState * state, int choice1, int choice, int currentPlayer);
int playAmbassador(struct gameState * state, int choice1, int choice2, int handPos, int currentPlayer);
int playMine(struct gameState * state, int choice1, int choice2, int hanPos, int currentPlayer);

#endif
