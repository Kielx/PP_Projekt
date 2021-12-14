#ifndef USER
#define USER

#include <string>

/**
 * @brief Klasa uzytkownika
 *
 */
class User
{
public:
  std::string imie;
  std::string nazwisko;
  std::string numerRejPojazdu;
  User *next;
  Pojazd *pojazd;
};

#endif