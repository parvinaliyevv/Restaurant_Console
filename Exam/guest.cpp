#include "Guest.h"

void Guest::SetName(const string& fullnameP) {
	if (fullnameP.size() < 3) throw ArgumentException("The name cannot be shorter than 3 characters!");
	this->_fullname = fullnameP;
}

shared_ptr<Dish> Guest::GetOrder(const int& index) const noexcept {
	uint32_t indexsor = 1;

	for (auto n : _basket)
		if (indexsor++ == index) return n;

	return shared_ptr<Dish>(nullptr);
}

void Guest::NewOrder(Restaurant& restaurant) {
	int index, amount;

	restaurant.ShowMenu();

	cout << "Enter dish index or NULL for break: ";
	cin >> index;

	cin.ignore();

	if (index == NULL) return;

	cout << "Enter the amount of dish or NULL for break: ";
	cin >> amount;

	cin.ignore();
	system("cls");

	if (amount == NULL) return;

	for (auto n : _basket) {
		if (restaurant.GetDish(index)->GetName()._Equal(n->dish->GetName())) {
			for (auto j : n->dish->GetIngredients()) {
				auto temp = restaurant._stock->GetProvision(j->product->GetName());
				temp->Decrease(amount * j->GetQuantity());
			}
			n->Increase(amount);
			return;
		}
	}

	auto copy = restaurant.CopyDish(index);
	auto dish = shared_ptr<Dish>{ new Dish(copy, amount) };

	for (auto n : dish->dish->GetIngredients()) {
		auto temp = restaurant._stock->GetProvision(n->product->GetName());
		temp->Decrease(amount * n->GetQuantity());
	}

	_basket.push_back(dish);
}
void Guest::DelOrder(Restaurant& restaurant) {
	if (_basket.empty()) throw DatabaseException("You haven't ordered anything yet!");

	int indexsor = 1, index;

	ShowBasket(restaurant);

	cout << "Enter order index or NULL for break: ";
	cin >> index;

	cin.ignore();
	system("cls");

	if (index == NULL) return;

	for (auto n = _basket.begin(); n != _basket.end(); n++) {
		if (indexsor++ == index) {
			_basket.erase(n);
			return;
		}
	}

	throw DatabaseException("There is no order in the cart with this index!");
}

void Guest::AddIngredientOnDish(Restaurant& restaurant) {
	if (_basket.empty()) throw DatabaseException("You haven't ordered anything yet!");

	int index;

	ShowBasket(restaurant);

	cout << "Enter order index or NULL for break: ";
	cin >> index;

	cin.ignore();
	system("cls");

	if (index == NULL) return;

	auto order = GetOrder(index);
	if (!order) throw DatabaseException("Order with this index was not found!");

	while (!cin.fail()) {
		int index, amount;

		restaurant._stock->ShowStock();

		cout << "Enter ingredient index or NULL for break: ";
		cin >> index;

		if (index == NULL) break;

		cout << "Enter the amount of ingredients or NULL for break: ";
		cin >> amount;

		if (amount == NULL) break;

		cin.ignore();
		system("cls");

		auto ingredient = restaurant._stock->GetProvision(index);

		if (ingredient) {
			if (amount > ingredient->GetQuantity()) throw DatabaseException("There are not enough ingredients in the stock!");
			order->dish->IncreaseIngredient(*ingredient, amount);
			ingredient->Decrease(amount);
		}
		else throw DatabaseException("Ingredient with this index is out of stock!");
	}

	cin.ignore();
}
void Guest::DelIngredientOnDish(Restaurant& restaurant) {
	if (_basket.empty()) throw DatabaseException("You haven't ordered anything yet!");

	int index;

	ShowBasket(restaurant);

	cout << "Enter order index or NULL for break: ";
	cin >> index;

	cin.ignore();
	system("cls");

	if (index == NULL) return;

	auto order = GetOrder(index);
	if (!order) throw DatabaseException("Order with this index was not found!");

	while (!cin.fail()) {
		int index, amount;

		order->dish->ShowIngredients();

		cout << "Enter ingredient index or NULL for break: ";
		cin >> index;

		if (index == NULL) break;

		cout << "Enter the amount of ingredients or NULL for break: ";
		cin >> amount;

		if (amount == NULL) break;

		cin.ignore();
		system("cls");

		auto ingredient = restaurant._stock->GetProvision(order->dish->GetIngredient(index).product->GetName());

		if (ingredient) {
			order->dish->DecreaseIngredient(*ingredient, amount);
			ingredient->Increase(amount);
		}
		else throw DatabaseException("Product with this index is out of stock!");
	}

	cin.ignore();
}

