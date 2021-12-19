#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <set>

#include "provision.h"
#include "product.h"
#include "table.h"
#include "functor.h"
#include "exceptions.h"

using namespace std;
using namespace exceptions;

namespace kitchen {
	class Stock {
	public:
		Stock() = default;
		Stock& operator=(const Stock& other) = delete;

		void AddProduct(const string& nameP, const int& caloriesP, const int& priceP, const int& amountP) throw(MyException);
		void DelProduct(const int& index) throw(MyException);

		shared_ptr<Provision> GetProvision(const string& nameP) const noexcept;
		shared_ptr<Provision> GetProvision(const int& index) const noexcept;

		bool SaveStock() const noexcept;
		bool LoadStock() noexcept;

		void ShowStock() const noexcept;

	private:
		set<shared_ptr<Provision>> _provisions;

	};
}
