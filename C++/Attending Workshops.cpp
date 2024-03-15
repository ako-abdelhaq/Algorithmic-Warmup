// Problem statement : https://www.hackerrank.com/challenges/attending-workshops/problem
#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.

struct Workshop
{
    int start;
    int duration;
    int end;
};

struct Available_Workshops
{
    int N;
    vector<Workshop> v;
    Available_Workshops(int &n)
    {
        v = vector<Workshop>(n);
        N = n;
    }
};

bool compare(Workshop &w1, Workshop &w2)
{
    return w1.end < w2.end;
}




//Implement the functions initialize and CalculateMaxWorkshops

Available_Workshops *initialize(int start_time[], int duration[], int n) 
{
    Available_Workshops *list = new Available_Workshops(n);
    
    for(int i=0;i<n;i++)
    {
        list->v[i].start = start_time[i];
        list->v[i].duration = duration[i];
        list->v[i].end = start_time[i] + duration[i];
    }
    sort(list->v.begin(),list->v.end(),compare);
    return list;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) 
{
    int end_time=0;
    int count=0;
    
    for(int i=0;i<ptr->N; i++){
        if(ptr->v[i].start >= end_time)
        {
            count += 1;
            end_time = ptr->v[i].end;
            
        }
    }
    return count;
}



int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
