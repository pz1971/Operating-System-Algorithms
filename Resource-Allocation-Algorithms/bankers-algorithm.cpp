#include <bits/stdc++.h>
using   namespace  std ;
using LL  =  long long ;

void operator += (vector<int> &a, vector<int> &b)
{
    for(int i = 0; i < a.size(); i++)
        a[i] += b[i];
}

bool operator <= (vector<int> &a, vector<int> &b)
{
    for(int i = 0; i < a.size(); i++)
        if(a[i] > b[i])
            return false;
    return true;
}

int main()
{
    // ** input part **
    int n, m ;  // n = number of processes, m = number of resources
    cout << "Enter number of processes: " ;
    cin >> n ;
    cout << "Enter number of resources: " ;
    cin >> m ;

    vector<vector<int> > mx(n, vector<int>(m, 0));          // matrix of max resources
    vector<vector<int> > allocated(n, vector<int>(m, 0));   // matrix of allocated resources

    for(int i = 0 ; i < n ; i ++)
    {
        cout << "Process " << i + 1 << endl ;
        for(int j = 0 ; j < m ; j ++)
        {
            cout << "Maximum value for resource " << j + 1 << ": " ;
            cin >> mx[i][j] ;
        }
        for(int j = 0 ; j < m ; j ++)
        {
            cout << "Allocated from resource " << j + 1 << ": " ;
            cin >> allocated[i][j] ;
        }

        cout << endl ;
    }

    vector<int> total(m) ;  // total resources
    vector<int> available(m) ; // available resources
    for(int i = 0 ; i < m ; i ++)
    {
        cout << "Enter total value of resource " << i + 1 << ": " ;
        cin >> total[i] ;

        available[i] = total[i] ;
        for(int j = 0 ; j < n ; j++)
            available[i] -= allocated[j][i] ;
    }
    // ** end of input part **

    vector<vector<int> > need(n, vector<int>(m, 0));    // matrix of need resources
    for(int i = 0 ; i < n ; i ++)
    {
        for(int j = 0 ; j < m ; j ++)
        {
            need[i][j] = mx[i][j] - allocated[i][j] ;
        }
    }

    cout << "The Max matrix:" << endl ;
    for(int i = 0 ; i < m ; i++)
        cout << "\tR" << i+1 ;
    cout << endl ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "P" << i + 1 << ":" ;
        for(int j = 0 ; j < m ; j++)
            cout << "\t" << mx[i][j] ;
        cout << endl ;
    }
    cout << endl ;
    cout << "The allocated matrix:" << endl ;
    for(int i = 0 ; i < m ; i++)
        cout << "\tR" << i+1 ;
    cout << endl ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "P" << i + 1 << ":" ;
        for(int j = 0 ; j < m ; j++)
            cout << "\t" << allocated[i][j] ;
        cout << endl ;
    }
    cout << endl ;
    cout << "The need matrix:" << endl ;
    for(int i = 0 ; i < m ; i++)
        cout << "\tR" << i+1 ;
    cout << endl ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "P" << i + 1 << ":" ;
        for(int j = 0 ; j < m ; j++)
            cout << "\t" << need[i][j] ;
        cout << endl ;
    }
    cout << endl ;

    vector<vector<int> > available_vectors{ available } ;

    vector<bool> finished(n, false) ;
    auto &work = available ;

    vector<int> safe_sequence ;

    while(true)
    {
        int i ;
        for(i = 0 ; i < n ; i ++)
        {
            if(!finished[i] and need[i] <= work)
                break ;
        }
        if(i == n)
            break ;

        safe_sequence.push_back(i) ;
        work += allocated[i] ;
        finished[i] = true ;

        available_vectors.push_back(work) ;
    }

    cout << "Available vectors:" << endl ;
    for(int i = 0 ; i < m ; i++)
        cout << "\tR" << i + 1 ;
    cout << endl ;
    for(auto &i : available_vectors)
    {
        for(auto j : i)
            cout << "\t" << j ;
        cout << endl ;
    }
    cout << endl ;

    bool safe_system = true ;
    for(int i = 0 ; i < n ; i ++)
    {
        if(!finished[i])
        {
            safe_system = false ;
            break ;
        }
    }

    if(safe_system)
    {
        cout << "The System is currently in safe state and " ;
        cout << "< " ;
        for(auto i : safe_sequence)
            cout << "P" << i + 1 << " " ;
        cout << "> is the safe sequence." << endl ;
    }
    else 
    {
        cout << "The System is currently not in safe state." << endl ;
    }

    return 0;
}

// 4
// 3
// 3
// 2
// 2
// 1
// 0
// 0
// 6
// 1
// 3
// 5
// 1
// 1
// 3
// 1
// 4
// 2
// 1
// 1
// 4
// 2
// 2
// 0
// 0
// 2
// 9
// 3
// 6
