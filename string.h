// #pragma once
#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>

class String{
 public :
  explicit String();
  String(const int n, const char c);
  String(const char* temp);
  String(const String& temp);
  String(char c);
  ~String();

  String& operator=(const String& temp);
  bool operator==(const String& temp);
  char& operator[](const int idx);
  const char& operator[](const int idx) const;
  String& operator+= (const char c);
  String& operator+= (const String& temp);
  friend String operator+(const String& str1, const String& str2); // + operator overloading

  void Swap(String& temp);
  size_t length() const;
  void push_back(const char c);
  void pop_back();
  char& front();
  const char& front() const;
  char& back();
  const char& back() const;
  bool empty();
  void clear();
  
  String substr(size_t start, size_t count) const;
  size_t find(const String& substr) const;
  size_t rfind(const String& substr) const;

 private :
  size_t buff_size_, string_size_;
  char *string_;
};

explicit String::String() : buff_size_(1),
                            string_size_(buff_size_ - 1),
                            string_(new char [buff_size_]){
  string_[buff_size_ - 1] = '\0';
}
String::String(const int n, const char c) : buff_size_(n + 1),
                                            string_size_(buff_size_ - 1),
                                            string_ (new char[buff_size_]) {
  memset(string_, c, n);
}
String::String(const char* temp) : buff_size_(strlen(temp) + 1),
                                   string_size_(buff_size_ - 1),
                                   string_(new char[buff_size_]) {
  memset(string_, '\0', buff_size_);
  memcpy(string_, temp, string_size_);
}

String::String(const String& temp) : buff_size_(temp.buff_size_),
                                     string_size_(temp.string_size_),
                                     string_(new char[buff_size_]) {
  memcpy(string_, temp.string_, string_size_);
  string_[string_size_] = '\0';
}
String::String(char c) : buff_size_(2),
                         string_size_(buff_size_ - 1),
                         string_(new char[buff_size_]) {
  string_[0] = c;
  string_[string_size_] = '\0';
}
String::~String() {
  string_size_ = 0;
  buff_size_ = 1;
  delete [] string_;
}

std::istream& operator>>(std::istream& in, String& temp) {
  temp.clear();
  char char_input;
  in.get(char_input);
  do {
    temp.push_back(char_input);
    in.get(char_input);
  } while (!in.eof() && char_input != '\n' && char_input != ' ' && char_input != '\0');
  char_input = '\n';
  return in;
}
std::ostream& operator<<(std::ostream& out, const String& temp) {
  for (size_t i = 0; i < temp.length(); ++i) {
    out << temp[i];
  }
  return out;
}
String& String::operator=(const String& temp) {
  if (this != &temp) {
    String temp_copy = temp;
    String::Swap(temp_copy);
  }
  return *this;
}
bool String::operator==(const String& temp) {
  return strcmp(temp.string_, string_) == 0;
}
char& String::operator[](const int idx) {
  return string_[idx];
}
const char& String::operator[](const int idx) const {
  return string_[idx];
}
String& String::operator+= (const char c) {
  this->push_back(c);
  return *this;
}
String& String::operator+= (const String& temp) {
  for (size_t i = 0; i < temp.string_size_; ++i) {
    this->push_back(temp.string_[i]);
  }
  return *this;
}
String operator+(const String& str1, const String& str2) {
  String ans = str1;
  ans += str2;
  return ans;
}

void String::Swap(String& temp) {
  std::swap(string_size_, temp.string_size_);
  std::swap(buff_size_, temp.buff_size_);
  std::swap(string_, temp.string_);
}
size_t String::length() const {
  return string_size_;
}
void String::push_back(const char c) {
  if (string_size_ + 1 >= buff_size_) {
    String copy = *this;
    delete[] string_;
    buff_size_ *= 2;
    string_ = new char [buff_size_];
    for (size_t i = 0; i < string_size_; ++i) {
      string_[i] = copy.string_[i];
    }
  }
  string_[string_size_++] = c;
  string_[string_size_] = '\0';
}
void String::pop_back() {
  if (string_size_ * 4 <= buff_size_) {
    String copy = *this;
    delete [] string_;
    buff_size_ = (buff_size_ + 1) / 2;
    string_ = new char[buff_size_];
    for (size_t i = 0; i < string_size_; ++i) {
      string_[i] = copy.string_[i];
    }
  }
  string_[--string_size_] = '\0';
}
char& String::front() {
  return string_[0];
}
const char& String::front() const {
  return string_[0];
}
char& String::back() {
  return string_[string_size_ - 1];
}
const char& String::back() const{
  return string_[string_size_ - 1];
}
bool String::empty() {
  return string_size_ == 0;
}
void String::clear() {
  delete [] string_;
  buff_size_ = 1;
  string_size_ = buff_size_ - 1;
  string_ = new char [buff_size_];
  string_[buff_size_ - 1] = '\0';
}
String String::substr(size_t start, size_t count) const{
  String sub_string;
  for (size_t i = start; i < start + count; ++i) {
    sub_string += string_[i];
  }
  return sub_string;
}
size_t String::find(const String& substr) const {
  size_t index = string_size_;
  for (size_t i = 0; i < string_size_; ++i) {
    bool flag = true;
    if (string_[i] == substr[0]) {
      for (size_t j = 0; j < substr.string_size_ && (j + i) < string_size_; ++j) {
        if (string_[j + i] != substr.string_[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        index = i;
        break;
      }
    }
  }
  return index;
}
size_t String::rfind(const String& substr) const {
  size_t length = substr.string_size_;
  char checker = substr[0];
  for (int index = static_cast<int>(string_size_ - 1); index >= 0; --index) {
    bool congruence_of_characters = true;
    if (string_[index] == checker) {
      for (size_t j = 0, k = index; j < length && k < string_size_; ++j, ++k) {
        if (string_[k] != substr[j]) {
          congruence_of_characters = false;
        }
      }
      if (congruence_of_characters) {
        return index;
      }
    }
  }
  return string_size_;
}

#endif