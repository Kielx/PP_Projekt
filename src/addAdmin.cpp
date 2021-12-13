#include <string>
#include <iostream>
#include <fstream>

#include "encrypt.h"

void addAdmin()
{
  srand((unsigned)time(NULL));
  std::string username;
  std::string password;
  int random = 5 + (rand() % 20);
  std::cout << "Podaj nazwe uzytkownika: ";
  std::cin >> username;
  std::cout << "Podaj haslo: ";
  std::getline(std::cin >> std::ws, password);
  std::ofstream plik;
  plik.open("authdata.txt", std::ios::app);
  plik
      << std::endl
      << encrypt(username, random) << ";" << random << ";" << encrypt(password, random);
}
