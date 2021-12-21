#pragma once
#include "interface.h"

namespace food {
	class Dolma : public Interface {
	public:
		Dolma(const string& nameP, const int& priceP) : Interface(nameP, priceP, 4) {}

		Interface* GetCopy() const noexcept override {
			return new Dolma(*this);
		}
	};
}
