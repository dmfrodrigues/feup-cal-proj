#ifndef ENCODED_STRING_H_INCLUDED
#define ENCODED_STRING_H_INCLUDED

#include <string>
#include <iostream>

class encoded_string: public std::string {
public:
    encoded_string();
    encoded_string(const char *s);
};

std::istream& operator>>(std::istream &is,       encoded_string &s);
std::ostream& operator<<(std::ostream &os, const encoded_string &s);

#endif //ENCODED_STRING_H_INCLUDED
