#include <iostream>
#include <vector>
#include <string>

class Task {
public:
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

class TaskManager {
private:
    std::vector<Task*> tasks;

public:
    TaskManager() = default;

    void addTask(const std::string& description) {
        tasks.push_back(new Task(description));
    }

    void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index]->completed = true;
        }
    }

    void displayTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks available." << std::endl;
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i << ": " << tasks[i]->description
                      << " [" << (tasks[i]->completed ? "Completed" : "Not Completed") << "]" << std::endl;
        }
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            delete tasks[index];
            tasks.erase(tasks.begin() + index);
        }
    }

    Task* getLastTask() const {
        return tasks.back();
    }

    void printLastTaskDescription() const {
        Task* lastTask = getLastTask();
        if (lastTask) {
            std::cout << "Last task: " << lastTask->description << std::endl;
        } else {
            std::cout << "No tasks available." << std::endl;
        }
    }
};

int main() {
    TaskManager manager;

    manager.addTask("Task 1");
    manager.addTask("Task 2");

    manager.displayTasks();

    manager.completeTask(1);
    
    manager.displayTasks();
    
    manager.printLastTaskDescription();

    return 0;
}