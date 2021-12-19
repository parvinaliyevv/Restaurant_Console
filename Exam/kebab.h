#pragma once
#include "interface.h"

namespace food {
	class Kebab : public Interface {
	public:
		Kebab(const string& nameP, const int& priceP) : Interface(nameP, priceP, 2) {}
	};
}
