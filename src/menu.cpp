#include <iostream>

#include "pojazd.h"
#include "user.h"
#include "main.h"
#include "colors.h"

void menu(Pojazd *headPojazd, User *headUser)
{

  int wybor = 0;

  std::string kontynuuj = "T";
  std::cout << CLEARSCREEN;
  do
  {
    std::cout << COLOR_BOLDRED
              << "\t**********Witaj w programie obslugujacym dzialanie serwisu!**********\n"
              << COLOR_RESET;
    std::cout
        << COLOR_BOLDRED
        << "\t**********Wybierz jedna z nastepujacych opcji poprzez wpisanie wlasciwej cyfry!**********\n"
        << COLOR_RESET << std::endl;
    std::cout << "1: Wypisz listę pojazdów\n";
    std::cout << "2: Wypisz listę użytkowników\n";
    std::cout << "3: Dodaj pojazd\n";
    std::cout << "4: Dodaj użytkownika\n";
    std::cout << "5: Dodaj opis do pojazdu\n";
    std::cout << "0: Opusc program\n";
    std::cin >> wybor;

    switch (wybor)
    {

    case 1:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 1 - Wypisz liste pojazdow" << COLOR_RESET
                << std::endl;
      printList(headPojazd);
      break;
    }
    case 2:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 2 - Wypisz liste użytkowników" << COLOR_RESET
                << std::endl;
      printList(headUser);
      break;
    }
    case 3:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 3 - Dodaj pojazd" << COLOR_RESET
                << std::endl;
      addCar(&headPojazd);
      break;
    }
    case 4:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 4 - Dodaj użytkownika" << COLOR_RESET
                << std::endl;
      addUser(&headUser);
      break;
    }
    case 5:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 5 - Dodaj opis" << COLOR_RESET
                << std::endl;
      addOpis();
      break;
    }
    case 0:
    {
      std::cout << COLOR_BOLDBLUE << "Wybrales 0 - Opuszczam program. Dziekujemy za korzystanie." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Wybrales niewlasciwa liczbe!" << std::endl;
    }
    }
    if (wybor != 0)
    {
      std::cout << "\n"
                << COLOR_BOLDGREEN
                << "Czy chcesz kontynuowac? T/n: "
                << COLOR_RESET;
      std::cin >> kontynuuj;
      wybor = (kontynuuj == "N" || kontynuuj == "n") ? 0 : 1;
      std::cout << CLEARSCREEN;
      linkUsersToCars(&headUser, &headPojazd);
    }

  } while (wybor != 0);
}