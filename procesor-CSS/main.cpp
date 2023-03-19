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

	size_t numberOfSelectorsInSection(int n) {
		int current = 0;
		Node* tmp = head;

		while (n > ROZ) {
			tmp = tmp->next;
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

				std::cout << s << std::endl;;

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