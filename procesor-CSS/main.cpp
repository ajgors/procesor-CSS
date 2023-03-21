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
		if (m_string != nullptr) {
			delete[] m_string;
		}
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
		os << obj.property << " : " << obj.value;
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

	NodeList(const T& data)
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

	~ListSingleLinked() {
		NodeList<T>* temp = head;
		while (temp != nullptr) {
			NodeList<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		head = nullptr;
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

	T* findByNazwa(T a);
	bool remove(T a);

	T* getElementByNumber(int number) {
		NodeList<T>* temp = head;
		int i = 1;
		while (temp != nullptr) {
			if (i == number)
				return &temp->data;
			temp = temp->next;
			i++;
		}

		return nullptr;
	}
};

template<>
atrybut* ListSingleLinked<atrybut>::findByNazwa(atrybut a) {
	NodeList<atrybut>* temp = head;
	while (temp != nullptr) {
		if (temp->data.property == a.property)
			return &temp->data;
		temp = temp->next;
	}
	return nullptr;
}

template<>
bool ListSingleLinked<atrybut>::remove(atrybut a) {
	NodeList<atrybut>* temp = head;
	NodeList<atrybut>* t = head->next;
	
	if (head->data.property == a.property) {
		delete head;
		head = t;
		return true;
	}

	while (temp->next != nullptr) {
		if (temp->next->data.property == a.property) {
			NodeList<atrybut>* temp2 = temp->next;

			temp->next = temp->next->next;
			delete temp2;
			break;
		}
		temp = temp->next;
	}


	return false;
}


template<>
bool ListSingleLinked<String>::remove(String a) {
	NodeList<String>* temp = head;
	if (temp->data == a) {
		head = head->next;
		delete temp;
		return true;
	}

	while (temp->next != nullptr) {
		if (temp->next->data == a) {
			temp = temp->next->next;
			delete temp->next;
		}
		temp = temp->next;
	}


	return true;
}


template<>
String* ListSingleLinked<String>::findByNazwa(String a) {
	NodeList<String>* temp = head;
	while (temp != nullptr) {
		if (temp->data == a)
			return &temp->data;
		temp = temp->next;
	}
	return nullptr;
}


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

	Block(const Block& other)
		: selektor(other.selektor), atrybuty(other.atrybuty), used(other.used)
	{
	}

	Block& operator=(const Block& b) {
		selektor = b.selektor;
		atrybuty = b.atrybuty;
		return *this;
	}

	void addAtribute(atrybut a) {
		//sprawdzic czy juz taki atrybut jest jak tak to zamienic

		//chyba dziala
		atrybut* k = atrybuty.findByNazwa(a);
		if (k) {
			k->value = a.value;
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

	size_t getAtributesLen() {
		return atrybuty.getLen();
	}

	void print() {
		selektor.print();
		atrybuty.print();
	}

	String getSelectorByNumber(int i) {


		String* ptr = selektor.getElementByNumber(i);

		if (ptr == nullptr) {
			return "";
		}
		return *ptr;
	}

	String getValueByProperty(atrybut att) {
		atrybut* ptr = atrybuty.findByNazwa(att);
		if (ptr == nullptr) {
			return "";
		}
		return ptr->value;
	}


	bool containsAttribute(String property) {
		atrybut* ptr = atrybuty.findByNazwa(atrybut(property, ""));
		return ptr == nullptr ? false : true;
	}

	bool containsSelector(String selector) {
		String* ptr = selektor.findByNazwa(selector);
		return ptr == nullptr ? false : true;
	}

	bool deleteAll() {
		//usowanie list obiekt zostaje (musi)
		selektor.~ListSingleLinked();
		atrybuty.~ListSingleLinked();
		return true;
	}


	bool removeAttribute(String n) {
		atrybuty.remove(atrybut(n, ""));
		return true;
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

	BlocksNode(const BlocksNode& other)
		:blocks(other.blocks), next(other.next), prev(other.prev), size(other.size)
	{
	}

	~BlocksNode()
	{
		delete[] blocks;
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

	void addAtEnd(const Block& block) {
		BlocksNode* temp = new BlocksNode;
		if (head == nullptr) {
			head = new BlocksNode;
		}
	}

	void addBlock(Block& block) {
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
			result += tmp->size;
			tmp = tmp->next;
		}

		return result;
	}

	int numberOfSelectorsInSection(int n) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (n > tmp->size) {
			n -= tmp->size;
			tmp = tmp->next;
			if (tmp == nullptr) {
				return 0;
			}
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


	int numberOfAtributesInSection(int n) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (n > tmp->size) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return 0;
			}
			n -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == n) {
				return tmp->blocks[k - 1].getAtributesLen();
			}
		}
		return 0;
	}

	//find j-th selector in i-th section
	String findSelectorInBlock(int index, int j) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (index > tmp->size) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return "";
			}
			index -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == index) {
				return tmp->blocks[k - 1].getSelectorByNumber(j);
			}
		}
		return "";
	};

	String findValueInSectionByPropertyName(int index, String property) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (index > tmp->size) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return "";
			}
			index -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == index) {
				return tmp->blocks[k - 1].getValueByProperty(atrybut(property, ""));
			}
		}
		return "";
	}

	int numberOfAtributes(String property) {
		BlocksNode* tmp = head;
		int count = 0;
		while (tmp != nullptr) {
			for (int i = 0, k = 0; i < ROZ; i++) {
				if (tmp->blocks[i].used == true) {
					if (tmp->blocks[i].containsAttribute(property)) {
						count++;
					}
				}
			}
			tmp = tmp->next;
		}
		return count;
	};

	int numberOfSelectorOfName(String selector) {
		BlocksNode* tmp = head;
		int count = 0;
		while (tmp != nullptr) {
			for (int i = 0, k = 0; i < ROZ; i++) {
				if (tmp->blocks[i].used == true) {
					if (tmp->blocks[i].containsSelector(selector)) {
						count++;
					}
				}
			}
			tmp = tmp->next;
		}
		return count;
	}

	bool deleteBlock(int index) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (index > tmp->size) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return false;
			}
			index -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == index) {
				tmp->size--;
				tmp->blocks[k - 1].used = false;
				tmp->blocks[k - 1].deleteAll();
				break;
				//tmp->blocks[k - 1].used = false;
			}

		}

		//usuwanie wezla jesli jest pusty
		if (tmp != head) {
			if (tmp->size == 0) {
				if (tmp->next != nullptr) {

					if (tmp->prev != nullptr) {
						tmp->prev->next = tmp->next;

					}
					tmp->next->prev = tmp->prev;
				}
				delete tmp;
			}
		}

		return true;
	}


	bool removeInIthBlockAttribute(int index, String n) {
		BlocksNode* tmp = head;

		//while (n > ROZ) {
		while (index > tmp->size) {
			tmp = tmp->next;
			if (tmp == nullptr) {
				return false;
			}
			index -= tmp->size;
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (tmp->blocks[i].used == true) {
				k++;
			}
			if (k == index) {
				tmp->blocks[k - 1].removeAttribute(n);
				if (tmp->blocks[k - 1].getAtributesLen() == 0) {
					tmp->blocks[k - 1].deleteAll();
					tmp->size--;
					tmp->blocks->used = false;
				}
				break;
			}

		}
		//usuwanie wezla jesli jest pusty
		if (tmp != head) {
			if (tmp->size == 0) {
				if (tmp->next != nullptr) {

					if (tmp->prev != nullptr) {
						tmp->prev->next = tmp->next;

					}
					tmp->next->prev = tmp->prev;
				}
				delete tmp;
			}
		}

		return true;
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
			//delete block;
			block = new Block();
			atributes = false;
			commands = false;
			selectors = true;
		}
		else if (commands) {

			if (tmp == "?") {
				std::cout << "? == " << bloki.numberOfSections() << std::endl;
			}
			if (tmp == ".") {
				bloki.printBlocks();
			}
			else if (tmp == "****") {
				commands = false;
				selectors = true;
				atributes = false;
			}
			else if (tmp.is_in(",S,?")) {
				// i, S, ? – wypisz liczbê selektorów dla sekcji nr i(numery zaczynaj¹ siê od 1), jeœli nie ma takiego bloku pomiñ;
				int n = atoi(tmp.c_str());

				if (n == 0) {
					//z,S,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ selektora z. Mo¿liwe jest 0;
					tmp.cut(tmp.length() - 5);
					int result = bloki.numberOfSelectorOfName(tmp);

					std::cout << tmp << ",S,? == " << result << std::endl;
				}
				else {
					int result = bloki.numberOfSelectorsInSection(n);
					if (result != 0) {
						std::cout << n << ",S,? == " << result << std::endl;
					}
				}


			}
			else if (tmp.is_in(",A,?")) {
				// wypisz liczbê atrybutów dla sekcji nr i, jeœli nie ma takiego bloku lub sekcji pomiñ;
				int n = atoi(tmp.c_str());

				if (n == 0) {
					//n, A, ? – wypisz ³¹czn¹(dla wszystkich bloków) liczbê wyst¹pieñ atrybutu nazwie n. (W ramach
					//pojedynczego bloku duplikaty powinny zostaæ usuniête na etapie wczytywania).Mo¿liwe jest 0;
					tmp.cut(tmp.length() - 5);

					int result = bloki.numberOfAtributes(tmp);
					std::cout << tmp << ",A,? == " << result << std::endl;
				}
				else {
					int result = bloki.numberOfAtributesInSection(n);
					if (result != 0) {
						std::cout << n << ",A,? == " << result << std::endl;
					}
				}

			}
			else if (tmp.is_in(",S,")) {

				//i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynaj¹ siê od 1) jeœli nie
				// ma sekcji lub selektora pomiñ;

				int i = atoi(tmp.c_str()); //find first number
				int j = atoi(tmp.c_str() + tmp.find_substring(",") + 3); //find third number
				String result = bloki.findSelectorInBlock(i, j);

				if (result.length() > 0) {
					std::cout << i << ",S," << j << " == " << result << std::endl;
				}
			}
			else if (tmp.is_in(",A,")) {
				// i, A, n – wypisz dla i - tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;

				int i = atoi(tmp.c_str()); //find first number
				String n = tmp.c_str() + tmp.find_substring(",") + 3;
				String result = bloki.findValueInSectionByPropertyName(i, n);

				if (result.length() > 0) {
					std::cout << i << ",A," << n << " == " << result << std::endl;
				}
			}
			else if (tmp.is_in(",E,")) {

			}
			else if (tmp.is_in(",D,*")) {
				//tmp.cut(tmp.length() - 5);
				int i = atoi(tmp.c_str());

				bool r = bloki.deleteBlock(i);

				if (r) {
					std::cout << i << ",D,*" << " == deleted" << std::endl;

				}
			}
			else if (tmp.is_in(",D,")) {
				int i = atoi(tmp.c_str()); //find first number
				String n = tmp.c_str() + tmp.find_substring(",") + 3;

				bool r = bloki.removeInIthBlockAttribute(i, n);

				if (r) {
					std::cout << i << ",D," << n << " == deleted" << std::endl;

				}
			}

		}
	}

	return 0;
}