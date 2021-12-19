#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>

using namespace std;

#define SEPARATOR " | "

class Table {
public:
	Table(const short& lengthP, initializer_list<string>&& categoryP, initializer_list<short>&& paddingsP);

	void PrintTableHeader();

	template<typename T> // Template modullara bolunmur - late binding
	void PrintTable(T data) {
		size_t index = 1;

		PrintTableHeader();

		for (auto n : data)
			cout << '[' << setw(_lengthID) << index++ << ']' << SEPARATOR << *n << endl;

		cout << endl;
	}

private:
	vector<string> _category;
	vector<short> _paddings;
	short _lengthID;
	short _lengthLine;

};
