#include "table.h"

Table::Table(const short& lengthP, initializer_list<string>&& categoryP, initializer_list<short>&& paddingsP) {
	this->_lengthID = lengthP;
	this->_lengthLine = lengthP + 2; // 2 - scope size

	for (int i = 0; i < categoryP.size(); i++) {
		this->_category.push_back(*(categoryP.begin() + i));
		this->_paddings.push_back(*(paddingsP.begin() + i));
		this->_lengthLine += *(paddingsP.begin() + i) + 3; // 3 - separator size
	}
}

void Table::PrintTableHeader() {
	cout << left << setfill('-');
	cout << setw(_lengthID + _lengthLine) << '-' << endl;

	cout << setfill(' ') << '[' << setw(_lengthID) << "NO" << ']' << SEPARATOR;

	for (int i = 0; i < _category.size(); i++) {
		cout << setw(_paddings[i]) << _category[i] << SEPARATOR;
	}

	cout << endl << setfill('-') << setw(_lengthID + _lengthLine) << '-' << endl;
	cout << left << setfill(' ');
}
