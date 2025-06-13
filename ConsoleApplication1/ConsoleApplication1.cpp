#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    //타이틀 검색 매서드
    void searchTitle(const string& title)  {
        bool found = false;
        cout << "[검색 결과 - 제목: " << title << "]" << endl;
        for (const Book& book : books) {
            if (book.title == title) {
                cout << "- " << book.title << " by " << book.author << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "입력한 제목과 일치하는 도서를 찾지 못했습니다." << endl;
        }
        

    }
    //
    void searchAuthor(const string& author) {
        bool found = false;
        cout << "[검색 결과 - 저자: " << author << "]" << endl;
        for (const Book& book : books) {
            if (book.author == author) {
                cout << "- " << book.title << " by " << book.author << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "입력한 저자와 일치하는 도서를 찾지 못했습니다." << endl;
        }

    }

    vector<Book>& getBooks()  {
        return books;
    }
};

class borrowManager {
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(Book& book,int quantity = 3) {
        string title = book.title;
        stock[title] = quantity;

    }
    void borrowBook(string& title) {
        if (stock.find(title) == stock.end()) {
            cout << "해당 도서는 재고에 없습니다." << endl;
            return;
        }
        if (stock[title] <= 0) {
            cout << "해당 도서는 모두 대여 중입니다." << endl;
            return;
        }
        stock[title]--;
        cout << title << " 도서가 대여되었습니다." << endl;

    }
    void returnBook(string& title) {
        if (stock.find(title) == stock.end()) {
            cout << "해당 도서는 이 도서관에서 관리하지 않습니다." << endl;
            return;
        }
        stock[title]++;
        cout << title << " 도서가 반납되었습니다." << endl;
    }
    void displayStock() {

        cout << "도서 재고 목록:" << endl;
        for (const auto& pair : stock) {
            cout << "- " << pair.first << ": " << pair.second << "권 남음" << endl;
        }

    }

};

int main() {
    BookManager manager;
    borrowManager bookSellManager;


    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 종료" << endl; // 프로그램 종료
        cout << "4. 책 타이틀로 검색" << endl;
        cout << "5. 책 저자로 검색" << endl;
        cout << "6. 책 대여" << endl;
        cout << "7. 책 반납" << endl;


        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author);
            vector<Book>& allBooks = manager.getBooks();
            // 책마다 BorrowManager에 재고 등록
            for (Book& book : allBooks) {
                bookSellManager.initializeStock(book);
            }
        }
        else if (choice == 2) { 
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 4) {
            string title;
            cout << "검색하고 싶은 제목을 입력하십쇼" << endl;
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.searchTitle(title);
            
        }
        else if (choice == 5) {

            string author;
            cout << "검색하고 싶은 책의 저자를 입력하십쇼" << endl;
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 제목 입력 (공백 포함)
            manager.searchAuthor(author);
        }
        else if (choice == 6) {
            string title;
            bookSellManager.displayStock();

            cout << "대여하고 싶은 책 제목을 입력하십쇼" << endl;
            cin.ignore();
            getline(cin, title);
            bookSellManager.borrowBook(title);
            
        }
        else if (choice == 7) {

            string title;
            bookSellManager.displayStock();
            cout << "반납하고 싶은 책을 입력하십쇼 " << endl;
            cin.ignore();
            getline(cin, title);
            bookSellManager.returnBook(title);
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}