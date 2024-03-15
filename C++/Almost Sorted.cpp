// Problem statement : https://www.hackerrank.com/challenges/almost-sorted/problem
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the almostSorted function below.
void almostSorted(vector<int> arr) {
    vector<int> arr_sorted = arr;
    sort(arr_sorted.begin(),arr_sorted.end());
    int i=0 , j ;
    vector<int> elementToSwap ;
    vector<pair<int,int>> elementToReverse;
    int elementToswap = 0;
    for(i=0;i<arr.size();i++){
        if(arr[i]!=arr_sorted[i]){
            elementToswap++;
            elementToSwap.push_back(i+1);
        }
        if(i<arr.size()-1 && arr[i]>=arr[i+1] && elementToReverse.empty()){
            auto p = make_pair(i,i+1);
            elementToReverse.push_back(p);
        }
        if(i<arr.size()-1 && arr[i]>=arr[i+1] && elementToReverse[0].second+1==i+1){
            elementToReverse[0].second++;
        }
    }
    if(elementToswap == 2) {
        cout<<"yes "<<endl;
        cout<<"swap "<<elementToSwap[0]<<" "<<elementToSwap[1]<<endl;
    }
    else {
        i = elementToReverse[0].first;
        j = elementToReverse[0].second;
        bool isequal = true;
        int x = j;
        int s = 0;
        //verify reverse part :
        for(int c=i ; c<=j ; c++){
            if(arr[c]==arr_sorted[x]){
                int temp = arr[c];
                arr[c] = arr[j-s];
                arr[j-s] = temp;
            }
            s++;
            x--;
        }
        for(int e=0 ;e<arr_sorted.size();e++){
            if(arr[e]!=arr_sorted[e]){
                isequal = false;
                break;
            }
            else {
                continue;
            }
        }
        if(isequal){
            i = elementToReverse[0].first;
            j = elementToReverse[0].second;
            i++;j++;
            cout<<"yes "<<endl;
            cout<<"reverse "<<i<<" "<<j<<endl;
        }else {
            cout<<"no"<<endl;
        }
    }
}

int main()
{
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

    almostSorted(arr);

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
