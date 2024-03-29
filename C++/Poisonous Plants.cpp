// Problem statement : https://www.hackerrank.com/challenges/poisonous-plants/problem
#include <bits/stdc++.h>
#include <stack>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p , int day) {
    int n = p.size();
    stack<int> s;
    vector<int> days(n, 0);
    int max_days = 0;
    for (auto i=0 ; i<n ; i++) {
        days[i] = 1;
        while (!s.empty() && p[i] <= p[s.top()]) {
            days[i] = max(days[i], days[s.top()] + 1);
            s.pop();
        }
        if (s.empty()) {
            days[i] = -1;
        }
        s.push(i);
        max_days = max(days[i], max_days);
    }
    return max_days;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p , 0);

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
