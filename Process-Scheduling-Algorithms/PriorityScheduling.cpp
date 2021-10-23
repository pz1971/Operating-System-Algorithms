/*
    Prioriy Scheduling (Non-preemptive version)
    Algo: Runs the process that has the highest priority. If two processes have the same priority, they are executed in the order they arrived.
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
    
    vector<int> CPU_times(n), arrival_times(n), priority_values(n) ;
    cout << "Enter the CPU times" << endl ;
    for(auto &i : CPU_times)
        cin >> i ;
    cout << "Enter the arrival times" << endl ;
    for(auto &i : arrival_times)
        cin >> i ;
    cout << "Enter the priority values" << endl ;
    for(auto &i : priority_values)
        cin >> i ; // ** lower value has higher priority
    // ** ** ** **

    int curr_time = 0 ;
    vector<int> waiting_times(n), turnaround_times(n) ;
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    deque<pair<int, int> > sorted_arrivals ; // ? (arrival time, PID)
    for(int i = 0 ; i < n ; i++)
        sorted_arrivals.push_back({arrival_times[i], i}) ;
    sort(sorted_arrivals.begin(), sorted_arrivals.end()) ;
    
    using pipii = pair<int, pair<int, int> > ;
    priority_queue<pipii, vector<pipii> , greater<pipii> > ready_queue ; // ? (priority value, (arrival time, PID))

    while(!sorted_arrivals.empty() or !ready_queue.empty())
    {
        if(ready_queue.empty() and !sorted_arrivals.empty())
        {
            pair<int, int> arrival_time_pid = sorted_arrivals.front() ;
            sorted_arrivals.pop_front() ;
            ready_queue.push({priority_values[arrival_time_pid.second], arrival_time_pid}) ;
        }

        if(!ready_queue.empty())
        {
            int pid = ready_queue.top().second.second ;
            ready_queue.pop() ;
            if(curr_time < arrival_times[pid])
                curr_time = arrival_times[pid] ;
            waiting_times[pid] = curr_time - arrival_times[pid] ;
            turnaround_times[pid] = waiting_times[pid] + CPU_times[pid] ;
            gantt.push_back(make_pair(pid, make_pair(curr_time, curr_time + CPU_times[pid]))) ;
            curr_time += CPU_times[pid] ;

            while(!sorted_arrivals.empty() and sorted_arrivals.front().first <= curr_time)
            {
                ready_queue.push({priority_values[sorted_arrivals.front().second], sorted_arrivals.front()}) ;
                sorted_arrivals.pop_front() ;
            }
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
