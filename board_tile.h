#ifndef BOARD_TILE_H
#define BOARD_TILE_H

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Color color;
    int value;

}board_tile_t;

void DrawBoard(SDL_Renderer* renderer, board_tile_t board[24][10]);
void InitBoard(board_tile_t board[24][10]);
void ScanBoard(board_tile_t board[24][10]);
void CascadeBoard(board_tile_t board[24][10], int line);

#endif // BOARD_TILE_H
