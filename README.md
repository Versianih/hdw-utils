# HDW-Utils

## Introduction
HDW-Utils is an Arduino library designed to simplify and encapsulate repetitive and common code snippets in hardware projects. The library provides functionalities for pin abstraction and a wait method with function execution, facilitating the development of electronic projects and promoting robotics education.

## Usage
Currently, the library offers two main functionalities:
1. **Pin Abstraction**: Allows the creation of objects that represent Arduino pins, facilitating the reading and writing of digital and analog values, as well as configuring pin modes (input, output, etc.) in a more intuitive way.
2. **WaitDo Method**: Implements a wait method that allows the execution of functions while waiting for a specified period, avoiding the use of the traditional `delay()`, which blocks program execution.

To use the library, simply include it in your Arduino project and create instances of the objects as needed.

## Examples
You can find several examples using:
- [Pin Abstraction](examples/pin_only/pin_only.ino)
- [WaitDo Method](examples/waitdo_only/waitdo_only.ino)
- [Or both together](examples/pin_waitdo/pin_waitdo.ino)

## Class Explanations
### Pin Class
The `Pin` class encapsulates the functionality of an Arduino pin, allowing operations such as reading, writing, and mode configuration. It simplifies the code by allowing you to work with pins in an object-oriented manner:
```cpp
Pin pinName(pinNumber, mode, pinType);
```
- `pinNumber`: Pin number on the Arduino.
- `mode`: Pin mode (INPUT, OUTPUT, INPUT_PULLUP).
- `pinType`: Pin type (DIGITAL or ANALOG).

### WaitDo Class
The `WaitDo` class implements a wait method that allows the execution of "tasks" (functions) during the waiting period. This is useful for avoiding code blocking and maintaining system responsiveness:
```cpp
// Initialization
WaitDo wd(maxNumberOfTasks);
```
- `maxNumberOfTasks`: Maximum number of tasks (functions) that can be registered for execution during the wait.

```cpp
// Add a task
wd.addTask(function, waitTime);
```
- `function`: Function to be executed during the wait.
- `waitTime`: Time in milliseconds to wait.

```cpp
// Execute registered tasks
wd.run();
```
- Executes the registered functions if the wait time has been reached.
- Should always be called within the main Arduino loop, placed at the beginning or end of `void loop()`.

## License
This project is licensed under the GNU Affero General Public License v3.0. Please refer to the [LICENSE](LICENSE) file for more details.

## Contributing
Contributions are welcome! Feel free to open issues or pull requests on the GitHub repository.