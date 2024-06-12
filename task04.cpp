#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
  string description;
  bool completed;
};
vector<Task> readTasksFromFile();
void writeTasksToFile(const vector<Task>& tasks);
void printTasks(const vector<Task>& tasks);
void addTask(vector<Task>& tasks);
void markTaskAsCompleted(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);

int main() {
  vector<Task> tasks = readTasksFromFile();

  int choice;

  do {

    cout << "\nTo-Do List Manager\n";
    cout << "1. View tasks\n";
    cout << "2. Add task\n";
    cout << "3. Mark task as completed\n";
    cout << "4. Remove task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

   
    switch (choice) {
      case 1:
        printTasks(tasks);
        break;
      case 2:
        addTask(tasks);
        break;
      case 3:
        markTaskAsCompleted(tasks);
        break;
      case 4:
        removeTask(tasks);
        break;
      case 5:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Invalid choice\n";
    }

    writeTasksToFile(tasks);

  } while (choice != 5);

  return 0;
}

vector<Task> readTasksFromFile() {
  vector<Task> tasks;
  ifstream file("tasks.txt");

  if (file.is_open()) {
    string description;
    char completed;

    while (getline(file, description)) {
      file >> completed;
      tasks.push_back({description, completed == 'Y'});
    }

    file.close();
  } else {
    cout << "Error opening file\n";
  }

  return tasks;
}

void writeTasksToFile(const vector<Task>& tasks) {
  ofstream file("tasks.txt");

  if (file.is_open()) {
    for (const Task& task : tasks) {
      file << task.description << " " << (task.completed ? 'Y' : 'N') << endl;
    }

    file.close();
  } else {
    cout << "Error opening file\n";
  }
}

void printTasks(const vector<Task>& tasks) {
  if (tasks.empty()) {
    cout << "There are no tasks in the list.\n";
    return;
  }

  cout << "\nTasks:\n";
  int index = 1;
  for (const Task& task : tasks) {
    cout << index << ". " << task.description << (task.completed ? " (completed)" : "") << endl;
    index++;
  }
}

void addTask(vector<Task>& tasks) {
  string description;
  cout << "Enter task description: ";
  cin.ignore();
  getline(cin, description);

  tasks.push_back({description, false});
  cout << "Task added successfully.\n";
}

void markTaskAsCompleted(vector<Task>& tasks) {
  if (tasks.empty()) {
    cout << "There are no tasks in the list.\n";
    return;
  }

  int index;
  cout << "Enter the index of the task to mark as completed: ";
  cin >> index;

  if (index > 0 && index <= tasks.size()) {
    tasks[index - 1].completed = true;
    cout << "Task marked as completed successfully.\n";
  } else {
    cout << "Invalid task index.\n";
  }
}

void removeTask(vector<Task>& tasks) {
  if (tasks.empty()) {
    cout << "There are no tasks in the list.\n";
    return;
  }

  int index;
  cout << "Enter the index of the task to remove: ";
  cin >> index;

  if (index > 0 && index <= tasks.size()) {
    tasks.erase(tasks.begin() + index - 1);
    cout << "Task removed successfully.\n";
  } else {
    cout << "Invalid task index.\n";
  }
}