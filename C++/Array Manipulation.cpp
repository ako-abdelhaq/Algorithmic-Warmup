// Problem statement : https://www.hackerrank.com/challenges/crush/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

#include <algorithm>
using namespace std;


int main() {
    long n,m,a,b,k,i,max_element=0,x=0;

    cin>>n>>m;
    long *v = new long [n+1]();

    for(i=0;i<m;i++)
    {
        cin>>a>>b>>k;
        v[a] += k;
        if((b)<n) v[b+1] -= k;
    }

    for(i=1;i<=n;i++)
    {
       x=x+v[i];
       max_element = max(max_element,x);
    }

    cout<<max_element<<endl;
    return 0;
}
