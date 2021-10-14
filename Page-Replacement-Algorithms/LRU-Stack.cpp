#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void LRU_stack(const int pages, const int frames, const vector<int> &ref)
{
    vector<deque<int> > table ;
    deque<int> stk(frames, -1) ;
    vector<bool> inStack(pages, false) ;

    for(auto i : ref)
    {
        if(inStack[i])
        {
            stk.erase(find(stk.begin(), stk.end(), i)) ;
            stk.push_front(i) ;
        }
        else
        {
            inStack[stk.back()] = false ;
            stk.pop_back() ;
            stk.push_front(i) ;
            inStack[i] = true ;
        }
        table.push_back(stk) ;
    }

    cout << endl ;
    for(int row = 0 ; row < frames ; row++)
    {
        for(int col = 0 ; col < table.size() ; col++)
        {
            if(table[col][row] == -1)
                cout << "    " ;
            else 
                cout << setw(4) << table[col][row] ;
        }
        cout << endl ;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << "Number of pages: " ;
    int pages ;
    cin >> pages ;

    cout << "Reference String: " ;
    string line ;
    cin.ignore() ;
    getline(cin, line) ;
    stringstream ss ;
    ss.clear() ;
    ss << line ;
    vector<int> ref ;
    int x ;
    while(ss >> x)
    {
        ref.push_back(x) ;
    }

    cout << "Number of Memory Page Frame: " ;
    int frames ;
    cin >> frames ;

    LRU_stack(pages, frames, ref) ;

    return 0;
}

// 8
// 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
// 3