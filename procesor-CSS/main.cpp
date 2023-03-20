#include <iostream>
//#include "stringImp.h"
#include "string.h"
#define ROZ 8


//Implementacja Stringa
class String {

private:
	size_t m_length;
	char* m_string;

public:

	String()
		:m_length(0), m_string(nullptr)
	{
	}

	String& operator=(const String& string) {

		m_length = string.m_length;
		delete[] m_string;
		m_string = new char[m_length + 1];
		//strcpy_s(m_string, m_length + 1, string.m_string);

		for (int i = 0; i < m_length; i++) {
			m_string[i] = string.m_string[i];
		}
		m_string[m_length] = '\0';

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
		//if (m_string == NULL) return false;
		return strcmp(m_string, other.m_string) == 0;
	}

	bool operator==(const char* other) {
		return strcmp(m_string, other) == 0;
	}

	bool operator!=(const char* other) {
		if (m_length == 0 && strlen(other) > 0) return true;

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

	String(const char* string)
		:m_length(strlen(string))
	{
		m_string = new char[m_length + 1];
		memcpy(m_string, string, m_length + 1);
	}

	~String() {
		delete[] m_string;
	}

	//copy constructor
	String(const String& other) {
		m_length = other.m_length;
		m_string = new char[other.m_length + 1];

		if (m_length > 0) {
			memcpy(m_string, other.m_string, m_length + 1);
		}
	}


	char& operator[](size_t index) {
		return m_string[index];
	}

	void print() {
		std::cout << m_string << std::endl;
	}

	String& append(const char* to_append) {

		size_t length = strlen(to_append);

		size_t new_length = m_length + length;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		if (new_string) {

			if (m_length > 0) {
				strcat_s(new_string, new_length + 1, m_string);
			}
			strcat_s(new_string, new_length + 1, to_append);
			delete[] m_string;
			m_string = new_string;
			m_length = new_length;
		}

		return *this;
	}

	String& operator+(const char* to_append) {
		return append(to_append);
	}

	size_t length() {
		return m_length;
	}

	int find_substring(const char* substring) {
		size_t length = strlen(substring);

		size_t cout = 0;
		for (size_t i = 0; i < m_length; i++) {
			for (size_t k = 0; k < length; k++) {
				if (m_string[i + k] == substring[k]) cout++;
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

	bool is_in(const char* substring) {
		return find_substring(substring) >= 0;
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

		if (new_string) {
			strncat_s(new_string, new_length + 1, m_string + index, new_length);
			delete[] m_string;
			m_string = new_string;
			m_length = new_length;
		}
	}

	//from 0 to index
	void cut(size_t index) {
		size_t new_length = index + 1;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		if (new_string) {
			strncat_s(new_string, new_length + 1, m_string, new_length);
			delete[] m_string;
			m_string = new_string;
			m_length = new_length;
		}
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
		m_length = 1;
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





//struct przetrzymuj¹cy atrybuty (property : value)
struct atrybut {
	String property;
	String value;

	atrybut()
		:property(""), value("")
	{
	}

	atrybut(String property, String value)
		:property(property), value(value)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const atrybut& obj)
	{
		os << obj.property << ":" << obj.value;
		return os;
	}
};


//node dla listy pojedyczej
template<typename T>
struct NodeList {


public:
	T data;
	NodeList* next;

	NodeList()
		: next(nullptr)
	{
	}

	NodeList(T data)
		: next(nullptr), data(data)
	{
	}
};


template<typename T>
class ListSingleLinked {

private:
	NodeList<T>* head;
public:


	ListSingleLinked()
		: head(nullptr)
	{
	}

	//git
	void add(T data) {

		if (head == nullptr) {
			head = new NodeList<T>(data);
		}
		else {
			NodeList<T>* temp = head;	
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = new NodeList<T>(data);
		}
	}

	//git
	void print() {
		NodeList<T>* temp = head;

		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	//git
	int getLen() {
		NodeList<T>* temp = head;
		int len = 0;
		while (temp != nullptr) {
			len++;
			temp = temp->next;
		}
		return len;
	}

	//nm czy git
	atrybut* findByNazwa(atrybut a) {
		NodeList<atrybut>* temp = head;
		while (temp != nullptr) {
			if (temp->data.property == a.property)
				return &(temp->data);
			temp = temp->next;
		}
		return nullptr;
	}
};


class Block {

private:
	ListSingleLinked<String> selektor;
	ListSingleLinked<atrybut> atrybuty;
public:
	bool used;

	Block()
		:used(false)
	{
	}

	Block& operator=(const Block& b) {
		selektor = b.selektor;
		atrybuty = b.atrybuty;
		return *this;
	}

	void addAtribute(atrybut a) {
		//sprawdzic czy juz taki atrybut jest jak tak to zamienic
		//atrybut* k = atrybuty.findByNazwa(a);
		//if (k) {
			//k->value = a.value;
		//}
		//else {
			atrybuty.add(a);
			//atrybuty.print();
		//}
	}
	void addSelektor(String selector) {
		selektor.add(selector);
	}

	size_t getSelectorLen() {
		return selektor.getLen();
	}

	void print() {
		selektor.print();
		atrybuty.print();
	}
};


//Node dla double linked list
struct BlocksNode {
	
public:
	Block* blocks;
	BlocksNode* next;
	BlocksNode* prev;
	size_t size;

	BlocksNode()
		:blocks(new Block[ROZ]), next(nullptr), prev(nullptr), size(0)
	{
	}
};


class ListDoubleLinked {

private:
	BlocksNode* head;
public:

	ListDoubleLinked()
		:head(nullptr)
	{
	}

	void addAtEnd(Block block) {
		BlocksNode* temp = new BlocksNode;
		if (head == nullptr) {
			head = new BlocksNode;
		}
	}

	void addBlock(Block block) {
		if (head == nullptr) {
			head = new BlocksNode;
		}
		BlocksNode* temp = head;
		while (temp->size >= ROZ) {
			if (temp->next == nullptr) {
				BlocksNode* t = new BlocksNode();
				t->prev = temp;
				temp->next = t;
				temp = t;
			}
			else {
				temp = temp->next;
			}
		}
		if (temp->size < ROZ) {
			for (int i = 0; i < ROZ; i++) {
				if (temp->blocks[i].used == false) {
					temp->blocks[i] = block;
					temp->blocks[i].used = true;
					temp->size++;
					break;
				}
			}
		}
	}

	void printBlocks() {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
				if (temp->blocks[i].used == true) {
					temp->blocks[i].print();
				}
			}
			temp = temp->next;
		}
	}

	~ListDoubleLinked() {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			delete[] temp->blocks;
			temp = temp->next;
		}
	}

	//liczba sekcji
	size_t numberOfSections() {
		size_t result = 0;

		BlocksNode* tmp = head;

		while (tmp != nullptr) {
			result += head->size;
			tmp = tmp->next;
		}

		return result;
	}

	int numberOfSelectorsInSection(int n) {
		int current = 0;
		BlocksNode* tmp = head;

		while (n > ROZ) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return -1;
			}
			n -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == n) {
				return tmp->blocks[k - 1].getSelectorLen();
			}
		}
		return 0;
	};
};


