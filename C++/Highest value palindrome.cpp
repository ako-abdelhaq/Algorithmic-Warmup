// Problem statement : https://www.hackerrank.com/challenges/richie-rich/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the highestValuePalindrome function below.
string highestValuePalindrome(string s, int n, int& k) {

    vector<bool> changes(n,false);  
    string str(s); 
    for(int i=0;i<n/2;i++){
        if(str[i]!=str[n-i-1]){
            changes[i]=true;
            k--;
        }
        if(str[i]<str[n-i-1]){
            str[i] = str[n-i-1];
        }
        else if(str[i]>str[n-i-1]){
            str[n-i-1] = str[i];
        }
        if(k < 0)     return "-1";       
    }

    int i=0;
    while (k > 0 && i < n/2){
        if (str[i]!='9'){
            if (changes[i]) k++;
            if (k > 1) {
                str[i]='9';
                str[n-i-1]='9'; 
                k-=2;
            }
        }       
        i++;        
    }

    if (n%2 == 1 && k > 0){
        str[n/2]='9';
    } 

    return  str;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
