// Junji Bressan
// 301 Section 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

// Primary functions
void printMenu();
void readBooks(vector<Book *> &myBooks);
int readPersons(vector<Person *> &myCardholders);
void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders);
void bookCheckout(vector<Book *> &myBooks, vector<Person *> myCardholders);
void bookReturn(vector<Book *> &myBooks);
void availableBooks(vector<Book *> myBooks);
void outstandingRentals(vector<Book *> myBooks);
void cardholderRentals(vector<Book *> myBooks, vector <Person *> myCardholders);

// Helper functions
int checkCardholder(vector<Person *> myCardholders, int id);
int checkBookID(vector<Book *> myBooks, int bookID);
void readRentalsFile(vector<int> &rentedBooks, vector<int> &cardIDs);
int findBookIndex(vector<Book *> myBooks, int bookID);
int findCardholderIndex(vector<Person *> myCardholders, int cardID);


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
    readRentals(books, cardholders);
    //cout << cardholders[17]->getFirstName() << endl;
    //cout << cardholders[17]->fullName() << endl;
    //cout << cardholders[17]->getLastName() << endl;
    //cout << books[49]->getTitle() << endl;


    int choice;
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
                bookCheckout(books, cardholders);
                break;

            case 2:
                // Book return
                  bookReturn(books);
                break;

            case 3:
                // View all available books
                availableBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                outstandingRentals(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                cardholderRentals(books, cardholders);
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
   } while(choice != 8);
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

// ============================================================================
// This function checks if the book ID the user entered is valid.
// If the book exists then it returns a zero. If not it returns a negative one.
int checkBookID(vector<Book *> myBooks, int bookID)
{
  int isValid = -1;

  for(int i = 0; i < myBooks.size(); i++)
  {
    if(bookID == myBooks[i]->getId())
    {
      isValid = 0;
      return isValid;
    }
  }
  return isValid;
}
// ============================================================================

// ============================================================================
// This function checks if the cardholder ID the user entered is valid.
// It checks to see if the cardholder exists and their card is active.
// If both these conditions are met it returns the index number of the
// cardholder. If not it returns a -1.
int checkCardholder(vector<Person *> myCardholders, int id)
{
  int isValid = -1, cardHolder = 0, cardID = id;

  for(int i = 0; i < myCardholders.size(); i++)
  {
    if(cardID == myCardholders[i]->getId() && myCardholders[i]->isActive() == 1)
    {
      return cardHolder = i;
    }
  }
  return isValid;
}
// ============================================================================

// ============================================================================
// This function will use the person pointer in the book class and point to
// the person object that has checked out the book based on rentals.txt. It
// does not return anything.
void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
  vector<int> rentedBooks;
  vector<int> cardIDs;
  Person *personPtr = nullptr;
  int bookID, bookIndex, userID, cardIndex;

  readRentalsFile(rentedBooks, cardIDs);

  for(int i = 0; i < rentedBooks.size(); i++)
  {
    bookID = rentedBooks[i];
    userID = cardIDs[i];
    bookIndex = findBookIndex(myBooks, bookID);
    cardIndex = findCardholderIndex(myCardholders, userID);
    personPtr = myCardholders[cardIndex];
    myBooks[bookIndex]->setPersonPtr(personPtr);
  }
}
// ============================================================================

// ============================================================================
// This function reads the information from rentals.txt and stores the book ID
// and the card ID in their respective vectors. It does not return anything.
void readRentalsFile(vector<int> &rentedBooks, vector<int> &cardIDs)
{
  ifstream readData;
  int bookID, cardID;

  readData.open("rentals.txt");

  while(readData >> bookID)
  {
    readData >> cardID;
    rentedBooks.push_back(bookID);
    cardIDs.push_back(cardID);
  }
  readData.close();
}
// ============================================================================

// ============================================================================
// This function finds the index in the myBooks vector containing the book
// object corresponding to the book ID stored in the bookID argument. It returns
// the index number of the book object based on matching book IDs.
int findBookIndex(vector<Book *> myBooks, int bookID)
{
  for(int i = 0; i < myBooks.size(); i++)
  {
    if(bookID == myBooks[i]->getId())
    {
      return i;
    }
  }
}
// ============================================================================

// ============================================================================
// This function finds the index in the myCardholders vector containing the
// person object that is currently renting a specific book. It returns the
// the index number of the person object based on matching card IDs.
int findCardholderIndex(vector<Person *> myCardholders, int cardID)
{
  for(int i = 0; i < myCardholders.size(); i++)
  {
    if(cardID == myCardholders[i]->getId())
    {
      return i;
    }
  }
}
// ============================================================================

