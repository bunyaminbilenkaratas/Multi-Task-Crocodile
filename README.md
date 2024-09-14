# Multi-Task-Crocodile

**Multi-Task-Crocodile** is a lightweight and efficient multitasking library designed for Arduino and other microprocessors. This library simplifies the management of multiple tasks, allowing you to execute different functions at defined intervals, making multitasking straightforward and easy.

## Features

- **Multitasking Support**: Manage and execute multiple tasks concurrently.
- **Flexible Scheduling**: Set task intervals and execution times easily.
- **Compatibility**: Works with Arduino and other microprocessor platforms.

## Getting Started

To get started with **Multi-Task-Crocodile**, follow these steps:

1. **Install the Library**: Download the library files and include them in your Arduino project or other microprocessor environment.
2. **Include the Header**: Add the `Task.h` file to your project and include it in your source code.
3. **Create Tasks**: Define tasks by creating instances of the `Task` class.
4. **Execute Tasks**: Use the `execute` method to run your tasks at specified intervals.

### Example Usage

```cpp
#include <Arduino.h>

// Task class definition
class Task {
  private:
    static int task_id_counter;
    int task_id;
    String task_name; // Arduino uses String instead of std::string
    unsigned long task_interval;
    unsigned long last_run_time;
    unsigned long (*current_millis)();

  public:
    Task(String name, unsigned long interval, unsigned long (*millis_func)()) 
        : task_name(name), task_interval(interval), current_millis(millis_func) {
        this->task_id = ++task_id_counter;
        this->last_run_time = current_millis();
    }

    void execute(void (*task_func)()) {
        unsigned long now = current_millis();
        
        if (now - last_run_time >= task_interval) {
            task_func();
            last_run_time = now;
        }
    }

    void setTaskInterval(unsigned long interval) {
        this->task_interval = interval;
    }

    String getTaskName() const {
        return task_name;
    }

    void resetTask() {
        last_run_time = current_millis();
    }

    int getTaskId() const {
        return task_id;
    }
};

// Static variable initialization
int Task::task_id_counter = 0;

// Task functions
void led1() {
    Serial.println("LED 1 Task is Running");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void led2() {
    Serial.println("LED 2 Task is Running");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

Task *ledTask1;
Task *ledTask2;

unsigned long platformMillis() {
    return millis(); // Use millis() function
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize tasks
    ledTask1 = new Task("LED 1", 2000, platformMillis);
    ledTask2 = new Task("LED 2", 1000, platformMillis);
}

void loop() {
    ledTask1->execute(led1);
    ledTask2->execute(led2);
}
```

## Notice

This project is currently under development. Features and functionality are subject to change. Check back for updates and new releases.

## Author

Created by [@karatasbilen](https://twitter.com/karatasbilen). Follow for updates and more projects!

## Contributing

Contributions are welcome! If you have ideas, suggestions, or improvements, feel free to submit a pull request or open an issue.

## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). See the LICENSE file for more details.

