#include <cpr/cpr.h>
#include <iostream>
#include <string>

int main()
{
	std::cout << "Introdu numele: ";
	std::string name;
	std::cin >> name;
	std::string url = "http://localhost:18080";

	auto response = cpr::Put(cpr::Url{ url + name });

	return 0;
}