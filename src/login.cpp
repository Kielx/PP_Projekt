#include <iostream>
#include <fstream>
#include <string>

#include "colors.h"
/**
 * @brief Funkcja ktora weryfikuje poprawnosc danych logowania
 *
 * @param username - nazwa uzytkownika
 * @param password - haslo uzytkownika
 * @return true - jesli dane logowania sa poprawne
 * @return false - jesli dane logowania sa niepoprawne
 */
bool authenticate(const std::string &username, const std::string &password)
{
  std::ifstream file("authdata.txt");
  std::string fusername, fpassword;

  while (file)
  {
    std::getline(file, fusername, ';'); // use ; as delimiter
    std::getline(file, fpassword);      // use line end as delimiter
    // remember - delimiter readed from input but not added to output
    if (fusername == username && fpassword == password)
      return true;
  }
  return false;
}

/**
 * @brief Funkcja sterujaca logowaniem
 *
 * @return true - jesli uzytkownik wpisal poprawne dane logowania
 * @return false - jesli uzytkownik wpisal niepoprawne dane logowania
 */
bool login()
{
  std::cout << CLEARSCREEN;
  std::cout << COLOR_BOLDRED
            << "\t**********Witaj w programie obslugujacym dzialanie serwisu!**********\n"
            << COLOR_RESET;
  std::cout
      << COLOR_BOLDRED
      << "**********Przed skorzystaniem z programu musisz się zalogować**********\n"
      << COLOR_RESET << std::endl;
  std::string username, password;
  std::cout << "Podaj nazwę użytkownika: ";
  std::cin >> username;
  std::cout << "Podaj hasło: ";
  std::cin >> password;
  return (int)authenticate(username, password);
}