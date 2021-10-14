#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void print_steps(const vector<int> &memory_requests, const vector<vector<int> > &matrix)
{
    cout << "Memory Allocation Step by step" << endl ;
    cout << "\t" ;
    for(auto i : memory_requests)
        cout << i << "\t" ;
    cout << endl ;
    for(int row = 0 ; row < matrix[0].size() ; row++)
    {
        for(int col = 0 ; col <= memory_requests.size() ; col++)
        {
            if(col < matrix.size())
                cout << matrix[col][row] << "\t" ;
            else 
                cout << "X\t" ;
        }
        cout << endl ;
    }
}

void print_external_fragmentation(const int external_fragmentation)
{
    cout << "External Fragmentation = " << external_fragmentation << endl ;
}

void first_fit(vector<int> holes, vector<int> memory_requests)
{
    cout << "First Fit" << endl ;
    int external_fragmentation = 0 ;
    vector<vector<int> > matrix { holes } ;

    for(auto req : memory_requests)
    {
        int id ;
        for(id = 0 ; id < holes.size() ; id++)
        {
            if(holes[id] >= req)
                break ;
        }
        if(id == holes.size())
        {
            external_fragmentation = accumulate(holes.begin(), holes.end(), 0) ;
            break ;
        }
        holes[id] -= req ;
        matrix.push_back(holes) ;
    }

    print_steps(memory_requests, matrix);
    print_external_fragmentation(external_fragmentation) ;
    cout << endl ;
}

void best_fit(vector<int> holes, vector<int> memory_requests)
{
    cout << "Best Fit" << endl ;
    set<pair<int, int> > ordered_holes ;
    for(int i = 0 ; i < holes.size() ; i++)
        ordered_holes.insert(make_pair(holes[i], i)) ;
    int external_fragmentation = 0 ;
    vector<vector<int> > matrix { holes } ;

    for(auto req : memory_requests)
    {
        auto it = ordered_holes.lower_bound(make_pair(req, -1)) ;
        if(it == ordered_holes.end() or it -> first < req)
        {
            external_fragmentation = accumulate(holes.begin(), holes.end(), 0) ;
            break ;
        }
        auto p = *it ;
        ordered_holes.erase(it) ;
        p.first -= req ;
        ordered_holes.insert(p) ;
        holes[p.second] -= req ;
        matrix.push_back(holes) ;
    }
    
    print_steps(memory_requests, matrix);
    print_external_fragmentation(external_fragmentation) ;
    cout << endl ;
}

void worst_fit(vector<int> holes, vector<int> memory_requests)
{
    cout << "Worst Fit" << endl ;
    set<pair<int, int> > ordered_holes ;
    for(int i = 0 ; i < holes.size() ; i++)
        ordered_holes.insert(make_pair(holes[i], i)) ;
    int external_fragmentation = 0 ;
    vector<vector<int> > matrix { holes } ;

    for(auto req : memory_requests)
    {
        auto it = ordered_holes.rbegin() ;
        if(it -> first < req)
        {
            external_fragmentation = accumulate(holes.begin(), holes.end(), 0) ;
            break ;
        }
        auto p = *it ;
        ordered_holes.erase(p) ;
        p.first -= req ;
        ordered_holes.insert(p) ;
        holes[p.second] -= req ;
        matrix.push_back(holes) ;
    }
    
    print_steps(memory_requests, matrix);
    print_external_fragmentation(external_fragmentation) ;
    cout << endl ;
}

int main()
{
    string line ;
    stringstream ss ;

    cout << "Memory Holes : " ;
    getline(cin, line) ;
    ss.clear();
    ss << line ;
    vector<int> holes ;
    int hole ;
    while(ss >> hole)
    {
        holes.push_back(hole) ;
    }

    cout << "Memory Requests : " ;
    getline(cin, line) ;
    ss.clear();
    ss << line ;
    vector<int> memory_requests ;
    int memory_request ;
    while(ss >> memory_request)
    {
        memory_requests.push_back(memory_request) ;
    }

    first_fit (holes, memory_requests);
    best_fit  (holes, memory_requests);
    worst_fit (holes, memory_requests);

    return 0;
}

// 50 200 70 115 15
// 100 10 35 15 23 6 25 55 88 40