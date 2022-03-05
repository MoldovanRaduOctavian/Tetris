#ifndef PIECE_H
#define PIECE_H

#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "board_tile.h"
#include "mt.h"

#define ACTIVE 1
#define PLACED 0

#define I 1
#define J 2
#define L 3
#define O 4
#define S 5
#define Z 6
#define T 7

#define NORMAL_COLLAPSE 300
#define ACCELERATED_COLLAPSE 50

#define LEFT -1
#define RIGHT 1

extern const int j_tet[4][4][4];
extern const int i_tet[4][4][4];
extern const int l_tet[4][4][4];
extern const int o_tet[4][4][4];
extern const int s_tet[4][4][4];
extern const int z_tet[4][4][4];
extern const int t_tet[4][4][4];

typedef struct
{
    SDL_Color color;
    int*** shapes;
    int current_rotation;
    int posx;
    int posy;
    int collapse_rate;

} piece_t;

piece_t* CreatePiece(int type, int posx, int posy, SDL_Color color);
void DrawPiece(SDL_Renderer* renderer, piece_t* piece);
int IntersectPiece(piece_t* piece, board_tile_t board[24][10]);
int*** GetTetromino(int type);
int CollapsePiece(piece_t* piece, board_tile_t board[24][10]);
void RotatePiece(piece_t* piece, board_tile_t board[24][10]);
int CheckBoundsPiece(piece_t* piece);
int CheckSideBoundsPiece(piece_t* piece);
int CheckBottomBoundsPiece(piece_t* piece);
void TranslatePiece(piece_t* piece, board_tile_t board[24][10]);
void ResetPiece(piece_t* piece);
void FastCollapsePiece(piece_t* piece);
void MoveHorizontalPiece(piece_t* piece, board_tile_t board[24][10], int direction);
void HandlePiece(piece_t* piece, board_tile_t board[24][10]);


#endif // PIECE_H
