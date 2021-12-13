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
  User *next;
  std::string numerRejPojazdu;
  Pojazd *pojazd;
};

#endif