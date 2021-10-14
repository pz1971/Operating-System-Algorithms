#include <bits/stdc++.h>
using   namespace  std ;

vector<vector<int> > adjacencyList ;
vector<vector<int> > deadlocks ;
vector<int> stk ; // using vector as a stack
vector<int> colors ;

// Detecting deadlocks in a graph using DFS
int DFS(int u)
{
    stk.push_back(u);
    colors[u] = 1 ;
    for(auto v : adjacencyList[u])
    {
        if(colors[v] == 0)
            DFS(v) ;
        else if(colors[v] == 1) // deadlock detected
        {
            deadlocks.push_back(vector<int> ()) ;
            int p = stk.size() - 1 ;

            deadlocks.back().push_back(v) ;
            while(p >= 0 and stk[p] != v)
                deadlocks.back().push_back( stk[p--] ) ;

            reverse(++deadlocks.back().begin(), deadlocks.back().end()) ;
        }
    }
    colors[u] = 2 ;
    stk.pop_back() ;
}

int main()
{
    
    // *** Input Part ***
    int numberOfNodes ;
    cout << "Number of nodes : " ;
    cin >> numberOfNodes ;
    vector<string> nodeNames(numberOfNodes) ;
    cout << "Node Names : " ;
    for(auto &i : nodeNames)
        cin >> i ;
    map<string, int> id ;
    for(int i = 0 ; i < numberOfNodes ; ++i)
        id[nodeNames[i]] = i ;

    adjacencyList.resize(numberOfNodes) ;
    colors = vector<int>(numberOfNodes, 0) ;

    string a, b, c ;

    int numberOfEdges ;
    cout << "Number of edges : " ;
    cin >> numberOfEdges ;
    cout << "Edges : " << endl ;
    for(int i = 0 ; i < numberOfEdges ; ++i)
    {
        cin >> a >> b >> c ; // a "to" c
        adjacencyList[id[a]].push_back(id[c]) ;
    }
    // *** End of Input Part ***

    for(int i = 0 ; i < numberOfNodes ; ++i)
    {
        // travarsing the Resourse Allocation Graph (RAG)
        if(colors[i] == 0)
            DFS(i) ;
    }

    // *** Output Part ***
    for(int i = 0 ; i < deadlocks.size() ; i++)
    {
        cout << i + 1 << " - Deadlock Detected Among nodes: " ;
        for(auto j : deadlocks[i])
            cout << nodeNames[j] << " " ;
        cout << endl ;
    }
    // *** End of Output Part ***

    return 0;
}

// ? Test Case 1
// 13
// R A C S D T B E F U V W G
// 13
// R to A
// A to S
// C to S
// F to S
// W to F
// D to S
// B to T
// D to T
// T to E
// E to V
// V to G
// G to U
// U to D
