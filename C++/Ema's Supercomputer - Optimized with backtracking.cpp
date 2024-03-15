// Problem statement: https://www.hackerrank.com/challenges/two-pluses/problem
// This is an optimized O(n²*m²*min(n,m)) solution that uses dynamic programming to get pluses in O(n*m) and backtracking
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
        int m = get_size();
        return 4*m + 1;
    }
    
    int get_size(){
        return min(min(left,right),min(top,down));
    }
    
    bool operator < (point p1) {
        int m = get_max_area();
        int n = p1.get_max_area();
        return m > n;
    }
};

bool bad_cell(vector<string> grid , int i , int j , int x){
    if(grid[i + x][j] != 'G'){
        return true;
    }
    if(grid[i - x][j] != 'G'){
        return true;
    }
    if(grid[i][j + x] != 'G'){
        return true;
    }
    if(grid[i][j - x] != 'G'){
        return true;
    }
    return false;
}

pair<int,int> get_max_sizes( vector<string> grid , point p1 , point p2 ){
    int x = 0 , i1 = p1.i , j1 = p1.j , i2 = p2.i , j2 = p2.j ;
    int s1 = 0 , s2 = 0; 
    vector<string> new_grid = grid;
    while( x <= p1.get_size() ){
        if( i1+x < grid.size() && i1-x > -1 && j1+x < grid[0].size() && j1-x > -1 ){
            if( bad_cell(new_grid,i1,j1,x) ){
                s1 = x-1;
                break;
            }
            else {
                new_grid[i1 + x][j1] = 'B';
                new_grid[i1 - x][j1] = 'B';
                new_grid[i1][j1 + x] = 'B';
                new_grid[i1][j1 - x] = 'B';
            }
        }
        else {
            s1 = x-1;
            break;
        }
        
        if( i2+x < grid.size() && i2-x > -1 && j2+x < grid[0].size() && j2-x > -1 ){
            if( bad_cell(new_grid,i2,j2,x) ){
                s2 = x-1;
                break;
            }
            else {
                new_grid[i2 + x][j2] = 'B';
                new_grid[i2 - x][j2] = 'B';
                new_grid[i2][j2 + x] = 'B';
                new_grid[i2][j2 - x] = 'B';
            }
        }
        else {
            s2 = x-1;
            break;
        }
        x++;
        if( x > p1.get_size() ){
            s1 = p1.get_size();
            s2 = s1;
        }
    }
    
    while( x <= p2.get_size() ){
        if( i2+x < grid.size() && i2-x > -1 && j2+x < grid[0].size() && j2-x > -1 ){
            if( bad_cell(new_grid,i2,j2,x) ){
                s2 = x-1;
                break;
            }
            else {
                new_grid[i2 + x][j2] = 'B';
                new_grid[i2 - x][j2] = 'B';
                new_grid[i2][j2 + x] = 'B';
                new_grid[i2][j2 - x] = 'B';
            }
        }
        else {
            s2 = x-1;
            break;
        }
        x++;
        if( x > p2.get_size() ){
            s2 = p2.get_size();
        }
    }
    return {s1,s2};
}

int max_size(vector<string> grid , point p1 , point p2){
    point p;
    int s1 = 0 , s2 = 0;     
    if( p1.get_size() < p2.get_size() ){
        auto max_sizes = get_max_sizes(grid,p1,p2);
        s1 = max_sizes.first;
        s2 = max_sizes.second;
    }
    else{
        auto max_sizes = get_max_sizes(grid,p2,p1);
        s1 = max_sizes.first;
        s2 = max_sizes.second;
    }
    int a1 = 4*s1 + 1;
    int a2 = 4*s2 + 1;
    return a1*a2;
}

pair<vector<point> , vector<int>> get_acceptable_pluses(vector<vector<point>> pluses){
    vector<point> acceptable;
    int surface = 0;
    vector<int> surfaces;
    vector<int> permutations , distinct_permutations;
    int current_surface = 0;
    for(int i = 0 ; i < pluses.size() ; i++){
        for(int j = 0 ; j < pluses[i].size() ; j++){
            current_surface = pluses[i][j].get_max_area();
            if( current_surface > 0 ){
                acceptable.push_back(pluses[i][j]);
                int size = min(min(pluses[i][j].left, pluses[i][j].right),min(pluses[i][j].top, pluses[i][j].down)) + 1;
                for(int s = 0 ; s < size ; s++){
                    surfaces.push_back( 4*s + 1 );
                }
            }
        }
    }
    
    for(int i = 0 ; i < surfaces.size() ; i++){
        for(int j = i ; j < surfaces.size() ; j++){
            permutations.push_back(surfaces[i]*surfaces[j]);
        }
    }
    
    
    sort(permutations.begin(),permutations.end(),greater<int>());
    sort(acceptable.begin(),acceptable.end());
    
    int curr = 0;
    for(int i = 0 ; i < permutations.size() ; i++){
        if(permutations[i] != curr){
            distinct_permutations.push_back(permutations[i]);
            curr = permutations[i];
        }
    }
    
    return {acceptable , distinct_permutations};
}

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


int twoPluses(vector<string> grid) {
    auto pluses = find_pluses(grid);
    auto pluses_and_surfaces = get_acceptable_pluses(pluses);
    vector<point> acceptable_pluses = pluses_and_surfaces.first;
    vector<int> surfaces = pluses_and_surfaces.second;
    int s = 0;
    int product = 0;
    int current_product = 0;
    bool flag = true;
    
    while(s < surfaces.size() ){
        for(int i = 0 ; i < acceptable_pluses.size() ; i++){
            flag = true;
            for(int j = i+1 ; flag && ( j < acceptable_pluses.size() ) ; j++){
                product = max_size(grid,acceptable_pluses[i],acceptable_pluses[j]); 
                
                if(current_product < product){
                    current_product = product;
                }
                else{
                    if(product == acceptable_pluses[i].get_max_area()*acceptable_pluses[j].get_max_area() && current_product >= product){
                        // Backtrack 
                        flag = false;
                    }
                }
                
                if(product == surfaces[s]){
                    return product;
                }
                
            }   
        }
        s++;
    }
    
    return product;
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
