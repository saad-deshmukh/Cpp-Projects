#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

// ======== Text Color Functions ========
void Red()          { cout << "\033[1;31m"; }
void Yellow()       { cout << "\033[1;33m"; }
void Blue()         { cout << "\033[0;34m"; }
void Green()        { cout << "\033[0;32m"; }
void Purple()       { cout << "\033[0;35m"; }
void White()        { cout << "\033[0;37m"; }
void Cyan()         { cout << "\033[0;36m"; }
void ResetTextColor(){ cout << "\033[0m"; }

// ======== Helper Functions ========
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool isValidPhone(const string& phone) {
    return regex_match(phone, regex("^[0-9]{10}$"));
}

bool isValidEmail(const string& email) {
    return regex_match(email, regex("^[\\w._%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$"));
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ======== Contact Class ========
class Contact {
public:
    string name;
    string phoneNo;
    string emailId;

    void printContact(int index) {
        Yellow();
        cout << "\nContact No   : " << setw(2) << setfill('0') << index << endl;
        Purple();
        cout << "-----------------------------\n";
        cout << "Name         : " << name << endl;
        cout << "Phone Number : " << phoneNo << endl;
        cout << "Email ID     : " << emailId << endl;
        ResetTextColor();
    }
};

// ======== Contact Book Class ========
class ContactBook {
private:
    vector<Contact> listOfContacts;

protected:
    void storeContactInFile();
    void readContactFromFile();
    bool nameExists(const string& name);

public:
    void mainMenu();
    void addNewContact();
    void viewAllContact();
    void searchContactByName();
    void deleteContactByName();
    void updateContact();
};

bool ContactBook::nameExists(const string& name) {
    for (auto& contact : listOfContacts) {
        if (toLowerCase(contact.name) == toLowerCase(name))
            return true;
    }
    return false;
}

void ContactBook::storeContactInFile() {
    ofstream fout("Contacts.txt");
    if (fout.is_open()) {
        for (const auto& contact : listOfContacts) {
            fout << contact.name << "\n";
            fout << contact.phoneNo << "\n";
            fout << contact.emailId << "\n";
        }
        fout.close();
    } else {
        Red(); cout << "Error: Could not open file for saving!" << endl; ResetTextColor();
    }
}

void ContactBook::readContactFromFile() {
    ifstream fin("Contacts.txt");
    if (fin.is_open()) {
        Contact contact;
        listOfContacts.clear();

        while (getline(fin, contact.name)) {
            getline(fin, contact.phoneNo);
            getline(fin, contact.emailId);
            listOfContacts.push_back(contact);
        }
        fin.close();
    }
}

void ContactBook::mainMenu() {
    int choice;
    readContactFromFile();
    cout << "Welcome to Contact Book" << endl;

    do {
        Green();
        cout << "\n==========================\n";
        cout << "1. Add New Contact\n";
        cout << "2. View All Contacts\n";
        cout << "3. Search Contact By Name\n";
        cout << "4. Delete Contact By Name\n";
        cout << "5. Update Contact\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        ResetTextColor();
        cin.ignore();
        clearScreen();

        switch (choice) {
            case 1: addNewContact(); break;
            case 2: viewAllContact(); break;
            case 3: searchContactByName(); break;
            case 4: deleteContactByName(); break;
            case 5: updateContact(); break;
            case 6: cout << "Exiting..." << endl; storeContactInFile(); break;
            default: Red(); cout << "Invalid choice, please try again." << endl; ResetTextColor();
        }
    } while (choice != 6);
}

void ContactBook::addNewContact() {
    Contact newContact;
    Blue();
    cout << "----------------------------------" << endl;
    cout << "Enter Name : ";
    getline(cin, newContact.name);

    if (nameExists(newContact.name)) {
        Red(); cout << "Contact with this name already exists!" << endl; ResetTextColor();
        return;
    }

    do {
        cout << "Enter Phone Number (10 digits): ";
        getline(cin, newContact.phoneNo);
        if (!isValidPhone(newContact.phoneNo))
            Red(), cout << "Invalid phone number!" << endl, ResetTextColor();
    } while (!isValidPhone(newContact.phoneNo));

    do {
        cout << "Enter Email ID : ";
        getline(cin, newContact.emailId);
        if (!isValidEmail(newContact.emailId))
            Red(), cout << "Invalid email format!" << endl, ResetTextColor();
    } while (!isValidEmail(newContact.emailId));

    ResetTextColor();
    listOfContacts.push_back(newContact);
    Green(); cout << "Contact added successfully!" << endl; ResetTextColor();
}

void ContactBook::viewAllContact() {
    if (listOfContacts.empty()) {
        Red(); cout << "No contacts available!" << endl; ResetTextColor();
        return;
    }

    sort(listOfContacts.begin(), listOfContacts.end(),
         [](const Contact& a, const Contact& b) {
             return toLowerCase(a.name) < toLowerCase(b.name);
         });

    int count = 1;
    for (auto& contact : listOfContacts)
        contact.printContact(count++);
}

void ContactBook::searchContactByName() {
    string name;
    cout << "Enter the name to search : ";
    getline(cin, name);
    bool found = false;

    for (auto& contact : listOfContacts) {
        if (toLowerCase(contact.name) == toLowerCase(name)) {
            contact.printContact(1);
            found = true;
        }
    }
    if (!found) {
        Red(); cout << "Contact not found!" << endl; ResetTextColor();
    }
}

void ContactBook::deleteContactByName() {
    string name;
    cout << "Enter the name to delete : ";
    getline(cin, name);
    bool found = false;

    for (auto it = listOfContacts.begin(); it != listOfContacts.end(); ++it) {
        if (toLowerCase(it->name) == toLowerCase(name)) {
            listOfContacts.erase(it);
            found = true;
            Green(); cout << "Contact deleted successfully!" << endl; ResetTextColor();
            break;
        }
    }
    if (!found) {
        Red(); cout << "Contact not found!" << endl; ResetTextColor();
    }
}

void ContactBook::updateContact() {
    string name;
    cout << "Enter the name to update : ";
    getline(cin, name);
    bool found = false;

    for (auto& contact : listOfContacts) {
        if (toLowerCase(contact.name) == toLowerCase(name)) {
            do {
                cout << "Enter new Phone Number (10 digits): ";
                getline(cin, contact.phoneNo);
                if (!isValidPhone(contact.phoneNo))
                    Red(), cout << "Invalid phone number!" << endl, ResetTextColor();
            } while (!isValidPhone(contact.phoneNo));

            do {
                cout << "Enter new Email ID : ";
                getline(cin, contact.emailId);
                if (!isValidEmail(contact.emailId))
                    Red(), cout << "Invalid email format!" << endl, ResetTextColor();
            } while (!isValidEmail(contact.emailId));

            found = true;
            Green(); cout << "Contact updated successfully!" << endl; ResetTextColor();
            break;
        }
    }
    if (!found) {
        Red(); cout << "Contact not found!" << endl; ResetTextColor();
    }
}

// ======== Main Function ========
int main() {
    ContactBook cb;
    cb.mainMenu();
    return 0;
}
