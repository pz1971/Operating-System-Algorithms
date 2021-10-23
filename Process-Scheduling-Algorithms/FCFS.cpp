/*
    First Come First Serve (FCFS)
    Type: Non-Preemptive
    Algo: Runs the process that arrives earlier.
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

    vector<pair<int, int> > ready_queue ; // ? (arrival time, PID)
    for(int i = 0 ; i < n ; i++)
        ready_queue.push_back(make_pair(arrival_times[i], i)) ;
    sort(ready_queue.begin(), ready_queue.end()) ;

    for(auto i : ready_queue)
    {
        int PID = i.second ;
        if(curr_time < arrival_times[PID])
            curr_time = arrival_times[PID] ;
        waiting_times[PID] = curr_time - arrival_times[PID] ;
        turnaround_times[PID] = waiting_times[PID] + CPU_times[PID] ;
        gantt.push_back(make_pair(PID + 1, make_pair(curr_time, curr_time + CPU_times[PID]))) ;
        curr_time += CPU_times[PID] ;
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
