#include "mt.h"
#include <stdlib.h>
#include <stdio.h>

int table[N];
int mt_index = N + 1;
const int lower_mask = (1 << R) - 1;
const int upper_mask = 0xffffffff & (~lower_mask);

void seed_mt(int seed)
{
    mt_index = N;
    table[0] = seed;

    for (int i=1; i<=N-1; i++)
        table[i] = 0xffffffff & (F * (table[i-1] ^ (table[i-1] >> (W-2))) + i);

}

void twist()
{
    int x, xa;
    for (int i=0; i<=N-1; i++)
    {
        x = (table[i] & upper_mask) + (table[(i+1) % N] & lower_mask);
        xa = x >> 1;

        if (x % 2 != 0)
            xa ^= A;

        table[i] = table[(i + M) % N] ^ xa;
    }

    mt_index = 0;
}

int extract()
{
    if (mt_index >= N)
    {
        if (mt_index > N)
            seed_mt(5489);
        twist();
    }

    int y = table[mt_index];
    y = y ^ ((y >> U) & D);
    y = y ^ ((y << SS) & B);
    y = y ^ ((y << TT) & C);
    y = y ^ (y >> 1);

    mt_index++;

    return 0xffffffff & y;
}
