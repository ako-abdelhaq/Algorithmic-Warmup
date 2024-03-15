// Problem statement : https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the matrixRotation function below.
void matrixRotation(vector<vector<int>> matrix, int cycles_num) {
    int m = matrix.size();
    int n = matrix[0].size();

    for(int r = 0; r < (min(n,m)/2); r++){    
                
        int h = m - (2*r) ;
        int w = n - (2*r) ;

        int len = 0;

        if(h > 0)    len += (h * 2);
        
        if(w > 0)    len += (w * 2);

        if(h > 0 && w > 0)    len -= 4;

        int cycles = cycles_num % len;
                        
        while(cycles > 0){
            int next = 0;
            int prev = matrix[r + 1][n - r - 1];

            for(int x = n - r - 1; x >= r; x--){
                next = matrix[r][x];
                matrix[r][x] = prev;
                prev = next;
            }

            for(int y = r + 1; y < m - r; y++){
                next = matrix[y][r];
                matrix[y][r] = prev;
                prev = next;
            }

            for(int x = r + 1; x < n - r; x++){
                next = matrix[m - r - 1][x];
                matrix[m - r - 1][x] = prev;
                prev = next;
            }

            for(int y = m - r - 2; y >= r; y--){
                next = matrix[y][n - r - 1];
                matrix[y][n - r - 1] = prev;
                prev = next;
            }
            cycles--;
        }
    }

    for(int y = 0; y < m; y++){
        for(int x = 0; x < n; x++){
            cout << matrix[y][x] << " ";
        }
        cout << endl;
    }
}


int main()
{
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);

    int n = stoi(mnr[1]);

    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
