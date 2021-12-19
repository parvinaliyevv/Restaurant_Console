#include "stock.h"

namespace kitchen {
	void Stock::AddProduct(const string& nameP, const int& caloriesP, const int& priceP, const int& amountP) {
		for (auto n = _provisions.begin(); n != _provisions.end(); n++) {
			if ((*n)->product->_name._Equal(nameP)) {
				(*n)->Increase(amountP);
				return;
			}
		}

		_provisions.insert(shared_ptr<Provision> { new Provision(new Product(nameP, caloriesP, priceP), amountP) });
	}
	void Stock::DelProduct(const int& indexP) {
		size_t indexor = 1;

		for (auto n = _provisions.begin(); n != _provisions.end(); n++) {
			if (indexor++ == indexP) {
				_provisions.erase(n);
				return;
			}
		}

		throw DatabaseException("Product with this index is out of stock!");
	}

	shared_ptr<Provision> Stock::GetProvision(const string& nameP) const noexcept {
		for (auto n = _provisions.begin(); n != _provisions.end(); n++)
			if ((*n)->product->_name._Equal(nameP)) return *n;

		return nullptr;
	}
	shared_ptr<Provision> Stock::GetProvision(const int& indexP) const noexcept {
		size_t indexor = 1;

		if (indexP > NULL && indexP <= _provisions.size()) {
			for (auto n = _provisions.begin(); n != _provisions.end(); n++)
				if (indexor++ == indexP) return (*n);
		}

		return nullptr;
	}

	bool Stock::SaveStock() const noexcept {
		ofstream file("stock.txt");

		file.setf(std::ios_base::left);

		if (file.is_open()) {
			string name;

			for (auto n = _provisions.begin(); n != _provisions.end(); n++) {

				name = (*n)->product->_name;
				replace_if(name.begin(), name.end(), ReplaceStringSymbol(' '), '_');

				file << setw(30) << name
					 << setw(10) << (*n)->product->_calories
					 << setw(10) << (*n)->product->_price
					 << setw(10) << (*n)->_quantity << endl;

				name.clear();
			}
		}
		else return false;

		file.close();

		return true;
	}
	bool Stock::LoadStock() noexcept {
		ifstream file("stock.txt");

		if (file.is_open()) {
			string name;
			int calories, price, quantity;

			while (!file.eof()) {

				file >> name >> calories >> price >> quantity;

				if (name._Equal("")) break;
				else {
					replace_if(name.begin(), name.end(), ReplaceStringSymbol('_'), ' ');
					AddProduct(name, calories, price, quantity);
				}

				name.clear();
			}
		}
		else return false;

		file.close();

		return true;
	}

	void Stock::ShowStock() const noexcept {
		short length = to_string(_provisions.size() + 10).size();

		if (!_provisions.empty()) {
			Table table(length, { "Name", "Calories", "Price", "Quantity" }, { 30, 10, 10, 10 });

			table.PrintTable(_provisions);
		}
		else cout << "Empty Stock!\n" << endl;
	}
}
