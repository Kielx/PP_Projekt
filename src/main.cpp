#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

#include "login.h"
#include "pojazd.h"
#include "user.h"
#include "menu.h"
#include "addAdmin.h"

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

void printList(Pojazd *n)
{
  std::cout << "Lista pojazdow: " << std::endl;
  while (n != NULL)
  {
    std::cout << n->numerRej << " " << n->nazwa << " " << n->rok << std::endl;
    n = n->next;
  }
}

void printList(User *n)
{
  std::cout << "Lista uzytkownikow: " << std::endl;
  while (n != NULL)
  {
    std::cout << n->imie << " " << n->nazwisko << " " << n->numerRejPojazdu << " " << n->pojazd->nazwa << " " << n->pojazd->rok << std::endl;
    n = n->next;
  }
}

// TODO: Change input to getline to avoid bugs with spaces
void addCar(Pojazd **head_ref)
{
  Pojazd *new_node = new Pojazd;
  std::cout << "Podaj numer rejestracyjny: ";
  std::cin >> new_node->numerRej;
  std::cout << "Podaj nazwe: ";
  std::cin >> new_node->nazwa;
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

int main()
{
  Pojazd *headPojazd = NULL;
  User *headUser = NULL;
  synchronizuj("pojazdy/", &headPojazd);
  synchronizuj("users/", &headUser);
  linkUsersToCars(&headUser, &headPojazd);
  if (login())
  {
    menu(headPojazd, headUser);
  }
  else
  {
    std::cout << "Niepoprawne dane logowania" << std::endl;
  }
  return 0;
}