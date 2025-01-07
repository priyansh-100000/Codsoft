#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
using namespace std;
void displayMenu() {
    cout << "\n=======Advanced Calculator=======\n";
    cout << "1. Addition (+)"<<endl;
    cout << "2. Subtraction (-)"<<endl;
    cout << "3. Multiplication (*)"<<endl;
    cout << "4. Division (/)"<<endl;
    cout << "5. Power (x^y)"<<endl;
    cout << "6. Square Root (√x)"<<endl;
    cout << "7. Factorial (x!)"<<endl;
    cout << "8. Exit\n";
    cout << "===================================="<<endl;
    cout << "Choose an operation: ";
}
long long factorial(int n) {
    if (n < 0) return -1;
    long long result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Enter numbers to add (type '=' to calculate): ";
            double num, sum = 0;
            while (cin >> num) {
                sum += num;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Result: " << sum <<endl;
            break;
        }
        case 2: {
            cout << "Enter numbers to subtract (first number is base, type '=' to calculate): ";
            double num, result;
            bool first = true;
            while (cin >> num) {
                if (first) {
                    result = num;
                    first = false;
                } else {
                    result -= num;
                }
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Result: " << result <<endl;
            break;
        }
        case 3: {
            cout<<"Enter numbers to multiply (type '=' to calculate): ";
            double num, product = 1;
            while (cin >> num) {
                product *= num;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Result: " << product <<endl;
            break;
        }
        case 4: {
            cout << "Enter numbers to divide (first number is base, type '=' to calculate): ";
            double num, result;
            bool first = true;
            while (cin >> num) {
                if (first) {
                    result = num;
                    first = false;
                } else {
                    if (num == 0) {
                        cout << "Error: Division by zero!"<<endl;
                        result = NAN;
                        break;
                    }
                    result /= num;
                }
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!isnan(result))
                cout << "Result: " << result <<endl;
            break;
        }
        case 5: {
            double base, exponent;
            cout << "Enter base: ";
            cin >> base;
            cout << "Enter exponent: ";
            cin >> exponent;
            cout << "Result: " <<pow(base, exponent)<<endl;
            break;
        }
        case 6: {
            double num;
            cout << "Enter number: ";
            cin >> num;
            cout << "Result: "<<sqrt(num)<<endl;
            }
            break;
        
        case 7: {
            int num;
            cout << "Enter number: ";
            cin >> num;
            if (num < 0) {
                cout << "Error: Factorial of a negative number is undefined!"<<endl;
            } else {
                cout << "Result: " << factorial(num)<<endl;
            }
            break;
        }
        case 8:
            cout << "Exiting calculator. Goodbye!"<<endl;
            break;
        default:
            cout << "Invalid choice. Please try again."<<endl;
        }
    } while (choice != 8);
    return 0;
}
