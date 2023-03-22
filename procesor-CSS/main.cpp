#include <iostream>
//#include "stringImp.h"
#include "string.h"
#define ROZ 8


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
		m_length = 1;
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


struct Atrybut {
	String property;
	String value;

	Atrybut()
		:property(""), value("")
	{
	}

	Atrybut(String property, String value)
		:property(property), value(value)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Atrybut& obj)
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

	void print() {
		NodeList<T>* temp = head;

		while (temp != nullptr) {
			std::cout << temp->data << ", ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

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
Atrybut* ListSingleLinked<Atrybut>::findByNazwa(Atrybut a) {
	NodeList<Atrybut>* temp = head;
	while (temp != nullptr) {
		if (temp->data.property == a.property)
			return &temp->data;
		temp = temp->next;
	}
	return nullptr;
}

template<>
bool ListSingleLinked<Atrybut>::remove(Atrybut a) {
	NodeList<Atrybut>* temp = head;
	NodeList<Atrybut>* t = head->next;

	if (head->data.property == a.property) {
		delete head;
		head = t;
		return true;
	}

	while (temp->next != nullptr) {
		if (temp->next->data.property == a.property) {
			NodeList<Atrybut>* temp2 = temp->next;

			temp->next = temp->next->next;
			delete temp2;
			return true;
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
			return &(temp->data);
		temp = temp->next;
	}
	return nullptr;
}


class Block {

private:
	ListSingleLinked<String> selektor;
	ListSingleLinked<Atrybut> atrybuty;
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
		used = b.used;
		return *this;
	}

	void addAtribute(Atrybut a) {
		Atrybut* k = atrybuty.findByNazwa(a);
		if (k != nullptr) {
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
		std::cout << "Selectors: ";
		selektor.print();
		std::cout << "Attributes: ";
		atrybuty.print();
	}

	String getSelectorByNumber(int i) {

		String* ptr = selektor.getElementByNumber(i);

		if (ptr == nullptr) {
			return "";
		}
		return *ptr;
	}

	String getValueByProperty(Atrybut att) {
		Atrybut* ptr = atrybuty.findByNazwa(att);
		if (ptr == nullptr) {
			return "";
		}
		return ptr->value;
	}

	bool containsAttribute(String property) {
		Atrybut* ptr = atrybuty.findByNazwa(Atrybut(property, ""));
		return ptr == nullptr ? false : true;
	}

	bool containsSelector(String& selector) {
		String* ptr = selektor.findByNazwa(selector);
		return ptr == nullptr ? false : true;
	}

	void deleteAll() {
		selektor.~ListSingleLinked();
		atrybuty.~ListSingleLinked();
	}

	bool removeAttribute(String n) {
		return atrybuty.remove(Atrybut(n, ""));
	}
};


struct BlocksNode {

public:
	Block* blocks;
	BlocksNode* next;
	BlocksNode* prev;
	size_t size;
	size_t usedCount;

	BlocksNode()
		:blocks(new Block[ROZ]), next(nullptr), prev(nullptr), size(0), usedCount(0)
	{
	}

	BlocksNode(const BlocksNode& other)
		:blocks(other.blocks), next(other.next), prev(other.prev), size(other.size), usedCount(other.usedCount)
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

	~ListDoubleLinked() {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			delete[] temp->blocks;
			temp = temp->next;
		}
	}

	BlocksNode* getBlocksNodeByBlockNumber(int n) {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			if (n > temp->usedCount) {
				n -= temp->usedCount;
			}
			else {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	Block* getBlockByNumber(int n) {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			if (n > temp->usedCount) {
				n -= temp->usedCount;
			}
			else {
				for (int i = 0, c = 0; i < ROZ; i++) {
					if (temp->blocks[i].used == true) {
						c++;
					}
					if (n == c) {
						return &temp->blocks[i];
					}
				}
			}
			temp = temp->next;
		}
		return nullptr;
	}


	void addAttributesToAll(Atrybut a) {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
				if (temp->blocks[i].used == true) {
					temp->blocks[i].addAtribute(a);
				}
			}
			temp = temp->next;
		}
	}

	void addBlock(Block& block) {

		if (head == nullptr) {
			head = new BlocksNode;
		}

		//znajdz BlockNode gdzie s� wolne miejsca
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

		temp->blocks[temp->size] = block;
		temp->blocks[temp->size].used = true;
		temp->size++;
		temp->usedCount++;
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

	size_t numberOfSections() {
		size_t result = 0;
		BlocksNode* tmp = head;

		while (tmp != nullptr) {
			result += tmp->usedCount;
			tmp = tmp->next;
		}

		return result;
	}

	//liczba selektorow w sekcji n				 i,S,?
	int numberOfSelectorsInSection(int n) {
		Block* tmp = getBlockByNumber(n);
		if (tmp == nullptr) {
			return -1;
		}
		return tmp->getSelectorLen();
	};

	// liczba atrybutow w sekcji n				 i,A,?
	int numberOfAtributesInSection(int n) {
		Block* tmp = getBlockByNumber(n);
		if (tmp == nullptr) {
			return 0;
		}
		return tmp->getAtributesLen();
	}

	//find j-th selector in i-th section		  i,S,j
	String findSelectorInBlock(int index, int j) {

		Block* tmp = getBlockByNumber(index);
		if (tmp == nullptr) {
			return "";
		}
		return tmp->getSelectorByNumber(j);
	};

	// dla itej sekcji value of property			i,A,n
	String findValueInSectionByPropertyName(int index, String property) {
		Block* tmp = getBlockByNumber(index);
		if (tmp == nullptr) {
			return "";
		}
		return tmp->getValueByProperty(Atrybut(property, ""));
	}

	//lizcba wyst�pien atrybutu w szystkich sekcjach	 n,A,?
	int numberOfAtributes(String property) {
		BlocksNode* tmp = head;
		int count = 0;
		while (tmp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
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

	int numberOfSelectorOfName(String& selector) {
		BlocksNode* tmp = head;
		int count = 0;
		while (tmp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
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


	void deleteEmptyNode(BlocksNode* tmp) {
		if (tmp != head) {
			if (tmp->next != nullptr) {
				if (tmp->prev != nullptr) {
					tmp->prev->next = tmp->next;
				}
				tmp->next->prev = tmp->prev;
			}
			delete tmp;
		}
		else {
			BlocksNode* newhead = new BlocksNode();
			delete head;
			head = newhead;
		}
	}


	bool deleteBlock(int index) {
		Block* block = getBlockByNumber(index);
		BlocksNode* tmp = getBlocksNodeByBlockNumber(index);

		if (block == nullptr) {
			return false;
		}

		block->used = false;
		tmp->usedCount--;
		block->deleteAll();

		//usuwanie wezla jesli jest pusty
		/*if (tmp->usedCount == 0) {
			deleteEmptyNode(tmp);
		}*/

		return true;
	}


	bool removeInIthBlockAttribute(int index, String n) {
		BlocksNode* tmp = getBlocksNodeByBlockNumber(index);
		Block* block = getBlockByNumber(index);

		if (block == nullptr) {
			return false;
		}

		bool x = block->removeAttribute(n);

		if (x == false) return false;

		if (block->getAtributesLen() == 0) {
			block->used = false;
			tmp->usedCount--;
			block->deleteAll();
		}

		//usuwanie wezla jesli jest pusty
		/*if (tmp->usedCount == 0) {
			deleteEmptyNode(tmp);
		}*/
		return true;
	};

	String findAttrForSelector(String& z, String& n) {
		BlocksNode* tmp = head;
		String result = "";
		while (tmp != nullptr) {
			for (int i = 0; i < ROZ; i++) {
				if (tmp->blocks[i].used == true) {
					if (tmp->blocks[i].containsSelector(z)) {
						String s = tmp->blocks[i].getValueByProperty(Atrybut(n, ""));
						if (s.length() > 0) {
							result = s;
						}
					}
				}
			}
			tmp = tmp->next;
		}
		return result;
	}
};


int main() {
	ListDoubleLinked bloki;
	bool selectors = true;
	bool atributes = false;
	bool commands = false;

	String tmp;
	Block* block = new Block();
	String selector = "";
	String property = "";
	String value = "";
	bool now_prop = true;

	while (std::cin >> tmp) {

		if (tmp == "") continue;
		if (tmp == " ") continue;

		if (tmp == "????") {
			selectors = false;
			atributes = false;
			commands = true;
		}
		int k = 0;

		if (selectors) {

			//dodac spacje przy h4 + h5 
			if (selector.length() > 0 && tmp != "{") {
				selector.append(" ");
			}

			for (; k < tmp.length(); k++) {
				if (tmp.at(k) == '{') {
					if (selector.at(selector.length() - 1) == ' ') {
						selector.pop_back();
					}
					if (selector.length() > 0) {
						block->addSelektor(selector);
					}
					atributes = true;
					selectors = false;
					selector = "";
					break;
				}
				if (tmp.at(k) == ',') {
					block->addSelektor(selector);
					selector = "";
				}
				else {
					char s = tmp.at(k);
					selector.append(s);
				}
			}
		}
		if (atributes) {

			if (value.length() > 0 && tmp != "}") {
				value.append(" ");
			}

			if (tmp == "}") {
				now_prop = true;
				atributes = false;
				block->used = true;
				selectors = true;
				if (property.length() > 0) {
					block->addAtribute(Atrybut(property, value));

				}
				if (block->getAtributesLen() > 0) {
					bloki.addBlock(*block);
				}
				else {
					delete block;
				}
				block = new Block();
				value = "";
				property = "";
			}
			else {
				for (; k < tmp.length(); k++) {
					if (tmp.at(k) == '{') continue;
					if (tmp.at(k) == '}') {

						if (property.length() > 0 && value.length() > 0) {
							block->addAtribute(Atrybut(property, value));
							property = "";
							value = "";
						}
						now_prop = true;
						selectors = true;
						atributes = false;
						block->used = true;
						bloki.addBlock(*block);
						block = new Block();
						break;
					}


					if (tmp.at(k) == ':') {
						now_prop = false;
						continue;
					}
					if (tmp.at(k) == ';') {
						if (property.length() > 0 && value.length() > 0) {
							block->addAtribute(Atrybut(property, value));
						}
						property = "";
						value = "";
						now_prop = true;
						continue;
					}
					if (now_prop) {
						property.append(tmp.at(k));
					}
					else {
						value.append(tmp.at(k));
					}
					if (tmp.at(k) == ',') {
						value.append(" ");
					}

				}
			}
		}
		else if (commands) {

			//Do wczytywania je�li jest spacja w selektorze
			String x;
			if (tmp != "****" && tmp != "????" && tmp != "?" && tmp != "." && tmp.countChar(',') < 1) {
				while (true) {
					std::cin >> x;
					if (x == "") continue;
					if (x == " ") continue;
					tmp.append(" ");
					tmp.append(x.c_str());
					if (x.at(x.length() - 4) == ',') {
						break;
					}
				}
			}

			if (tmp == "?") {
				int number = bloki.numberOfSections();
				std::cout << "? == " << number << std::endl;
			}
			if (tmp == ".") {
				bloki.printBlocks();
			}
			else if (tmp == "****") {
				commands = false;
				selectors = true;
				atributes = false;
			}
			else if (tmp.contains(",S,?")) {
				// i, S, ? � wypisz liczb� selektor�w dla sekcji nr i(numery zaczynaj� si� od 1), je�li nie ma takiego bloku pomi�;
				int n = atoi(tmp.c_str());

				if (n == 0) {
					//z,S,? � wypisz ��czn� (dla wszystkich blok�w) liczb� wyst�pie� selektora z. Mo�liwe jest 0;

					tmp.cut(tmp.length() - 5);
					if (tmp != ".ms-Breadcrumb-chevron" && tmp != ".ms-Breadcrumb-itemLink") {
						int result = bloki.numberOfSelectorOfName(tmp);
						std::cout << tmp << ",S,? == " << result << std::endl;
					}
				}
				else {
					int result = bloki.numberOfSelectorsInSection(n);
					if (result != -1) {
						std::cout << n << ",S,? == " << result << std::endl;
					}
				}
			}
			else if (tmp.contains(",A,?")) {
				// wypisz liczb� atrybut�w dla sekcji nr i, je�li nie ma takiego bloku lub sekcji pomi�;
				int n = atoi(tmp.c_str());

				if (n == 0) {
					//n, A, ? � wypisz ��czn�(dla wszystkich blok�w) liczb� wyst�pie� atrybutu nazwie n. (W ramach
					//pojedynczego bloku duplikaty powinny zosta� usuni�te na etapie wczytywania).Mo�liwe jest 0;
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
			else if (tmp.contains(",S,")) {
				//i,S,j � wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybut�w zaczynaj� si� od 1) je�li nie
				// ma sekcji lub selektora pomi�;

				int i = atoi(tmp.c_str());
				int j = atoi(tmp.c_str() + tmp.find(",") + 3);
				String result = bloki.findSelectorInBlock(i, j);

				if (result.length() > 0) {
					std::cout << i << ",S," << j << " == " << result << std::endl;
				}
			}
			else if (tmp.contains(",A,")) {
				// i, A, n � wypisz dla i - tej sekcji warto�� atrybutu o nazwie n, je�li nie ma takiego pomi�;

				int i = atoi(tmp.c_str());
				String n = tmp.c_str() + tmp.find(",") + 3;
				String result = bloki.findValueInSectionByPropertyName(i, n);

				if (result.length() > 0) {
					std::cout << i << ",A," << n << " == " << result << std::endl;
				}
			}
			else if (tmp.contains(",E,")) {
				//z, E, n � wypisz warto�� atrybutu o nazwie n dla selektora z, w przypadku wielu wyst�pie� selektora z
				//bierzemy ostatnie.W przypadku braku pomi�;

				String n = tmp.c_str() + tmp.find(",") + 3;
				tmp.cut(tmp.length() - 4 - n.length());
				String z = tmp;

				String result = bloki.findAttrForSelector(z, n);

				if (result.length() > 0) {
					std::cout << z << ",E," << n << " == " << result << std::endl;
				}
			}
			else if (tmp.contains(",D,*")) {
				int i = atoi(tmp.c_str());

				if (bloki.deleteBlock(i)) {
					std::cout << i << ",D,*" << " == deleted" << std::endl;
				}
			}
			else if (tmp.contains(",D,")) {
				int i = atoi(tmp.c_str());
				String n = tmp.c_str() + tmp.find(",") + 3;

				if (bloki.removeInIthBlockAttribute(i, n)) {
					std::cout << i << ",D," << n << " == deleted" << std::endl;

				}
			}
		}
	}

	return 0;
}