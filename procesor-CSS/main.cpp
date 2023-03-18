#include <iostream>
#define ROZ 8

//sekcje jako listy 2 



template<typename T>
class List {
	
private:
	T data;
	List* next;
public:


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
		List* temp = this;
		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	int getLen() {
		List* temp = this;
		int len = 0;
		while (temp != nullptr) {
			len++;
			temp = temp->next;
		}
		return len;
	}
};



class Block {
public:
	List<std::string> selektor;
	List<std::string> atrybuty;
	bool used;
	Block()
		: selektor(""), atrybuty(""), used(false)
	{

	}

	Block(std::string selektor, std::string atrybut)
		:selektor(selektor), atrybuty(atrybut), used(true)
	{
	}
};

//template<typename T>
class ListLinked {

public:
	Block* blocks;
	size_t size;
	ListLinked* next;
	ListLinked* prev;

	ListLinked()
		:blocks(new Block[ROZ]), size(0), next(nullptr), prev(nullptr)
	{
	}

	void addBlock(Block block) {
		if (size < ROZ) {
			for (int i = 0; i < ROZ; i++) {
				if (blocks[i].used == false) {
					this->blocks[i] = block;
					this->blocks[i].used = true;
					this->size++;
					break;
				}
			}
		}
		else {
			ListLinked* temp = new ListLinked();
			temp->prev = this;
			this->next = temp;
		}

	}

	void printBlocks() {
		for (int i = 0; i < ROZ; i++) {
			if (blocks[i].used == true) {
				blocks[i].selektor.print();
				blocks[i].atrybuty.print();
			}
		}
	}

	~ListLinked() {
		delete[] blocks;
	}
};




int main() {
	ListLinked bloki;

	bool selectors = true;
	bool atributes = false;
	while (true) {

		std::string tmp;
		Block block;
		if (selectors) {
			bool end = false;
			block.used = true;
			while (true) {
				std::cin >> tmp;
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
				else {
					block.selektor.add(tmp);
				}
			}
			if (end) break;
		}
		if (atributes) {

			std::string value;
			bool running = true;
			while (tmp != "}" && value != "}" && running ) {
				if (tmp != "") {
					block.selektor.add(tmp.substr(1));
					tmp = "";
				}
				else {
					std::cin >> tmp;
					if (tmp == "}") break;
					tmp.pop_back();
				}
				std::cin >> value;
				if (value == "}") break;
				std::cout << value.back();
				if (value.back() == '}') {
					value.pop_back();
					running = false;
				}
				
				value.pop_back();

				block.atrybuty.add(tmp + " == " +  value);
				tmp = "";
			}
			bloki.addBlock(block);
			atributes = false;
			selectors = true;
		}

	}
	bloki.printBlocks();

	
	return 0;
}