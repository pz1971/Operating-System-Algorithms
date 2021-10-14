#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void FIFO (const int pages, const int frames, const vector<int> &ref)
{
    deque<int> dq ;
    vector<bool> inDeque (pages, false) ;
    int page_faults = 0 ;

    for(auto i : ref)
    {
        if(inDeque[i])
            continue ;

        page_faults++ ;
        dq.push_back(i) ;
        inDeque[i] = true ;

        if(dq.size() > frames)
        {
            inDeque[dq.front()] = false ;
            dq.pop_front() ;
        }
    }

    cout << "Number of page fault using FIFO Page replacement Algorithm: " << page_faults << endl ;
    cout << "Page Fault Rate: " << ((page_faults * 100.0) / ref.size()) << "%" << endl ;
}

void optimal (const int pages, const int frames, const vector<int> &ref)
{
    const int inf = INT_MAX ;
    deque<int> nextCalls[pages] ;
    for(int i = 0 ; i < ref.size() ; i++)
        nextCalls[ref[i]].push_back(i) ;
    for(int i = 0 ; i < pages ; i++)
        nextCalls[i].push_back(inf) ;
    
    int page_faults = 0 ;
    vector<int> vec ;
    vector<bool> inVec(pages, false) ;

    for(auto i : ref)
    {
        if(inVec[i])
        {
            nextCalls[i].pop_front() ;
            continue ;
        }
            
        page_faults++ ;
        if(vec.size() < frames)
        {
            vec.push_back(i) ;
            inVec[i] = true ;
            nextCalls[i].pop_front() ;
        }
        else 
        {
            int id = 0 ;
            for(int j = 1 ; j < vec.size() ; j++)
            {
                if(nextCalls[vec[j]].front() > nextCalls[vec[id]].front())
                    id = j ;
            }
            inVec[vec[id]] = false ;
            vec[id] = i ;
            inVec[i] = true ;
            nextCalls[i].pop_front() ;
        }
    }

    cout << "Number of page fault using Optimal Page replacement Algorithm: " << page_faults << endl ;
    cout << "Page Fault Rate: " << ((page_faults * 100.0) / ref.size()) << "%" << endl ;
}

void LRU (const int pages, const int frames, const vector<int> &ref)
{
    vector<int> prevCall(pages, -1) ;

    int page_faults = 0 ;
    vector<int> vec ;
    vector<bool> inVec(pages, false) ;

    int pos = -1 ;
    for(auto i : ref)
    {
        ++pos ;
        if(inVec[i])
        {
            prevCall[i] = pos ;
            continue ;
        }
            
        page_faults++ ;
        if(vec.size() < frames)
        {
            vec.push_back(i) ;
            inVec[i] = true ;
            prevCall[i] = pos ;
        }
        else 
        {
            int id = 0 ;
            for(int j = 1 ; j < vec.size() ; j++)
            {
                if(prevCall[vec[j]] < prevCall[vec[id]])
                    id = j ;
            }
            inVec[vec[id]] = false ;
            vec[id] = i ;
            inVec[i] = true ;
            prevCall[i] = pos ;
        }
    }

    cout << "Number of page fault using Least Recently Used Page replacement Algorithm: " << page_faults << endl ;
    cout << "Page Fault Rate: " << ((page_faults * 100.0) / ref.size()) << "%" << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << noshowpoint << setprecision(0) ;

    cout << "Number of Pages: " ;
    int pages ;
    cin >> pages ;
    cout << "Number of Page References: " ;
    int n ;
    cin >> n ;
    cout << "Reference String: " ;
    vector<int> ref(n) ;
    for(auto &i : ref)
        cin >> i ;
    cout << "Number of Memory Page Frame: " ;
    int frames ;
    cin >> frames ;

    FIFO(pages, frames, ref) ;
    optimal(pages, frames, ref) ;
    LRU(pages, frames, ref) ;

    return 0;
}

// 8
// 22
// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
// 3