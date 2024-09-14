#include "Task.h"

int Task::task_id_counter = 0;

Task::Task(std::string name, unsigned long interval, unsigned long (*millis_func)()) 
    : task_name(name), task_interval(interval), current_millis(millis_func) {
    this->task_id = ++task_id_counter;
    this->last_run_time = current_millis();
}

void Task::execute(std::function<void()> task_func) {
    unsigned long now = current_millis();
    
    if (now - last_run_time >= task_interval) {
        task_func();
        last_run_time = now;
    }
}

void Task::setTaskInterval(unsigned long interval) {
    this->task_interval = interval;
}

std::string Task::getTaskName() const {
    return task_name;
}

void Task::resetTask() {
    last_run_time = current_millis();
}

int Task::getTaskId() const {
    return task_id;
}
