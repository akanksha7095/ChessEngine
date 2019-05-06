#include "stdio.h"
#include "defs.h"

#define MOVE(f, t, ca, pro, fl) ((f) | ((t) << 7) | ( (ca) << 14) | ( (pro) << 20) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

int LoopSlidePce[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0}; // to know which pce to move

int LoopSlideIndex[2] = {0, 4};
int LoopNonSlideIndex[2] = {0, 3};

int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

int NumDir[13] = { 0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

// LoopSlideindex[BLACK] = 4;
// LoopSlidePce[LoopSlideindex[side]] = wB;

int LoopNonSlidePce[6] = { wN, wK, 0, bN, bK, 0};


void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list)
{
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddWhitePawnCapMove( const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list)
{

	ASSERT(PieceValidEmpty(cap));
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));

	if(RanksBrd[from] == RANK_7)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
	}
	else
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
}

void AddWhitePawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list)
{

	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));

	if(RanksBrd[from] == RANK_7)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
	}
	else
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
}

void AddBlackPawnCapMove( const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list)
{
	ASSERT(PieceValidEmpty(cap));
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));

	if(RanksBrd[from] == RANK_2)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
		AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
	}
	else
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
}

void AddBlackPawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list)
{
	
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));

	if(RanksBrd[from] == RANK_2)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
	}
	else
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list)
{
	ASSERT(CheckBoard(pos));

	list->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0, t_sq = 0;
	int pceNum = 0;
	int dir = 0, index = 0, pceIndex = 0;

	printf("\nSide: %d\n", side);

	if(side == WHITE)
	{
		for(pceNum = 0; pceNum < pos->pceNum[wP]; pceNum++)
		{
			sq = pos->pList[wP][pceNum];
			ASSERT(SqOnBoard(sq));

			if(pos->pieces[sq + 10] == EMPTY)
			{
				AddWhitePawnMove(pos, sq, sq + 10, list);
				if(RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY)
					AddQuietMove(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
			}

			if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK)
				AddWhitePawnCapMove(pos, sq, sq + 9, pos->pieces[sq + 9], list);

			if(!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK)
				AddWhitePawnCapMove(pos, sq, sq + 11, pos->pieces[sq + 11], list);
		
			if(sq + 9 == pos->enPas)
				AddCaptureMove(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), list);

			if(sq + 11 == pos->enPas)
				AddCaptureMove(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), list);
		}
	}
	else
	{
		for(pceNum = 0; pceNum < pos->pceNum[bP]; pceNum++)
		{
			sq = pos->pList[bP][pceNum];
			ASSERT(SqOnBoard(sq));

			if(pos->pieces[sq - 10] == EMPTY)
			{
				AddBlackPawnMove(pos, sq, sq - 10, list);
				if(RanksBrd[sq] == RANK_2 && pos->pieces[sq - 20] == EMPTY)
					AddQuietMove(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
			}

			if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE)
				AddBlackPawnCapMove(pos, sq, sq - 9, pos->pieces[sq - 9], list);

			if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE)
				AddWhitePawnCapMove(pos, sq, sq - 11, pos->pieces[sq - 11], list);

			if(sq - 9 == pos->enPas)
				AddCaptureMove(pos, MOVE(sq, sq - 9, EMPTY, EMPTY, MFLAGEP), list);

			if(sq - 11 == pos->enPas)
				AddCaptureMove(pos, MOVE(sq, sq - 11, EMPTY, EMPTY, MFLAGEP), list);
		}

	}
	// Loop for slide pieces
	pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePce[pceIndex++];
    while(pce != 0)
    {
    	ASSERT(PieceValid(pce));
    	printf("slider pceIndex: %d pce: %d\n", pceIndex,pce);

    	pce = LoopSlidePce[pceIndex++];
    }

    // Loop for Non slide
    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePce[pceIndex++];
    while(pce != 0)
    {
    	ASSERT(PieceValid(pce));
    	printf("non slider pceIndex: %d pce: %d\n", pceIndex,pce);

    	for(pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++)
    	{
    		sq = pos->pList[pce][pceNum];
    		ASSERT(SqOnBoard(sq));
    		printf("Piece: %c on %s \n", PceChar[pce], PrSq(sq));

    		for(index = 0; index < NumDir[pce]; index++)
    		{
    			dir = PceDir[pce][index];
    			t_sq = sq + dir;

    			if(SQOFFBOARD(t_sq))
    				continue;
    			// black ^ 1 = white   white ^ 1 = black

    			if(pos->pieces[t_sq] != EMPTY)
    			{
    				if(PieceCol[pos->pieces[t_sq]] == side ^ 1)
    					printf("\tCapture on %s\n", PrSq(t_sq));

    				continue;
    			}
    			printf("\tNormal on %s\n", PrSq(t_sq));
    		}
    	}

    	pce = LoopNonSlidePce[pceIndex++];
    }
	
}