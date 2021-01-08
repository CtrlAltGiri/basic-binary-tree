#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <climits>
#include <ctime>
#include <bitset>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>

#define MAX_LIMIT 700    // defines the maximum number of products in a transaction.
#define NO_BITS 70
#define fileName "Chess/dem.csv"
#define INT_MAX_FINAL 9007199254740991

unsigned long int MemUsage = 0;

typedef struct node{
	std::bitset<NO_BITS> val;
	unsigned int qty;
	node *child, *right;
}*NODE;
