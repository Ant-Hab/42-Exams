#include "bigint.hpp"
#include <algorithm>

// Private Helper
void bigint::trim() {
    size_t first_non_zero = str.find_first_not_of('0');
    if (first_non_zero != std::string::npos) {
        str = str.substr(first_non_zero);
    } else {
        str = "0";
    }
}

// Constructors
bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num) : str(std::to_string(num)) {}

bigint::bigint(const bigint& source) : str(source.str) {}

// Assignment
bigint& bigint::operator=(const bigint& source) {
    if (this != &source) {
        this->str = source.str;
    }
    return *this;
}

// Addition
bigint bigint::operator+(const bigint& other) const {
    std::string s1 = this->str;
    std::string s2 = other.str;
    
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    
    std::string res;
    int carry = 0;
    size_t max_len = std::max(s1.length(), s2.length());
    
    for (size_t i = 0; i < max_len || carry; ++i) {
        int d1 = (i < s1.length()) ? s1[i] - '0' : 0;
        int d2 = (i < s2.length()) ? s2[i] - '0' : 0;
        
        int sum = d1 + d2 + carry;
        carry = sum / 10;
        res.push_back((sum % 10) + '0');
    }
    
    std::reverse(res.begin(), res.end());
    
    bigint result;
    result.str = res;
    return result;
}

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

// Increment
bigint& bigint::operator++() {
    *this = *this + bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;
    ++(*this);
    return temp;
}

// Shift Operations (unsigned int)
bigint bigint::operator<<(unsigned int n) const {
    if (this->str == "0") return *this;
    
    bigint temp = *this;
    temp.str.append(n, '0');
    return temp;
}

bigint bigint::operator>>(unsigned int n) const {
    bigint temp = *this;
    if (n >= temp.str.length()) {
        temp.str = "0";
    } else {
        temp.str.erase(temp.str.length() - n, n);
    }
    temp.trim(); // Ensure no leading zeros if shifting leaves them
    return temp;
}

bigint& bigint::operator<<=(unsigned int n) {
    *this = *this << n;
    return *this;
}

bigint& bigint::operator>>=(unsigned int n) {
    *this = *this >> n;
    return *this;
}

// Shift Operations (bigint)
bigint bigint::operator<<(const bigint& other) const {
    // using std::stoul converts string to unsigned long
    return *this << std::stoul(other.str);
}

bigint bigint::operator>>(const bigint& other) const {
    return *this >> std::stoul(other.str);
}

bigint& bigint::operator<<=(const bigint& other) {
    *this = *this << std::stoul(other.str);
    return *this;
}

bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> std::stoul(other.str);
    return *this;
}

// Comparisons
bool bigint::operator==(const bigint& other) const {
    return this->str == other.str;
}

bool bigint::operator!=(const bigint& other) const {
    return !(*this == other);
}

bool bigint::operator<(const bigint& other) const {
    // If lengths differ, the shorter string is the smaller number
    if (this->str.length() != other.str.length()) {
        return this->str.length() < other.str.length();
    }
    // If lengths are equal, lexicographical comparison works
    return this->str < other.str;
}

bool bigint::operator>(const bigint& other) const {
    return other < *this; 
}

bool bigint::operator<=(const bigint& other) const {
    return !(other < *this);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}

// Output Stream
std::ostream& operator<<(std::ostream& output, const bigint& obj) {
    output << obj.str;
    return output;
}