void Guest::ShowHistory(Restaurant& restaurant) {
	auto history = LoadHistory();
	if (!history[0]) throw DatabaseException("Your order history is out of stock!");

	short length = to_string(history.size() + 10).size();


	Table table(length, { "Name", "Price", "Amount", "Date" }, { 30, 10, 10, 25 });
	table.PrintTable(history);
}
void Guest::ShowBasket(Restaurant& restaurant) {
	short length = to_string(_basket.size() + 10).size();

	if (!_basket.empty()) {
		Table table(length, { "Name", "Calories", "Price", "Amount" }, { 30, 10, 10, 10 });
		table.PrintTable(_basket);
	}
	else cout << "Empty Basket!\n" << endl;
}
void Guest::InfoDish(Restaurant& restaurant) {
	if (_basket.empty()) throw DatabaseException("You haven't ordered anything yet!");

	int index;

	ShowBasket(restaurant);

	cout << "Enter order index or NULL for break: ";
	cin >> index;

	cin.ignore();
	system("cls");

	if (index == NULL) return;

	auto order = GetOrder(index);
	if (!order) throw DatabaseException("Order with this index was not found!");

	order->dish->Info();
}

void Guest::SubmitBasket(Restaurant& restaurant) {
	if (_basket.empty()) throw DatabaseException("You haven't ordered anything yet!");
	else {
		for (auto n : _basket) SaveHistory(n);
		restaurant.CookDish(_basket);
		_basket.clear();
	}
}

bool Guest::SaveHistory(shared_ptr<Dish> data) const {
	ofstream file("client_history.txt", ios_base::app);
	file.setf(std::ios_base::left);

	if (file.is_open()) {
		string fullnameClient = _fullname, nameDish = data->dish->GetName(), date;

		auto temp = time(NULL);
		char* buffer = new char[50];
		ctime_s(buffer, 50, &temp);

		date = buffer;

		replace_if(fullnameClient.begin(), fullnameClient.end(), ReplaceStringSymbol(' '), '_');
		replace_if(nameDish.begin(), nameDish.end(), ReplaceStringSymbol(' '), '_');
		replace_if(date.begin(), date.end(), ReplaceStringSymbol(' '), '_');

		file << setw(30) << fullnameClient
			<< setw(30) << nameDish
			<< setw(10) << data->dish->GetPrice()
			<< setw(10) << data->GetAmount()
			<< setw(25) << date;

	}
	else return false;

	return true;
}
vector<shared_ptr<Guest::ClientHistory>> Guest::LoadHistory() const {
	ifstream file("client_history.txt");

	vector<shared_ptr<ClientHistory>> history;

	if (file.is_open()) {
		string fullnameClient;

		while (!file.eof()) {
			shared_ptr<ClientHistory> order{ new ClientHistory };

			file >> fullnameClient >> order->nameDish >> order->price >> order->amount >> order->date;

			replace_if(fullnameClient.begin(), fullnameClient.end(), ReplaceStringSymbol('_'), ' ');
			replace_if(order->nameDish.begin(), order->nameDish.end(), ReplaceStringSymbol('_'), ' ');
			replace_if(order->date.begin(), order->date.end(), ReplaceStringSymbol('_'), ' ');

			if (fullnameClient._Equal("")) break;
			else if (!_fullname._Equal(fullnameClient)) continue;
			else history.push_back(order);

			fullnameClient.clear();
		}

	}
	else return vector<shared_ptr<Guest::ClientHistory>>{nullptr};

	return history;
}

