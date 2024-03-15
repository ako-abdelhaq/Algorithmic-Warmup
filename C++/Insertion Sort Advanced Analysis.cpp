// Problem statement : https://www.hackerrank.com/challenges/insertion-sort/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long merge(vector<int>& arr, int l, int r){
    int m = (l + r) / 2;
    vector<int> v(r - l + 1);
    int k = 0;
    int i = l;
    int j = m + 1;
    long count = 0;
    while(i <= m && j <= r) {
        if(arr[i] > arr[j]) {
            v[k] = arr[j];
            j++ ;
            count += m - i + 1;
        }
        else{
            v[k] = arr[i];
            i++;
        }
        k++;          
    }
    while(i <= m) {
        v[k] = arr[i];
        i++ ; k++;    
    }
    
    while(j <= r) {
        v[k] = arr[j];
        j++ ; k++;
    }

    k=0;

    for(int x=l ; x<=r ; x++){
        arr[x] = v[k];
        k++;
    }

    return count;
}

long mergeSort(vector<int>& arr, int l , int r){
    if(l >= r)
        return 0;
    int m = (l + r) / 2;
    long count = 0;
    count += mergeSort(arr, l , m); 
    count += mergeSort(arr, m + 1, r);
    count += merge(arr, l, r); 
    return count;
}



// Complete the insertionSort function below.
long insertionSort(vector<int>& arr) {
    return mergeSort(arr, 0, arr.size()-1);
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

        long result = insertionSort(arr);

        fout << result << "\n";
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
