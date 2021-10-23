/*
    Shortest Remaining Time Next(SRTN)
    Type: Preemptive
    Algo: Runs the shortest available process, if a new shorter process arrives, switch context to the new process.
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
    vector<pair<int, int> > response_times(n) ; // ? first value is flag, second is the response time
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    set<int> arrival_events(arrival_times.begin(), arrival_times.end()) ;

    // ? Timestamp[i] contains the set of process ids that arrive at i-th time
    map<int, vector<int> > timestamp ;
    for(int i = 0 ; i < n ; i++)
        timestamp[arrival_times[i]].push_back(i) ;
    
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> >  > ready_queue ;

    while(!arrival_events.empty())
    {
        curr_time = *arrival_events.begin() ;
        for(auto &i : timestamp[curr_time])
            ready_queue.push(make_pair(CPU_times[i], i)) ;
        timestamp.erase(curr_time) ;
        arrival_events.erase(curr_time) ;

        while(!ready_queue.empty())
        {
            int curr_proc = ready_queue.top().second ;
            ready_queue.pop() ;
            waiting_times[curr_proc] += curr_time - arrival_times[curr_proc] ;

            int execution_time = CPU_times[curr_proc] ;
            if(!arrival_events.empty() and curr_time + execution_time > *arrival_events.begin())
                execution_time -= curr_time + execution_time - *arrival_events.begin() ;


            if(execution_time > 0)
            {
                gantt.push_back(make_pair(curr_proc, make_pair(curr_time, curr_time + execution_time))) ;
                curr_time += execution_time ;
                CPU_times[curr_proc] -= execution_time ;
                if(response_times[curr_proc].first == 0)
                    response_times[curr_proc] = make_pair(1, waiting_times[curr_proc]) ;
            }

            turnaround_times[curr_proc] += execution_time ;
            arrival_times[curr_proc] = curr_time ;
            if(CPU_times[curr_proc] > 0)
            {
                timestamp[curr_time].push_back(curr_proc) ;
                arrival_events.insert(curr_time) ;
            }
        }
    }

    for(int i = 0 ; i < n ; i++)
        turnaround_times[i] += waiting_times[i] ;

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
