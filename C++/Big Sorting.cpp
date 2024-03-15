// Problem statement : https://www.hackerrank.com/challenges/big-sorting/problem
#include <bits/stdc++.h>

using namespace std;

struct comp{
    bool operator()(string s1 , string s2){
        bool isTrue = false;
        if(s1.length()>s2.length()){
            return true;
        }
        else if (s2.length()>s1.length()) {
            return false;
        }
        else{
            for(int i = 0 ; i < s1.length() ; i++){
                if(s1[i]>s2[i]){
                    isTrue = true;
                    break;
                }
                else if(s2[i]>s1[i]){
                    isTrue = false;
                    break;
                }
                else {
                    continue;
                }
            }
            return isTrue;
        }
    }
};

// Complete the bigSorting function below.
vector<string> bigSorting(vector<string> unsorted) {
    priority_queue<string , vector<string> , comp> q;
    int i = 0 , n = unsorted.size();
    vector<string> v(n);
    for(string s : unsorted){
        q.push(s);
    }
    while(!q.empty() && i<n){
        v[i] = q.top();
        q.pop();
        i++;
    }
    v.shrink_to_fit();
    return v;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> unsorted(n);

    for (int i = 0; i < n; i++) {
        string unsorted_item;
        getline(cin, unsorted_item);

        unsorted[i] = unsorted_item;
    }

    vector<string> result = bigSorting(unsorted);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
