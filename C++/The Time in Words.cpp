// Problem statement : https://www.hackerrank.com/challenges/the-time-in-words/problem
#include <bits/stdc++.h>

using namespace std;

// Complete the timeInWords function below.
vector<string> numbers = {"zero", "one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty","twenty one","twenty two","twenty three","twenty four","twenty five","twenty six","twenty seven","twenty eight","twenty nine"
};
 
string timeInWords(int h, int m) {
    string time = "";
    if(m==0){
        time = numbers[h] + " ";
        time += "o' clock";
    }
    else if( m == 15 ){
        time = "quarter past " + numbers[h];
    }
    else if ( m == 30){
        time = "half past " + numbers[h];
    }
    else if( m == 45){
        time = "quarter to " + numbers[h+1];
    }
    else if( m < 30){
        if(m == 1){
            time = "one minute past " + numbers[h];
        }else {
            time = numbers[m] + " minutes past " + numbers[h];
        }
    }
    else {
        if(m == 59){
            time = "one minute to " + numbers[h+1];
        }else {
            time = numbers[60-m] + " minutes to " + numbers[h+1];
        }
    }
    return time;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int h;
    cin >> h;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string result = timeInWords(h, m);

    fout << result << "\n";

    fout.close();

    return 0;
}
