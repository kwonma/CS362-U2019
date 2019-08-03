#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char inputChar(int state, int tcCount)
{
	// code to get to state 9 should execute 477 times ...
	if(state < 9){
		return (char)(tcCount % 128);
	}
	else  {
		return ' ';
	}
}

char *inputString(int state, int tcCount)
{
	int i;
	// check if time to start testing string input
	if (state == 9) {
		int charCount = tcCount % 10;
		char output[charCount];
		for(i = 0; i < (charCount); i++){
			//generate all ASCII values 0-127
			output[i] = (char)(rand() % 128);
		} 
		return output;
	}
	else { // no point testing this until it can be confirmed
		return "";
	}
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar(state, tcCount);
		s = inputString(state, tcCount);
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
				&& s[2] == 's' && s[3] == 'e'
				&& s[4] == 't' && s[5] == '\0'
				&& state == 9)
		{
			printf("error ");
			exit(200);
		}
		if (tcCount > 1000000) {
			exit(10);
		}
	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
