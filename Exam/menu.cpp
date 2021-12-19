#include "menu.h"

void Menu::PrintMenu() noexcept {
	std::cout << "[1] - Login to the program as an administrator" << endl;
	std::cout << "[2] - Login to the program as an guest" << endl;
	std::cout << "[0] - Exit program\n" << endl;
}

void Menu::PrintGuestMenu() noexcept {
	std::cout << "[1] - Create a new order" << endl;
	std::cout << "[2] - Delete order from stock" << endl;
	std::cout << "[3] - Add ingredients to dish" << endl;
	std::cout << "[4] - Remove ingredients from dish" << endl;
	std::cout << "[5] - Info Client Dish" << endl;
	std::cout << "[6] - Show Client Basket" << endl;
	std::cout << "[7] - Show Client History" << endl;
	std::cout << "[8] - Submit an order for processing" << endl;
	std::cout << "[0] - Main Menu\n" << endl;
}

void Menu::PrintAdminMenu() noexcept {
	std::cout << "[1] - Create a new dish template" << endl;
	std::cout << "[2] - Remove dish template" << endl;
	std::cout << "[3] - Add product to stock" << endl;
	std::cout << "[4] - Remove product from the stock" << endl;
	std::cout << "[5] - Increase product in stock" << endl;
	std::cout << "[6] - Decrease product from the stock" << endl;
	std::cout << "[7] - Show Restaurant Stock" << endl;
	std::cout << "[8] - Show Restaurant Menu" << endl;
	std::cout << "[9] - Show Restaurant Statistics" << endl;
	std::cout << "[0] - Main Menu\n" << endl;
}
