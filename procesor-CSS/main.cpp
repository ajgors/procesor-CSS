#include <iostream>
#include "stringImp.h"
#include "string.h"
#define ROZ 8


//sekcje jako listy 2 

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
		os << obj.nazwa/* << " " << obj.wartosc*/;
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

//template<typename T>
class ListLinked {

private:
	size_t size;
public:
	Block* blocks;
	ListLinked* next;
	ListLinked* prev;

	ListLinked()
		:blocks(new Block[ROZ]), size(0), next(nullptr), prev(nullptr)
	{
	}

	void addBlock(Block block) {
		
		ListLinked* temp = this;
		
		while (temp->size >= ROZ) {
			if (temp->next == nullptr) {
				ListLinked* t = new ListLinked();
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
		ListLinked* temp = this;
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
		delete[] blocks;
	}

	size_t getSize() {
		return size;
	}

	//liczba sekcji
	size_t numberOfSections() {
		size_t result = 0;

		ListLinked* tmp = this;

		while (tmp != nullptr) {
			result += tmp->getSize();
			tmp = tmp->next;
		}

		return result;
	}

	size_t numberOfSelectorsInSection(int n) {
		int current = 0;
		ListLinked* tmp = this;

		while (n > ROZ) {
			tmp = tmp->next;
			n -= tmp->getSize();
		}

		for (int i = 0, k = 0; i < ROZ; i++) {
			if (blocks[i].used == true) {
				k++;
			}
			if (k == n) {
				return blocks[k-1].getSelectorLen();
			}
		}
		return 0;
	};
};




int main() {
	ListLinked bloki;
	bool selectors = true;

	bool atributes = false;
	bool commands = false;

	while (true) {

		String tmp;
		Block block;
		if (selectors) {
			bool end = false;
			block.used = true;
			while (true) {
				//char* buffor = new char[50];
				//std::cin >> buffor;
				std::cin >> tmp;
				//tmp = buffor;
				if (tmp == "{") {
					selectors = false;
					atributes = true;
					tmp = "";
					break;
				}
				else if (tmp.at(0) == '{') {
					selectors = false;
					atributes = true;
					break;
				}
				else if (tmp == "?") {
					end = true;
					break;
				}
				else if (tmp == "????") {
					selectors = false;
					atributes = false;
					commands = true;
					break;
				}
				else {
					if (tmp.at(tmp.length()-1) == ',') {
						tmp.pop_back();
					}
					if (tmp != " ") {
						block.addSelektor(tmp);
					}
				}
			}
			if (end) break;
		}
		if (atributes) {
			String value;
			bool running = true;
			while (tmp != "}" && value != "}" && running ) {
	
				if (tmp != "") {
					//tmp = tmp.substr(1);
					tmp.pop_back();
				}
				else {
					std::cin >> tmp;
					if (tmp == "}") break;
					tmp.pop_back();
				}
				std::cin >> value;
				if (value == "}") break;
				if (value.at(value.length() -1) == '}') {
					value.pop_back();
					running = false;
				}
				
				value.pop_back();
				if (tmp != "" && value != "") {
					block.addAtribute(atrybut(tmp, value));
				}
				tmp = "";
			}
			bloki.addBlock(block);
			atributes = false;
			selectors = true;
		}
		if (commands) {
			std::cin >> tmp;
			if (tmp == "?") {
				std::cout << "? == " << bloki.numberOfSections() << std::endl;
			}
			else if (tmp == "****") {
				break;
			}
			else if (tmp.is_in("S,?")) {
				int n;
				tmp.cut(tmp.length() - 4); //remove S,?
				n = atoi(tmp.c_str());
				size_t result = bloki.numberOfSelectorsInSection(n);
				std::cout << n << ",S,? == " << result << std::endl;
			}
			
		}

	}
	bloki.printBlocks();
	
	return 0;
}