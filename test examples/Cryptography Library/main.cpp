#include <iostream>
#include <string>
using namespace std;

#include "cryptor.hpp"

int main()
{
    cryptor::set_key("it is my custom key!");
	std::string line;
	std::getline(std::cin, line);
    auto enc = cryptor::encrypt(line);
    auto dec = cryptor::decrypt(enc);
    cout << "key: " << cryptor::get_key() << endl;
    cout << "enc: " << enc << endl;
    cout << "dec: " << dec << endl;
}