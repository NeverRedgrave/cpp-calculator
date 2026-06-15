#include "calculator.h"

bool ReadNumber(Number& number) {
    Number input_value = 0.0;
    if (!(std::cin >> input_value)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    number = input_value;
    return true;
}

void RunCalculatorCycle() {
    Number initial_number = 0.0;
    if (!ReadNumber(initial_number)) {
        return;
    }

    Number sum = initial_number;
    Number memory = 0.0;
    bool is_memory_empty = true;
    std::string command;

    while (std::cin >> command) {
        if (command == "q") {
            break;
        }
        if (command == "=") {
            std::cout << sum << std::endl;
            continue;
        }
        if (command == "c") {
            sum = 0;
            continue;
        }
        if (command == "s") {
            memory = sum;
            is_memory_empty = false;
            continue;
        }
        if (command == "l") {
            if (is_memory_empty) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return;
            }
            sum = memory;
            continue;
        }

        if (command == "+" || command == "-" || command == "*" || 
            command == "/" || command == "**" || command == ":") {
            
            Number next_number = 0.0;
            if (!ReadNumber(next_number)) {
                return;
            }

            if (command == "+") {
                sum += next_number;
            } else if (command == "-") {
                sum -= next_number;
            } else if (command == "*") {
                sum *= next_number;
            } else if (command == "/") {
                sum /= next_number;
            } else if (command == "**") {
                sum = std::pow(sum, next_number);
            } else if (command == ":") {
                sum = next_number;
            }
        } else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return;
        }
    }
}