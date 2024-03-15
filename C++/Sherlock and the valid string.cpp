// Problem statement : https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    map<char,int> characters_frequecy;
    for(auto character : s){
        if(characters_frequecy.find(character)!=characters_frequecy.end()){
            characters_frequecy[character]++;
        }else{
            characters_frequecy[character] = 1;
        }
    }
    bool utilized = false;
    int base_freq = characters_frequecy[s[0]];
    string isvalid = "YES";
    for(auto c : characters_frequecy){
        if( c.second==base_freq ){
            base_freq = c.second;
        }
        else if(c.second != base_freq && !utilized){
            utilized = true ;
            if((c.second>base_freq && c.second-1==base_freq)){
                c.second--;
                base_freq = c.second;
            }
            else if (c.second<base_freq && c.second==base_freq-1) {
                c.second++;
            }
            else if(c.second==1){
                continue;
            }
            else {
                isvalid = "NO";
                break;
            }
        } 
        else {
            isvalid = "NO";
            break;
        }
    }
    return isvalid;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
