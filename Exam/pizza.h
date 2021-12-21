#pragma once
#include "interface.h"

namespace food {
	class Pizza : public Interface {
	public:
		Pizza(const string& nameP, const int& priceP) : Interface(nameP, priceP, 1) {}

		Interface* GetCopy() const noexcept override {
			return new Pizza(*this);
		}
	};
}
