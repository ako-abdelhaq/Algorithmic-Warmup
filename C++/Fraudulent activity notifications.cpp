// Problem statement : https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int median(vector<int> &freq,int d){
    int sum = 0 , n = freq.size();
    for(int i=0;i<n;++i){
        sum+=freq[i];
        if(2*sum>d) return (2*i);
        else if(2*sum==d){
            for(int j=i+1;i<n;++j){
                if(freq[j]) return (i+j);
            }
        }
    }
    return 0;
}

int activityNotifications(vector<int> expenditure, int d) {
    vector<int> frequencies(200,0);
    int n = expenditure.size() , count = 0;
    for(int i=0;i<d;++i){
        frequencies[expenditure[i]]++;
    }
    for(int i=d;i<n;++i){
        if(expenditure[i] >= median(frequencies,d)) count++;
        frequencies[expenditure[i]]++;
        frequencies[expenditure[i-d]]--;
    }
    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
