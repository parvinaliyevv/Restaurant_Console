#include "Restaurant.h"

Restaurant::Restaurant(const string& nameP) : _safeDeposit(NULL), _stock(new Stock) {
	SetName(nameP);

	_category.push_back(new string("Pizza"));
	_category.push_back(new string("Kebab"));
	_category.push_back(new string("Khangal"));
	_category.push_back(new string("Dolma"));

	_stock->LoadStock();
	LoadDishs();
	LoadSafeDeposit();
}
Restaurant::~Restaurant() {
	_stock->SaveStock();
	SaveDishs();
	SaveSafeDeposit();
}

void Restaurant::SetName(const string& nameP) {
	if (nameP.size() < 3) throw ArgumentException("Restaurant name cannot be shorter than 3 characters!");
	this->_name = nameP;
}

void Restaurant::IncreaseMoney(const int& moneyP) {
	if (moneyP < NULL || moneyP > INT_MAX / 2) throw ArgumentException("Money cannot be negative or fantastic!");

	this->_safeDeposit += moneyP;
	SaveStatistics(moneyP, income);
}
void Restaurant::DecreaseMoney(const int& moneyP) {
	if (moneyP < NULL || moneyP > INT_MAX / 2) throw ArgumentException("Money cannot be negative or fantastic!");
	else if (moneyP > this->_safeDeposit) throw DatabaseException("Not enough money in the restaurant!");

	this->_safeDeposit -= moneyP;
	SaveStatistics(moneyP, cost);
}

bool Restaurant::CheckDish(shared_ptr<Interface> dish) const noexcept {
	for (auto n : dish->GetIngredients()) {
		auto temp = _stock->GetProvision(n->product->GetName());

		if (temp) {
			if (temp->GetQuantity() >= n->GetQuantity()) continue;
			else return false;
		}
		else return false;
	}

	return true;
}
Interface* Restaurant::CopyDish(const int& indexP) {
	shared_ptr<Interface> dish = GetDish(indexP);
	Interface* copy = nullptr;

	if (!dish) throw DatabaseException("Dish with this index is out of stock!");

	if (dish->GetDishCategory() == 1) {
		Pizza* derived = dynamic_cast<Pizza*>(&(*dish));
		copy = new Pizza(*derived);
	}
	else if (dish->GetDishCategory() == 2) {
		Kebab* derived = dynamic_cast<Kebab*>(&(*dish));
		copy = new Kebab(*derived);
	}
	else if (dish->GetDishCategory() == 3) {
		Khangal* derived = dynamic_cast<Khangal*>(&(*dish));
		copy = new Khangal(*derived);
	}
	else if (dish->GetDishCategory() == 4) {
		Dolma* derived = dynamic_cast<Dolma*>(&(*dish));
		copy = new Dolma(*derived);
	}
	else throw ArgumentException("Wrong Meal ID!");

	return copy;
}

shared_ptr<Interface> Restaurant::GetDish(const int& indexP) const noexcept {
	size_t indexor = 1;

	for (auto n = _dishs.begin(); n != _dishs.end(); n++)
		if (CheckDish((*n))) {
			if (indexor++ == indexP) return *n;
		}

	return nullptr;
}
shared_ptr<Interface> Restaurant::GetDish(const string& nameP) const noexcept {
	for (auto n = _dishs.begin(); n != _dishs.end(); n++)
		if ((*n)->GetName()._Equal(nameP)) return *n;

	return nullptr;
}

void Restaurant::ShowMenu(const string& name) const noexcept {
	short length = to_string(_dishs.size() + 10).size();

	if (name._Equal("guest")) {
		list<shared_ptr<Interface>> dishs;

		for (auto n : _dishs) {
			if (CheckDish(n)) dishs.push_back(n);
		}

		if (!dishs.empty()) {
			Table table(length, { "Name", "Calories", "Price" }, { 30, 10, 10 });

			table.PrintTable(dishs);
		}
		else cout << "Empty Menu!" << endl;
	}
	else {
		if (!_dishs.empty()) {
			Table table(length, { "Name", "Calories", "Price" }, { 30, 10, 10 });

			table.PrintTable(_dishs);
		}
		else cout << "Empty Menu!" << endl;
	}
}
void Restaurant::ShowCategory() const noexcept {
	Table table(2, { "Name" }, { 20 });
	table.PrintTable(_category);
}

