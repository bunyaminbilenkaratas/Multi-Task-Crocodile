#include "Task.h"

int Task::task_id = 0;
int Task::number_of_running_tasks = 0;
unsigned long Task::min_interval = 4294967295; // millis function (in Arduino) will overflow after approximately 50 days.

unsigned long Task::timer() {
    return millis(); // Use millis function for Arduino.
}

void Task::TestAndSet_Min_Interval(unsigned long interval) {
    if (interval < 1) {
        Serial.println(" !!! Fatal error interval value cannot be less than 1 .");
        exit(1);
    }
    
    if (min_interval > interval) {
        min_interval = interval;
    }
    
    task_interval = interval;
}

Task::Task(String task_name, unsigned long task_interval) {
    task_id = ++task_id;
    this->task_name = task_name;
    this->task_interval = task_interval;
    task_created_timer = timer();
    number_of_running_tasks++;
}

Task::~Task() {
    number_of_running_tasks--;
}

void Task::Task_start(void (*content)()) {
    unsigned long control_start_time = timer();
    now_timer_read = timer();
    if (now_timer_read - previous_timer_read > task_interval) {
        previous_timer_read = now_timer_read;
        (*content)();
    }
    unsigned long control_stop_time = timer();
    if (control_stop_time - control_start_time > 10000) {
        Serial.println("ATTENTION !!! task duration took too long, this may destabilize other tasks.");
    }
}

int Task::getTask_id() {
    return task_id;
}

String Task::getTask_name() {
    return task_name;
}

void Task::ChangeTask_name(String task_name) {
    this->task_name = task_name;
}

void Task::ChangeTask_interval(unsigned long task_interval) {
    this->task_interval = task_interval;
}

void Task::Task_terminate() {
    delete this;
}
