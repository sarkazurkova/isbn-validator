//
// Created by student on 17.03.2025.
//

#ifndef ISBN_KNIHA_H
#define ISBN_KNIHA_H
#include <string>
#include <vector>
using std::string;

#define MAXSTRING 150
#define ISBN_10 10
#define ISBN_13 13
//#define X 10

class Kniha {
public:
    Kniha();
    Kniha(string,string,string);
    ~Kniha();
    string getIsbn()const;
    string getTitle()const;
    string getAuthor()const;
    bool setIsbn(const string&);
    bool setTitle(const string&);
    bool setAuthor(const string&);
    bool setKniha(const string&, const string&, const string&);

    string getPrefix()const;
    string getRegion()const;
    string getVydavatel()const;
    string getVydani()const;
    string getIsbnNum()const;
    bool isbnValidation();
    string regionSlovy()const;
    friend std::ostream& operator<<(std::ostream& os, const Kniha& k);
    friend std::vector<string> splitIsbn (const string &);
    Kniha& operator =(const Kniha&);
    bool operator ==(const Kniha&)const;

private:
    string isbn;
    string title;
    string author;

};

#endif //ISBN_KNIHA_H
