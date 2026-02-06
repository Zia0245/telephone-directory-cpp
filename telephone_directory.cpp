#include <iostream>
#include <fstream>
using namespace std;

void opening();
void menu();
void displayContacts(char** names, char** phoneNumbers, int size);
bool isNumeric(char*);
void addContact(char**& names, char**& phoneNumbers, int& size, int& rowCapacity);
void deleteContact(char** names, char** phoneNumbers, int& size);
void updateContact(char** names, char** phoneNumbers, int size);
void FileOutput(char** names, char** phoneNumbers, int size);

int main() {
    char** names = nullptr;
    char** phoneNumbers = nullptr;
    opening();
    int rowCapacity = 2;
    names = new char* [rowCapacity];
    phoneNumbers = new char* [rowCapacity];

    int size = 0;

    int choice;
    while (true) {
        menu();
        cin >> choice;

        cin.ignore(1000, '\n');

        if (choice == 1) {
            addContact(names, phoneNumbers, size, rowCapacity);
        }
        else if (choice == 2) {
            deleteContact(names, phoneNumbers, size);
        }
        else if (choice == 3) {
            updateContact(names, phoneNumbers, size);
        }
        else if (choice == 4) {
            cout << "Exiting the program." << endl;
            break;
        }
        else {
            cout << "Wrong Choice. Choose from (1-4)" << endl;
        }
    }

    FileOutput(names, phoneNumbers, size);

    for (int i = 0; i < size; i++) {
        delete[] names[i];
        delete[] phoneNumbers[i];
    }

    delete[] names;
    names = nullptr;
    delete[] phoneNumbers;
    phoneNumbers = nullptr;

    system("pause");
    return 0;
}

void opening() {
    cout << "\t\t\t*******************************\n";
    cout << "\t\t\t     Contacts Book Program\n";
    cout << "\t\t\t*******************************\n\n";
}

void menu() {
    cout << "\n========== MENU ==========\n";
    cout << "Press 1 to add contact" << endl;
    cout << "Press 2 to delete contact" << endl;
    cout << "Press 3 to update contact" << endl;
    cout << "Press 4 to exit" << endl;
    cout << "==========================\n";
    cout << "Enter your choice: ";
}

void displayContacts(char** names, char** phoneNumbers, int size) {
    if (size == 0) {
        cout << "\n>>> No contacts available <<<\n";
        return;
    }

    cout << "\n==================== CONTACT LIST ====================\n";
    cout << "Sr\tName\t\t\tContact" << endl;
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << "\t" << names[i] << "\t\t\t" << phoneNumbers[i] << endl;
    }
    cout << "======================================================\n";
}

bool isNumeric(char* num) {
    if (num[0] == '\0') {
        return false;
    }

    while (*num) {
        if (*num < '0' || *num > '9') {
            return false;
        }
        num++;
    }
    return true;
}

void addContact(char**& names, char**& phoneNumbers, int& size, int& rowCapacity) {
    if (size == rowCapacity) {
        int newCapacity = rowCapacity * 2;

        char** newNames = new char* [newCapacity];
        char** newPhoneNumbers = new char* [newCapacity];

        for (int i = 0; i < size; i++) {
            newNames[i] = names[i];
            newPhoneNumbers[i] = phoneNumbers[i];
        }

        delete[] names;
        delete[] phoneNumbers;

        names = newNames;
        phoneNumbers = newPhoneNumbers;

        rowCapacity = newCapacity;
    }

    names[size] = new char[30];
    phoneNumbers[size] = new char[20];

    cout << "\n--- Add New Contact ---" << endl;
    cout << "Enter the name: ";
    cin.getline(names[size], 30);

    bool digit = false;
    do {
        cout << "Enter the phone number (numeric only): ";
        cin.getline(phoneNumbers[size], 20);

        digit = isNumeric(phoneNumbers[size]);

        if (!digit) {
            cout << "\n*** Invalid phone number. Please enter digits only ***\n" << endl;
        }
    } while (!digit);

    size++;
    cout << "\n>>> Contact added successfully! <<<" << endl;

    displayContacts(names, phoneNumbers, size);
}

void deleteContact(char** names, char** phoneNumbers, int& size) {
    if (size == 0) {
        cout << "\n*** No contacts to delete ***" << endl;
        return;
    }

    displayContacts(names, phoneNumbers, size);

    int index;
    cout << "\nEnter Sr number to delete: ";
    cin >> index;
    cin.ignore(1000, '\n');

    if (index < 1 || index > size) {
        cout << "\n*** Invalid Sr number ***" << endl;
    }
    else {
        delete[] names[index - 1];
        delete[] phoneNumbers[index - 1];

        for (int i = index - 1; i < size - 1; i++) {
            names[i] = names[i + 1];
            phoneNumbers[i] = phoneNumbers[i + 1];
        }

        size--;
        cout << "\n>>> Contact deleted successfully! <<<" << endl;
    }

    displayContacts(names, phoneNumbers, size);
}

void updateContact(char** names, char** phoneNumbers, int size) {
    if (size == 0) {
        cout << "\n*** No contacts to update ***" << endl;
        return;
    }

    displayContacts(names, phoneNumbers, size);

    int index;
    cout << "\nEnter Sr number to update: ";
    cin >> index;
    cin.ignore(1000, '\n');

    if (index < 1 || index > size) {
        cout << "\n*** Invalid Sr number ***" << endl;
    }
    else {
        delete[] names[index - 1];
        delete[] phoneNumbers[index - 1];

        names[index - 1] = new char[30];
        phoneNumbers[index - 1] = new char[20];

        cout << "\n--- Update Contact ---" << endl;
        cout << "Enter new name: ";
        cin.getline(names[index - 1], 30);

        bool digit = false;
        do {
            cout << "Enter new phone number (numeric only): ";
            cin.getline(phoneNumbers[index - 1], 20);

            digit = isNumeric(phoneNumbers[index - 1]);

            if (!digit) {
                cout << "\n*** Invalid phone number. Please enter digits only ***\n" << endl;
            }
        } while (!digit);

        cout << "\n>>> Contact updated successfully! <<<" << endl;
    }

    displayContacts(names, phoneNumbers, size);
}

void FileOutput(char* names[], char* phoneNumbers[], int size) {
    ofstream file("data.txt");

    if (file.is_open()) {
        if (size == 0) {
            file << "No contacts to save." << endl;
        }
        else {
            file << "==================== SAVED CONTACTS ====================\n";
            file << "Sr\tName\t\t\tContact\n";
            file << "--------------------------------------------------------\n";
            for (int i = 0; i < size; i++) {
                file << i + 1 << "\t" << names[i] << "\t\t\t" << phoneNumbers[i] << endl;
            }
            file << "========================================================\n";
        }
        file.close();

        cout << "\n================================================" << endl;
        cout << "All contacts saved to file 'data.txt'" << endl;
        cout << "================================================\n" << endl;
    }
    else {
        cout << "\n*** Unable to open file for writing ***" << endl;
    }
}
