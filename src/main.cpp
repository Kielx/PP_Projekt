#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>

#include "login.h"
#include "pojazd.h"
#include "user.h"
#include "menu.h"
#include "addAdmin.h"
#include "colors.h"

// Sprawdza z jakiej platformy korzysta uzytkownik
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__linux__)
#define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE,
#else
#define PLATFORM_NAME NULL
#endif

// Zwraca nazwe platformy jesli jest podana, w przeciwnym wypadku pusta
const char *get_platform_name()
{
  return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}

namespace fs = std::filesystem;

void push(Pojazd **head_ref, Pojazd *pojazd)
{
  pojazd->next = (*head_ref);
  (*head_ref) = pojazd;
}

void push(User **head_ref, User *user)
{
  user->next = (*head_ref);
  (*head_ref) = user;
}

// TODO: Change input to getline to avoid bugs with spaces
void addCar(Pojazd **head_ref)
{
  Pojazd *new_node = new Pojazd;
  std::cout << "Podaj numer rejestracyjny: ";
  std::cin >> new_node->numerRej;
  std::cout << "Podaj nazwe: ";
  std::getline(std::cin >> std::ws, new_node->nazwa);
  std::cout << "Podaj rok: ";
  std::cin >> new_node->rok;
  new_node->next = NULL;
  std::ofstream plik;
  plik.open("pojazdy/" + new_node->numerRej + ".txt");
  plik << new_node->numerRej << std::endl
       << new_node->nazwa << std::endl
       << new_node->rok << std::endl;
  push(head_ref, new_node);
}

void addUser(User **head_ref)
{
  User *new_node = new User;
  std::cout << "Podaj imie: ";
  std::cin >> new_node->imie;
  std::cout << "Podaj nazwisko: ";
  std::cin >> new_node->nazwisko;
  std::cout << "Podaj numer rejestracyjny pojazdu: ";
  std::cin >> new_node->numerRejPojazdu;
  new_node->next = NULL;
  std::ofstream plik;
  plik.open("users/" + new_node->imie + "-" + new_node->nazwisko + ".txt");
  plik << new_node->imie << std::endl
       << new_node->nazwisko << std::endl
       << new_node->numerRejPojazdu << std::endl;
  push(head_ref, new_node);
}

void addOpis()
{
  std::string numerRej;
  std::string opis;
  std::string podpis;
  std::cout << "Podaj numer rejestracyjny pojazdu: ";
  std::cin >> numerRej;
  std::cout << "Podaj opis: ";
  std::getline(std::cin >> std::ws, opis);
  std::cout << "Podaj podpis: ";
  std::getline(std::cin >> std::ws, podpis);
  std::ofstream plik;
  plik.open("pojazdy/" + numerRej + ".txt", std::ios::app);
  plik
      << "-" << std::endl
      << opis << std::endl
      << podpis << std::endl
      << "---" << std::endl;
}

void listFiles(std::string path)
{
  for (const auto &entry : fs::directory_iterator(path))
  {
    std::string line;
    std::ifstream myfile(entry.path()); //"pojazdy/" + entry.path().filename().string());
    if (myfile.is_open())
    {
      while (getline(myfile, line))
      {
        std::cout << line << '\n';
      }
      myfile.close();
    }

    else
      std::cout << "Unable to open file";
  }
}

void synchronizuj(std::string path, Pojazd **head)
{
  std::array<std::string, 3> dane;
  for (const auto &entry : fs::directory_iterator(path))
  {

    std::string line;
    std::ifstream myfile(entry.path());
    if (myfile.is_open())
    {
      for (int i = 0; i < 3; i++)
      {
        getline(myfile, line);
        dane.at(i) = line;
      }
      myfile.close();
    }
    else
      std::cout << "Unable to open file";

    Pojazd *nowy = NULL;
    nowy = new Pojazd();
    nowy->numerRej = dane.at(0);
    nowy->nazwa = dane.at(1);
    nowy->rok = std::stoi(dane.at(2));
    push(head, nowy);
  }
}

void synchronizuj(std::string path, User **head)
{
  std::array<std::string, 3> dane;
  for (const auto &entry : fs::directory_iterator(path))
  {
    std::string line;
    std::ifstream myfile(entry.path());
    if (myfile.is_open())
    {
      for (int i = 0; i < 3; i++)
      {
        getline(myfile, line);
        dane.at(i) = line;
      }
      myfile.close();
    }
    else
      std::cout << "Unable to open file";

    User *nowy = NULL;
    nowy = new User();
    nowy->imie = dane.at(0);
    nowy->nazwisko = dane.at(1);
    nowy->numerRejPojazdu = dane.at(2);
    push(head, nowy);
  }
}

void linkUsersToCars(User **head, Pojazd **head2)
{
  User *tmp = *head;
  Pojazd *tmp2 = *head2;
  while (tmp != NULL)
  {
    while (tmp2 != NULL)
    {
      if (tmp->numerRejPojazdu == tmp2->numerRej)
      {
        tmp->pojazd = tmp2;
        tmp2->user = tmp;
        break;
      }
      tmp2 = tmp2->next;
    }
    tmp = tmp->next;
    tmp2 = *head2;
  }
}

int main()
{
  Pojazd *headPojazd = NULL;
  User *headUser = NULL;

  if (login())
  {

    if (strcmp(get_platform_name(), "linux") == 0 || strcmp(get_platform_name(), "windows") == 0)
    {
      system("tar -xzf data.tar.gz");
      synchronizuj("pojazdy/", &headPojazd);
      synchronizuj("users/", &headUser);
      linkUsersToCars(&headUser, &headPojazd);
      menu(headPojazd, headUser);
      system("tar -czf data.tar.gz users pojazdy");
      system("rm -r users pojazdy");
    }
    else
    {
      std::cout << "Twój system nie obsługuje tej aplikacji" << std::endl;
    }
  }
  else
  {
    std::cout << "Niepoprawne dane logowania" << std::endl;
  }
  return 0;
}