#include "dish.h"

namespace food {
	Interface::Interface(const string& nameP, const int& priceP, const int& dishCategoryP) : _dishCategory(dishCategoryP) {
		SetName(nameP);
		SetPrice(priceP);
	}

	void Interface::SetName(const string& nameP) {
		if (nameP.size() < 3) throw ArgumentException("Dish name cannot be shorter than 3 characters!");
		this->_name = nameP;
	}
	void Interface::SetPrice(const int& priceP) {
		if (priceP < NULL || priceP > INT_MAX / 2) throw ArgumentException("The price of a dish cannot be negative or fantasy!");
		this->_price = priceP;
	}

	void Interface::IncreaseIngredient(Provision productP, const int& quantityP) {
		for (auto n = _ingredients.begin(); n != _ingredients.end(); n++) {
			if ((*n)->product->GetName()._Equal(productP.product->GetName())) {
				(*n)->Increase(quantityP);
				return;
			}
		}

		productP.SetQuantity(quantityP);
		_ingredients.push_back(shared_ptr<Provision> { new Provision(productP) });
	}
	void Interface::DecreaseIngredient(Provision productP, const int& quantityP) {
		for (auto n = _ingredients.begin(); n != _ingredients.end(); n++) {
			if ((*n)->product->GetName()._Equal(productP.product->GetName())) {
				(*n)->Decrease(quantityP);

				if ((*n)->GetQuantity() == NULL) _ingredients.erase(n);
				return;
			}
		}

		throw DatabaseException("Ingredient with this index is not in dish!");
	}

	size_t Interface::GetIngredientsCalories() const noexcept {
		size_t result = NULL;

		for (auto n = _ingredients.begin(); n != _ingredients.end(); n++)
			result += (*n)->product->GetCalories() * (*n)->GetQuantity();

		return result;
	}
	const Provision& Interface::GetIngredient(const int& indexP) const {
		size_t indexor = 1;

		if (indexP > NULL && indexP <= _ingredients.size())
			for (auto n : _ingredients) if (indexor++ == indexP) return (*n);

		throw DatabaseException("Ingredient with this index is out of in dish!");
	}

	void Interface::ShowIngredients() const noexcept {
		short length = to_string(_ingredients.size() + 10).size();

		Table table(length, { "Name", "Calories", "TRASH :(", "Quantity" }, { 30, 10, 10, 10 });
		table.PrintTable(_ingredients);
	}

	bool Interface::SaveDish() const noexcept {
		ofstream file("dishs.txt", ios_base::app);

		file.setf(std::ios_base::left);

		if (file.is_open()) {
			string name = _name;
			replace_if(name.begin(), name.end(), ReplaceStringSymbol(' '), '_');

			file << setw(30) << name
				 << setw(5) << _dishCategory
				 << setw(10) << _price
				 << setw(5) << _ingredients.size();

			for (auto n = _ingredients.begin(); n != _ingredients.end(); n++) {
				string ingredient = (*n)->product->GetName();
				replace_if(ingredient.begin(), ingredient.end(), ReplaceStringSymbol(' '), '_');

				file << setw(30) << ingredient
					 << setw(10) << (*n)->product->GetCalories()
					 << setw(10) << (*n)->GetQuantity();
			}

			file << endl;
		}
		else return false;

		file.close();

		return true;
	}
	void Interface::Info() const noexcept {
		cout << "Name: " << _name << endl;
		cout << "Price: " << _price << endl;
		cout << "Total calories: " << GetIngredientsCalories() << endl;
		cout << "Ingredients:\n" << endl;

		ShowIngredients();
	}
	void Interface::PrepareIngredients(const unique_ptr<Stock>& stock) {
		while (!cin.fail()) {
			int index, amount;

			stock->ShowStock();

			cout << "Enter ingredient index or NULL for continue: ";
			cin >> index;

			cin.ignore();

			if (index == NULL) break;

			cout << "Enter the amount of ingredients or NULL for continue: ";
			cin >> amount;

			cin.ignore();

			if (amount == NULL) break;

			system("cls");

			auto product = stock->GetProvision(index);

			if (product) IncreaseIngredient(*product, amount);
			else throw DatabaseException("Ingredient with this index is out of stock!");
		}
	}
	void Interface::Cook() const noexcept {
		cout << "Took an order called " << _name << endl;
		cout << "We take and put the plum ingredients on the dish..." << endl;
		Sleep(_ingredients.size() * 1000);

		cout << "Let's start cooking..." << endl;
		Sleep(3000);

		cout << "The order called " << _name << " is ready!" << endl;
	}
}
