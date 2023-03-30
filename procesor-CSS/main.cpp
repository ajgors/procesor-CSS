#include <iostream>
#include "string.h"
#include "StringImpl.h"
#define ROZ 8


struct Attribute {
	String property;
	String value;

	Attribute()
		:property(), value()
	{
	}

	Attribute(const String& property, const String& value)
		:property(property), value(value)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Attribute& att) {
		os << att.property << ":" << att.value;
		return os;
	}
};


template<typename T>
struct ListNode {
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
	ListNode<T>* m_head;
	ListNode<T>* m_tail;
	size_t m_size;
public:

	List()
		: m_head(nullptr), m_tail(nullptr), m_size(0)
	{
	}

	~List() {
		ListNode<T>* temp = m_head;
		while (temp != nullptr) {
			ListNode<T>* next = temp->next;
			delete temp;
			temp = next;
		}
		m_head = nullptr;
	}

	void add(const T& data) {
		if (m_head == nullptr) {
			m_head = new ListNode<T>(data);
			m_tail = m_head;
		}
		else {
			ListNode<T>* temp = new ListNode<T>(data);
			m_tail->next = temp;
			m_tail = temp;
		}
		m_size++;
	}

	void print() {
		ListNode<T>* temp = m_head;
		while (temp != nullptr) {
			std::cout << temp->data << ", ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	size_t getSize() {
		return m_size;
	}

	T* findByName(T a);

	bool remove(T a);

	T* getElementByNumber(size_t number) {
		ListNode<T>* temp = m_head;
		size_t i = 0;
		while (temp != nullptr) {
			if (i == number) {
				return &temp->data;
			}
			temp = temp->next;
			i++;
		}
		return nullptr;
	}
};

template<>
Attribute* List<Attribute>::findByName(Attribute a) {
	ListNode<Attribute>* temp = m_head;
	while (temp != nullptr) {
		if (temp->data.property == a.property)
			return &temp->data;
		temp = temp->next;
	}
	return nullptr;
}

template<>
bool List<Attribute>::remove(Attribute a) {
	ListNode<Attribute>* temp = m_head;

	if (m_head->data.property == a.property) {
		m_head = m_head->next;
		delete temp;
		m_size--;
		return true;
	}

	while (temp->next != nullptr) {
		if (temp->next->data.property == a.property) {
			ListNode<Attribute>* tempNext = temp->next;

			temp->next = temp->next->next;
			delete tempNext;
			m_size--;
			return true;
		}
		temp = temp->next;
	}

	return false;
}

template<>
String* List<String>::findByName(String a) {
	ListNode<String>* temp = m_head;
	while (temp != nullptr) {
		if (temp->data == a)
			return &(temp->data);
		temp = temp->next;
	}
	return nullptr;
}


class Block {

private:
	List<String> m_selectors;
	List<Attribute> m_attributes;
public:
	bool m_used;

	Block()
		:m_used(false)
	{
	}

	Block(const Block& other)
		: m_selectors(other.m_selectors), m_attributes(other.m_attributes), m_used(other.m_used)
	{
	}

	Block& operator=(const Block& b) {
		m_selectors = b.m_selectors;
		m_attributes = b.m_attributes;
		m_used = b.m_used;
		return *this;
	}

	void addAttribute(const Attribute& a) {
		Attribute* k = m_attributes.findByName(a);
		if (k != nullptr) {
			k->value = a.value;
		}
		else {
			m_attributes.add(a);
		}
	}

	void addSelector(String& selector) {
		m_selectors.add(selector);
	}

	size_t getSelectorsNumber() {
		return m_selectors.getSize();
	}

	size_t getAtributesNumber() {
		return m_attributes.getSize();
	}

	void print() {
		std::cout << "Selectors: ";
		m_selectors.print();
		std::cout << "Attributes: ";
		m_attributes.print();
	}

	String getSelectorByNumber(size_t i) {

		String* ptr = m_selectors.getElementByNumber(i - 1);

		if (ptr == nullptr) {
			return "";
		}
		return *ptr;
	}

	String getValueByProperty(const Attribute& att) {
		Attribute* ptr = m_attributes.findByName(att);
		if (ptr == nullptr) {
			return "";
		}
		return ptr->value;
	}

	bool containsAttribute(String& property) {
		Attribute* ptr = m_attributes.findByName(Attribute(property, ""));
		return ptr == nullptr ? false : true;
	}

	bool containsSelector(String& selector) {
		String* ptr = m_selectors.findByName(selector);
		return ptr == nullptr ? false : true;
	}

	void deleteAll() {
		m_selectors.~List();
		m_attributes.~List();
	}

	bool removeAttribute(String& n) {
		return m_attributes.remove(Attribute(n, ""));
	}
};


struct BlocksNode {
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
	BlocksNode* m_head;
	BlocksNode* m_tail;
	size_t m_size;
public:

	ListDoublyLinked()
		:m_head(nullptr), m_tail(nullptr), m_size(0)
	{
	}

