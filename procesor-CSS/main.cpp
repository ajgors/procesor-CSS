#include <iostream>
//#include "stringImp.h"
#include "string.h"
#define ROZ 8


//sekcje jako listy 2 


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


	//nowe

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
	String(const String& other)

	{
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

	size_t find_substring(const char* substring) {
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
		size_t new_length = index+1;

		char* new_string = new char[new_length + 1];
		std::memset(new_string, 0, new_length + 1);

		if (new_string) {
			strncat_s(new_string, new_length + 1, m_string, new_length);
			delete[] m_string;
			m_string = new_string;
			m_length = new_length;
		}

	}

	//substring

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
	//friend pozwala funkcji ktora pobiera obiekt miec dostêp do prywatnych pól
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

struct atrybut {
	//String nazwa;
	String nazwa;
	String wartosc;


	atrybut()
		:nazwa(""), wartosc("")
	{

	}

	atrybut(String nazwa, String wartosc)
		:nazwa(nazwa), wartosc(wartosc)
	{

	}

	friend std::ostream& operator<<(std::ostream& os, const atrybut& obj)
	{
		os << obj.nazwa << ":" << obj.wartosc;
		return os;
	}

};

template<typename T>
class List {
	
private:
	T data;
	List* next;
public:


	List()
		: next(nullptr)
	{
	
	}

	List(T data) {
		this->data = data;
		this->next = nullptr;
	}

	void add(T data) {
		List* temp = this;

		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new List(data);
	}

	void print() {
		List* temp = this->next;

		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	int getLen() {
		List* temp = this->next;
		int len = 0;
		while (temp != nullptr) {
			len++;
			temp = temp->next;
		}
		return len;
	}

	atrybut* findByNazwa(String nazwa) {
		List* temp = this;
		while (temp != nullptr) {
			if (temp->data.nazwa == nazwa)
				return &(temp->data);
			temp = temp->next;
		}
		return nullptr;
	}
};



class Block {
	
private: 
	List<String> selektor;
	List<atrybut> atrybuty;
public:
	
	bool used;
	Block()
		:used(false)
	{

	}

	Block(String selektor, String nazwa, String value)
		:selektor(selektor), atrybuty(atrybut(nazwa,value)), used(true)
	{
	}

	Block(const Block& b) {
		selektor = b.selektor;
		atrybuty = b.atrybuty;
	}
	
	Block& operator=(const Block& b) {
		selektor = b.selektor;
		atrybuty = b.atrybuty;
		return *this;
	}

	void addAtribute(atrybut a) {
		//sprawdzic czy juz taki atrybut jest jak tak to zamienic

		atrybut* k = atrybuty.findByNazwa(a.nazwa);
		if (k) {
			k->wartosc = a.wartosc;
		}
		else {
			atrybuty.add(a);
		}
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


struct Node {
	

public:
	Block* blocks;
	Node* next;
	Node* prev;
	size_t size;

	Node()
		:blocks(new Block[ROZ]), next(nullptr), prev(nullptr), size(0)
	{
	}

};

//template<typename T>
class ListLinked {

private:
	Node* head;
public:

	ListLinked()
		:head(nullptr)
	{
	}

	void addAtEnd(Block block) {
		Node* temp = new Node;
		if (head == nullptr) {
			head = new Node;
		}

	}

	void addBlock(Block block) {
		Node* temp = head;
		if (head == nullptr) {
			head = new Node;
			temp = head;
		}
		while (temp->size >= ROZ) {
			if (temp->next == nullptr) {
				Node* t = new Node();
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
		Node* temp = head;
		while (temp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
				if (temp->blocks[i].used == true) {
					temp->blocks[i].print();
				}
			}
			temp = temp->next;
		}
	}

	~ListLinked() {
		Node* temp = head;
		while (temp != nullptr) {
			delete[] temp->blocks;
			temp = temp->next;
		}
	}


	//liczba sekcji
	size_t numberOfSections() {
		size_t result = 0;

		Node* tmp = head;

		while (tmp != nullptr) {
			result += head->size;
			tmp = tmp->next;
		}

		return result;
	}

	int numberOfSelectorsInSection(int n) {
		int current = 0;
		Node* tmp = head;

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
				return tmp->blocks[k-1].getSelectorLen();
			}
		}
		return 0;
	};
};

// zle zapisuje margin : 4p 4p 4p 4p
// robi margin : 4p, 4p:4p
// while char != ; or } wczytuj dalej tmp.apped -> 4p -> 4p.append 4p = 4p 4p


int main() {
	ListLinked bloki;
	bool selectors = true;

	bool atributes = false;
	bool commands = false;

	String tmp;
	while (std::cin >> tmp) {
			
		Block block;
		if (selectors) {
			bool end = false;
			block.used = true;
			//while (true) {
				//char* buffor = new char[50];
				//std::cin >> buffor;
				//std::cin >> tmp;
				//std::cout << tmp;
			//std::cout << "w selektorach";
				//tmp = buffor;
				if (tmp == "{") {
					selectors = false;
					atributes = true;
					tmp = "";
					//break;
				}
				else if (tmp.at(0) == '{') {
					selectors = false;
					atributes = true;
					//break;
				}
				else if (tmp == "?") {
					//end = true;
					//break;
				}
				else if (tmp == "????") {
					//std::cout << "hello";
					selectors = false;
					atributes = false;
					commands = true;
					continue;
					//break;
				}
				else {
					if (tmp.at(tmp.length()-1) == ',') {
						tmp.pop_back();
					}
					if (tmp != " ") {
						block.addSelektor(tmp);
					}
				}
		/*	}
			if (end) break;*/
		}
		if (atributes) {
			String value;
			bool running = true;
			while (tmp != "}" && value != "}" && running ) {
				//std::cout << "w atrybutach";
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


				if (s.at(s.length() -1) == '}') {
					s.pop_back();
					running = false;
				}

				//Ÿle jest zmieniana m_length przy append naprawione

				if (s.at(s.length() -1) == ';') {
					s.pop_back();
				}

				if (tmp != "" && value != "") {
					block.addAtribute(atrybut(tmp, s));
				}
				tmp = "";
			}
			block.used = true;
			bloki.addBlock(block);
			atributes = false;
			commands = false;
			selectors = true;
		}
		else if (commands) {
			//std::cout << "w komendach";
			//std::cin >> tmp;
			//std::cout << tmp << std::endl;
			if (tmp == "?") {
				std::cout << "? == " << bloki.numberOfSections() << std::endl;
			}
			else if (tmp == "****") {
				commands = false;
				selectors = true;
				atributes = false;
			}
			else if (tmp.is_in("S,?") != -1) {
				int n;
				//tmp.cut(tmp.length() - 4); //remove S,?
				n = atoi(tmp.c_str());
				int result = bloki.numberOfSelectorsInSection(n);
				std::cout << "------" << n << std::endl;
				
				if (result != -1) {
					std::cout << n << ",S,? == " << result << std::endl;
				}
			}
			
		}

	}
	
	return 0;
}