#pragma once
#include "interface.h"

namespace food {
	class Khangal : public Interface {
	public:
		Khangal(const string& nameP, const int& priceP) : Interface(nameP, priceP, 3) {}
	};
}
