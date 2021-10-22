#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void FCFS(const int number_of_heads, const vector<int> &requests, int pos)
{
    vector<int> order {pos} ;
    int total_movement = 0 ;
    for(auto i : requests)
    {
        order.push_back(i) ;
        total_movement += abs(i - pos) ;
        pos = i ;
    }

    cout << "Cylinder Serving Order: " ;
    for(int i = 0 ; i < order.size() ; i++)
    {
        cout << order[i] ;
        cout << (i + 1 == order.size() ? "\n" : " -> ") ;
    }
    cout << "Total Cylinder movement: " << total_movement << endl ;
}

int main()
{
    
    cout << "Number of heads: " ;
    int number_of_heads ;
    cin >> number_of_heads ;
    cin.ignore() ;

    string line ;
    stringstream ss ;
    cout << "Cylinder requests: " ;
    getline(cin, line) ;
    ss.clear() ;
    ss << line ;

    vector<int> requests ;
    int req ;
    while(ss >> req)
    {
        requests.push_back(req) ;
    }

    cout << "Current head position: " ;
    int pos ;
    cin >> pos ;

    cout << endl ;

    cout << "FCFS" << endl ;
    FCFS(number_of_heads, requests, pos) ;

    return 0;
}

// 200
// 98 183 37 122 14 124 65 67
// 53