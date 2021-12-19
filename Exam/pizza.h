#pragma once
#include "interface.h"

namespace food {
	class Pizza : public Interface {
	public:
		Pizza(const string& nameP, const int& priceP) : Interface(nameP, priceP, 1) {}
	};
}
