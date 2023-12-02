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

 

int main()
{
    
  
    map<string,pair<int,vector<string>>> task;
    map<string,int> task_priority,task_finish_time;
    vector<pair<string,pair<int,int>>> task_shedule;
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
         task[task_name] = {duration,dependency_tasks};
         task_priority[task_name] = 0;
         task_finish_time[task_name] = 0;
    }
    
    // Step 2 find task_priority
    for(auto it:task){
         string task_name = it.first;
         // cout<<task_name<<endl;
         for(auto sub:it.second.second){
             task_priority[sub]++;
         }
    }

    // Step 3 make scheduled task
    for (auto it : task_priority) {
        string task_name = it.first;
        int priority = it.second; 
        int duration = task[task_name].first;
        task_shedule.push_back({task_name,{priority,duration}});
    }
    sort(task_shedule.begin(), task_shedule.end(), taskComparator);
    for(auto it:task_shedule){
        cout<<it.first<<" "<<it.second.first<<" "<<it.second.second<<endl;
    }

    // Empolyee section
    vector<pair<int,pair<int,int>> employee;
    map<int,string> employee_map;
    int number_of_employee = 4;
    for(int i=0;i<number_of_employee;i++){
        string emp_id;
        int emp_s;
        int emp_e;
        cin>>emp_id>>emp_s>>emp_e;
        employee.push_back({emp_s,{emp_e,i}});
        employee_map[i] = emp_id;
    }
    // arrange emplyee based on star working hour
    sort(employee.begin(),employee.end());

    for(auto it:employee){
      cout<<it.first<<" "<<it.second.first<<endl;
    }
    
    // intialize emplyee matrix
    int maxtrix[number_of_employee][25];

    for(auto it: task_shedule){
          string task_name = it.first;
          int duration = it.second.second;
          int can_start = 0;
          for(auto d:task[task_name].second){
               if(task_finish_time[d]>can_start){
                  can_start = task_finish_time[d];
               }
          }

          for(auto emp:employee){
               int emp_s = emp.first;
               int emp_e = emp.second.first;
               int emp_id = emp.second.second;
               // assign task
          }

    }

    
}
