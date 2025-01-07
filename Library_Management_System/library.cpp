#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<map>
#include<ctime>
#include<algorithm>
#include<sstream>
using namespace std;
class Book {
public:
 string title;
 string author;
 string isbn;
    bool isAvailable;
    Book(string tit, string author, string i) : title(tit), author(author), isbn(i), isAvailable(true) {}
};
class Borrower{
public:
    string name;
    string borrowedisbn;
    time_t dueDate,returndate;
    Borrower(string borrowerName, string isbn, time_t due):name(borrowerName),borrowedisbn(isbn),dueDate(due){}
    Borrower():name(""),borrowedisbn(""), dueDate(0),returndate(){}
    Borrower(string name, string isbn, time_t due,time_t returndate) : name(name), borrowedisbn(isbn), dueDate(due),returndate(returndate){}
};
class Library{
private:
    vector<Book> books;
    map<string, Borrower> borrowers;

    time_t bookduedate(){
         time_t duedate=time(0)+(14*24*60*60);
         return duedate;
    }


     time_t inputDate(){
        string input;
     struct tm tmStruct={0};
     cout<< " Enter date of returning (format: YYYY-MM-DD): ";
     getline(cin,input);
     istringstream ss(input);
     ss>>get_time(&tmStruct, "%Y-%m-%d");
       if (ss.fail()) {
        throw invalid_argument("Invalid date format. Please use YYYY-MM--DD format.");
     }
     time_t date=mktime(&tmStruct);
     if (date == -1) {
        throw invalid_argument("Failed to convert date to time. Please check the input.");
      }
      return date;
}

     double calculateoverduefine(){
        time_t duedate=bookduedate();
        time_t returndate=inputDate();
          if (returndate>duedate) {
            int daysOverdue = (returndate-duedate)/(24*60*60);
            cout<<"Book overdue by"<<" "<<daysOverdue<<" "<<"days"<<endl;
            return daysOverdue *50;
        }
        return 0.0;
    }

 void displayBooks(const vector<Book>& bookList){
     cout << left << setw(20) << "Title" << setw(20) << "Author" << setw(20) << "isbn" << "Availability"<<endl;
     cout << string(60, '-') <<endl;
     for (const auto& book : bookList) {
     cout << left << setw(20) << book.title<< setw(20) << book.author <<setw(20) << book.isbn<< (book.isAvailable ? "Available" : "Checked Out") <<endl;
        }
    }

public:
    void addbook() {
        string title, author, isbn;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author name: ";
        cin.ignore();
        getline(cin, author);
        cout << "Enter isbn: ";
        cin.ignore();
        getline(cin, isbn);
        books.emplace_back(title, author, isbn);
        cout << "Book added successfully..."<<endl;
      }
        void searchbook() {
        string query;
        cout << "Enter title, author, or isbn to search: ";
        cin.ignore();
        getline(cin, query);
        vector<Book> results;
        for (const auto& book : books) {
            if(book.title.find(query)==string::npos||book.author.find(query)==string::npos||book.isbn.find(query)== string::npos){
                results.push_back(book);
            }
        }

        if(results.empty()){
            cout << "No books found matching the query."<<endl;
        } else {
            displayBooks(results);
        }
    }

    void checkoutbook() {
        string isbn, borrowerName;
        cout << "Enter isbn of the book to checkout: ";
        cin.ignore();
        getline(cin, isbn);
         auto i = find_if(books.begin(), books.end(), [&isbn](const Book& book) {return book.isbn == isbn && book.isAvailable;});

         if (i == books.end()) {
            cout << "Enter borrower name: ";
            getline(cin,borrowerName);
            time_t due=bookduedate();
            borrowers[isbn] = Borrower(borrowerName,isbn,due);
            i->isAvailable = false;

            cout << "Book checked out successfully! Due in 14 days."<<endl;
        } else {
            cout << "Book is either not available or does not exist."<<endl;
        }
    }

    void returnbook() {
        string isbn;
        cout << "Enter isbn of the book to return: ";
        cin.ignore();
        getline(cin, isbn);
          auto i = borrowers.find(isbn);
        if (i!= borrowers.end()) {
            auto book_it = find_if(books.begin(), books.end(),[&isbn](const Book& book) {return book.isbn == isbn;});
             if (book_it != books.end()) {
                book_it->isAvailable = true;
            }
            borrowers.erase(i);
             cout << "Book returned successfully."<<endl;
        } else {
            cout << "No record of this book being borrowed."<<endl;
        }
    }
 void calculatefine() {
        string isbn;
        cout << "Enter isbn of the book to calculate fine: ";
        cin.ignore();
        getline(cin, isbn);
        auto i = borrowers.find(isbn);
        if (i== borrowers.end()) {
            double fine = calculateoverduefine();
            if(fine > 0){
                cout <<"Overdue fine for this book is: Rs."<<fine<<endl;
            } 
            else{
                cout <<"Book is within due date."<<endl;
            }
        } 
         else{
            cout <<"No record of this book being borrowed."<<endl;
        }
    }
};
int main() {
    Library lib;
    int choice;
do {
   cout << "\n !!! Welcome to the Library Management System !!!"<<endl;
   cout << "1. Add Book to Database"<<endl;
    cout << "2. Search a Book"<<endl;
    cout << "3. Checkout Book"<<endl;
    cout << "4. Return a Book"<<endl;
    cout << "5. Calculate Fine"<<endl;
    cout << "6. Exit"<<endl;
    cout << "Enter your choice: ";
        cin >> choice;
         switch (choice) {
            case 1:
                lib.addbook();
                break;
            case 2:
                lib.searchbook();
                break;
            case 3:
                lib.checkoutbook();
                break;
            case 4:
                lib.returnbook();
                break;
            case 5:
                lib.calculatefine();
                break;
            case 6:
                cout << "Exiting system. Have a nice day"<<endl;
                break;
            default:
                cout << "Invalid choice. Please try again."<<endl;
        }
    } while (choice != 6);
       return 0;
}
