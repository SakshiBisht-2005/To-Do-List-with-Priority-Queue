#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class Task {
public:
    string description;
    int priority;
    Task(string desc, int pri) : description(desc), priority(pri) {} 

    //For priority_queue:: higher priority number = higher priority
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

};  

priority_queue<Task>taskQueue;
list<Task>completedTasks;

const string TASKS_FILE = "tasks.txt";
const string COMPLETED_FILE = "completed.txt";

void addTask() {
    string desc;
    int pri;
    cout<<"Enter task dexcription: ";
    cin.ignore();
    getline(cin,desc);
    cout<<"Enter priority (higher = more important):";
    cin>>pri;
    taskQueue.push(Task(desc,pri));
    cout<<"Task.added.\n";
}

void viewTasks() {
    if(taskQueue.empty()) {
        cout<<"No pending tasks.\n";
        return;
    }
    cout<<"Pending Tasks:\n";
    priority_queue<Task> temp = taskQueue;
    int ind = 1;
    while(!temp.empty()) {
        Task t = temp.top();
        temp.pop();
        cout<<ind++<<".["<<t.priority<<"]"<<t.description<<endl;
    }
}

void saveTasks() {
    ofstream out(TASKS_FILE);
    while(!taskQueue.empty()) {
        Task t = taskQueue.top();
        out<< t.description<<"||"<<t.priority<<"\n";
        taskQueue.pop();
    }
    out.close();
}

void completeTask() {
    if(taskQueue.empty()) {
        cout<<"No tasks to complete."<<endl;
        return;
    }
    Task t = taskQueue.top();
    taskQueue.pop();
    completedTasks.push_back(t);
    cout<<"Completed::"<<t.description<<endl;
}

void viewCompleteTasks() {
    if(completedTasks.empty()) {
        cout<<"No completed tasks."<<endl;
        return;
    }
    cout<<"Completed Tasks:"<<endl;
    int idx = 1;
    for(const Task& t : completedTasks) {
        cout<<idx++<<".["<<t.priority<<"]"<<t.description<<endl;
    }
}

void saveCompleted() {
    ofstream out(COMPLETED_FILE);
    for (const Task& t : completedTasks) {
        if (!t.description.empty()) {
            out << t.description << "|" << t.priority << "\n";
        }
    }
    out.close();
}


void loadTasks() {
    ifstream in(TASKS_FILE) ;
    string line;
    while(getline(in, line)) {
        stringstream ss(line);
        string desc;
        int pri;
        getline(ss,desc,'|');
        ss>>pri;
        taskQueue.push(Task(desc,pri));
    }
    in.close();

    ifstream cfile(COMPLETED_FILE);
    while(getline(cfile,line)) {
        stringstream ss(line);
        string desc;
        int pri;
        getline(ss,desc,'|');
        ss>>pri;
        completedTasks.push_back(Task(desc,pri));
    }
    cfile.close();
}

void menu () {
    cout<<"\n ==== To-Do List ====\n";
    cout<<"1. Add Task\n";
    cout<<"2. View Pending Tasks\n";
    cout<<"3. Complete Top Priority Task\n";
    cout<<"4. View Complete Tasks\n";
    cout<<"5. Save and Exit\n";
    cout<<" ======================== \n";
    cout<<"Choose an option ::";
}

int main () {
    loadTasks();

    int choice;
    do {
        menu();
        cin>>choice;
        switch(choice) {
            case 1: addTask();break;
            case 2: viewTasks(); break;
            case 3: completeTask(); break;
            case 4: viewCompleteTasks(); break;
            case 5:
                saveTasks();
                saveCompleted();
                cout<<"Tasks Saved. Goodbye!! \n";
                break;
            default: cout<<"Invalid Option.\n";
        }
    }while(choice != 5);

    return 0;
}