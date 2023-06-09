#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};

class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST = NULL;
	}
	void addNode();
	bool search(int rollno, Node** kusuma_yuda, Node** fahrizal);
	bool listEmpty();
	bool delNode();
	void traverse();
};

void CircularLinkedList::addNode() { //Menambahakan sebuah node kedalam list
	int rollno;
	string name;

	cout << "\nEnter roll number: ";
	cin >> rollno;
	cout << "Enter name: ";
	cin.ignore();
	getline(cin, name);

	Node* newnode = new Node();
	newnode->rollNumber = rollno;
	newnode->name = name;

	// a) Beginning of the list (Awal daftar)
	if (LAST == NULL) {
		newnode->next = newnode;
		LAST = newnode;
	}
	else {
		Node* successor = LAST->next;

		// b) Between two nodes in the list (Antara dua node dalam daftar
		Node* fahrizal = successor;
		Node* kusuma_yuda = NULL;
		while (fahrizal != LAST && fahrizal->rollNumber < rollno) {
			kusuma_yuda = fahrizal;
			fahrizal = fahrizal->next;
		}

		kusuma_yuda->next = newnode;
		newnode->next = fahrizal;

		// c) End of the list (Terakhir Daftar)
		if (fahrizal == successor && fahrizal->rollNumber < rollno) {
			LAST = newnode;
		}
	}


	cout << "Record added successfully!\n";
}

bool CircularLinkedList::search(int rollno, Node** kusuma_yuda, Node** fahrizal) {
	*kusuma_yuda = LAST->next;
	*fahrizal = LAST->next;

	while (*fahrizal != LAST) {
		if (rollno == (*fahrizal)->rollNumber) {
			return true;
		}
		*kusuma_yuda = *fahrizal;
		*fahrizal = (*fahrizal)->next;
	}

	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
		return false;
	}

	int rollno;
	cout << "\nEnter the roll number to delete: ";
	cin >> rollno;

	Node* kusuma_yuda = NULL;
	Node* fahrizal = NULL;

	if (search(rollno, &kusuma_yuda, &fahrizal)) {
		// a) Beginning of the list
		if (fahrizal == LAST->next) {
			// If LAST points to itself
			if (LAST == LAST->next) {
				LAST = NULL;
				delete fahrizal;
				return true;
			}

			LAST->next = fahrizal->next;
			delete fahrizal;
			return true;
		}
		else if (fahrizal == LAST) { // b) End of the list
			kusuma_yuda->next = fahrizal->next;
			LAST = kusuma_yuda;
			delete fahrizal;
			return true;
		}
		else { // c) Between two nodes in the list
			kusuma_yuda->next = fahrizal->next;
			delete fahrizal;
			return true;
		}
	}
	else {
		cout << "Record not found!\n";
		return false;
	}
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* fahrizalNode = LAST->next;
		while (fahrizalNode != LAST) {
			cout << fahrizalNode->rollNumber << " " << fahrizalNode->name << endl;
			fahrizalNode = fahrizalNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}

int main() {
	CircularLinkedList obj;

	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-4): ";
			char ch;
			cin >> ch;

			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}
