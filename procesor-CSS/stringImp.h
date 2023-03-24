#include <iostream>

class String {

private:
	size_t m_length;
	char* m_string;
public:

	String()
		:m_length(0), m_string(nullptr)
	{
	}

	~String() {
		delete[] m_string;
	}

	String(const char* string)
		:m_length(strlen(string))
	{
		m_string = new char[m_length + 1];
		memcpy(m_string, string, m_length + 1);
	}

	String(const String& other) {
		m_length = other.m_length;
		m_string = new char[other.m_length + 1];

		if (m_length > 0) {
			memcpy(m_string, other.m_string, m_length + 1);
		}
	}

	String& operator=(const String& string) {

		if (this != &string) {
			m_length = string.m_length;
			delete[] m_string;
			m_string = new char[m_length + 1];
			strcpy_s(m_string, m_length + 1, string.m_string);
		}
		return *this;
	}

	String& operator=(const char* string) {

		m_length = strlen(string);
		delete[] m_string;
		m_string = new char[m_length + 1];
		strcpy_s(m_string, m_length + 1, string);

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
			m_length--;
			char* new_string = new char[m_length + 1];
			memcpy(new_string, m_string, m_length);
			new_string[m_length] = '\0';
			delete[] m_string;
			m_string = new_string;
		}
	}

	char& operator[](size_t index) {
		return m_string[index];
	}

	void print() {
		std::cout << m_string << std::endl;
	}

	String append(char to_append) {

		size_t new_length = m_length + 1;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		if (m_length > 0) {
			strcat_s(new_string, new_length + 1, m_string);
		}
		strncat_s(new_string, new_length + 1, &to_append, 1);

		delete[] m_string;
		m_string = new_string;
		m_length = new_length;
		return *this;
	}

	String& append(const char* to_append) {

		size_t length = strlen(to_append);
		size_t new_length = m_length + length;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		if (m_length > 0) {
			strcat_s(new_string, new_length + 1, m_string);
		}
		strcat_s(new_string, new_length + 1, to_append);

		delete[] m_string;
		m_string = new_string;
		m_length = new_length;

		return *this;
	}

	String& operator+(const char* to_append) {
		return append(to_append);
	}

	size_t length() {
		return m_length;
	}

	//returns index of searched string start point if not found returns -1
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
	void slice(size_t index) {
		size_t new_length = m_length - index;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		strncat_s(new_string, new_length + 1, m_string + index, new_length);
		delete[] m_string;
		m_string = new_string;
		m_length = new_length;
	}

	//from 0 to index
	void cut(size_t index) {
		size_t new_length = index + 1;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		strncat_s(new_string, new_length + 1, m_string, new_length);
		delete[] m_string;
		m_string = new_string;
		m_length = new_length;
	}

	String substr(int start, int end) {
		String new_string;

		for (int i = start; i < end; i++) {
			new_string.append(m_string[i]);
		}
		return new_string;
	}

	char at(size_t index) {
		return m_string[index];
	}

	char* c_str() {
		return m_string;
	}

	void clear() {
		delete[] m_string;
		m_string = new char[1];
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
};


std::ostream& operator<<(std::ostream& os, const String& string)
{
	os << string.m_string;
	return os;
}


std::istream& operator>>(std::istream& in, String& out)
{
	char* buffer = new char[100];
	memset(buffer, 0, 100);
	in >> buffer;
	out = buffer;
	delete[] buffer;
	return in;
}