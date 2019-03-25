#include "stdio.h"
#include "defs.h"
#include "stdlib.h"

#define FEN0 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 1 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"


int main() {

	AllInit();

	S_BOARD board[1];

	int move = 0;
	int from = A2, to = H7;
	int cap = wR, prom = bK;

	move = ((from) | (to << 7 ) | (cap << 14) | (prom << 20));

	printf("from: %d to: %d cap: %d prom:%d", FROMSQ(move), TOSQ(move), CAPTURED(move),
		PROMOTED(move));

	printf("Algebric from: %s\n", PrSq(from));
	printf("Algebric to: %s\n", PrSq(to));
	printf("Algebric move: %s\n", PrMove(move));

	return 0;
}