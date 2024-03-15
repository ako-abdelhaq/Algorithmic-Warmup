// Problem statement : https://www.hackerrank.com/challenges/two-characters/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// Complete the alternate function below.
bool verify_alternate(string& s){
    int n = s.length();
    if(n%2 == 0){
        bool isTrue = true;
        for(int i=0;i<n/2;i+=2){
            if(s[0]==s[n-2-i] && s[1]==s[n-1-i] && s[i]!=s[i+1] && s[i]==s[n-2-i] && s[i+1]==s[n-1-i]){
                continue;
            }else{
                isTrue = false;
                break;
            }
        }
        return isTrue;
    }
    else{
        bool isTrue = true;
        if(s[0] != s[n/2]){
            isTrue = false;
        }
        else{
            for(int i=0;i<n/2;i+=2){
                if(s[0]==s[n-1-i] && s[1]==s[n-2-i] && s[i]!=s[i+1] && s[i]==s[n-1-i] && s[i+1]==s[n-2-i]){
                    continue;
                }else{
                    isTrue = false;
                    break;
                }
            }
        }
        return isTrue;
    }
}

int alternate(string s) {
    
    set<char> character_set;
    for(char c : s){
        character_set.insert(c);
    }
    vector<char> characters;
    for(char c : character_set){
        characters.push_back(c);
    }
    int count = 0;
    vector<pair<char,char>> pairs;
    for(int i = 0;i<characters.size()-1;i++){
        for(int j=i+1;j<characters.size();j++){
            pairs.push_back({characters[i],characters[j]});
        }
    }
    string temp = "";
    for(auto& p : pairs){
        temp = "";
        for(int i=0;i<s.length();i++){
            if(s[i] == p.first || s[i]==p.second){
                temp += s[i];
            }
        }
        if(verify_alternate(temp) && temp.length()>count){
            count = max(count,(int)temp.length());
            cout<<temp<<endl;
        }
    }
    return count;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
