#include "stdio.h"
#include "defs.h"

int main() {
	AllInit();
	
	U64 playBitBoard = 0ULL;


	playBitBoard |= (1ULL << SQ64(D2));
	playBitBoard |= (1ULL << SQ64(D3));
	playBitBoard |= (1ULL << SQ64(D4));

	PrintBitBoard(playBitBoard);

	printf("\n");
	int count  = CNT(playBitBoard);
	printf("count: %d\n", count);

	int idx  = POP(&playBitBoard);
	printf("idx: %d\n", idx);
	PrintBitBoard(playBitBoard);
	count  = CNT(playBitBoard);
	printf("Count: %d\n", count);

	return 0;
}