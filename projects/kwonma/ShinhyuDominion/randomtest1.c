#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include <time.h>

// baron random test

int main() {
	struct gameState G1, G2; // define generic game state
	int i,j, r, p, temp;
	int rand1;
	int supply_count, estate_count;

	rand1 = (rand() % 2); // 50% change of entering in yes or no for choice1 and choice2
	srand(time(0));

	for(i = 0; i < 10000; i++) {
		printf("%d", i);
		/* START SETTING UP HAND */
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G1)[j] = rand() % 256; 		
		}
		G1.whoseTurn = 0;
		// adjust starting players
		p = (rand() % 4);
		G1.deckCount[p] = (rand() % MAX_DECK);
		G1.discardCount[p] = (rand() % MAX_DECK);
		G1.handCount[p] = (rand() % MAX_HAND);
		if (i % 50 == 0) {	// sets numBuys to 0
			G1.numBuys = 0;
		}
		else {
			G1.numBuys = (rand() % INT_MAX);
		}
		if(i % 10 == 0) { // will set supply of estates to 0
			supply_count = 0;
			G1.supplyCount[estate] = supply_count;
			//	printf("Supply Count = %d\n", G1.supplyCount[estate]);
		}
		if((i + 5) % 10 == 0) {
			supply_count = 1;
			G1.supplyCount[estate] = supply_count;
		}
		else { 
			supply_count = (rand() % INT_MAX);
			G1.supplyCount[estate] = supply_count;
		}
		// assign hand
		G1.hand[p][0] = baron;
		temp = 0;
		for(j = 1; j < G1.handCount[p]; j++) {
			if(temp < estate_count)
			{
				G1.hand[p][j] = estate;
				temp++;
			}
			else { break; } 
		}
		/* FINISHED SETTING UP HAND */
		memcpy(&G2, &G1, sizeof(struct gameState)); // make copy of gameState to compare G2 to G1


		if (i % 3 == 0) { // run test 1
			// test for either option that function returns 0
			r = baronCard(rand1, &G1, 0);
			//printf("	Baron output for random test 1: %d\n", r);
			assert(r==0);
			//printf("		Input: %d:%d 	Supply: %d	Estate in hand: %d\n", rand1, rand2, supply_count, estate_count);	
			if(G1.numBuys == G2.numBuys + 1) {
				printf("		Test 1 passed\n");
			}
			else {
				printf("		Test 1 failed: number of buys not incremented properly\n");
			}
		}
		else if( i % 3 == 1 ) { // run test 2
			//	if (i % 50 ==0) {
			//	printf("	Supply Count = %d\n", G1.supplyCount[estate]);
			//	}
			// test for any integer value > 0 for choice 1
			r = baronCard(0, &G1, 0);
			//printf("	Baron output for random test 2: %d\n", r);
			assert(r==0);
			//printf("		Input: %d 	Supply: %d	Estate in hand: %d\n", rand3, supply_count, estate_count);	
			if(G1.numBuys == G2.numBuys + 1) {
				printf("		Test 2 passed\n");
			}
			else {
				printf("		Test 2 failed: number of buys not incremented properly\n");
			}
			if(estate_count > 1) {
				//assert(G1.coins == (G2.coins + 4));	
				if(G1.coins != G2.coins + 4) { printf("     Test 2 failed: Coins for G1 (%d) != G2 + 4 (%d)\n", G1.coins, G2.coins + 4); }
				//assert(G1.handCount[p] == G2.handCount[p] - 1);
				else if(G1.handCount[p] != (G2.handCount[p] - 1)) { printf("	Test 2 failed: handCount for G1 (%d) != G2 - 1 (%d)\n", G1.handCount[p], (G2.handCount[p] - 1)); }
				else { printf("        Test 2 passed\n"); }
			}
			else{ 
				assert(G1.coins == G2.coins);	
				if(supply_count == 0) {
					//assert(G1.supplyCount[estate] == (G2.supplyCount[estate]));
					if(G1.supplyCount[estate] != 0) { printf("     Test 2 failed: supplyCount for G1 (%d) != 0\n", G1.supplyCount[estate]); }
					//assert(G1.supplyCount[estate] == 0);
					else if(G1.supplyCount[estate] != (G2.supplyCount[estate])) { 
						printf("     Test 2 failed: supplyCount for G1 (%d) != G2 (%d)\n", G1.supplyCount[estate], G2.supplyCount[estate]); }
					else {  printf("        		Test 2 passed\n"); }
				}
				else {	
					//assert(G1.supplyCount[estate] == (G2.supplyCount[estate]-1)); 
					if (G1.supplyCount[estate] != G2.supplyCount[estate] -1) { 
						printf("     Test 2 failed: supplyCount for G1 (%d) != G2 - 1 (%d)\n", G1.supplyCount[estate], G2.supplyCount[estate]-1 ); } 
					else { printf("       		 Test 2 passed\n"); }
				}
			} 
		}
		else if(i % 3 == 2) { // run test 3
			// test for any integer value > 0 for choice 2
			r = baronCard(1, &G1, 0);
			//printf("	Baron output for random test 3: %d\n", r);
			assert(r==0);
			//printf("		Input: %d 	Supply: %d	Estate in hand: %d\n", rand4, supply_count, estate_count);	
			if(G1.numBuys == G2.numBuys + 1) {
				printf("		Test 3 passed\n");
			}
			else {
				printf("		Test 3 failed: number of buys not incremented properly\n");
			}
			assert(G1.coins == G2.coins);
			if(supply_count == 0) {
				//assert(G1.supplyCount[estate] == (G2.supplyCount[estate]));
				//assert(G1.supplyCount[estate] == 0);
				if(G1.supplyCount[estate] != 0) { printf("     Test 3 failed: supplyCount for G1 (%d) != 0\n", G1.supplyCount[estate]); }
				else if(G1.supplyCount[estate] != (G2.supplyCount[estate])) { 
					printf("     Test 3 failed: supplyCount for G1 (%d) != G2 (%d)\n", G1.supplyCount[estate], G2.supplyCount[estate]); }
				else { printf("		Test 3 passed\n"); }
			}
			else {	
				//printf("G2: %d G1: %d \n", G2.supplyCount[estate], G1.supplyCount[estate]);
				//assert(G1.supplyCount[estate] == (G2.supplyCount[estate]-1)); 
				if (G1.supplyCount[estate] != G2.supplyCount[estate] -1) { 
					printf("     Test 3 failed: supplyCount for G1 (%d) != G2 - 1 (%d)\n", G1.supplyCount[estate], G2.supplyCount[estate]-1 ); } 
				else { printf("		Test 3 passed\n"); }
			}
		}
	}
}
