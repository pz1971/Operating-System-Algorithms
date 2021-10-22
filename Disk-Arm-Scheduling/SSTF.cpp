#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void SSTF(const int number_of_heads, const vector<int> &requests, int pos)
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

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

    cout << "SSTF" << endl ;
    SSTF(number_of_heads, requests, pos) ;

    return 0;
}

// 200
// 98 183 37 122 14 124 65 67
// 53