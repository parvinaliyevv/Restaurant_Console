#include <conio.h>

#include "restaurant.h"
#include "admin.h"
#include "guest.h"
#include "menu.h"

using namespace std;

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"

// ABOUT

/*

Desing pis alinib, consolda design eliyemmedim, evezine table hazirladim

Exceptionlar mainde tutulur

Ingredientleri inheritance elemedim, eleseydim sirf kateqoriyalara bolmek lazim olacaqdi
pendir daxil etmek istesem pendir kateqoriyasi mutleq olmali idi.

Yemekleri inheritance eledim 4 kateqoriyaya uygun fayldan oxuyananda da down and up cast eliyir

Fayl save ve load restaurant classin constructor ve destructorunda gedir

friend classlar - cout overloading eliyende her defe funksiyalar cagirmasin deye yazilib

virtual methodlari yeniden override elemedim elave eliyesi bir sey aglima gelmedi,
lakin nese elave olunsa inheritance olan classlara problemsiz override olunacaq

Admin yeni yemey elave edende productlar cixmir, sablon olaraq menyuya elave olunur

*/

int main() {
	system("color E");

	Restaurant restaurant("Come Again!");
	short choice;

	cout << "Welcome to the restaurant called << Come Again >> !" << endl;
	system("pause");

respawn:
	system("cls");

	Menu::PrintMenu();

	cout << "Enter one of the paragraphs: ";
	choice = _getch() - 48;

	system("cls");

	if (choice == NULL) return EXIT_SUCCESS;
	else if (choice == 1) {
		void (Admin:: * func[9])(Restaurant&) = {
				&Admin::NewDish, &Admin::DelDish, &Admin::NewProduct, &Admin::DelProduct,
				&Admin::IncreaseProduct, &Admin::DecreaseProduct, &Admin::ShowStock, &Admin::ShowMenu, &Admin::ShowStatistics
		};
		bool flag = false;

		{
			string name, password;

			cout << "Enter your admin username: ";
			getline(cin, name);

			cout << "Enter your admin password: ";
			getline(cin, password);

			system("cls");

			if (name._Equal(ADMIN_USERNAME) && password._Equal(ADMIN_PASSWORD)) flag = true;
		}

		if (flag) {
			unique_ptr<Admin> admin{ new Admin };

			while (true) {
				Menu::PrintAdminMenu();

				cout << "Enter one of the paragraphs: ";
				choice = _getch() - 48;

				system("cls");

				if (choice == NULL) goto respawn;
				else if (choice < NULL || choice > 9) {
					cout << "You entered the wrong paragraph!\n";
					continue;
				}

				try {
					((*admin).*func[choice - 1])(restaurant);
				}
				catch (const  std::exception& ex) {
					cout << ex.what() << endl;
				}

				system("pause");
				system("cls");
			}
		}
		else {
			cout << "You entered an incorrect username or password!\n";
			system("pause");
			goto respawn;
		}
	}
	else if (choice == 2) {
		unique_ptr<Guest> guest;
		void (Guest:: * func)(Restaurant&) = nullptr;

		{
			string name;

			cout << "Enter the full name of the guest: ";
			getline(cin, name);

			system("cls");

			try {
				guest = unique_ptr<Guest>{ new Guest(name) };
			}
			catch (const std::exception& ex) {
				cout << ex.what() << endl;
				system("pause");
				goto respawn;
			}
		}

		while (true) {
			Menu::PrintGuestMenu();

			cout << "Enter one of the paragraphs: ";
			choice = _getch() - 48;

			system("cls");

			switch (choice) {
			case 0:
				goto respawn;
				break;
			case 1:
				func = &Guest::NewOrder;
				break;
			case 2:
				func = &Guest::DelOrder;
				break;
			case 3:
				func = &Guest::AddIngredientOnDish;
				break;
			case 4:
				func = &Guest::DelIngredientOnDish;
				break;
			case 5:
				func = &Guest::InfoDish;
				break;
			case 6:
				func = &Guest::ShowBasket;
				break;
			case 7:
				func = &Guest::ShowHistory;
				break;
			case 8:
				func = &Guest::SubmitBasket;
				break;
			default:
				cout << "You entered the wrong paragraph!\n";
				system("cls");
				continue;
			}

			try {
				((*guest).*func)(restaurant);
			}
			catch (const exception& ex) {
				cout << ex.what() << endl;
			}

			system("pause");
			system("cls");
		}
	}
	else {
		cout << "You entered the wrong paragraph!\n";
		system("pause");
		goto respawn;
	}

	return EXIT_SUCCESS;
}