int main() {
	ListDoubleLinked bloki;
	bool selectors = true;
	bool atributes = false;
	bool commands = false;
	
	String tmp;
	Block* block = new Block();
	
	while (std::cin >> tmp) {

		if (selectors) {
			if (tmp == "{") {
				selectors = false;
				atributes = true;
				tmp = "";
			}
			else if (tmp.at(0) == '{') {
				selectors = false;
				atributes = true;
			}
			else if (tmp == "????") {
				selectors = false;
				atributes = false;
				commands = true;
				continue;
			}
			else {
				if (tmp.at(tmp.length() - 1) == ',') {
					tmp.pop_back();
				}
				if (tmp != " ") {
					block->addSelektor(tmp);
				}
			}
		}
		if (atributes) {
			String value;
			bool running = true;
			while (tmp != "}" && value != "}" && running) {
				if (tmp != "") {
					tmp.slice(1);
					tmp.pop_back();
				}
				else {
					std::cin >> tmp;
					if (tmp == "}") break;
					tmp.pop_back();
				}

				String s;

				std::cin >> value;
				s.append(value.c_str());

				while (value.at(value.length() - 1) != ';' && value.at(value.length() - 1) != '}') {
					std::cin >> value;
					s.append(" ");
					s.append(value.c_str());

				}

				if (s.at(s.length() - 1) == '}') {
					s.pop_back();
					running = false;
				}

				if (s.at(s.length() - 1) == ';') {
					s.pop_back();
				}

				if (tmp != "" && value != "") {
					block->addAtribute(atrybut(tmp, s));
				}
				tmp = "";
			}
			bloki.addBlock(*block);
			delete block;
			block = new Block();
			atributes = false;
			commands = false;
			selectors = true;
		}
		else if (commands) {

			if (tmp == "?") {
				std::cout << "? == " << bloki.numberOfSections() << std::endl;
			}
			else if (tmp == "****") {
				commands = false;
				selectors = true;
				atributes = false;
			}
			else if (tmp.is_in(",S,?")) {
				
				std::cout << "w S,?" << std::endl;
				int n;
				n = atoi(tmp.c_str());
				int result = bloki.numberOfSelectorsInSection(n);
				if (result != -1) {
					std::cout << n << ",S,? == " << result << std::endl;
				}
			}
		}
	}

	return 0;
}