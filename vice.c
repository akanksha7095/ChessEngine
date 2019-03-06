#include "stdio.h"
#include "defs.h"

int main() {
	AllInit();
	
	U64 playBitBoard = 0ULL;

	printf("Start:\n");
	PrintBitBoard(playBitBoard);

	playBitBoard |= (1ULL << SQ64(D2));
	printf("added\n");
	PrintBitBoard(playBitBoard);

	playBitBoard |= (1ULL << SQ64(G2));
	printf("added\n");
	PrintBitBoard(playBitBoard);

	return 0;
}