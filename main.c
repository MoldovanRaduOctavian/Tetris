#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "piece.h"
#include "board_tile.h"

int m[][4] = { {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0}
};

void draw_grid(SDL_Renderer* renderer)
{
    int i, j;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0);
    for (i = 1; i <= 9; i++)
        SDL_RenderDrawLine(renderer, 30 * i, 0, 30 * i, 720);
    for (i = 1; i <= 23; i++)
        SDL_RenderDrawLine(renderer, 0, 30 * i, 300, 30 * i);

    //SDL_RenderPresent(renderer);

}

board_tile_t board[24][10];
int test[24][10];

void draw_piece(SDL_Renderer* renderer, int x, int y, int piece[][4])
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0, 0);
    SDL_Rect rect;
    for (int i=0; i < 3; i++)
        for (int j=0; j < 3; j++)
            if (piece[i][j])
            {
                rect.x = x + j * 30;
                rect.y = y + i * 30;
                rect.h = 30;
                rect.w = 30;

                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }
    //SDL_RenderPresent(renderer);
}

int main(int argc, char** argv)
{

    seed_mt(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    //board[1][1] = 0;
    SDL_Color color = {0xff, 0xf8, 0xff, 0};
    piece_t* piece = CreatePiece(rand() % 7 + 1, 90, 0, color);

    SDL_Color BoardColor = {0xff, 0, 0, 0};

    InitBoard(board);

    //piece->current_rotation++;
    //piece->current_rotation++;

    //printf("%d ", IntersectPiece(piece, board));
    printf("%d  %d %d", CheckBoundsPiece(piece), piece->shapes[piece->current_rotation][3][2], IntersectPiece(piece, board));

    int running = 1;

    int t1 = 0, t2 = 0;

    while(running)
    {
        SDL_Event e;

        piece->collapse_rate = NORMAL_COLLAPSE;

        while (SDL_PollEvent(&e))
         {
             if (e.type == SDL_QUIT)
                running = 0;

             else if (e.type == SDL_KEYDOWN)
                switch (e.key.keysym.sym)
             {
                 case SDLK_DOWN: piece->collapse_rate = ACCELERATED_COLLAPSE;break;
                 case SDLK_LEFT: MoveHorizontalPiece(piece, board, LEFT);break;
                 case SDLK_RIGHT: MoveHorizontalPiece(piece, board, RIGHT);break;
                 //case SDLK_UP: RotatePiece(piece);break;
             }

             else if (e.type == SDL_KEYUP)
                if (e.key.keysym.sym == SDLK_UP)
                    RotatePiece(piece, board);
         }

        //t2 = SDL_GetTicks();

        /*if (t2 - t1 > 500)
        {
            RotatePiece(piece);
            t1 = t2;
        }*/
        //if (!CheckBoundsPiece(piece))
        //RotatePiece(piece);
        //if (IntersectPiece(piece, board))
        if (!CollapsePiece(piece, board))
            {
                TranslatePiece(piece, board);
                ResetPiece(piece);
            }

        ScanBoard(board);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        //draw_grid(renderer);
        DrawBoard(renderer, board);
        DrawPiece(renderer, piece);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
