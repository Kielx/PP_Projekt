#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>
// Sleep dla niepoprawnych logowan
#include <chrono>
#include <thread>
// Weryfikacja wprowadzanych danych
#include <limits>

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
void addCar(Pojazd **head_ref)
{

  Pojazd *new_node = new Pojazd;
  std::cout << "Podaj numer rejestracyjny: ";
  std::getline(std::cin >> std::ws, new_node->numerRej);
  // Sprawdzamy, czy wprowadzony numer jest poprawny
  // Jeśli zawiera spacje, to zwracamy odpowiedni komunikat
  if (std::cin.fail() || new_node->numerRej.find(' ') != std::string::npos)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Niepoprawny numer rejestracyjny. Numer nie może zawierać spacji.\n";
    return;
  }

  std::cout << "Podaj nazwe: ";
  std::getline(std::cin >> std::ws, new_node->nazwa);
  std::cout << "Podaj rok: ";
  std::cin >> new_node->rok;
  // Sprawdzamy, czy wprowadzony rok jest poprawny
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Podano niepoprawny rok produkcji.\n";
    return;
  }

  std::cout << "Podaj przebieg pojazdu: ";
  std::cin >> new_node->przebieg;
  // Sprawdzamy, czy wprowadzony przebieg jest poprawny
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Podano nieprawidłowy przebieg pojazdu.\n";
    return;
  }

  new_node->next = NULL;
  std::ofstream plik;
  plik.open("pojazdy/" + new_node->numerRej + ".txt");
  plik << new_node->numerRej << std::endl
       << new_node->nazwa << std::endl
       << new_node->rok << std::endl
       << new_node->przebieg << std::endl;
  push(head_ref, new_node);
}

void addUser(User **head_ref)
{
  User *new_node = new User;
  std::cout << "Podaj imie: ";
  std::getline(std::cin >> std::ws, new_node->imie);
  // Sprawdzamy, czy wprowadzone imie jest poprawne
  // Jeśli zawiera spacje, to zwracamy odpowiedni komunikat
  if (std::cin.fail() || new_node->imie.find(' ') != std::string::npos)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Podano niepoprawne imię, nie może ono zawierać spacji. Jeśli Twoje imię jest dwuczłonowe, połącz je za pomocą znaku '-'\n";
    return;
  }
  std::cout << "Podaj nazwisko: ";
  std::getline(std::cin >> std::ws, new_node->nazwisko);
  // Sprawdzamy, czy wprowadzone imie jest poprawne
  // Jeśli zawiera spacje, to zwracamy odpowiedni komunikat
  if (std::cin.fail() || new_node->nazwisko.find(' ') != std::string::npos)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Podano niepoprawne nazwisko, nie może ono zawierać spacji. Jeśli Twoje nazwisko jest dwuczłonowe, połącz je za pomocą znaku '-'\n";
    return;
  }
  new_node->numerRejPojazdu = "brak";
  new_node->next = NULL;
  std::ofstream plik;
  plik.open("users/" + new_node->imie + "-" + new_node->nazwisko + ".txt");
  plik << new_node->imie << std::endl
       << new_node->nazwisko << std::endl
       << new_node->numerRejPojazdu << std::endl;
  push(head_ref, new_node);
}

std::fstream &GotoLine(std::fstream &file, int num)
{
  file.seekg(std::ios::beg);
  for (int i = 0; i < num - 1; ++i)
  {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return file;
}

void addOpis()
{
  std::string numerRej;
  std::string opis;
  std::string podpis;
  unsigned int przebieg;
  std::string data;
  std::cout << "Podaj numer rejestracyjny pojazdu: ";
  std::cin >> numerRej;

  std::ofstream plik;
  if (std::filesystem::exists("pojazdy/" + numerRej + ".txt"))
  {
    std::cout << "Podaj opis: ";
    std::getline(std::cin >> std::ws, opis);
    std::cout << "Podaj datę wpisu: ";
    std::getline(std::cin >> std::ws, data);
    std::cout << "Podaj aktualny przebieg: ";
    std::cin >> przebieg;
    std::cout << "Podaj podpis: ";
    std::getline(std::cin >> std::ws, podpis);
    plik.open("pojazdy/" + numerRej + ".txt", std::ios::app);
    plik
        << "-" << std::endl
        << "opis:" << opis << std::endl
        << "data:" << data << std::endl
        << "przebieg:" << przebieg << std::endl
        << "podpis:" << podpis << std::endl
        << "---" << std::endl;
    std::cout << "Poprawnie dodano wpis do pojazdu " << numerRej << std::endl;
    // Zmieniamy przebieg pojazdu w pliku
    std::fstream plik("pojazdy/" + numerRej + ".txt");
    GotoLine(plik, 4);
    plik << przebieg << std::endl;

    plik.close();
  }
  else
  {
    std::cout << "Dodawanie wpisu nie powiodło się - Podany pojazd nie istnieje w bazie danych" << std::endl;
  }
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
  *head = NULL;
  std::array<std::string, 4> dane;
  for (const auto &entry : fs::directory_iterator(path))
  {

    std::string line;
    std::ifstream myfile(entry.path());
    if (myfile.is_open())
    {
      for (int i = 0; i < 4; i++)
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
    nowy->przebieg = std::stoi(dane.at(3));
    push(head, nowy);
  }
}

void synchronizuj(std::string path, User **head)
{
  *head = NULL;
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

void linkUserToCar()
{
  std::string numerRej;
  std::string imie;
  std::string nazwisko;
  std::string line;
  std::cout << "Podaj numer rejestracyjny pojazdu: ";
  std::cin >> numerRej;
  std::cout << "Podaj imie: ";
  std::cin >> imie;
  std::cout << "Podaj nazwisko: ";
  std::cin >> nazwisko;
  std::fstream plik;
  plik.open("users/" + imie + "-" + nazwisko + ".txt");
  if (plik.is_open())
  {
    plik << imie << std::endl
         << nazwisko << std::endl
         << numerRej << std::endl;
    std::cout << "Poprawnie zapisano dane" << std::endl;
  }
  else
  {
    std::cout << "Nie udało się zapisać danych do pliku" << std::endl;
  }

  plik.close();
}

int main()
{
  Pojazd *headPojazd = NULL;
  User *headUser = NULL;
  int failed = 0;
  int success = 0;
  std::string cont = "";
  while (!strcmp(cont.c_str(), "n") == 0 && success == 0)
  {
    if (login())
    {
      success++;
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
      failed++;
      std::cout << "Niepoprawne dane logowania" << std::endl;
      if (failed % 3 == 0)
      {
        std::cout << "Zbyt wiele nieprawidłowych prób logowania, upewnij się, że klawisz Caps-Lock jest wyłączony i spróbuj ponownie za chwilę" << std::endl;
        std::chrono::milliseconds timespan(5000);
        std::this_thread::sleep_for(timespan);
      }
      std::cout << "Czy chcesz spróbować ponownie? (t/n) ";
      std::cin >> cont;
    }
  }

  return 0;
}