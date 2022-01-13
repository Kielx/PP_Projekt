#include <iostream>
#include <fstream>
#include <filesystem>

#include "pojazd.h"
#include "user.h"
#include "menu.h"
#include "colors.h"

void printList(Pojazd *n)
{
  int licznik = 0;
  std::cout << std::endl;
  std::cout << COLOR_BOLDYELLOW << "\t Lista pojazdow: " << COLOR_RESET << std::endl;
  std::cout << std::endl;
  while (n != NULL)
  {
    licznik++;
    std::cout << COLOR_BOLDWHITE "\t\t" << licznik << COLOR_RESET << std::endl;
    std::cout << "Numer rejestracyjny: " << COLOR_BOLDWHITE << n->numerRej << COLOR_RESET << std::endl;
    std::cout << "Typ: " << COLOR_BOLDWHITE << n->nazwa << COLOR_RESET << std::endl;
    std::cout << "Rok produkcji: " << COLOR_BOLDWHITE << n->rok << COLOR_RESET << std::endl;
    std::cout << "Przebieg: " << COLOR_BOLDWHITE << n->przebieg << COLOR_RESET << std::endl;
    n->user ? std::cout << "Właściciel: " << COLOR_BOLDWHITE << n->user->imie << " " << n->user->nazwisko << COLOR_RESET << std::endl : std::cout << "Właściciel: " << COLOR_BOLDRED << "Brak" << COLOR_RESET << std::endl;
    std::cout << std::endl;
    n = n->next;
  }
}

void printList(User *n)
{
  int licznik = 0;
  std::cout << std::endl;
  std::cout << COLOR_BOLDYELLOW << "\t Lista Użytkowników: " << COLOR_RESET << std::endl;
  std::cout << std::endl;
  while (n != NULL)
  {
    licznik++;
    std::cout << COLOR_BOLDWHITE "\t\t" << licznik << COLOR_RESET << std::endl;
    std::cout << "Imie i nazwisko: " << COLOR_BOLDWHITE << n->imie << " " << n->nazwisko << COLOR_RESET << std::endl;
    if (n->pojazd)
    {
      std::cout << "Numer rejestracyjny pojazdu: " << COLOR_BOLDWHITE << n->numerRejPojazdu << COLOR_RESET << std::endl;
      std::cout << "Typ pojazdu: " << COLOR_BOLDWHITE << n->pojazd->nazwa << COLOR_RESET << std::endl;
      std::cout << "Rok produkcji: " << COLOR_BOLDWHITE << n->pojazd->rok << COLOR_RESET << std::endl;
    }
    else
    {
      std::cout << "Pojazd: " << COLOR_BOLDRED << "Brak" << COLOR_RESET << std::endl;
    }

    std::cout << std::endl;
    n = n->next;
  }
}

