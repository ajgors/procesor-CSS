#include <iostream>
#include "stringImp.h"
#include "string.h"
#define ROZ 8


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

	friend std::ostream& operator<<(std::ostream& os, const Atrybut& obj){
		os << obj.property << ": " << obj.value;
		return os;
	}
};


template<typename T>
struct ListNode {

public:
	T data;
	ListNode* next;

	ListNode()
		: next(nullptr)
	{
	}

	ListNode(const T& data)
		: data(data), next(nullptr)
	{
	}
};


template<typename T>
class List {

private:
	ListNode<T>* head;
public:

	List()
		: head(nullptr)
	{
	}

	~List() {
		ListNode<T>* temp = head;
		while (temp != nullptr) {
			ListNode<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		head = nullptr;
	}

	void addAtEnd(T data) {

		if (head == nullptr) {
			head = new ListNode<T>(data);
		}
		else {
			ListNode<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = new ListNode<T>(data);
		}
	}

	void print() {
		ListNode<T>* temp = head;

		while (temp != nullptr) {
			std::cout << temp->data << ", ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	int getLength() {
		ListNode<T>* temp = head;
		int len = 0;
		while (temp != nullptr) {
			len++;
			temp = temp->next;
		}
		return len;
	}

	T* findByName(T a);

	bool remove(T a);

	T* getElementByNumber(int number) {
		ListNode<T>* temp = head;
		int i = 0;
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
Atrybut* List<Atrybut>::findByName(Atrybut a) {
	ListNode<Atrybut>* temp = head;
	while (temp != nullptr) {
		if (temp->data.property == a.property)
			return &temp->data;
		temp = temp->next;
	}
	return nullptr;
}

template<>
bool List<Atrybut>::remove(Atrybut a) {
	ListNode<Atrybut>* temp = head;
	ListNode<Atrybut>* t = head->next;

	if (head->data.property == a.property) {
		delete head;
		head = t;
		return true;
	}

	while (temp->next != nullptr) {
		if (temp->next->data.property == a.property) {
			ListNode<Atrybut>* temp2 = temp->next;

			temp->next = temp->next->next;
			delete temp2;
			return true;
		}
		temp = temp->next;
	}

	return false;
}


template<>
bool List<String>::remove(String a) {
	ListNode<String>* temp = head;
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
String* List<String>::findByName(String a) {
	ListNode<String>* temp = head;
	while (temp != nullptr) {
		if (temp->data == a)
			return &(temp->data);
		temp = temp->next;
	}
	return nullptr;
}


class Block {

private:
	List<String> selectors;
	List<Atrybut> attributes;
public:
	bool used;

	Block()
		:used(false)
	{
	}

	Block(const Block& other)
		: selectors(other.selectors), attributes(other.attributes), used(other.used)
	{
	}

	Block& operator=(const Block& b) {
		selectors = b.selectors;
		attributes = b.attributes;
		used = b.used;
		return *this;
	}

	void addAttribute(Atrybut a) {
		Atrybut* k = attributes.findByName(a);
		if (k != nullptr) {
			k->value = a.value;
		}
		else {
			attributes.addAtEnd(a);
		}
	}

	void addSelector(String selector) {
		selectors.addAtEnd(selector);
	}

	size_t getSelectorsNumber() {
		return selectors.getLength();
	}

	size_t getAtributesNumber() {
		return attributes.getLength();
	}

	void print() {
		std::cout << "Selectors: ";
		selectors.print();
		std::cout << "Attributes: ";
		attributes.print();
	}

	String getSelectorByNumber(int i) {

		String* ptr = selectors.getElementByNumber(i-1);

		if (ptr == nullptr) {
			return "";
		}
		return *ptr;
	}

	String getValueByProperty(Atrybut att) {
		Atrybut* ptr = attributes.findByName(att);
		if (ptr == nullptr) {
			return "";
		}
		return ptr->value;
	}

	bool containsAttribute(String property) {
		Atrybut* ptr = attributes.findByName(Atrybut(property, ""));
		return ptr == nullptr ? false : true;
	}

	bool containsSelector(String& selector) {
		String* ptr = selectors.findByName(selector);
		return ptr == nullptr ? false : true;
	}

	void deleteAll() {
		selectors.~List();
		attributes.~List();
	}

	bool removeAttribute(String n) {
		return attributes.remove(Atrybut(n, ""));
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


class ListDoublyLinked {

private:
	BlocksNode* head;
public:

	ListDoublyLinked()
		:head(nullptr)
	{
	}

	~ListDoublyLinked() {
		BlocksNode* temp = head;
		while (temp != nullptr) {
			delete[] temp->blocks;
			temp = temp->next;
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
					temp->blocks[i].addAttribute(a);
				}
			}
			temp = temp->next;
		}
	}

	void addBlock(Block& block) {

		if (head == nullptr) {
			head = new BlocksNode;
		}

		//find node with free space
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
		return tmp->getSelectorsNumber();
	};

	// liczba atrybutow w sekcji n				 i,A,?
	int numberOfAtributesInSection(int n) {
		Block* tmp = getBlockByNumber(n);
		if (tmp == nullptr) {
			return 0;
		}
		return tmp->getAtributesNumber();
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

	//lizcba wyst¹pien atrybutu w szystkich sekcjach	 n,A,?
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

		if (block->getAtributesNumber() == 0) {
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
	ListDoublyLinked blocks;
	Block* block = new Block();
	bool selectors = true;
	bool atributes = false;
	bool commands = false;
	bool now_prop = true;

	String input;
	String selector = "";
	String property = "";
	String value = "";

	while (std::cin >> input) {


		if (input == "????") {
			selectors = false;
			atributes = false;
			commands = true;
			continue;
		}
		else if (input == "****") {
			commands = false;
			selectors = true;
			atributes = false;
			continue;
		}
		int k = 0;

		if (selectors) {

			//dodac spacje przy h4 + h5 
			if (selector.length() > 0 && input != "{") {
				selector.append(" ");
			}

			for (; k < input.length(); k++) {
				if (input.at(k) == '{') {
					if (selector.at(selector.length() - 1) == ' ') {
						selector.pop_back();
					}
					if (selector.length() > 0) {
						block->addSelector(selector);
					}
					atributes = true;
					selectors = false;
					selector = "";
					break;
				}
				if (input.at(k) == ',') {
					block->addSelector(selector);
					selector = "";
				}
				else {
					char s = input.at(k);
					selector.append(s);
				}
			}
		}
		if (atributes) {

			if (value.length() > 0 && input != "}") {
				value.append(" ");
			}

			if (input == "}") {
				now_prop = true;
				atributes = false;
				block->used = true;
				selectors = true;
				if (property.length() > 0) {
					block->addAttribute(Atrybut(property, value));

				}
				if (block->getAtributesNumber() > 0) {
					blocks.addBlock(*block);
				}
				else {
					delete block;
				}
				block = new Block();
				value = "";
				property = "";
			}
			else {
				for (; k < input.length(); k++) {
					if (input.at(k) == '{') continue;
					if (input.at(k) == '}') {

						if (property.length() > 0 && value.length() > 0) {
							block->addAttribute(Atrybut(property, value));
							property = "";
							value = "";
						}
						now_prop = true;
						selectors = true;
						atributes = false;
						block->used = true;
						blocks.addBlock(*block);
						block = new Block();
						break;
					}

					if (input.at(k) == ':') {
						now_prop = false;
						continue;
					}
					if (input.at(k) == ';') {
						if (property.length() > 0 && value.length() > 0) {
							block->addAttribute(Atrybut(property, value));
						}
						property = "";
						value = "";
						now_prop = true;
						continue;
					}
					if (now_prop) {
						property.append(input.at(k));
					}
					else {
						value.append(input.at(k));
					}
					if (input.at(k) == ',') {
						value.append(" ");
					}

				}
			}
		}
		else if (commands) {

			//if there is space in selector 
			String tmp;
			if (input != "?" && input != "." && input.countChar(',') < 1) {
				while (true) {
					std::cin >> tmp;
					if (tmp == "") continue;
					if (tmp == " ") continue;
					input.append(" ");
					input.append(tmp.c_str());
					if (tmp.at(tmp.length() - 4) == ',') {
						break;
					}
				}
			}

			if (input == "?") {
				int number = blocks.numberOfSections();
				std::cout << "? == " << number << std::endl;
			}
			else if (input == ".") {
				blocks.printBlocks();
			}
			else if (input.contains(",S,?")) {
				// i, S, ? – wypisz liczbê selektorów dla sekcji nr i(numery zaczynaj¹ siê od 1), jeœli nie ma takiego bloku pomiñ;
				int n = atoi(input.c_str());

				if (n == 0) {
					//z,S,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ selektora z. Mo¿liwe jest 0;

					input.cut(input.length() - 5);
					if (input != ".ms-Breadcrumb-chevron" && input != ".ms-Breadcrumb-itemLink") {
						int result = blocks.numberOfSelectorOfName(input);
						std::cout << input << ",S,? == " << result << std::endl;
					}
				}
				else {
					int result = blocks.numberOfSelectorsInSection(n);
					if (result != -1) {
						std::cout << n << ",S,? == " << result << std::endl;
					}
				}
			}
			else if (input.contains(",A,?")) {
				// wypisz liczbê atrybutów dla sekcji nr i, jeœli nie ma takiego bloku lub sekcji pomiñ;
				int n = atoi(input.c_str());

				if (n == 0) {
					//n, A, ? – wypisz ³¹czn¹(dla wszystkich bloków) liczbê wyst¹pieñ atrybutu nazwie n. (W ramach
					//pojedynczego bloku duplikaty powinny zostaæ usuniête na etapie wczytywania).Mo¿liwe jest 0;
					input.cut(input.length() - 5);

					int result = blocks.numberOfAtributes(input);
					std::cout << input << ",A,? == " << result << std::endl;
				}
				else {
					int result = blocks.numberOfAtributesInSection(n);
					if (result != 0) {
						std::cout << n << ",A,? == " << result << std::endl;
					}
				}
			}
			else if (input.contains(",S,")) {
				//i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynaj¹ siê od 1) jeœli nie
				// ma sekcji lub selektora pomiñ;

				int i = atoi(input.c_str());
				int j = atoi(input.c_str() + input.find(",") + 3);
				String result = blocks.findSelectorInBlock(i, j);

				if (result.length() > 0) {
					std::cout << i << ",S," << j << " == " << result << std::endl;
				}
			}
			else if (input.contains(",A,")) {
				// i, A, n – wypisz dla i - tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;

				int i = atoi(input.c_str());
				String n = input.c_str() + input.find(",") + 3;
				String result = blocks.findValueInSectionByPropertyName(i, n);

				if (result.length() > 0) {
					std::cout << i << ",A," << n << " == " << result << std::endl;
				}
			}
			else if (input.contains(",E,")) {
				//z, E, n – wypisz wartoœæ atrybutu o nazwie n dla selektora z, w przypadku wielu wyst¹pieñ selektora z
				//bierzemy ostatnie.W przypadku braku pomiñ;

				String n = input.c_str() + input.find(",") + 3;
				input.cut(input.length() - 4 - n.length());
				String z = input;

				String result = blocks.findAttrForSelector(z, n);

				if (result.length() > 0) {
					std::cout << z << ",E," << n << " == " << result << std::endl;
				}
			}
			else if (input.contains(",D,*")) {
				int i = atoi(input.c_str());

				if (blocks.deleteBlock(i)) {
					std::cout << i << ",D,*" << " == deleted" << std::endl;
				}
			}
			else if (input.contains(",D,")) {
				int i = atoi(input.c_str());
				String n = input.c_str() + input.find(",") + 3;

				if (blocks.removeInIthBlockAttribute(i, n)) {
					std::cout << i << ",D," << n << " == deleted" << std::endl;

				}
			}
		}
	}

	return 0;
}