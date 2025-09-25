#include <iostream>
#include <fstream>
#include <iomanip> 
using namespace std;

class Library {
    string id, name, author, search;
    fstream file;

public:
    void showAll();
    void extractBook();
    void addBook();
    void deleteBook();
} obj;

int main() {
    char choice;
    while (true) {
        cout << "\n==================================" << endl;
        cout << "       LIBRARY MANAGEMENT       " << endl;
        cout << "==================================" << endl;
        cout << "1 - Show All Books" << endl;
        cout << "2 - Extract Book by ID" << endl;
        cout << "3 - Add Book (ADMIN)" << endl;
        cout << "4 - Delete Book (ADMIN)" << endl;
        cout << "5 - Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        switch (choice) {
        case '1':
            obj.showAll();
            break;
        case '2':
            obj.extractBook();
            break;
        case '3':
            obj.addBook();
            break;
        case '4':
            obj.deleteBook();
            break;
        case '5':
            cout << "Exiting Program... Goodbye! " << endl;
            return 0;
        default:
            cout << "⚠ Invalid Choice... Try again!" << endl;
        }
    }
    return 0;
}

// Add Book
void Library::addBook() {
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Author Name :: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    file << id << "*" << name << "*" << author << endl;
    file.close();

    cout << " Book Added Successfully!\n";
}

// Show All Books
void Library::showAll() {
    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "⚠ No books found. Please add first.\n";
        return;
    }

    cout << "\n-----------------------------------------------------------\n";
    cout << setw(15) << "Book ID" << setw(25) << "Book Name" << setw(25) << "Author\n";
    cout << "-----------------------------------------------------------\n";

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        cout << setw(15) << id << setw(25) << name << setw(25) << author << endl;
    }
    file.close();
}

// Extract Book by ID
void Library::extractBook() {
    cout << "\nEnter Book ID to search :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "⚠ File not found!\n";
        return;
    }

    bool found = false;
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        if (id == search) {
            cout << "\n Book Found:\n";
            cout << "ID: " << id << "\nName: " << name << "\nAuthor: " << author << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << " Book ID not found!\n";
    }
    file.close();
}

// Delete Book
void Library::deleteBook() {
    cout << "\nEnter Book ID to delete :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "⚠ File not found!\n";
        return;
    }

    fstream temp;
    temp.open("temp.txt", ios::out);

    bool deleted = false;
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');

        if (id != search) {
            temp << id << "*" << name << "*" << author << endl;
        } else {
            deleted = true;
        }
    }
    file.close();
    temp.close();

    remove("bookData.txt");
    rename("temp.txt", "bookData.txt");

    if (deleted)
        cout << " Book Deleted Successfully!\n";
    else
        cout << " Book ID not found!\n";
}
