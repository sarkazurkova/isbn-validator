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

bool Kniha::setKniha(const string& isbn, const string& title, const string& author)
{
    if (!setIsbn(isbn) | !setTitle(title) | !setAuthor(author)) {
        return false;
    }
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    return true;
}

//nastaví isbn
bool Kniha::setIsbn(const string &isbn) {
    if(isbn.length() == ISBN_10 + 3){
        this->isbn = isbn;
        if (!isbnValidation()) {
            this->isbn = "";
            return false;
        }
        return true;
    }
    if(isbn.length() == ISBN_13 + 4){
        this->isbn = isbn;
        if (!isbnValidation()) {
            this->isbn = "";
            return false;
        }
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

//Získa prefix z isbn pokud je to ISBN-13
string Kniha::getPrefix() const {
    std::vector<string> parts = splitIsbn(this->isbn);
    return parts[0];
}


//Odstraní pomlčky nebo mezery v isbn
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

/*Vrací část isbn s regionem*/
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

/*Vrací část isbn s vydavatelem*/
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

/*Vrací část isbn s číslem vydání*/
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

/*Metoda pro validaci ISBN pomocí regulárních výrazů*/
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

/*Switch vrací region slovy podle přiděleného čísla jazyku nebo regionu*/
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

/*přetížení operátoru výpisu << */
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

std::vector<string> splitIsbn(const string& isbn) {
    std::vector<std::string> parts;
    string cleaned;

    // Nahrazení mezer a pomlček jednotně pomlčkami
    for (char c : isbn) {
        if (c == ' ' || c == '-') {
            cleaned += '-';
        }
        else {
            cleaned += c;
        }
    }
}

/*přetížení operátoru = (přiřazování)*/
Kniha& Kniha::operator=(const Kniha& k) {
    // kontrola totožnosti objektu
    if (this != &k) {
        setKniha(k.getIsbn(), k.getTitle(), k.getAuthor());
    }
    return *this;
}

/*přetížení operátoru == (porovnání)*/
bool Kniha::operator==(const Kniha &k) const
{
    if (this->isbn == k.isbn && this->title == k.title && this->author == k.author) {
        return true;
    }
    return false;
}
