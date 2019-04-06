#pragma once
#include <inttypes.h>

#define dsize(v) ((int)v.size())
#define dlast(v) (v[dsize(v) - 1])
#define dmax(a, b) (((a) > (b)) ? (a) : (b))
#define dmin(a, b) (((a) < (b)) ? (a) : (b))

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long int ull;