/*
    Prioriy Scheduling (preemptive version)
    Algo: Runs the process that has the highest priority. If two processes have the same priority, they are executed in the order they arrived.
          If a process arrives with a higher priority than the current process, it preempts the current process.
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
    vector<pair<int, int> > response_times(n) ; // ? (flag, time)
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int, int> > > sorted_arrivals ; // ? (arrival time, PID)
    for(int i = 0 ; i < n ; i++)
        sorted_arrivals.push({arrival_times[i], i}) ;
    
    using pipii = pair<int, pair<int, int> > ;
    priority_queue<pipii, vector<pipii> , greater<pipii> > ready_queue ; // ? (priority value, (arrival time, PID))

    while(!sorted_arrivals.empty() or !ready_queue.empty())
    {
        if(ready_queue.empty())
        {
            ready_queue.push(make_pair(priority_values[sorted_arrivals.top().second], sorted_arrivals.top())) ;
            sorted_arrivals.pop() ;
        }

        int pid = ready_queue.top().second.second ;
        ready_queue.pop() ;
        if(curr_time < arrival_times[pid])
            curr_time = arrival_times[pid] ;

        int execution_time = CPU_times[pid] ;
        if(!sorted_arrivals.empty() and sorted_arrivals.top().first <= curr_time + execution_time and priority_values[sorted_arrivals.top().second] < ready_queue.top().first)
            execution_time -= (curr_time + execution_time - sorted_arrivals.top().first) ;
        
        if(execution_time > 0)
        {
            waiting_times[pid] += curr_time - arrival_times[pid] ;
            turnaround_times[pid] += curr_time - arrival_times[pid] + execution_time ;
            if(response_times[pid].first == 0)
                response_times[pid] = make_pair(1, waiting_times[pid]) ;
            gantt.push_back(make_pair(pid, make_pair(curr_time, curr_time + execution_time))) ;
            curr_time += execution_time ;
            CPU_times[pid] -= execution_time ;
        }

        while(!sorted_arrivals.empty() and sorted_arrivals.top().first <= curr_time)
        {
            ready_queue.push(make_pair(priority_values[sorted_arrivals.top().second], sorted_arrivals.top())) ;
            sorted_arrivals.pop() ;
        }

        if(CPU_times[pid] > 0)
        {
            arrival_times[pid] = curr_time ;
            ready_queue.push(make_pair(priority_values[pid], make_pair(arrival_times[pid], pid))) ;
        }
    }

    int total_response_time = 0 ;
    for(auto &i : response_times)
        total_response_time += i.second ;
    int total_waiting_time = 0 ;
    for(auto &i : waiting_times)
        total_waiting_time += i ;
    int total_turnaround_time = 0 ;
    for(auto &i : turnaround_times)
        total_turnaround_time += i ;
    double average_response_time = (double) total_response_time / n ;
    double average_waiting_time = (double) total_waiting_time / n ;
    double average_turnaround_time = (double) total_turnaround_time / n ;
    
    // ** Output part
    cout << "Gantt-Chart:" << endl ;
    show_gantt(gantt) ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Process " << i + 1 << ": " ;
        cout << "Response Time : " << response_times[i].second << " Waiting Time : " << waiting_times[i] << " Turnaround Time : " << turnaround_times[i] << endl ;
    }
    cout << "Average Response Time : " << average_response_time << endl ;
    cout << "Average Waiting Time : " << average_waiting_time << endl ;
    cout << "Average Turnaround Time : " << average_turnaround_time << endl ;
    // ** ** ** **

    return 0;
}
