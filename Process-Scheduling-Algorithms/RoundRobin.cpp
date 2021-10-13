/*
    Round Robin Algorithm
    Type: Preemptive
    Algo: Runs the process that arrives earlier. If the current process runs longer than Q (which is predefined),
          it removes the current process and insert it at the end of the queue and switches context to the next process.
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
    int Q = 3 ;
    cout << "Enter the Time Quantum: " ;
    cin >> Q ;
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
    vector<pair<int, int> > response_times(n) ; // ? response_times[i] = <flag, response time> 
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))
    deque<pair<int, int> > sorted_arrivals ; // ? sorted_arrivals[i] = <arrival_time, PID>
    for(int i = 0 ; i < n ; i++)
        sorted_arrivals.push_back(make_pair(arrival_times[i], i)) ;
    sort(sorted_arrivals.begin(), sorted_arrivals.end()) ;

    queue<int> ready_queue ;

    while(!ready_queue.empty() or !sorted_arrivals.empty())
    {
        if(ready_queue.empty() and !sorted_arrivals.empty())
        {
            ready_queue.push(sorted_arrivals[0].second) ;
            sorted_arrivals.pop_front() ;
        }
        
        int pid = ready_queue.front() ;
        ready_queue.pop() ;
        if(curr_time < arrival_times[pid])
            curr_time = arrival_times[pid] ;
        int execution_time = min(CPU_times[pid], Q) ;
        if(execution_time > 0)
        {
            waiting_times[pid] += curr_time - arrival_times[pid] ;
            turnaround_times[pid] += curr_time - arrival_times[pid] + execution_time ;
            if(response_times[pid].first == 0)
                response_times[pid] = make_pair(1, waiting_times[pid]) ;
            CPU_times[pid] -= execution_time ;
            gantt.push_back(make_pair(pid, make_pair(curr_time, curr_time + execution_time))) ;
            curr_time += execution_time ;
        }
        while(!sorted_arrivals.empty() and sorted_arrivals.front().first <= curr_time)
        {
            ready_queue.push(sorted_arrivals.front().second) ;
            sorted_arrivals.pop_front() ;
        }
        if(CPU_times[pid] > 0)
        {
            ready_queue.push(pid) ;
            arrival_times[pid] = curr_time ;
        }
    }

    int total_waiting_time = 0 ;
    for(auto &i : waiting_times)
        total_waiting_time += i ;
    int total_turnaround_time = 0 ;
    for(auto &i : turnaround_times)
        total_turnaround_time += i ;
    int total_response_time = 0 ;
    for(auto &i : response_times)
        total_response_time += i.second ;
    double average_waiting_time = (double) total_waiting_time / n ;
    double average_turnaround_time = (double) total_turnaround_time / n ;
    double average_response_time = (double) total_response_time / n ;

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
