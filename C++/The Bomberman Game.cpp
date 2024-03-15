// Problem statement : https://www.hackerrank.com/challenges/bomber-man/problem
#include <bits/stdc++.h>
#include <map>

using namespace std;

vector<string> split_string(string);

// Complete the bomberMan function below.
vector<string> bomberMan(int n, vector<string> grid) {
    vector<string> set1=grid, set2, set3;
    for (int i=0;i<grid.size();i++){
        for (int j=0;j<grid[0].size();j++){
            set1[i][j]='O';
        }
    }
    set2=set3=set1;
    for (int i=0;i<grid.size();i++){
        for (int j=0;j<grid[0].size();j++){
            if (grid[i][j]=='O')
            {
                if (i>0)    set2[i-1][j]='.';
                if (i<grid.size()-1)    set2[i+1][j]='.';
                if (j>0)    set2[i][j-1]='.';
                if (j<grid[0].size()-1) set2[i][j+1]='.';
                set2[i][j]='.';
            }
        }
    }
    for (int i=0;i<grid.size();i++){
        for (int j=0;j<grid[0].size();j++){
            if (set2[i][j]=='O')
            {
                if (i>0)    set3[i-1][j]='.';
                if (i<set2.size()-1)    set3[i+1][j]='.';
                if (j>0)    set3[i][j-1]='.';
                if (j<set2[0].size()-1) set3[i][j+1]='.';
                set3[i][j]='.';
            }
        }
    }
    if(n==1) return grid;
    else if(n%2==0) return set1;
    else if(n%4==3) return set2;
    else  return set3;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string rcn_temp;
    getline(cin, rcn_temp);

    vector<string> rcn = split_string(rcn_temp);

    int r = stoi(rcn[0]);

    int c = stoi(rcn[1]);

    int n = stoi(rcn[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

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
