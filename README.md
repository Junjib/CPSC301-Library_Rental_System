# CPSC301-Program4

# Name: Junji Bressan
# Email: Junjib@csu.fullerton.edu

# Description
This program is a library rental system. It contains options that allows the user to checkout books, return books, view all available books, view all rented books, view all books rented by a particular person, open a new library card, close a library card, and to end the program.
The program has two classes book and person. In the checkout.cpp file containing the main function two vectors are declared containing pointers that point to objects of the book class and objects of the person class. The main reads from provided text files and fills in these vectors with pointers pointing to the objects of their respective classes. There is a third file rentals.txt which contains the book ID and the card ID, based on these IDs the book class contains a pointer that points to a person object if the book IDs match then the person pointer in that particular object will find the person object with a matching card ID. This will be how the program keeps track of which books are currently checked out and by who. Below will be explanations of the options listed above.

# Checkout Book
This option allows the user to checkout a book provided that the card ID entered is valid checking to make sure that the card is active and exists in the system. Then the user will be asked to enter the ID of the book that they wish to checkout. The function will check to make sure that the book ID entered is valid by making sure that the book has not already been checked out and that the book exists within the system. Provided that the user passes all of these checks then the book will be successfully checked out and the books vector will be updated.

# Return Book
This option allows the user to return a book. The function will ask the user to input the ID of the book that they wish to return. The function will check to make sure that the book is currently checked out and exists within the system. If the book ID is valid then the book will be returned with the book vector being updated.

# View all Available Books
This option will display the books that are currently still available to be checked out. The book ID, author, title, and category will displayed to the user.

# View Outstanding Rentals
This option will display the books that are currently checked out. It will display the book ID, title, author, cardholder name, and the card ID.

# View Outstanding Rentals for a Cardholder
This option will display the books that are currently checked out by a specific cardholder.
The function will ask the user to enter the card ID. It will check to make sure that the ID is valid and that the user has checked out books. If the ID passes then the books that the cardholder has checked out will displayed.

# Open New Library Card
This option will allow the user to open a new library card or to reactivate one that is currently inactive. The user will be asked to enter a first name and last name. If the name is new then a new card will be created. If the name entered is for a card that is currently inactive then it will be reactivated. We are going under the assumption that there are no duplicate names.

# Close Library Card
This option will allow the user to deactivate an active card. It will ask the user to enter a card ID and will check to ensure that the ID is valid and that the ID is not currently inactive. If the ID passes then the user will be asked if they are sure that they want to deactivate the card. If yes then the card will be deactivated.

# End Program
This option when selected will exit the program, but not before updating the persons.txt and rentals.txt files and handling any dynamic memory.  
