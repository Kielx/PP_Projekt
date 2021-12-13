#ifndef POJAZD
#define POJAZD

#include <string>

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
  Pojazd *next;
  std::string opis;
};

#endif