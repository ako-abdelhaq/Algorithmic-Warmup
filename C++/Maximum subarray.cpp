// Problem statement : https://www.hackerrank.com/challenges/maxsubarray/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the maxSubarray function below.
int maximum_subarray(vector<int> arr){
    int global_sum = -100000000;
    int cur_sum = global_sum;
    for(int i=0;i<arr.size();i++){
        cur_sum = max(cur_sum+arr[i],arr[i]);
        if(cur_sum>global_sum){
            global_sum = cur_sum;
        }
    }
    return global_sum;
}
int maximum_subsequence(vector<int> arr){
    int max_e = *max_element(arr.begin(),arr.end());
    int sum;
    max_e>0 ? sum = 0 : sum = max_e;
    int j = sum; 
    for(int i=0;i<arr.size();i++){
        arr[i]> j ? sum += arr[i] : sum += 0;
    }
    return sum;
}
vector<int> maxSubarray(vector<int> arr) {
    if(!arr.empty())
        return {maximum_subarray(arr),maximum_subsequence(arr)};
    else
        return {0};
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        vector<int> result = maxSubarray(arr);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

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
