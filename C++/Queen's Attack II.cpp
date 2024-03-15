// Problem statement : https://www.hackerrank.com/challenges/queens-attack-2/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    int d10 = n - r_q;
    int d01 = n - c_q;
    int d_0 = r_q - 1;
    int d0_ = c_q - 1;
    int d11 = min(d10, d01);
    int d__ = min(d_0, d0_);
    int d1_ = min(d10, d0_);
    int d_1 = min(d_0, d01);
    for (auto obstacle : obstacles) {
        if (obstacle[0] == r_q) {
            if (obstacle[1] > c_q)
                d01 = min(d01, obstacle[1] - c_q - 1);
            else
                d0_ = min(d0_, c_q - obstacle[1] - 1);
        }
        else if (obstacle[1] == c_q) {
            if (obstacle[0] < r_q)
                d_0 = min(d_0, r_q - obstacle[0] - 1);
            else
                d10 = min(d10, obstacle[0] - r_q - 1);
        }
        else if (obstacle[0] - r_q == obstacle[1] - c_q) {
            if (obstacle[0] > r_q)
                d11 = min(d11, obstacle[0] - r_q - 1);
            else
                d__ = min(d__, r_q - obstacle[0] - 1);
        }
        else if (obstacle[0] - r_q == c_q - obstacle[1]) {
            if (obstacle[0] > r_q)
                d1_ = min(d1_, obstacle[0] - r_q - 1);
            else
                d_1 = min(d_1, r_q - obstacle[0] - 1);
        }
    }
    return d01 + d10 + d_0 + d0_ + d11 + d1_ + d_1 + d__;
}

int main(){

    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

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
