// Problem statement : https://www.hackerrank.com/challenges/bitset-1/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long Long;
const unsigned int _2p31 = pow(2,31);
#define f(x) (x * p + q) % _2p31


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  

    unsigned int n, s, p, q, result=0;
    cin >> n >> s >> p >> q;
    
    unsigned cur = s % _2p31;
    unsigned prev = cur + 1;
    while ((cur != prev) && (result < n)) {
        result++;
        prev = cur;
        cur = f(cur);
    }

    cout << result;

    return 0;
}



