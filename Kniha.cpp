//
// Created by student on 17.03.2025.
//

#include "Kniha.h"
#include <string>
#include <sstream>
#include <regex>
#include <cctype>
#include <algorithm>
#include <iostream>
#define BOOK_ISBN "978-80-251-1583-1"
#define BOOK_AUTHOR "Jesse Liberty"
#define BOOK_TITLE "Naučte se C++ za 21 dní"

using namespace std;

//vychozi konstruktor
Kniha::Kniha() {
    this->isbn = BOOK_ISBN;
    this->title = BOOK_TITLE;
    this->author = BOOK_AUTHOR;
}

//gettery isbn, nazvu a autora
string Kniha::getIsbn() const {
    return this->isbn;
}

string Kniha::getTitle() const {
    return this->title;
}

string Kniha::getAuthor() const {
    return this->author;
}

//nastavi nazev knihy
bool Kniha::setTitle(const string &title) {
    if(2 < title.length() && title.length() < MAXSTRING){
        this->title = title;
        return true;
    }
    return false;
}

//nastavi autora
bool Kniha::setAuthor(const string &author) {
    if(2 < title.length() && title.length() < MAXSTRING){
        this->author = author;
        return true;
    }
    return false;
}

//nastavi isbn
bool Kniha::setIsbn(const string &isbn) {
    if(isbn.length() == ISBN_10 + 3){
        this->isbn = isbn;
        return true;
    }
    if(isbn.length() == ISBN_13 + 4){
        this->isbn = isbn;
        return true;
    }
    return false;
}

//nastavi celou knihu
Kniha::Kniha(string isbn, string title, string author) {
    if(!setIsbn(isbn) || !setTitle(title) || !setAuthor(author)){
        this->isbn = BOOK_ISBN;
        this->title = BOOK_TITLE;
        this->author = BOOK_AUTHOR;
    }
}

Kniha::~Kniha()
{
}

//ziska prefix z isbn pokud je to ISBN-13
string Kniha::getPrefix() const {
    std::vector<string> parts = splitIsbn(this->isbn);
    return parts[0];
}


//odstrani pomlcky nebo mezery v isbn
string Kniha::getIsbnNum() const {
    string isbnNum = this->isbn;
    if(this->isbn.length() == ISBN_10+3){
        if(isbnNum.find('-')!=std::string::npos){
            isbnNum.erase(std::remove(isbnNum.begin(), isbnNum.end(), '-'), isbnNum.end());
        }
        else if(isbnNum.find(' ')!=std::string::npos){
            isbnNum.erase(std::remove(isbnNum.begin(), isbnNum.end(), ' '), isbnNum.end());
        }
    }
    if(this->isbn.length() == ISBN_13+4){
        if(isbnNum.find('-')!=std::string::npos){
            isbnNum.erase(std::remove(isbnNum.begin(), isbnNum.end(), '-'), isbnNum.end());
        }
        else if(isbnNum.find(' ')!=std::string::npos){
            isbnNum.erase(std::remove(isbnNum.begin(), isbnNum.end(), ' '), isbnNum.end());
        }
    }
    return isbnNum;
}

string Kniha::getRegion() const {
    std::vector<string> parts = splitIsbn(this->isbn);
    string isbnNum = getIsbnNum();
    if(isbnNum.length() == ISBN_10){
        return parts[0];
    }
    else if(isbnNum.length() == ISBN_13){
        return parts[1];
    }
}

string Kniha::getVydavatel() const {
    std::vector<string> parts = splitIsbn(this->isbn);
    string isbnNum = getIsbnNum();
    if(isbnNum.length() == ISBN_10){
        return parts[1];
    }
    else if(isbnNum.length() == ISBN_13){
        return parts[2];
    }
}

string Kniha::getVydani() const {
    std::vector<string> parts = splitIsbn(this->isbn);
    string isbnNum = getIsbnNum();
    if(isbnNum.length() == ISBN_10){
        return parts[2];
    }
    else if(isbnNum.length() == ISBN_13){
        return parts[3];
    }
}


bool Kniha::isbnValidation() {
    string raw = getIsbnNum();
    string isbn= this->isbn;
    int delimiters = 0;


    /*Regulární výraz zkontroluje, jestli isbn odpovídá platnému formátu*/
    regex regex13(R"(^((978|979)([-]\d+){4})|((978|979)([ ]\d+){4})$)");
    regex regex10(R"(^((\d+[-]){3}[xX\d])|((\d+[ ]){3}[xX\d])$)");

    /*Kontrola ISBN10*/
    if (regex_match(isbn, regex10)) {
        
        /*Cifry se postupně násobí podle pozice, nakonec se zkontrolují*/
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            sum += (raw[i] - '0') * (10 - i);
        }

        char last = raw[9];
        int checkDigit = (last == 'X' || last == 'x') ? 10 : (isdigit(last) ? last - '0' : -1);
        if (checkDigit == -1) return false;

        sum += checkDigit;
        return (sum % 11 == 0);
    }
    /*Kontrola ISBN13*/
    else if (regex_match(isbn, regex13)) {
        
        int sum = 0;
        for (int i = 0; i < 13; ++i) {
            int digit = raw[i] - '0';
            sum += (i % 2 == 0) ? digit : digit * 3;
        }
        return (sum % 10 == 0);
    }

    return false;
}

string Kniha::regionSlovy() const {
    string regionS = getRegion();
    int region = stoi(regionS);
    string nazevR;
    switch (region){
        case 0:
        case 1:
            nazevR = "anglicky";
            break;
        case 2:
            nazevR = "francouzky";
            break;
        case 3:
            nazevR = "nemecky";
            break;
        case 4:
            nazevR = "japonsky";
            break;
        case 5:
            nazevR = "rusky";
            break;
        case 7:
            nazevR = "cinsky";
            break;
        case 80:
            nazevR = "cesky nebo slovensky";
            break;
        default:
            nazevR = "";
            break; 
    }

    return nazevR;
}

std::ostream &operator<<(std::ostream &os, const Kniha &k){
    os << "ISBN: " << k.getIsbn();
    if(k.isbn.length() == ISBN_13+4){
        os << "     Prefix: " << k.getPrefix(); 
    }
    os << "     Region: " << k.getRegion() << " (" << k.regionSlovy() << ")" << "    Vydavatel: " << k.getVydavatel() << "   Vydani: " << k.getVydani() <<std::endl;
    os << "Autor: " << k.getAuthor() << std::endl;
    os << "Nazev: " << k.getTitle() << std::endl;
    return os;
}

std::vector<string> splitIsbn(const string &isbn){
    std::vector<std::string> parts;
    string cleaned;

    // Nahrazení mezer a pomlček jednotně pomlčkami
    for (char c : isbn) {
        if (c == ' ' || c == '-') {
            cleaned += '-';
        } else {
            cleaned += c;
        }
    }

    std::stringstream ss(cleaned);
    string part;

    while (std::getline(ss, part, '-')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }

    return parts;

}
