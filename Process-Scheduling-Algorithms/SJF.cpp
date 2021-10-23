/*
    Shortest Job First (SJF)
    Type: Non-Preemptive
    Algo: Runs the shortest available process. Here, response time is equivalent to the waiting time.
*/

#include <bits/stdc++.h>
using   namespace  std ;

void show_gantt(vector<pair<int, pair<int, int> > > gantt)
{
    int curr_time = 0 ;
    cout << "(0)" ;
    for(auto &pipii : gantt)
    {
        if(pipii.second.first > curr_time)
        {
            cout << "---<idle>---" << "(" << pipii.second.first << ")" ;
            curr_time = pipii.second.first ;
        }
        cout << "---" << "<p" << pipii.first + 1 << ">---(" << pipii.second.second << ")" ;
        curr_time = pipii.second.second ;
    }
    cout << endl ;
}

int main()
{
    
    // ** Input part
    int n ;
    cout << "Enter the number of process: " ;
    cin >> n ;
    
    vector<int> CPU_times(n), arrival_times(n) ;
    cout << "Enter the CPU times" << endl ;
    for(auto &i : CPU_times)
        cin >> i ;
    cout << "Enter the arrival times" << endl ;
    for(auto &i : arrival_times)
        cin >> i ;
    // ** ** ** **

    int curr_time = 0 ;
    vector<int> waiting_times(n), turnaround_times(n) ;
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    // ? Timestamp[i] contains the set of <cpu time, id> pairs that arrive at i-th time
    map<int, set<pair<int, int> > > timestamp ;
    for(int i = 0 ; i < n ; i++)
        timestamp[arrival_times[i]].insert(make_pair(CPU_times[i], i)) ;

    while(!timestamp.empty())
    {
        int curr_process = timestamp.begin()->second.begin()->second ;
        timestamp.begin()->second.erase(timestamp.begin()->second.begin()) ;
        if(timestamp.begin()->second.empty())
            timestamp.erase(timestamp.begin()) ;
        
        queue<int> ready_queue ;
        ready_queue.push(curr_process) ;

        while(!ready_queue.empty())
        {
            curr_process = ready_queue.front() ;
            ready_queue.pop() ;

            if(curr_time < arrival_times[curr_process])
                curr_time = arrival_times[curr_process] ;
            waiting_times[curr_process] = curr_time - arrival_times[curr_process] ;
            turnaround_times[curr_process] = waiting_times[curr_process] + CPU_times[curr_process] ;
            gantt.push_back(make_pair(curr_process + 1, make_pair(curr_time, curr_time + CPU_times[curr_process]))) ;
            curr_time += CPU_times[curr_process] ;

            vector<pair<int, int> > temp ;
            for(auto &i : timestamp)
            {
                if(i.first <= curr_time)
                {
                    for(auto &j : i.second)
                        temp.push_back(make_pair(CPU_times[j.second], j.second)) ;
                    i.second.clear() ;
                }
            }
            while(timestamp.begin() != timestamp.end() && timestamp.begin()->second.empty())
                timestamp.erase(timestamp.begin()) ;

            sort(temp.begin(), temp.end()) ;
            for(auto &j : temp)
                ready_queue.push(j.second) ;
        }
    }

    int total_waiting_time = 0 ;
    for(auto &i : waiting_times)
        total_waiting_time += i ;
    int total_turnaround_time = 0 ;
    for(auto &i : turnaround_times)
        total_turnaround_time += i ;
    double average_waiting_time = (double) total_waiting_time / n ;
    double average_turnaround_time = (double) total_turnaround_time / n ;

    // ** Output part
    cout << "Gantt-Chart:" << endl ;
    show_gantt(gantt) ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Process " << i + 1 << ": " ;
        cout << "Waiting/Response Time : " << waiting_times[i] << " Turnaround Time : " << turnaround_times[i] << endl ;
    }
    cout << "Average Waiting/Response Time : " << average_waiting_time << endl ;
    cout << "Average Turnaround Time : " << average_turnaround_time << endl ;
    // ** ** ** **

    return 0;
}
