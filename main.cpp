#include <iostream>
#include "Kniha.h"

using std::cin, std::cout, std::endl;

/*void cleaningBuffer() {
    if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    }  
}*/

/*Proběhne první validace podle délky stringu.
i rozhodne, jak se string validuje -> 1 = validuje ISBN; 2 = validuje název a autora*/
bool validace(string value, int i){
    switch(i){
        case 1:
            if(value.length()!= ISBN_10+3 && value.length()!=ISBN_13+4){
                //cout << "2."<<value << endl;
                cout << "Neplatne isbn." << endl;
                return false;
                
            }
            break;
        case 2:
            if(value.length() > MAXSTRING){
                //cout << "2."<<value << endl;
                return false;
            }
    }
    //cout << "2." << value << endl;
    return true;
}

string enter(string s, int i){
    string value;
    cout << "Zadej " << s;
    getline(cin, value);
    cout << value << endl;
    if (validace(value, i)){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //cout<< "3. true " << value << endl;
        return value;
    }
    //cout << "3. false " << value << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return "";
}

int main() {
    string isbn;
    string title;
    string author;
    
    Kniha kniha1;
    Kniha kniha2 ("978 1 4088 5566 9", "Harry Potter and the Chamber of Secrets", "J. K. Rowling");
    Kniha kniha3 ("80-00-00898-X", "Harry Potter a tajemná komnata", "J. K. Rowlingová");
    std::cout << kniha1<< std::endl;
    std::cout << kniha2<< std::endl;
    std::cout << kniha3<< std::endl;

    char pokracovat = 'a';

    while (pokracovat == 'a' || pokracovat == 'A') {
        isbn = enter("isbn knihy: ", 1);
        title = enter("nazev knihy: ", 2);
        author = enter("autora knihy: ", 2);

        if (isbn.empty() || title.empty() || author.empty()) {
            cout << " Jedna z hodnot je neplatna. Zkuste to znovu." << endl;
            continue;
        }

        Kniha kniha(isbn, title, author);
        if (!kniha.isbnValidation()) {
            cout << "Neplatne ISBN. Zadejte znovu." << endl;
            continue;
        }

        cout << kniha << endl;

        cout << "Chcete zadat dalsi knihu? (a/n): ";
        cin >> pokracovat;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vyčistit vstup
        
    }

    cout << "Program ukoncen." << endl;

}