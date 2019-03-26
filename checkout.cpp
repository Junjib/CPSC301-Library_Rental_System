// Junji Bressan
// 301 Section 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu();
void readBooks(vector<Book *> &myBooks);
int readPersons(vector<Person *> &myCardholders);


/* You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {
    return;
}

int readPersons(vector<Person *> & myCardholders) {
    return 0;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int newID = 0;

    readBooks(books);
    newID = readPersons(cardholders);

    /*int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);*/
      return 0;
}

// ============================================================================
// This function displays a menu for the library's book rental system.
// It does not return any thing.
void printMenu()
{
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}
// ============================================================================

// ============================================================================
// This function reads from the books.txt file and stores the information
// in books vector. It takes the books vector as an argument by
// reference. It does not return anything.
void readBooks(vector<Book *> &myBooks)
{
  int id;
  string title, author, category, discard;
  ifstream readData;
  Book *bookPtr = nullptr;

  readData.open("books.txt");

  while(readData >> id)
  {
    getline(readData, discard);
    getline(readData, title);
    getline(readData, author);
    getline(readData, category);
    bookPtr = new Book(id, title, author, category);
    myBooks.push_back(bookPtr);
  }
  delete bookPtr;
  bookPtr = nullptr;

  readData.close();
}
// ============================================================================

// ============================================================================
// This function reads from the persons.txt file and stores the information
// in the cardholders vector. It takes the cardholders vector as an argument
// by reference. It returns an integer value which is the highest ID number
// plus 1.
int readPersons(vector<Person *> &myCardholders)
{
  int cardID;
  bool active;
  string firstName, lastName;
  ifstream readData;
  Person *personPtr = nullptr;

  readData.open("persons.txt");

  while(readData >> cardID)
  {
    readData >> active;
    readData >> firstName;
    readData >> lastName;
    personPtr = new Person(cardID, active, firstName, lastName);
    myCardholders.push_back(personPtr);
  }
  delete personPtr;
  personPtr = nullptr;
  readData.close();

  return (cardID + 1);
}
// ============================================================================
