//Problem statement : https://www.hackerrank.com/challenges/two-pluses/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */
 
bool sort_by_size(const pair<pair<int,int>,int> point1 , const pair<pair<int,int>,int> point2 ){
    return point1.second > point2.second;
}

bool verify_plus(vector<string> grid , pair<pair<int,int>,int> point){
    pair<int,int> center = point.first;
    int size = point.second;
    for(int i = 0 ; i < size ; i++){
        if( center.first + i >= grid.size() ){
            return false;
        }
        if( center.first - i < 0 ){
            return false;
        }
        if( center.second + i >= grid[0].size() ){
            return false;
        }
        if( center.second - i < 0 ){
            return false;
        }
        if(grid[center.first][center.second + i] != 'G'){
            return false;
        }
        if(grid[center.first][center.second - i] != 'G'){
            return false;
        }
        if(grid[center.first + i][center.second] != 'G'){
            return false;
        }
        if(grid[center.first - i][center.second] != 'G'){
            return false;
        }
    }
    return true;
}

vector<pair<pair<int,int>,int>> get_pluses(vector<string> grid){
    vector<pair<pair<int,int>,int>> acceptable;
    pair<pair<int,int>,int> point;
    for(int i = 0 ; i < grid.size() ; i++){
        for(int j = 0 ; j < grid[i].size() ; j++){
            point.first.first = i;
            point.first.second = j;
            for(int s = 1 ; s < (min(i,(int)grid[i].size()-j) + 2) ; s++){
                point.second = s;
                if( verify_plus(grid, point) ){
                    acceptable.push_back(point);
                    //cout << "point " << point.first.first << " , " << point.first.second << "  -> size : " << point.second << endl; 
                }
            }
        }
    }
    sort(acceptable.begin(),acceptable.end(),sort_by_size);
    /*
    for( auto p : acceptable){
        cout << "point " << p.first.first << " , " << p.first.second << "  -> size : " << p.second << endl; 
    }
    */
    return acceptable;
}

bool verify_two_pluses(vector<string> grid , pair<pair<int,int>,int> point1 , pair<pair<int,int>,int> point2){
    vector<string> new_grid = grid;
    for(int i = 0 ; i < point1.second ; i++){
        new_grid[point1.first.first + i][point1.first.second] = 'B';
        new_grid[point1.first.first - i][point1.first.second] = 'B';
        new_grid[point1.first.first][point1.first.second + i] = 'B';
        new_grid[point1.first.first][point1.first.second - i] = 'B';
    }
    return verify_plus(new_grid , point2);
}

int twoPluses(vector<string> grid) {
    vector<pair<pair<int,int>,int>> acceptable = get_pluses(grid);
    int ans = 0;
    int surface1 = 0 , surface2 = 0;
    for(int i = 0 ; i < acceptable.size() ; i++){
        for(int j = 0 ; j < acceptable.size() ; j++){
            if( i != j && verify_two_pluses(grid , acceptable[i] , acceptable[j])){
                surface1 = 4*(acceptable[i].second - 1) + 1;
                surface2 = 4*(acceptable[j].second - 1) + 1;
                ans = max(ans , surface1*surface2);
            }
        }
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

    fout << result << "\n";

    fout.close();

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