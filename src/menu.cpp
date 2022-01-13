#include <iostream>

#include "pojazd.h"
#include "user.h"
#include "main.h"
#include "colors.h"
#include "display.h"
#include "delete.h"

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
    std::cout << "3: Wyswietl dane pojazdu\n";
    std::cout << "4: Wyswietl dane użytkownika\n";
    std::cout << "5: Dodaj/Edytuj pojazd\n";
    std::cout << "6: Dodaj użytkownika\n";
    std::cout << "7: Połącz użytkownika z pojazdem\n";
    std::cout << "8: Dodaj opis do pojazdu\n";
    std::cout << "9: Usuń pojazd\n";
    std::cout << "10: Usuń użytkownika\n";
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
      std::cout << COLOR_BOLDBLUE << "Wybrales 3 - Wyswietl dane pojazdu" << COLOR_RESET
                << std::endl;
      wyswietlDanePojazdu(headPojazd);
      break;
    }
    case 4:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 4 - Wyswietl dane użytkownika" << COLOR_RESET
                << std::endl;
      wyswietlDaneUzytkownika(headUser);
      break;
    }
    case 5:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 5 - Dodaj pojazd" << COLOR_RESET
                << std::endl;
      addCar(&headPojazd);
      break;
    }
    case 6:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 6 - Dodaj użytkownika" << COLOR_RESET
                << std::endl;
      addUser(&headUser);
      break;
    }
    case 7:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 7 - Połącz użytkownika z pojazdem" << COLOR_RESET
                << std::endl;
      linkUserToCar();
      break;
    }
    case 8:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 8 - Dodaj wpis serwisowy pojazdu" << COLOR_RESET
                << std::endl;
      addOpis();
      break;
    }
    case 9:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 9 - Usuń pojazd" << COLOR_RESET
                << std::endl;
      deleteCar(&headPojazd);
      break;
    }
    case 10:
    {
      std::cout << CLEARSCREEN;
      std::cout << COLOR_BOLDBLUE << "Wybrales 10 - Usuń użytkownika" << COLOR_RESET
                << std::endl;
      deleteUser(&headUser);
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
      synchronizuj("pojazdy/", &headPojazd);
      synchronizuj("users/", &headUser);

      linkUsersToCars(&headUser, &headPojazd);
    }

  } while (wybor != 0);
}