// Problem statement : https://www.hackerrank.com/challenges/simple-text-editor/problem
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    string S = "";
    stack<string> operationQueue;
    int q;
    cin>>q;
    int option;
    while(q-->0){
        cin>>option;
        switch(option){
            case 1 : 
            {
                string temp;
                cin>>temp;
                S.append(temp);
                operationQueue.push(S);
                break;
            }
            case 2 : 
            {
                int k;
                cin>>k;
                for(int i=k;i>0;i--){
                    S.pop_back();
                }
                operationQueue.push(S);
                break;
            }
            case 3 : 
            {
                int k;
                cin>>k;
                if(k > (int)S.length() || S.empty())    
                    break;
                else
                    cout<<S[k-1]<<"\n";
                
                break;
            }
            case 4 :
            {
                operationQueue.pop();
                if(operationQueue.empty()){
                    S = "";
                }
                else{
                    S = operationQueue.top();
                }
                break;
            }
        }
    }
    return 0;
}
