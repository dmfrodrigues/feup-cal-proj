#include "encoded_string.h"

#include <iomanip>

encoded_string::encoded_string():std::string(){}
encoded_string::encoded_string(const char *s):std::string(s){}

std::istream& operator>>(std::istream &is,       encoded_string &s){
    s = "";
    std::string str; is >> str;
    size_t i = 0;
    while(i < str.size()){
        if(str[i] == '%'){
            if(i+2 >= str.size()) throw std::invalid_argument("invalid argument "+str);
            std::stringstream ss;
            ss << std::hex << str.substr(i+1,2);
            int a; ss >> a;
            s += char(a);
            i += 3;
        }else{
            s += str[i++];
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const encoded_string &s){
    os.fill('0');
    os << std::hex;
    for(const char &c:s){
        if(isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            os << c;
        }else{
            os << std::uppercase << '%'
               << std::setw(2) << int((unsigned char)c)
               << std::nouppercase;
        }
    }
    return os;
}
