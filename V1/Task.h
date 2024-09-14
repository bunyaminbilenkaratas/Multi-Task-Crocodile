#ifndef TASK_H
#define TASK_H

#include <string>
#include <functional>

class Task {
  private:
    static int task_id_counter;
    int task_id;
    std::string task_name;
    unsigned long task_interval;
    unsigned long last_run_time;
    unsigned long (*current_millis)();

  public:
    Task(std::string name, unsigned long interval, unsigned long (*millis_func)());
    void execute(std::function<void()> task_func);
    void setTaskInterval(unsigned long interval);
    std::string getTaskName() const;
    void resetTask();
    int getTaskId() const;
};

#endif // TASK_H
