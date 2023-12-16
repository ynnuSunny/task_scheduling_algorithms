/*
Algorithms steps:
 1. Take Task information like task_id, duration, dependecy_task
 2. Set Task Priority based on dependency
 3. Make task shedule based on priority and duration. [Task odering]

 4. Take Employee information like employee_id, start_working_hour, end_working_hour.
 5. Make a shedule maxtrix of size number_of_employee*24 [for shedule 24 hour task]
 6. Arrange employee based on employee task working hour.

 Sheduller Function
 7. for task in Task: 
        can_start = max(0,d_f) for d_f in task[dependecy]
        task_duration = task[duration]

        for emp in Employee:
            s_emp = emp.start_woring_hour;
            e_emp = emp.end_woring_hour;
            id_emp = emp.id
            for time in range s_emp to e_emp:
                 if(time>=can_start):
                       if(time+task_duration<=e_emp):
                           fill_the_shedule_matrix
                           update_employee_start_woring_hour_for_next_task
                           set_task_is_completed and break

             if task_is_completed then break


*/


#include <bits/stdc++.h>

 
using namespace std;

bool taskComparator(const std::pair<std::string, std::pair<int, int>>& a, const std::pair<std::string, std::pair<int, int>>& b) {
    // First, compare based on the first value of the pair in descending order
    if (a.second.first != b.second.first) {
        return a.second.first > b.second.first;
    }
    // If the first values are equal, then compare based on the second value in descending order
    return a.second.second > b.second.second;
}

vector<string> arrangeTasks(const vector<string>& tasks, const vector<vector<string>>& dependencies) {
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> inDegree;

    // Build the graph and calculate in-degrees
    for (const string& task : tasks) {
        graph[task] = vector<string>();
        inDegree[task] = 0;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        for (const string& dependent : dependencies[i]) {
            graph[dependent].push_back(tasks[i]);
            inDegree[tasks[i]]++;
        }
    }

    // Perform topological sort
    queue<string> q;
    for (const auto& entry : inDegree) {
        if (entry.second == 0) {
            q.push(entry.first);
        }
    }

    vector<string> result;
    while (!q.empty()) {
        string currentTask = q.front();
        q.pop();
        result.push_back(currentTask);

        for (const string& dependent : graph[currentTask]) {
            inDegree[dependent]--;
            if (inDegree[dependent] == 0) {
                q.push(dependent);
            }
        }
    }

    return result;
}

int main()
{
    
  
    map<string,pair<int,vector<string>>> task;
    map<string,int> task_priority,task_finish_time;
    vector<pair<string,pair<int,int>>> task_shedule;
    vector<string> tasks;
    vector<vector<string>> dependencies;
    for(int i=0;i<5;i++){
         string task_name;
         int duration;
         int num_depenecy_task;
         cin>>task_name>>duration>>num_depenecy_task;
          
         vector<string> dependency_tasks;
         for(int j=0;j<num_depenecy_task;j++){
             string dep;
             cin>>dep;

             dependency_tasks.push_back(dep);

         }
         dependencies.push_back(dependency_tasks);
         tasks.push_back(task_name);
         task[task_name] = {duration,dependency_tasks};
         task_priority[task_name] = 0;
         task_finish_time[task_name] = 0;
    }

    tasks = arrangeTasks(tasks, dependencies);;
    
    int number_of_employee = 4;
    char maxtrix[number_of_employee][25];
    for(int i=0;i<number_of_employee;i++){
        for(int j=1;j<25;j++){
            maxtrix[i][j] = '.';
        }
    }

    vector<pair<pair<int,int>,int>>employee;
    map<string,int> employee_map;
    
    for(int i=0;i<number_of_employee;i++){
        string emp_id;
        int emp_s;
        int emp_e;
        cin>>emp_id>>emp_s>>emp_e;
        for(int j=emp_s;j<=emp_e;j++){
            maxtrix[i][j] = '?';
        }
        
        employee.push_back({{emp_s,emp_e},i});
        employee_map[emp_id] = i;
    }
    sort(employee.begin(), employee.end());


    for(auto it: tasks){
          string task_name = it;
          int duration = task[task_name].first;
          int can_start = 0;
          // find start time based on dependecy.
          for(auto d:task[task_name].second){
               can_start = max(can_start,task_finish_time[d]);
          }

          int id = -1;
          int new_start_time = 0;
          int new_finish_time = 0;
          bool isAssign = false;
          sort(employee.begin(), employee.end());
          for(auto emp: employee){
              
              if(max(can_start,emp.first.first)+duration<=emp.first.second){
                  new_start_time = max(can_start,emp.first.first)+duration;
                  new_finish_time = emp.first.second;
                  id = emp.second;
                  task_finish_time[task_name] = new_start_time;
                  cout<<task_name<<" "<<task_finish_time[task_name]<<"emp :" <<id<<endl;
                  for(int s = max(can_start,emp.first.first);s<new_finish_time;s++){
                     maxtrix[id][s] = '#';
                  }
                  isAssign = true;
                  break;
              }
              
          }
          if(isAssign){
             employee[id].first.first = new_start_time+1;
          }
             
    }

    for(auto it:task_finish_time){
        cout<<it.first<<" "<<it.second<<endl;
    }

    cout<<"Matrix"<<endl;;
    for(int i=0;i<number_of_employee;i++){
        for(int j=1;j<25;j++){
            cout<<maxtrix[i][j];
        }
        cout<<endl;
    }

    
}
