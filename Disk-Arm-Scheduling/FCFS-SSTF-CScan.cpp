#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void FCFS(const int heads, const vector<int> &requests, int pos)
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

void SSTF(const int heads, const vector<int> &requests, int pos)
{
    // ?? Shortest Seek Time First
    // ?? Nearest request first
    vector<int> order {pos} ;
    int total_movement = 0 ;
    multiset<int> req(requests.begin(), requests.end()) ;

    while(!req.empty())
    {
        // ? get the immediate request to the left and to the right. Grant which is closer
        auto right = req.lower_bound(pos);
        if(right != req.begin())
        {
            auto left = right ;
            left-- ;
            if(right == req.end())  // No node in the right side
            {
                order.push_back(*left) ;
                total_movement += abs(*left - pos);
                pos = *left ;
                req.erase(left) ;
            }
            else 
            {
                if(abs(*left - pos) < abs(*right - pos))    // left node is closer
                {
                    order.push_back(*left) ;
                    total_movement += abs(*left - pos);
                    pos = *left ;
                    req.erase(left) ;
                }
                else        // right node is closer
                {
                    order.push_back(*right) ;
                    total_movement += abs(*right - pos);
                    pos = *right ;
                    req.erase(right) ;
                }
            }
        }
        else // no node in the right side
        {
            order.push_back(*right) ;
            total_movement += abs(*right - pos);
            pos = *right ;
            req.erase(right) ;
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

void C_Scan_right(const int heads, const vector<int> &requests, int pos)
{
    // ?? Requests are granted only towards the right
    vector<int> order {pos} ;
    int total_movement = 0 ;
    vector<int> req(requests.begin(), requests.end()) ;
    sort(req.begin(), req.end()) ;

    int ii = lower_bound(req.begin(), req.end(), pos) - req.begin() ;   // first request to start with
    for(int i = ii ; i < req.size() ; i++)
    {
        order.push_back(req[i]) ;
        total_movement += abs(pos - req[i]) ;
        pos = req[i] ;
    }
    if(0 < ii)
    {
        order.push_back(req[0]) ;
        total_movement += heads - pos + req[0] ;
        pos = req[0] ;
    }
    for(int i = 1 ; i < ii ; i++)
    {
        order.push_back(req[i]) ;
        total_movement += abs(pos - req[i]) ;
        pos = req[i] ;
    }

    cout << "Cylinder Serving Order: " ;
    for(int i = 0 ; i < order.size() ; i++)
    {
        cout << order[i] ;
        cout << (i + 1 == order.size() ? "\n" : " -> ") ;
    }
    cout << "Total Cylinder movement: " << total_movement << endl ;
}

void C_Scan_left(const int heads, const vector<int> &requests, int pos)
{
    // ?? Requests are granted only towards the left
    vector<int> order {pos} ;
    int total_movement = 0 ;
    vector<int> req(requests.begin(), requests.end()) ;
    sort(req.begin(), req.end()) ;

    int ii = upper_bound(req.begin(), req.end(), pos) - req.begin() ;   // ii - 1 is the first request to start with
    for(int i = ii - 1 ; i >= 0 ; i--)
    {
        order.push_back(req[i]) ;
        total_movement += abs(pos - req[i]) ;
        pos = req[i] ;
    }
    if(ii + 1 < req.size())
    {
        order.push_back(req.back()) ;
        total_movement += heads - pos + req.back() ;
        pos = req.back() ;
    }
    for(int i = req.size() - 2 ; i >= ii ; i--)
    {
        order.push_back(req[i]) ;
        total_movement += abs(pos - req[i]) ;
        pos = req[i] ;
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << "Number of heads: " ;
    int heads ;
    cin >> heads ;
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
    FCFS(heads, requests, pos) ;
    cout << "SSTF" << endl ;
    SSTF(heads, requests, pos) ;
    cout << "C-SCAN (right)" << endl ;
    C_Scan_right(heads, requests, pos) ;
    cout << "C-SCAN (left)" << endl ;
    C_Scan_left(heads, requests, pos) ;

    return 0;
}

// 200
// 98 183 37 122 14 124 65 67
// 53