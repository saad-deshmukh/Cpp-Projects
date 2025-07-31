#include <iostream>
#include <cstdlib>  
using namespace std;

void miniCalculator() {
    cout << "Welcome to Calculator" << endl;
    cout << "------------------------" << endl;

    float num1, num2;
    char choice;

    while (true) {
        cout << "Enter < + > for addition" << endl;
        cout << "Enter < - > for subtraction" << endl;
        cout << "Enter < * > for multiplication" << endl;
        cout << "Enter < / > for division" << endl;
        cout << "Enter < % > for remainder (integers only)" << endl;
        cout << "Enter < E > for Exit..!" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        system("clear");

        cout << "------------------------" << endl << endl;

        switch (choice) {
            case '+':
                cout << "Enter two numbers : ";
                cin >> num1 >> num2;
                cout << "Sum of " << num1 << " and " << num2 << " is : " << num1 + num2;
                break;
            case '-':
                cout << "Enter two numbers : ";
                cin >> num1 >> num2;
                cout << "Difference of " << num1 << " and " << num2 << " is : " << num1 - num2;
                break;
            case '*':
                cout << "Enter two numbers : ";
                cin >> num1 >> num2;
                cout << "Product of " << num1 << " and " << num2 << " is : " << num1 * num2;
                break;
            case '/':
                cout << "Enter two numbers : ";
                cin >> num1 >> num2;
                if (num2 != 0)
                    cout << "Division of " << num1 << " by " << num2 << " is : " << num1 / num2;
                else
                    cout << "Error: Division by zero!";
                break;
            case '%':
                int a, b;
                cout << "Enter two integers : ";
                cin >> a >> b;
                if (b != 0)
                    cout << "Remainder of " << a << " % " << b << " is : " << a % b;
                else
                    cout << "Error: Division by zero!";
                break;
            case 'E':
            case 'e':
                cout << "Thank you for using the calculator!" << endl;
                exit(0);
            default:
                cout << "Enter a valid choice!" << endl;
        }
        cout << endl << endl;
    }
}

int main() {
    miniCalculator();
    return 0;
}
