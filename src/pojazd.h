#ifndef POJAZD
#define POJAZD

#include <string>

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