#pragma once
#include <iostream>
#include <string>

#include "restaurant.h"
#include "exceptions.h"
#include "table.h"

using namespace std;
using namespace exceptions;

class Admin {
public:
	Admin() = default;
	Admin(const Admin& other) = delete;
	Admin& operator=(const Admin& other) = delete;

	void NewDish(Restaurant& restaurant) throw(MyException);
	void DelDish(Restaurant& restaurant) throw(MyException);

	void NewProduct(Restaurant& restaurant) throw(MyException);
	void DelProduct(Restaurant& restaurant) throw(MyException);

	void IncreaseProduct(Restaurant& restaurant) throw(MyException);
	void DecreaseProduct(Restaurant& restaurant) throw(MyException);

	void ShowMenu(Restaurant& restaurant) noexcept { restaurant.ShowMenu("admin"); }
	void ShowStock(Restaurant& restaurant) noexcept { restaurant._stock->ShowStock(); }

	void ShowStatistics(Restaurant& restaurant) noexcept;
};
