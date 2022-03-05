#ifndef MT_H
#define MT_H

#define W 32
#define N 624
#define M 397
#define R 31
#define A 0x9908b0df
#define U 11
#define D 0xffffffff
#define SS 7
#define B 0x9d2c5680
#define TT 15
#define C 0xefc60000
#define LL 18
#define F 1812433253


void seed_mt(int seed);
int extract();
void twist();

#endif // MT_H
