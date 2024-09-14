#ifndef TASK_H
#define TASK_H

#include <Arduino.h> // Include Arduino-specific headers for String, millis(), etc.

class Task {
    private:
        static int task_id;
        String task_name;
        unsigned long task_created_timer;
        static int number_of_running_tasks;
        static unsigned long min_interval;
        unsigned long task_interval;
        unsigned long now_timer_read;
        unsigned long previous_timer_read;
        
        unsigned long timer();

        void TestAndSet_Min_Interval(unsigned long interval);

    public:
        Task(String task_name = "null", unsigned long task_interval = 1000);
        ~Task();

        void Task_start(void (*content)());
        int getTask_id();
        String getTask_name();
        void ChangeTask_name(String task_name);
        void ChangeTask_interval(unsigned long task_interval);
        void Task_terminate();
};

#endif // TASK_H
