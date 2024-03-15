// Problem statement : https://www.hackerrank.com/challenges/weighted-uniform-string/problem
#include <bits/stdc++.h>

using namespace std;

// Complete the weightedUniformStrings function below.
vector<string> weightedUniformStrings(string s, vector<int> queries) {
    unordered_set<int> set;
    set.emplace(0);
    set.emplace(s[0]-'a'+1);
    int count=1;
    for(int i=1;i<s.length();i++)
        {
        if(s[i]!=s[i-1])
            count=1;
        else
            count++;
        set.emplace((s[i]-'a'+1)*count);
    }
    vector<string> v;
    for(int i = 0; i < queries.size(); i++){
        if(set.find(queries[i])!=set.end())
            v.push_back("Yes");
        else
            v.push_back("No");
    }
    return v;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<string> result = weightedUniformStrings(s, queries);

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
