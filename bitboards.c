#include "stdio.h"
#include "defs.h"

const int BitTable[64] = {61, 28, 56, 2, 43, 8, 27, 11, 20, 3, 24, 38, 62, 23, 33, 18, 57, 48, 15, 53, 58, 12, 49, 
	10, 39, 37, 34, 36, 55, 51, 31, 26, 47, 63, 32, 4, 21, 50, 7, 54, 45, 42, 29, 22, 60, 0, 9, 5, 41, 17, 40, 30, 
	46, 6, 13, 52, 1, 14, 16, 59, 35, 44, 25, 19
};

int PopBit(U64 *bb){
	U64 b = *bb ^ (*bb - 1);
	unsigned int fold  = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
	*bb &= (*bb - 1);
	return BitTable[(fold * 0x783a9b23) >> 26];
}

int CountBits(U64 b){
	int r; 
	for(r = 0; b; r++, b &= b - 1);
	return r;
}


void PrintBitBoard(U64 bb){

	U64 shiftMe = 1ULL;

	int rank = 0;
	int file = 0;
	int sq = 0;
	int sq64 = 0;

	printf("\n");
	for(rank = RANK_8; rank >= RANK_1; rank--)
	{
		for(file = FILE_A; file <= FILE_H; file++)
		{
			sq = FR2Sq(file, rank);// 120 based
			sq64 = SQ64(sq); //64 based 
			if((shiftMe << sq64) & bb)
				printf("X");
			else
				printf("-");
		}
		printf("\n");
	}
	printf("\n\n");
}