#include <iostream>
#include <string>
#include "Chipers/abash_cipher.cpp"


int main() {
	Abash_Cipher Abash("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "file.txt");
	std::cout << Abash << std::endl;

	return 0;
}