void Restaurant::AddDish(const int& mealID) {
	Interface* dish = nullptr;
	string name;

	ShowMenu();

	cout << "Enter the name of the dish: ";
	getline(cin, name);

	if (GetDish(name)) throw DatabaseException("The dish is already in menu!");

	int price;

	cout << "Enter the price of the dish: ";
	cin >> price;

	cin.ignore();
	system("cls");

	switch (mealID) {
	case 1:
		dish = new Pizza(name, price);
		break;
	case 2:
		dish = new Kebab(name, price);
		break;
	case 3:
		dish = new Khangal(name, price);
		break;
	case 4:
		dish = new Dolma(name, price);
		break;
	default:
		throw ArgumentException("Wrong Meal index!");
	}

	dish->PrepareIngredients(_stock);
	_dishs.push_back(shared_ptr<Interface>(dish));
}
void Restaurant::AddDish(const string& nameP, const int& priceP, const int& mealCategory, const vector<Provision>& ingredients) {
	Interface* dish = nullptr;

	switch (mealCategory) {
	case 1:
		dish = new Pizza(nameP, priceP);
		break;
	case 2:
		dish = new Kebab(nameP, priceP);
		break;
	case 3:
		dish = new Khangal(nameP, priceP);
		break;
	case 4:
		dish = new Dolma(nameP, priceP);
		break;
	default:
		throw ArgumentException("Wrong Meal index!");
	}

	for (auto n : ingredients) dish->IncreaseIngredient(n, n.GetQuantity());
	_dishs.push_back(shared_ptr<Interface>(dish));
}
void Restaurant::DelDish(const int& indexP) {
	size_t indexor = 1;

	if (!_dishs.empty()) {
		for (auto n = _dishs.begin(); n != _dishs.end(); n++)
			if (indexor++ == indexP) {
				_dishs.erase(n);
				return;
			}
	}

	throw DatabaseException("Dish with this index is out of stock!");
}

void Restaurant::CookDish(list<shared_ptr<Dish>>& _basket) {
	for (auto n = _basket.begin(); n != _basket.end(); n++) {
		(*n)->dish->Cook();
		IncreaseMoney((*n)->dish->GetPrice() * (*n)->GetAmount());
		cout << endl << endl;
	}

	system("cls");

	cout << "All dishs are ready, order is ready. Bon Appetit!\n" << endl;
}

void Restaurant::SaveDishs() const noexcept {
	ofstream file("dishs.txt");
	file.close();

	for (auto n : _dishs) n->SaveDish();
}
bool Restaurant::LoadDishs() noexcept {
	ifstream file("dishs.txt");

	if (file.is_open()) {
		string name, ingredient;
		int mealCategory, price, amount, quantity, calories;
		vector<Provision> ingredients;

		while (!file.eof()) {
			file >> name >> mealCategory >> price >> amount;

			for (int i = 0; i < amount; i++) {
				file >> ingredient >> calories >> quantity;
				replace_if(ingredient.begin(), ingredient.end(), ReplaceStringSymbol('_'), ' ');
				ingredients.push_back(Provision(new Product(ingredient, calories, 1), quantity));
			}

			if (name._Equal("")) break;
			else {
				replace_if(name.begin(), name.end(), ReplaceStringSymbol('_'), ' ');
				AddDish(name, price, mealCategory, ingredients);
			}

			ingredients.clear();
			name.clear();
		}

	}
	else return false;

	file.close();

	return true;
}

void Restaurant::SaveSafeDeposit() const noexcept {
	ofstream file("restaurant_safe_deposit.txt");

	if (file.is_open()) file << _safeDeposit;

	file.close();
}
void Restaurant::LoadSafeDeposit() noexcept {
	ifstream file("restaurant_safe_deposit.txt");

	if (file.is_open()) file >> _safeDeposit;

	file.close();
}

bool Restaurant::SaveStatistics(const int& moneyP, const int& modeP) const noexcept {
	ofstream file("restaurant_statistics.txt", ios_base::app);
	file.setf(std::ios_base::left);

	auto temp = time(NULL);
	tm* now = new tm;
	localtime_s(now, &temp);

	if (file.is_open()) {

		file << setw(5) << modeP
			<< setw(10) << moneyP
			<< setw(10) << now->tm_year + 1900 // ctime vaxti duzgun hesablamir
			<< setw(10) << now->tm_mon + 1
			<< setw(10) << now->tm_mday << endl;

	}
	else return true;

	file.close();

	return false;
}
vector<shared_ptr<Restaurant::RestaurantStatistics>> Restaurant::LoadStatistics() noexcept {
	ifstream file("restaurant_statistics.txt");

	vector<shared_ptr<RestaurantStatistics>> statistics;

	if (file.is_open()) {

		while (!file.eof()) {
			shared_ptr<RestaurantStatistics> statistic{ new RestaurantStatistics };
			int mode = NULL;

			file >> mode >> statistic->money >> statistic->year >> statistic->month >> statistic->day;

			for (auto n = statistics.begin(); n != statistics.end(); n++) {
				if ((*(*n)) == (*statistic)) {
					if (mode == income) (*n)->money += statistic->money;
					else if (mode == cost) (*n)->money += -(statistic->money);

					mode = NULL;
					break;
				}
			}

			if (mode == NULL) continue;
			else {
				if (mode == cost) statistic->money += -(statistic->money) * 2; // for negative
				statistics.push_back(statistic);
			}
		}

	}

	file.close();

	return statistics;
}
