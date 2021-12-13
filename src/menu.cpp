#include <iostream>

#include "pojazd.h"
#include "user.h"
#include "main.h"

/**
 * @defgroup COLOR_GROUP COLOR Definicje kolorow uzywanych w terminalu
 *
 * @brief Definicje kolorow uzywanych w terminalu
 * @{
 */
#define COLOR_RESET "\033[0m"
/** Black */
#define COLOR_BLACK "\033[30m"
/** Red */
#define COLOR_RED "\033[31m"
/** Green */
#define COLOR_GREEN "\033[32m"
/** Yellow */
#define COLOR_YELLOW "\033[33m"
/** Blue */
#define COLOR_BLUE "\033[34m"
/** Magenta */
#define COLOR_MAGENTA "\033[35m"
/** Cyan */
#define COLOR_CYAN "\033[36m"
/** White */
#define COLOR_WHITE "\033[37m"
/** Bold Black */
#define COLOR_BOLDBLACK "\033[1m\033[30m"
/** Bold Red */
#define COLOR_BOLDRED "\033[1m\033[31m"
/** Bold Green */
#define COLOR_BOLDGREEN "\033[1m\033[32m"
/** Bold Yellow */
#define COLOR_BOLDYELLOW "\033[1m\033[33m"
/** Bold Blue */
#define COLOR_BOLDBLUE "\033[1m\033[34m"
/** Bold Magenta */
#define COLOR_BOLDMAGENTA "\033[1m\033[35m"
/** Bold Cyan */
#define COLOR_BOLDCYAN "\033[1m\033[36m"
/** Bold White */
#define COLOR_BOLDWHITE "\033[1m\033[37m"
/** Magiczna komenda czyszczaca ekran terminala ref. https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code */
#define CLEARSCREEN "\033[H\033[2J\033[3J"
/**@}*/

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
      int ile;
      std::cout << COLOR_BOLDBLUE << "Wybrales 3 - Dodaj pojazd" << COLOR_RESET
                << std::endl;
      addCar(&headPojazd);
      break;
    }
    case 4:
    {
      std::cout << CLEARSCREEN;
      int ile;
      std::cout << COLOR_BOLDBLUE << "Wybrales 4 - Dodaj użytkownika" << COLOR_RESET
                << std::endl;
      addUser(&headUser);
      break;
    }
    case 5:
    {
      std::cout << CLEARSCREEN;
      int ile;
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