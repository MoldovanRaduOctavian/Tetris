#include "piece.h"

const int j_tet[4][4][4] = {{{1, 0, 0, 0},{1, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 1, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0}},
                      {{0, 0, 0, 0},{1, 1, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{0, 1, 0, 0},{1, 1, 0, 0},{0, 0, 0, 0}}
};

const int i_tet[4][4][4] = {
    {{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0},{0, 0, 0, 0}},
    {{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0}},
    {{0, 0, 0, 0},{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0}},
    {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0}}
};

const int l_tet[4][4][4] = {{{0, 0, 1, 0},{1, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0}},
                      {{0, 0, 0, 0},{1, 1, 1, 0},{1, 0, 0, 0},{0, 0, 0, 0}},
                      {{1, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0}}
};

const int o_tet[4][4][4] = {{{0, 1, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
};

const int s_tet[4][4][4] = {{{0, 1, 1, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{0, 1, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}},
                      {{0, 0, 0, 0},{0, 1, 1, 0},{1, 1, 0, 0},{0, 0, 0, 0}},
                      {{1, 0, 0, 0},{1, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0}}
};

const int z_tet[4][4][4] = {{{1, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 0, 1, 0},{0, 1, 1, 0},{0, 1, 0, 0},{0, 0, 0, 0}},
                      {{0, 0, 0, 0},{1, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{1, 1, 0, 0},{1, 0, 0, 0},{0, 0, 0, 0}}
};

const int t_tet[4][4][4] = {{{0, 1, 0, 0},{1, 1, 1, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{0, 1, 1, 0},{0, 1, 0, 0},{0, 0, 0, 0}},
                      {{0, 0, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0},{0, 0, 0, 0}},
                      {{0, 1, 0, 0},{1, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0}}
};

piece_t* CreatePiece(int type, int posx, int posy, SDL_Color color)
{
    piece_t* p = (piece_t*)malloc(sizeof(piece_t));
    p->shapes = GetTetromino(type);

    p->posx = posx;
    p->posy = posy;
    p->color = color;
    p->current_rotation = 0;
    p->collapse_rate = NORMAL_COLLAPSE;

    return p;
}

void DrawPiece(SDL_Renderer* renderer, piece_t* piece)
{
    SDL_SetRenderDrawColor(renderer, piece->color.r, piece->color.g, piece->color.b, 0);
    SDL_Rect rect;
    for (int i=0; i < 4; i++)
        for (int j=0; j < 4; j++)
            if (piece->shapes[piece->current_rotation][i][j])
            {
                rect.x = piece->posx + j * 30;
                rect.y = piece->posy + i * 30;
                rect.h = 30;
                rect.w = 30;

                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }
}

int*** GetTetromino(int type)
{
   int x, y, z;
   int*** ret  = (int***)malloc(sizeof(int**) * 4);
   for (x=0; x<4; x++)
        ret[x] = (int**)malloc(sizeof(int*) * 4);
   for (x=0; x<4; x++)
        for (y=0; y<4; y++)
        ret[x][y] = (int*)malloc(sizeof(int) * 4);


   switch (type)
   {
        case I:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = i_tet[x][y][z];
            break;
        case J:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = j_tet[x][y][z];
            break;
        case L:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = l_tet[x][y][z];
            break;
        case O:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = o_tet[x][y][z];
            break;
        case S:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = s_tet[x][y][z];
            break;
        case Z:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = z_tet[x][y][z];
            break;

        case T:
            for (x=0; x<4; x++)
                for (y=0; y<4; y++)
                    for (z=0; z<4; z++)
                        ret[x][y][z] = t_tet[x][y][z];
            break;
   }

   return ret;
}

int IntersectPiece(piece_t* piece, board_tile_t board[24][10])
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
                if (piece->shapes[piece->current_rotation][i][j] == 1)
                    if (board[i + piece->posy/30][j + piece->posx/30].value == 1)
                        return 1;

    return 0;
}


int CollapsePiece(piece_t* piece, board_tile_t board[24][10])
{
    static int t1 = 0, t2 = 0;
    int ok = 0;
    piece_t aux = *piece;
    aux.posy += 30;


    t2 = SDL_GetTicks();
    if (!CheckBoundsPiece(&aux) && !IntersectPiece(&aux, board))
    {
        ok = 1;
        if (t2 - t1 > piece->collapse_rate)
        {
            piece->posy += 30;
            t1 = t2;
        }

    }

    return ok;
}

int CheckBoundsPiece(piece_t* piece)
{
    for (int i=0;  i<4; i++)
        for (int j=0; j<4; j++)
            if (piece->shapes[piece->current_rotation][i][j] == 1 &&
                ( piece->posx + j * 30 < 0 || piece->posx + (j+1) * 30 > 300 || piece->posy + (i + 1) * 30 > 720))
                    return 1;
    return 0;
}

int CheckBottomBoundsPiece(piece_t* piece)
{
    for (int i=0;  i<4; i++)
        for (int j=0; j<4; j++)
            if (piece->shapes[piece->current_rotation][i][j] == 1 && piece->posy + (i + 1) * 30 > 720)
                    return 1;
    return 0;
}

int CheckSideBoundsPiece(piece_t* piece)
{
    for (int i=0;  i<4; i++)
        for (int j=0; j<4; j++)
            if (piece->shapes[piece->current_rotation][i][j] == 1 &&
                ( piece->posx + j * 30 < 0 || piece->posx + (j+1) * 30 > 300 ))
                    return 1;
    return 0;
}

void RotatePiece(piece_t* piece, board_tile_t board[24][10])
{
    piece_t aux = *piece;
    aux.current_rotation = (aux.current_rotation + 1) % 4;

    if (!CheckSideBoundsPiece(&aux) && !IntersectPiece(&aux, board))
        piece->current_rotation = (piece->current_rotation + 1) % 4;
}

void TranslatePiece(piece_t* piece, board_tile_t board[24][10])
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (piece->shapes[piece->current_rotation][i][j] == 1)
            {
                board[i + piece->posy/30][j + piece->posx/30].value = 1;
                board[i + piece->posy/30][j + piece->posx/30].color = piece->color;
            }
}

// fix memory leak
void ResetPiece(piece_t* piece)
{
    int i, j;

    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
            free(piece->shapes[i][j]);

        free(piece->shapes[i]);
    }

    free(piece->shapes);

    piece->shapes = GetTetromino(1 + extract() % 7);
    piece->posx = 0;
    piece->posy = 0;

    SDL_Color color = {extract() % 0xff, extract() % 0xff, extract() % 0xff, 0};
    piece->color = color;
}


void FastCollapsePiece(piece_t* piece)
{
    piece->collapse_rate = ACCELERATED_COLLAPSE;
}


void MoveHorizontalPiece(piece_t* piece, board_tile_t board[24][10], int direction)
{
    piece_t aux = *piece;
    aux.posx += direction * 30;

    if (!CheckSideBoundsPiece(&aux) && !IntersectPiece(&aux, board))
        piece->posx += direction * 30;
}


void HandlePiece(piece_t* piece, board_tile_t board[24][10])
{
    return;
}
