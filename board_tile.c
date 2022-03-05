#include "board_tile.h"

void InitBoard(board_tile_t board[24][10])
{
    int i, j;
    SDL_Color color = {0, 0, 0, 0};
    for (i=0; i<24; i++)
        for (j=0; j<10; j++)
        {
            board[i][j].value = 0;
            board[i][j].color = color;
        }
}

void DrawBoard(SDL_Renderer* renderer, board_tile_t board[24][10])
{
    int i, j;

    SDL_Rect rect;
    for (i=0; i<24; i++)
        for (j=0; j<210; j++)
            if (board[i][j].value == 1)
            {
                rect.y = i * 30;
                rect.x = j * 30;
                rect.h = 30;
                rect.w = 30;

                SDL_SetRenderDrawColor(renderer, board[i][j].color.r, board[i][j].color.g, board[i][j].color.b, 0);
                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0);
    for (i = 1; i <= 9; i++)
        SDL_RenderDrawLine(renderer, 30 * i, 0, 30 * i, 720);
    for (i = 1; i <= 23; i++)
        SDL_RenderDrawLine(renderer, 0, 30 * i, 300, 30 * i);

}


void CascadeBoard(board_tile_t board[24][10], int line)
{
    int i, j;
    for (i=line; i>=1; i--)
        for (j=0; j<10; j++)
            {
                board[i][j].value = board[i-1][j].value;
                board[i][j].color = board[i-1][j].color;
            }
}

void ScanBoard(board_tile_t board[24][10])
{
    int i, j, ok = 1;
    for (i=0; i<24; i++)
    {
        ok = 1;
        for (j=0; j<10; j++)
            if (board[i][j].value == 0)
                ok = 0;

        if (ok)
            CascadeBoard(board, i);

    }

}