void wyswietlDanePojazdu(Pojazd *head)
{
  Pojazd *tmp = head;
  std::string numerRejestracyjny;
  std::cout << "Podaj numer rejestracyjny pojazdu, którego dane chcesz wyświetlić: ";
  std::cin >> numerRejestracyjny;
  // Sprawdzamy czy lista jest pusta - jesli tak to podajemy odpowiedni komunikat
  if (tmp == NULL)
  {
    std::cout << "Lista pojazdów jest pusta" << std::endl;
  }
  // Jesli lista nie jest pusta to wykonujemy petle, ktora przechodzi przez cala liste
  while (tmp != NULL)
  {
    // Jesli numer rejestracyjny znajduje sie w liscie to wyswietlamy dane
    if (tmp->numerRej == numerRejestracyjny)
    {
      int licznik = 0;
      std::cout << "Numer rejestracyjny: " << tmp->numerRej << std::endl
                << "Nazwa: " << tmp->nazwa << std::endl
                << "Rok: " << tmp->rok << std::endl;
      // Sprawdzamy czy do pojazdu dopisany jest wlasciciel - jesli tak to wyswietlamy dane
      // Jesli nie to nie wyswietlamy
      // Bez tego warunku w przypadku braku wlasciciela wyswietlil by sie blad
      if (tmp->user)
      {
        std::cout << "Właściciel: " << tmp->user->imie << " " << tmp->user->nazwisko << std::endl;
      }
      // Otwieramy plik z danymi pojazdu
      std::ifstream plik;
      plik.open("pojazdy/" + numerRejestracyjny + ".txt");
      if (plik.is_open())
      {
        std::string line;
        // Dopóki nie napotkamy końca pliku iterujemy po kazdej linii
        while (getline(plik, line))
        {
          // Jeśli linia to "-" oznacza to, że pojazd ma opis
          if (line == "-")
          {
            // Zwiekszamy licznik by wiedziec ktory wpis w pliku jest opisem
            licznik++;
            std::cout << licznik << " Wpis:" << std::endl;
            while (getline(plik, line))
            {
              // Jesli doszlismy do konca oznaczonego "---" to znaczy, ze konczymy wczytywanie opisu
              if (line == "---")
              {
                break;
              }
              // Jesli nie to wyswietlamy linie opisu
              std::cout << line << std::endl;
            }
          }
        }
        // Jesli licznik jest rowny 0 to pojazd nie ma opisu
        if (licznik == 0)
        {
          std::cout << "Nie dodano jeszcze żadnych wpisów dla tego pojazdu" << std::endl;
        }
        // Zamykamy plik
        plik.close();
      }
      else
        std::cout << "Nie udało się otworzyć pliku" << std::endl;
      return;
    }
    // Przechodzimy kolejno przez kazdy element listy do momentu napotkania numeru rejestracyjnego
    tmp = tmp->next;
  }
  // Jesli nie znaleziono pojazdu w liscie to wyswietlamy odpowiedni komunikat
  std::cout << "Podanego pojazdu nie znaleziono na liście" << std::endl;
}

void wyswietlDaneUzytkownika(User *head)
{
  User *tmp = head;
  std::string imie;
  std::string nazwisko;
  std::cout << "Podaj imię użytkownika: ";
  std::cin >> imie;
  std::cout << "Podaj nazwisko użytkownika: ";
  std::cin >> nazwisko;
  int licznik = 0;
  // Sprawdzamy czy lista jest pusta - jesli tak to podajemy odpowiedni komunikat
  if (tmp == NULL)
  {
    std::cout << "Lista użytkowników jest pusta" << std::endl;
  }
  // Jesli lista nie jest pusta to wykonujemy petle, ktora przechodzi przez cala liste
  while (tmp != NULL)
  {
    // Jesli numer rejestracyjny znajduje sie w liscie to wyswietlamy dane
    if (tmp->imie == imie && tmp->nazwisko == nazwisko)
    {
      licznik++;
      std::cout << "Imie: " << tmp->imie << std::endl
                << "Nazwisko: " << tmp->nazwisko << std::endl;

      // Sprawdzamy czy do pojazdu dopisany jest wlasciciel - jesli tak to wyswietlamy dane
      // Jesli nie to nie wyswietlamy
      // Bez tego warunku w przypadku braku wlasciciela wyswietlil by sie blad
      if (tmp->pojazd)
      {
        std::cout << "Numer rejestracyjny pojazdu: " << tmp->pojazd->numerRej << std::endl
                  << "Typ pojazdu: " << tmp->pojazd->nazwa << std::endl
                  << "Rok produkcji: " << tmp->pojazd->rok << std::endl;
      }
    }
    // Przechodzimy kolejno przez kazdy element listy do momentu napotkania użytkownika o podanych danych
    tmp = tmp->next;
  }
  // Jesli nie znaleziono pojazdu w liscie to wyswietlamy odpowiedni komunikat
  if (licznik == 0)
    std::cout << "Podanego użytkownika nie znaleziono w bazie" << std::endl;
}