// ============================================================================
// This function allows the user to checkout a book provided that: their ID is
// valid, the book ID is valid, and the book has not been checked out yet.
// If all these conditions are met the user will be able to checkout the book
// they requested.
void bookCheckout(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
  int cardID, cardIndex, bookID, bookIndex, isValid = 0, cardHolder = 0;
  string name;
  Person *personPtr = nullptr;

// Card ID validation.
  cout << "Please enter the card ID: ";
  cin >> cardID;
  cardHolder = checkCardholder(myCardholders, cardID);
  if(cardHolder != -1)
  {
    cout << "Cardholder: " << myCardholders[cardHolder]->fullName() << endl;
  }
  else
  {
    cout << "Card ID not found\n";
    return;
  }

// Book ID validation, rental status, and completion of rental.
  cout << "Please enter the book ID: ";
  cin >> bookID;
  isValid = checkBookID(myBooks, bookID);
  if(isValid == -1)
  {
    cout << "Book ID not found\n";
    return;
  }
  else
  {
    for(int i = 0; i < myBooks.size(); i++)
    {
      if(bookID == myBooks[i]->getId() && myBooks[i]->getPersonPtr() != nullptr)
      {
        cout << "Book already checked out\n";
        return;
      }
    }
    for(int j = 0; j < myBooks.size(); j++)
    {
      if(bookID == myBooks[j]->getId())
      {
        cout << "Title: " << myBooks[j]->getTitle() << endl;
        cout << "Rental Completed\n";
        cardIndex = findCardholderIndex(myCardholders, cardID);
        bookIndex = findBookIndex(myBooks, bookID);
        personPtr = myCardholders[cardIndex];
        myBooks[bookIndex]->setPersonPtr(personPtr);
      }
    }
  }
}
// ============================================================================

// ============================================================================
// This function allows the user to return a book provided that the book ID is
// valid and the book being returned is currently rented.
void bookReturn(vector<Book *> &myBooks)
{
  int bookID, bookIndex, isValid = 0;
  Person *personPtr = nullptr;

  cout << "Please enter the book ID to return: ";
  cin >> bookID;
  isValid = checkBookID(myBooks, bookID);
  bookIndex = findBookIndex(myBooks, bookID);
  if(isValid == -1 || myBooks[bookIndex]->getPersonPtr() == nullptr)
  {
    cout << "Book ID not found\n";
    return;
  }
  else
  {
    for(int i = 0; i < myBooks.size(); i++)
    {
      if(bookID == myBooks[i]->getId())
      cout << "Title: " << myBooks[i]->getTitle() << endl;
      myBooks[bookIndex]->setPersonPtr(personPtr);
    }
  }
  cout << "Return Completed\n";
}
// ============================================================================

// ============================================================================
// This function displays all of the books that are still available.
void availableBooks(vector<Book *> myBooks)
{
  int bookCounter = 0;

  for(int i = 0; i < myBooks.size(); i++)
  {
    if(myBooks[i]->getPersonPtr() == nullptr)
    {
      cout << "Book ID: " << myBooks[i]->getId() << endl;
      cout << "Title: " << myBooks[i]->getTitle() << endl;
      cout << "Author: " << myBooks[i]->getAuthor() << endl;
      cout << "Category: " << myBooks[i]->getCategory() << endl << endl;
      bookCounter++;
    }
  }
  if(bookCounter == 0)
  {
    cout << "No available books\n";
  }
}
// ============================================================================

// ============================================================================
// This function displays the books that currently rented out.
void outstandingRentals(vector<Book *> myBooks)
{
  int rentalCounter = 0;

  for(int i = 0; i < myBooks.size(); i++)
  {
    if(myBooks[i]->getPersonPtr() != nullptr)
    {
      cout << "Book ID: " << myBooks[i]->getId() << endl;
      cout << "Title: " << myBooks[i]->getTitle() << endl;
      cout << "Author: " << myBooks[i]->getAuthor() << endl;
      cout << "Cardholder: " << myBooks[i]->getPersonPtr()->fullName() << endl;
      cout << "Card ID: " << myBooks[i]->getPersonPtr()->getId() << endl << endl;
      rentalCounter++;
    }
  }
  if(rentalCounter == 0)
  {
    cout << "No outstanding rentals\n";
  }
}
// ============================================================================

// ============================================================================
// This function asks the user to enter a card ID and then displays the books
// currently rented out by that cardholder. So long the card ID entered is valid.
void cardholderRentals(vector<Book *> myBooks, vector <Person *> myCardholders)
{
  int cardID, cardHolder, cardholderRentalsCntr = 0;

  cout << "Please enter the card ID: ";
  cin >> cardID;
  cardHolder = checkCardholder(myCardholders, cardID);
  if(cardHolder == -1)
  {
    cout << "Card ID not found\n";
    return;
  }
  else
  {
    cout << "Cardholder: " << myCardholders[cardHolder]->fullName() << endl;
    for(int i = 0; i < myBooks.size(); i++)
    {
      if(myBooks[i]->getPersonPtr() != nullptr && cardID == myBooks[i]->getPersonPtr()->getId())
      {
        cout << endl;
        cout << "Book ID: " << myBooks[i]->getId() << endl;
        cout << "Title: " << myBooks[i]->getTitle() << endl;
        cout << "Author: " << myBooks[i]->getAuthor() << endl;
        cardholderRentalsCntr++;
      }
    }
    if(cardholderRentalsCntr == 0)
    {
      cout << "No books currently checked out\n";
    }
  }
}
// ============================================================================
