// Problem statement: https://www.hackerrank.com/challenges/two-pluses/problem
// This is an optimized O(n²*m²*min(n,m)²) solution that uses dynamic programming to get pluses in O(n*m) 
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

struct point{
    int i;
    int j;
    int center;
    int top;
    int down;
    int left;
    int right;
    
    point(){
        i = -1;
        j = -1;
        center = 0;
        top = 0;
        down = 0;
        left = 0;
        right = 0;
    }
    
    int get_max_area(){
        if( center == 0 ){
            return 0;
        }
        int m = min(min(left,right),min(top,down));
        return 4*m + 1;
    }
};


vector<vector<point>> find_pluses(vector<string> grid){
    int n = grid.size() , m = grid[0].size();
    vector<vector<point>> pluses( n , vector<point>(m) );
    
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            pluses[i][j].i = i;
            pluses[i][j].j = j;
            if( grid[i][j] == 'G' ){
                pluses[i][j].center = 1;
                if( i > 0 && grid[i-1][j] == 'G'){
                    pluses[i][j].top = pluses[i-1][j].top + 1;
                }
                if( j > 0 && grid[i][j-1] == 'G'){
                    pluses[i][j].left = pluses[i][j-1].left + 1;
                }
            }
            if( grid[n-1 - i][m-1 - j] == 'G'){
                pluses[n-1 - i][m-1 - j].center = 1;
                if( n-1 - i > 0 && grid[ n-1 - i - 1 ][m-1 - j] == 'G'){
                    pluses[n-1 - i-1][m-1 - j].down = pluses[n-1 - i][m-1 - j].down + 1;
                }
                if (m-1 - j > 0 && grid[n-1 - i][ m-1 - j - 1 ] == 'G') {
                    pluses[n-1-i][m-1 - j-1].right = pluses[n-1 - i][m-1 - j].right + 1;
                }
            }
            
        }
    }
    return pluses;
}

vector<point> get_acceptable_pluses(vector<vector<point>> pluses){
    vector<point> acceptable;
    int surface = 0;
    int current_surface = 0;
    
    for(int i = 0 ; i < pluses.size() ; i++){
        for(int j = 0 ; j < pluses[i].size() ; j++){
            current_surface = pluses[i][j].get_max_area();
            if( current_surface > 0 ){
                point p = pluses[i][j];
                int size = min(min(p.left,p.right),min(p.top,p.down)) + 1;
                for(int s = 0 ; s < size ; s++){
                    p.left = s;
                    p.right = s;
                    p.top = s;
                    p.down = s;
                    acceptable.push_back(p);
                }
            }
        }
    }
    return acceptable;
}

bool verify_plus(vector<string> grid , point p){
    int size = min(min(p.left,p.right),min(p.top,p.down)) + 1;
    for(int i = 0 ; i < size ; i++){
        if( p.i + i >= grid.size() ){
            return false;
        }
        if( p.i - i < 0 ){
            return false;
        }
        if( p.j + i >= grid[0].size() ){
            return false;
        }
        if( p.j - i < 0 ){
            return false;
        }
        if(grid[p.i][p.j + i] != 'G'){
            return false;
        }
        if(grid[p.i][p.j - i] != 'G'){
            return false;
        }
        if(grid[p.i + i][p.j] != 'G'){
            return false;
        }
        if(grid[p.i - i][p.j] != 'G'){
            return false;
        }
    }
    return true;
}

bool no_overlap(vector<string> grid , point p1 , point p2){
    vector<string> new_grid = grid;
    int size = min(min(p1.left,p1.right),min(p1.top,p1.down)) + 1;
    
    for(int i = 0 ; i < size ; i++){
        new_grid[p1.i + i][p1.j] = 'B';
        new_grid[p1.i - i][p1.j] = 'B';
        new_grid[p1.i][p1.j + i] = 'B';
        new_grid[p1.i][p1.j - i] = 'B';
    }
    return verify_plus(new_grid , p2);
}

int twoPluses(vector<string> grid) {
    auto pluses = find_pluses(grid);
    vector<point> acceptable_pluses = get_acceptable_pluses(pluses);
    int s = 0;
    int product = 0;
    int max_product = 0;
    
    for(int i = 0 ; i < acceptable_pluses.size() ; i++){
        for(int j = i + 1 ; j < acceptable_pluses.size() ; j++){
        
            if( i != j && no_overlap(grid , acceptable_pluses[i] , acceptable_pluses[j])){
                product = acceptable_pluses[i].get_max_area() * acceptable_pluses[j].get_max_area();
                max_product = max(max_product , product);
            }
            
        }
        
    }
    
    return max_product;
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