#include "Admin.h"

void Admin::NewDish(Restaurant& restaurant) {
	int index;

	restaurant.ShowCategory();

	cout << "Enter dish index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;

	system("cls");

	restaurant.AddDish(index);
}
void Admin::DelDish(Restaurant& restaurant) {
	int index;

	restaurant.ShowMenu("admin");

	cout << "Enter dish index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;
	
	system("cls");

	restaurant.DelDish(index);
}

void Admin::NewProduct(Restaurant& restaurant) {
	string name;

	restaurant._stock->ShowStock();

	cout << "Enter product name or NULL to break: ";
	getline(cin, name);

	if (name._Equal("0")) return;

	if (restaurant._stock->GetProvision(name)) throw DatabaseException("The product is already in stock!");

	int ccal, price, amount;

	cout << "Enter product calories: ";
	cin >> ccal;

	cin.ignore();

	if (ccal == NULL) return;

	cout << "Enter product price: ";
	cin >> price;

	cin.ignore();

	if (price == NULL) return;

	cout << "Enter product amount: ";
	cin >> amount;

	cin.ignore();

	if (amount == NULL) return;

	system("cls");

	int&& money = amount * price;

	if (restaurant.GetMoney() < money) throw DatabaseException("Not enough money in the restaurant!");

	restaurant._stock->AddProduct(name, price, ccal, amount);
	restaurant.DecreaseMoney(money);
}
void Admin::DelProduct(Restaurant& restaurant) {
	int index;

	restaurant._stock->ShowStock();

	cout << "Enter product index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;

	system("cls");

	restaurant._stock->DelProduct(index);
}

void Admin::IncreaseProduct(Restaurant& restaurant) {
	int index;

	restaurant._stock->ShowStock();

	cout << "Enter product index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;

	system("cls");
	
	auto provision = restaurant._stock->GetProvision(index);

	if (provision) {
		int amount;

		cout << "Enter product amount: ";
		cin >> amount;

		cin.ignore();

		int&& money = amount * provision->product->GetPrice();

		if (restaurant.GetMoney() < money) {
			throw DatabaseException("Not enough money in the restaurant!");
		}
		else {
			provision->Increase(amount);
			restaurant.DecreaseMoney(money);
		}

	}
	else throw DatabaseException("Product with this index is out of stock!");
}
void Admin::DecreaseProduct(Restaurant& restaurant) {
	int index;

	restaurant._stock->ShowStock();

	cout << "Enter product index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;

	system("cls");

	auto provision = restaurant._stock->GetProvision(index);

	if (provision) {
		int amount;

		cout << "Enter product amount: ";
		cin >> amount;

		cin.ignore();

		provision->Decrease(amount);
	}
	else throw DatabaseException("Product with this NO is out of stock!");
}

void Admin::ShowStatistics(Restaurant& restaurant) noexcept {
	auto statistics = restaurant.LoadStatistics();
	short length = to_string(statistics.size() + 10).size();

	cout << "The restaurant currently has " << restaurant.GetMoney() << '$' << endl << endl;

	system("pause");
	system("cls");

	Table table(length, { "Year", "Month", "Day", "Income" }, { 10, 10, 10, 10 });
	table.PrintTable(statistics);
}
