#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Task {
    string description;
    bool completed;
};
class todolist {
private:
    vector<Task> tasks;

public:
    void addTask(const string &taskDescription) {
        Task newTask = {taskDescription, false};
        tasks.push_back(newTask);
        cout << "Task '" << taskDescription << "' added successfully." <<endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks in the list."<<endl;
        } else {
            cout << "\nTo-Do List:"<<endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << i + 1 << ". " << tasks[i].description << " [" << (tasks[i].completed ? "Completed" : "Pending") << "]" <<endl;
            }
        }
    }

    void markTaskCompleted(size_t taskNumber) {
        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1].completed = true;
            cout << "Task " << taskNumber << " marked as completed."<<endl;
        } else {
            cout << "Invalid task number."<<endl;
        }
    }

    void removeTask(size_t taskNumber) {
        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            cout << "Task '" << tasks[taskNumber - 1].description << "' removed successfully." << endl;
            tasks.erase(tasks.begin() + taskNumber - 1);
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void menu() {
        while (true) {
            cout << "\nTo-Do List Manager" << endl;
            cout << "1. Add Task" << endl;
            cout << "2. View Tasks" << endl;
            cout << "3. Mark Task as Completed" << endl;
            cout << "4. Remove Task" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice (1-5): ";
            int choice;
            cin >> choice;
            cin.ignore();
             switch (choice) {
            case 1: {
                cout << "Enter the task: ";
                string taskDescription;
                getline(cin, taskDescription);
                addTask(taskDescription);
                break;
            }
            case 2:
                viewTasks();
                break;
            case 3: {
                cout << "Enter task number to mark as completed: ";
                size_t taskNumber;
                cin >> taskNumber;
                markTaskCompleted(taskNumber);
                break;
            }
            case 4: {
                cout << "Enter task number to remove: ";
                size_t taskNumber;
                cin >> taskNumber;
                removeTask(taskNumber);
                break;
            }
            case 5:
                cout << "Exiting To-Do List Manager. Goodbye!" <<endl;
                return;
            default:
                cout << "Invalid choice. Please try again." <<endl;
            }
        }
    }
};

int main() {
    todolist list;
    list.menu();
    return 0;
}
