#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class String {

private:
	size_t m_length;
	char* m_string;
	size_t m_capacity;

	void resize() {

		if (m_length >= m_capacity) {
			m_capacity = 2 * m_length;
			char* new_string = new char[m_capacity]();
			memcpy(new_string, m_string, m_capacity);
			delete[] m_string;
			m_string = new_string;
		}
		else if (m_length < m_capacity / 2 && m_length > 1) {
			m_capacity /= 2;
			char* new_string = new char[m_capacity]();
			memcpy(new_string, m_string, m_capacity);
			delete[] m_string;
			m_string = new_string;
		}
	}

public:

	String()
		:m_length(0), m_string(new char[1]()), m_capacity(1)
	{
	}

	~String() {
		delete[] m_string;
	}

	String(const char* string)
		:m_length(strlen(string)), m_capacity(strlen(string) + 1)
	{
		m_string = new char[m_capacity]();
		memcpy(m_string, string, m_length + 1);
	}

	String(const String& other) {
		m_length = other.m_length;
		m_capacity = other.m_capacity;
		m_string = new char[m_capacity];

		memcpy(m_string, other.m_string, m_capacity);
	}

	String& operator=(const String& string) {

		if (this != &string) {
			m_length = string.m_length;
			m_capacity = string.m_capacity;
			delete[] m_string;
			m_string = new char[m_capacity]();
			strcpy(m_string, string.m_string);
		}
		return *this;
	}

	String& operator=(const char* string) {

		if (string != nullptr) {
			m_length = strlen(string);
			m_capacity = m_length +1;
			delete[] m_string;
			m_string = new char[m_capacity]();
			if (m_length > 0) {
				strcpy(m_string, string);
			}

		}
		else {
			clear();
		}
		return *this;

	}

	bool operator==(String& other) {
		return strcmp(m_string, other.m_string) == 0;
	}

	bool operator==(const char* other) {
		return strcmp(m_string, other) == 0;
	}

	bool operator!=(const char* other) {
		return strcmp(m_string, other) != 0;
	}

	void pop_back() {
		if (m_length > 0) {
			m_string[m_length] = '\0';
			m_length--;
			
			resize();
		}
	}

	char& operator[](size_t index) {
		return m_string[index];
	}

	void print() {
		std::cout << m_string << std::endl;
	}

	String append(char to_append) {
		m_length += 1;
		resize();
		strncat(m_string, &to_append, 1);
		return *this;
	}

	String& append(const char* to_append) {

		size_t length = strlen(to_append);
		m_length += length;
		resize();
		strcat(m_string, to_append);
		return *this;
	}

	String& operator+(const char* to_append) {
		return append(to_append);
	}

	size_t length() {
		return m_length;
	}

	int find(const char* str) {
		size_t length = strlen(str);

		size_t cout = 0;
		for (size_t i = 0; i < m_length; i++) {
			for (size_t k = 0; k < length; k++) {
				if (m_string[i + k] == str[k]) cout++;
				else {
					i += cout;
					cout = 0;
					break;
				}
				if (cout == length) return i;
			}
		}
		return -1;
	}

	bool contains(const char* substring) {
		return find(substring) >= 0;
	}

	void toUpperCase() {
		for (size_t i = 0; i < m_length; i++) {
			m_string[i] = toupper(m_string[i]);
		}
	}
	void toLowerCase() {
		for (size_t i = 0; i < m_length; i++) {
			m_string[i] = tolower(m_string[i]);
		}
	}

	//from index to end
	String slice(size_t index) {
		return substr(index, m_length);
	}

	//from 0 to index
	String cut(size_t index) {
		return substr(0, index);
	}

	String substr(int start, int end) {
		size_t size = end - start;
		char *new_string = new char[size + 1]();
		strncpy(new_string, m_string + start, size);
		new_string[size] = '\0';
		return String(new_string);
	}

	char at(size_t index) {
		return m_string[index];
	}

	char* c_str() {
		return m_string;
	}

	void clear() {
		delete[] m_string;
		m_string = new char[1]();
		m_capacity = 1;
		m_length = 0;
	}

	int countChar(char c) {
		int count = 0;
		for (size_t i = 0; i < m_length; i++) {
			if (m_string[i] == c) count++;
		}
		return count;
	}

	friend std::ostream& operator<<(std::ostream& os, const String& string);
	friend std::istream& operator>>(std::istream& is, String& out);

	void trim() {
		int start = 0;
		int end = m_length - 1;

		while (m_string[start] == ' ') start++;
		while (m_string[end] == ' ') end--;
		*this = substr(start, end + 1);
	}
};


std::ostream& operator<<(std::ostream& os, const String& string){
	os << string.m_string;
	return os;
}


std::istream& operator>>(std::istream& in, String& out){
	char* buffor = new char[100]();
	in >> buffor;
	out = buffor;
	delete[] buffor;
	return in;
}