	~ListDoublyLinked() {
		BlocksNode* temp = m_head;
		while (temp != nullptr) {
			delete[] temp->blocks;
			temp = temp->next;
		}
	}

	void printBlocks() {
		BlocksNode* temp = m_head;
		while (temp != nullptr) {
			for (size_t i = 0; i < ROZ; i++) {
				if (temp->blocks[i].m_used == true) {
					temp->blocks[i].print();
				}
			}
			temp = temp->next;
		}
	}

	BlocksNode* getBlocksNodeByBlockNumber(size_t n) {
		BlocksNode* temp = m_head;
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

	Block* getBlockByNumber(size_t n) {
		BlocksNode* temp = m_head;
		while (temp != nullptr) {
			if (n > temp->usedCount) {
				n -= temp->usedCount;
			}
			else {
				for (size_t i = 0, c = 0; i < ROZ; i++) {
					if (temp->blocks[i].m_used == true) {
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

	void addBlock(Block& block) {

		if (m_head == nullptr) {
			m_head = new BlocksNode;
			m_tail = m_head;
		}
		
		if (m_tail->size >= ROZ) {
			BlocksNode* t = new BlocksNode();
			t->prev = m_tail;
			m_tail->next = t;
			m_tail = t;
		}
		
		m_tail->blocks[m_tail->size] = block;
		m_tail->blocks[m_tail->size].m_used = true;
		m_tail->size++;
		m_tail->usedCount++;
		m_size++;
	}

	size_t getSize() {
		return m_size;
	}

	size_t numberOfSelectorsInSection(size_t n) {
		Block* tmp = getBlockByNumber(n);
		if (tmp == nullptr) {
			return -1;
		}
		return tmp->getSelectorsNumber();
	};

	size_t numberOfAtributesInSection(size_t n) {
		Block* tmp = getBlockByNumber(n);
		if (tmp == nullptr) {
			return 0;
		}
		return tmp->getAtributesNumber();
	}

	String findSelectorInBlock(size_t index, size_t j) {

		Block* tmp = getBlockByNumber(index);
		if (tmp == nullptr) {
			return "";
		}
		return tmp->getSelectorByNumber(j);
	};

	String findValueInSectionByPropertyName(size_t index, String& property) {
		Block* tmp = getBlockByNumber(index);
		if (tmp == nullptr) {
			return "";
		}
		return tmp->getValueByProperty(Attribute(property, ""));
	}

	size_t numberOfAttributesOfName(String& property) {
		BlocksNode* tmp = m_head;
		size_t count = 0;
		while (tmp != nullptr) {
			for (size_t i = 0; i < ROZ; i++) {
				if (tmp->blocks[i].m_used == true) {
					if (tmp->blocks[i].containsAttribute(property)) {
						count++;
					}
				}
			}
			tmp = tmp->next;
		}
		return count;
	};

	size_t numberOfSelectorOfName(String& selector) {
		BlocksNode* tmp = m_head;
		size_t count = 0;
		while (tmp != nullptr) {
			for (size_t i = 0; i < ROZ; i++) {
				if (tmp->blocks[i].m_used == true) {
					if (tmp->blocks[i].containsSelector(selector)) {
						count++;
					}
				}
			}
			tmp = tmp->next;
		}
		return count;
	}

	void DeleteNode(BlocksNode* node) {
		if (node == nullptr) {
			return;
		}
		if (node->next != nullptr) {
			node->next->prev = node->prev;
		}
		if (node == m_head) {
			m_head = node->next;
		}
		else {
			node->prev->next = node->next;
		}
		delete node;
	}

	bool deleteBlock(size_t index) {
		Block* block = getBlockByNumber(index);
		BlocksNode* blocksNode = getBlocksNodeByBlockNumber(index);

		if (block == nullptr) {
			return false;
		}

		block->m_used = false;
		blocksNode->usedCount--;
		m_size--;
		block->deleteAll();

		if (blocksNode->usedCount == 0) {
			DeleteNode(blocksNode);
		}

		return true;
	}

	bool removeInIthBlockAttribute(size_t index, String& n) {
		BlocksNode* blocksNode = getBlocksNodeByBlockNumber(index);
		Block* block = getBlockByNumber(index);

		if (block == nullptr) {
			return false;
		}

		if (!block->removeAttribute(n)) return false;

		if (block->getAtributesNumber() == 0) {
			block->m_used = false;
			m_size--;
			blocksNode->usedCount--;
			block->deleteAll();
		}

		if (blocksNode->usedCount == 0) {
			DeleteNode(blocksNode);
		}
		return true;
	};

	String findAttrForSelector(String& z, String& n) {
		BlocksNode* tmp = m_head;
		String result = "";
		while (tmp != nullptr) {
			for (size_t i = 0; i < ROZ; i++) {
				if (tmp->blocks[i].m_used == true) {
					if (tmp->blocks[i].containsSelector(z)) {
						String s = tmp->blocks[i].getValueByProperty(Attribute(n, ""));
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
	bool isSelectors = true;
	bool isAtributes = false;
	bool isCommands = false;
	bool isProperty = true;
	String input;
	String selector;
	String property;
	String value;
	String command;
	while (std::cin >> input) {

		if (input == "????") {
			isSelectors = false;
			isAtributes = false;
			isCommands = true;
			continue;
		}
		else if (input == "****") {
			isCommands = false;
			isSelectors = true;
			isAtributes = false;
			continue;
		}
		size_t k = 0;

		if (isSelectors) {

			if (selector.length() > 0 && input != "{") {
				selector.append(" ");
			}

			for (; k < input.length(); k++) {
				if (input[k] == '{') {
					if (selector[selector.length() - 1] == ' ') {
						selector.pop_back();
					}
					if (selector.length() > 0) {
						block->addSelector(selector);
					}
					isAtributes = true;
					isSelectors = false;
					selector = "";
					break;
				}
				if (input[k] == ',') {
					block->addSelector(selector);
					selector = "";
				}
				else {
					char s = input[k];
					selector.append(s);
				}
			}
		}
		if (isAtributes) {

			if (value.length() > 0 && input != "}") {
				value.append(" ");
			}
			for (; k < input.length(); k++) {
				if (input[k] == '{') continue;
				if (input[k] == '}') {

					if (property.length() > 0 && value.length() > 0) {
						block->addAttribute(Attribute(property, value));
						property = "";
						value = "";
					}
					isProperty = true;
					isSelectors = true;
					isAtributes = false;
					if (block->getAtributesNumber() > 0) {
						blocks.addBlock(*block);
					}
					else {
						delete block;
					}
					
					block = new Block();
					break;
				}

				if (input[k] == ':') {
					isProperty = false;
					continue;
				}
				if (input[k] == ';') {
					if (property.length() > 0 && value.length() > 0) {
						block->addAttribute(Attribute(property, value));
					}
					property = "";
					value = "";
					isProperty = true;
					continue;
				}
				if (isProperty) {
					property.append(input[k]);
				}
				else {
					value.append(input[k]);
				}
			}
		}
		else if (isCommands) {

			if (input == "?") {
				std::cout << "? == " << blocks.getSize() << std::endl;
			}
			else if (input == ".") {
				blocks.printBlocks();
			}
			else {

				for (; k < input.length(); k++) {
					command.append(input[k]);
				}
				if (command.countChar(',') == 0) {
					command.append(" ");
				}

				if (command.countChar(',') == 2) {
					if (command.contains(",S,?")) {
						size_t n = atoi(command.c_str());

						if (n == 0) {
							command = command.cut(command.length() - 4);
							size_t result = blocks.numberOfSelectorOfName(command);
							std::cout << command << ",S,? == " << result << std::endl;
						}
						else {
							size_t result = blocks.numberOfSelectorsInSection(n);
							if (result != -1) {
								std::cout << n << ",S,? == " << result << std::endl;
							}
						}
					}
					else if (command.contains(",A,?")) {
						size_t n = atoi(command.c_str());

						if (n == 0) {
							command = command.cut(command.length() - 4);

							size_t result = blocks.numberOfAttributesOfName(command);
							std::cout << command << ",A,? == " << result << std::endl;
						}
						else {
							size_t result = blocks.numberOfAtributesInSection(n);
							if (result != 0) {
								std::cout << n << ",A,? == " << result << std::endl;
							}
						}
					}
					else if (command.contains(",S,")) {

						size_t i = atoi(command.c_str());
						size_t j = atoi(command.c_str() + command.find(",") + 3);
						String result = blocks.findSelectorInBlock(i, j);

						if (result.length() > 0) {
							std::cout << i << ",S," << j << " == " << result << std::endl;
						}
					}
					else if (command.contains(",A,")) {

						size_t i = atoi(command.c_str());
						String n = command.c_str() + command.find(",") + 3;
						String result = blocks.findValueInSectionByPropertyName(i, n);

						if (result.length() > 0) {
							std::cout << i << ",A," << n << " == " << result << std::endl;
						}
					}
					else if (command.contains(",E,")) {

						String n = command.c_str() + command.find(",") + 3;
						command = command.cut(command.length() - 3 - n.length());
						String z = command;

						String result = blocks.findAttrForSelector(z, n);

						if (result.length() > 0) {
							std::cout << z << ",E," << n << " == " << result << std::endl;
						}
					}
					else if (command.contains(",D,*")) {
						size_t i = atoi(command.c_str());

						if (blocks.deleteBlock(i)) {
							std::cout << i << ",D,*" << " == deleted" << std::endl;
						}
					}
					else if (command.contains(",D,")) {
						size_t i = atoi(command.c_str());
						String n = command.c_str() + command.find(",") + 3;

						if (blocks.removeInIthBlockAttribute(i, n)) {
							std::cout << i << ",D," << n << " == deleted" << std::endl;
						}
					}
					command = "";
				}
				else if (command.countChar(',') > 2) {
					command = "";
				}
			}
		}

	}
	return 0;
}