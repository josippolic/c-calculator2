#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

// Funkcija za čitanje poslednjeg broja računanja iz fajla
int read_last_calculation_number() {
    std::ifstream file("calculator.txt");
    std::string line;
    int last_number = 0;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            // Pokušavamo da parsiramo broj posle "Calculation"
            if (line.find("Calculation") != std::string::npos) {
                size_t pos = line.find("Calculation") + 11;
                int number = std::stoi(line.substr(pos));
                last_number = std::max(last_number, number);
            }
        }
        file.close();
    }
    
    return last_number;
}

void save_to_file(const std::string &result, int count, bool is_first) {
    std::ofstream file("calculator.txt", std::ios::app); // Otvori fajl u režimu dodavanja
    if (file.is_open()) {
        if (is_first) {
            file << "Calculation " << count << ":\n";  // Dodaj broj računanja samo prvi put
        }
        file << result << "\n";  // Dodaj rezultat
        file.close();  // Zatvori fajl
    } else {
        std::cout << "Unable to open file for writing.\n";
    }
}

void perform_operation(char operation, double x, double y, int count, bool &is_first) {
    double result = 0;
    std::string result_str;
    switch (operation) {
        case '+':
            result = std::abs(x + y);
            result_str = "Addition: " + std::to_string(result);
            break;
        case '-':
            result = std::abs(x - y);
            result_str = "Subtraction: " + std::to_string(result);
            break;
        case '*':
            result = std::abs(x * y);
            result_str = "Multiplication: " + std::to_string(result);
            break;
        case '/':
            if (y == 0) {
                result_str = "Error: Division by zero is not allowed.";
                std::cout << result_str << "\n";
                save_to_file(result_str, count, is_first);
                return;
            }
            if (y > x) {
                result = y / x;
            } else {
                result = x / y;
            }
            result_str = "Division: " + std::to_string(result);
            break;
        default:
            result_str = "Invalid operation!";
            std::cout << result_str << "\n";
            save_to_file(result_str, count, is_first);
            return;
    }
    std::cout << "Result: " << result << "\n";
    save_to_file(result_str, count, is_first); // Save result to file
    is_first = false;  // Set to false after first operation for this calculation
}

void perform_all_operations(double x, double y, int count) {
    std::string result_str;
    std::string all_results;
    bool is_first = true;  // Flag to indicate if it's the first operation

    result_str = "Addition: " + std::to_string(std::abs(x + y));
    std::cout << result_str << "\n";
    all_results += result_str + "\n";
    save_to_file(result_str, count, is_first);
    is_first = false;

    result_str = "Subtraction: " + std::to_string(std::abs(x - y));
    std::cout << result_str << "\n";
    all_results += result_str + "\n";
    save_to_file(result_str, count, is_first);

    result_str = "Multiplication: " + std::to_string(std::abs(x * y));
    std::cout << result_str << "\n";
    all_results += result_str + "\n";
    save_to_file(result_str, count, is_first);

    if (y != 0) {
        if (y > x) {
            result_str = "Division: " + std::to_string(y / x);
            std::cout << result_str << "\n";
            all_results += result_str + "\n";
            save_to_file(result_str, count, is_first);
        } else {
            result_str = "Division: " + std::to_string(x / y);
            std::cout << result_str << "\n";
            all_results += result_str + "\n";
            save_to_file(result_str, count, is_first);
        }
    } else {
        result_str = "Division by zero is not allowed.";
        std::cout << result_str << "\n";
        all_results += result_str + "\n";
        save_to_file(result_str, count, is_first);
    }
}

int main() {
    double x, y;
    char operation;
    std::string answer;
    
    // Pročitaj poslednji broj računanja
    int count = read_last_calculation_number() + 1;

    std::cout << "Enter first number: ";
    std::cin >> x;

    std::cout << "Enter second number: ";
    std::cin >> y;

    std::cout << "Do you want to calculate all operations (yes/no)? ";
    std::cin >> answer;

    if (answer == "yes" || answer == "Yes") {
        std::cout << "\nPerforming all operations:\n";
        perform_all_operations(x, y, count);
    } else {
        std::cout << "Choose operation (+, -, *, /): ";
        std::cin >> operation;

        bool is_first = true;
        perform_operation(operation, x, y, count, is_first);
    }

    return 0;
}
