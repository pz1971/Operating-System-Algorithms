#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

#define LEFT 0
#define RIGHT 1

void SCAN(const int number_of_heads, const vector<int> &requests, int pos, const int direction)
{
    vector<int> order {pos} ;
    int total_movement = 0 ;

    vector<int> req(requests.begin(), requests.end()) ;
    sort(req.begin(), req.end()) ;

    if(direction == LEFT)
    {
        int ii = upper_bound(req.begin(), req.end(), pos) - req.begin() ;
        for(int i = ii-1 ; i >= 0 ; i--)
        {
            order.push_back(req[i]) ;
            total_movement += abs(pos - req[i]) ;
            pos = req[i] ;
        }
        if(req[0] != 0)
        {
            order.push_back(0) ;
            total_movement += abs(pos) ;
            pos = 0 ;
        }
        for(int i = ii ; i < req.size() ; i++)
        {
            order.push_back(req[i]) ;
            total_movement += abs(pos - req[i]) ;
            pos = req[i] ;
        }
    }
    else
    {
        int ii = lower_bound(req.begin(), req.end(), pos) - req.begin() ;
        for(int i = ii ; i < req.size() ; i++)
        {
            order.push_back(req[i]) ;
            total_movement += abs(pos - req[i]) ;
            pos = req[i] ;
        }
        if(req.back() != number_of_heads - 1)
        {
            order.push_back(number_of_heads - 1) ;
            total_movement += abs(number_of_heads - 1 - pos) ;
            pos = number_of_heads - 1 ;
        }
        for(int i = ii - 1 ; i >= 0 ; i--)
        {
            order.push_back(req[i]) ;
            total_movement += abs(pos - req[i]) ;
            pos = req[i] ;
        }
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

    cout << "SCAN (initial direction is left):" << endl ;
    SCAN(number_of_heads, requests, pos, LEFT) ;
    cout << "SCAN (initial direction is right):" << endl ;
    SCAN(number_of_heads, requests, pos, RIGHT) ;

    return 0;
}
