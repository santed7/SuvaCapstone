/*
 * Project DrCoxQuickPM
 * Description: This is a quick and simple project management program
 * Author:CHAT GPT...modified by DrVernonCox 
 * Date:5May23
 */

/*This program is a simple project management system that allows users to create projects, 
add tasks to projects, update task statuses, and display project details.
The program uses a vector of Project structs to store information about each project, including the project name, 
description, and a vector of Task structs that represent each task associated with the project. Each Task struct contains a name, 
description, and status (which is initialized to "In progress" when a new task is created).
The program provides a simple command-line interface that allows users to select from a set of options using a switch statement. 
The createProject() function allows users to create a new project by entering a name and description, 
which are then added to the projects vector. The addTask() function allows users to add a new task to an 
existing project by entering the project name, task name, and task description. The updateTaskStatus() function 
allows users to update the status of a task by entering the project name, task name, and new status. 
The displayProjectDetails() function allows users to display information about a project, including the project name, description, 
and a list of tasks with their current status.
The main function uses a do-while loop to repeatedly display the available options and prompt the user for input 
until the user chooses to exit the program. The user's input is used to determine which function to call using the switch statement.
*Overall, this program provides a simple, command-line based project management system that could be 
used by individuals or small teams to track project tasks and statuses. However, it could be extended to include additional 
features such as due dates for tasks, user assignments, and task priorities.
*/

#include <iostream>
#include <string>
#include <vector>
class Task {
public:
    std::string name;
    std::string status;
};

class Project {
public:
    std::string name;
    std::string description;
    std::vector<Task> tasks;
};

void createProject(std::vector<Project>& projects);
void addTask(std::vector<Project>& projects);
void updateTaskStatus(std::vector<Project>& projects);

// define a task structure
struct Task {
    std::string name;
    std::string description;
    std::string status;
};

// define a project structure
struct Project {
    std::string name;
    std::string description;
    std::vector<Task> tasks;
};
void setup() {
    Serial.begin(9600);
}


// function to create a new project
void createProject(std::vector<Project>& projects) {
    Project newProject;
    Serial.println("Enter project name: ");
    while (!Serial.available()) { }
    newProject.name = Serial.readStringUntil('\n');
    Serial.println("Enter project description: ");
    while (!Serial.available()) { }
    newProject.description = Serial.readStringUntil('\n');
    projects.push_back(newProject);
    Serial.println("Project created successfully!");
}

// function to add a task to a project
void addTask(std::vector<Project>& projects) {
    std::string projectName;
    Serial.println("Enter project name: ");
    while (!Serial.available()) { }
    projectName = Serial.readStringUntil('\n');
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            Task newTask;
            Serial.println("Enter task name: ");
            while (!Serial.available()) { }
            newTask.name = Serial.readStringUntil('\n');
            Serial.println("Enter task description: ");
            while (!Serial.available()) { }
            newTask.description = Serial.readStringUntil('\n');
            newTask.status = "In progress";
            projects[i].tasks.push_back(newTask);
            Serial.println("Task added successfully!");
            return;
        }
    }
    Serial.println("Project not found!");
}

// function to update task status
void updateTaskStatus(std::vector<Project>& projects) {
    std::string projectName, taskName, newStatus;
    Serial.println("Enter project name: ");
    while (!Serial.available()) { }
    projectName = Serial.readStringUntil('\n');
    Serial.println("Enter task name: ");
    while (!Serial.available()) { }
    taskName = Serial.readStringUntil('\n');
    Serial.println("Enter new task status: ");
    while (!Serial.available()) { }
    newStatus = Serial.readStringUntil('\n');
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            for (int j = 0; j < projects[i].tasks.size(); j++) {
                if (projects[i].tasks[j].name == taskName) {
                    projects[i].tasks[j].status = newStatus;
                    Serial.println("Task status updated successfully!");
                    return;
                }
            }
            Serial.println("Task not found!");
            return;
        }
    }
    Serial.println("Project not found!");
}

// function to display project details
void displayProjectDetails(vector<Project>& projects) {
    string projectName;
    Serial.println("Enter project name: ");
    projectName = Serial.readStringUntil('\n');
    for (int i = 0; i < projects.size(); i++) {
        if (projects[i].name == projectName) {
            Serial.println("Project Name: " + projects[i].name);
            Serial.println("Project Description: " + projects[i].description);
            Serial.println("Tasks:");
            for (int j = 0; j < projects[i].tasks.size(); j++) {
                Serial.println("- " + projects[i].tasks[j].name + " (" + projects[i].tasks[j].status + ")");
            }
            return;
        }
    }
    Serial.println("Project not found!");
}


void loop() {
    std::vector<Project> projects;
    int choice;
    do {
        Serial.println("Select an option:");
        Serial.println("1. Create a new project");
        Serial.println("2. Add a task to a project");
        Serial.println("3. Update task status");
        Serial.println("4. Display project details");
        Serial.println("5. Exit");
        while (Serial.available() == 0) {}
        choice = Serial.parseInt();
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
            Serial.println("Goodbye!");
            break;
            default:
            Serial.println("Invalid choice, please try again.");
            break;
        }
    } while (choice != 5);
}