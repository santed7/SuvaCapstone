/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vernon/Documents/IoT/SuvaCapstone/DirectLinePM/src/DirectLinePM.ino"
/*
 * Project DirectLinePM
 * Description:
 * Author:
 * Date:
 */

#include <iostream>
#include <string>
#include <vector>

int main();
#line 12 "c:/Users/Vernon/Documents/IoT/SuvaCapstone/DirectLinePM/src/DirectLinePM.ino"
using namespace std;

// define a task structure
struct Task {
    string name;
    string description;
    string status;
};

// define a project structure
struct Project {
    string name;
    string description;
    vector<Task> tasks;
};

// function to create a new project
void createProject(vector<Project>& projects) {
    Project newProject;
    cout << "Enter project name: ";
    cin >> newProject.name;
    cout << "Enter project description: ";
    cin >> newProject.description;
    projects.push_back(newProject);
    cout << "Project created successfully!" << endl;
}

// function to add a task to a project
void addTask(vector<Project>& projects) {
    string projectName;
    cout << "Enter project name: ";
    cin >> projectName;
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            Task newTask;
            cout << "Enter task name: ";
            cin >> newTask.name;
            cout << "Enter task description: ";
            cin >> newTask.description;
            newTask.status = "In progress";
            projects[i].tasks.push_back(newTask);
            cout << "Task added successfully!" << endl;
            return;
        }
    }
    cout << "Project not found!" << endl;
}

// function to update task status
void updateTaskStatus(vector<Project>& projects) {
    string projectName, taskName, newStatus;
    cout << "Enter project name: ";
    cin >> projectName;
    cout << "Enter task name: ";
    cin >> taskName;
    cout << "Enter new task status: ";
    cin >> newStatus;
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            for (int j = 0; j < projects[i].tasks.size(); j++) {
                if (projects[i].tasks[j].name == taskName) {
                    projects[i].tasks[j].status = newStatus;
                    cout << "Task status updated successfully!" << endl;
                    return;
                }
            }
            cout << "Task not found!" << endl;
            return;
        }
    }
    cout << "Project not found!" << endl;
}

// function to display project details
void displayProjectDetails(vector<Project>& projects) {
    string projectName;
    cout << "Enter project name: ";
    cin >> projectName;
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            cout << "Project Name: " << projects[i].name << endl;
            cout << "Project Description: " << projects[i].description << endl;
            cout << "Tasks:" << endl;
            for (int j = 0; j < projects[i].tasks.size(); j++) {
                cout << "- " << projects[i].tasks[j].name << " (" << projects[i].tasks[j].status << ")" << endl;
            }
            return;
        }
    }
    cout << "Project not found!" << endl;
}

int main() {
    vector<Project> projects;
    int choice;
    do {
        cout << "Select an option:" << endl;
        cout << "1. Create a new project" << endl;
        cout << "2. Add a task to a project" << endl;
        cout << "3. Update task status" << endl;
        cout << "4. Display project details" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
      switch(choice) {
            case 1:
            createProject(projects);
            break;
            case 2:
            addTask(projects);
            break;
            case 3:
            updateTaskStatus(projects);
            break;
            case 4:
            displayProjectDetails(projects);
            break;
            case 5:
            cout << "Goodbye!" << endl;
            break;
            default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 5);
    return 0;
}
