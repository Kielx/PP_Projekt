#ifndef POJAZD
#define POJAZD

#include <string>

class User;

/**
 * @brief Klasa pojazdu
 *
 */
class Pojazd
{
public:
  std::string numerRej;
  std::string nazwa;
  int rok;
  User *user;
  std::string opis;
  Pojazd *next;
};

#endif