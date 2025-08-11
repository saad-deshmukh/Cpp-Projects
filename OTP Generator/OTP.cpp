#include <iostream>
#include <random>
#include <string>
using namespace std;

string secureOTPGenerator(int size) {
    const string digits = "0123456789";
    string otp;
    otp.reserve(size); // Avoid repeated memory allocations

    // Use random_device for secure seeding
    random_device rd; 
    mt19937 gen(rd()); // Mersenne Twister engine Ensure numbers between 0 and 9 are equally likely.
    uniform_int_distribution<> dist(0, digits.size() - 1);

    for (int i = 0; i < size; i++) {
        otp += digits[dist(gen)];
    }
    return otp;
}

int main() {
    int inputData = 6; // Change to 4 or 6

    if (inputData == 4 || inputData == 6) {
        string OTP = secureOTPGenerator(inputData);
        cout << "Secure OTP: " << OTP << endl;
    } else {
        cout << "Invalid OTP size. Please choose 4 or 6 digits." << endl;
    }

    return 0;
}
