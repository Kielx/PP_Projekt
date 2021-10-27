#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

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

class Pojazd
{
public:
  std::string numerRej;
  std::string nazwa;
  int rok;
  Pojazd *next;
  std::string opis;
};

class User
{
public:
  std::string imie;
  std::string nazwisko;
  User *next;
  std::string numerRejPojazdu;
  Pojazd *pojazd;
};

/**
 * @brief Dodaje element na poczatku listy
 * 
 * @param head_ref - wskaznik na poczatek listy
 * @param pojazd - wskaznik nowego element
 */
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

/**
 * @brief Funkcja wypisuje zawartośc listy
 * 
 * @param n - wskaznik na poczatek listy
 */
void printList(Pojazd *n)
{
  std::cout << "Lista pojazdow: " << std::endl;
  while (n != NULL)
  {
    std::cout << n->numerRej << " " << n->nazwa << " " << n->rok << std::endl;
    n = n->next;
  }
}

/**
 * @brief Funkcja wypisuje na ekran liste uzytkownikow
 * 
 * @param n - wskaznik na poczatek listy uzytkownikow
 */
void printList(User *n)
{
  std::cout << "Lista uzytkownikow: " << std::endl;
  while (n != NULL)
  {
    std::cout << n->imie << " " << n->nazwisko << " " << n->numerRejPojazdu << " " << n->pojazd->nazwa << " " << n->pojazd->rok << std::endl;
    n = n->next;
  }
}

/**
 * @brief Funkcja dodaje pojazd i tworzy nowy plik z danymi
 * 
 * @param n - wskaznik na poczatek listy
 */
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

/**
 * @brief Funkcja dodaje uzytkownika i tworzy nowy plik z danymi
 * 
 */
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

/**
 * @brief Funkcja pozwala na dodanie opisu do pojazdu
 * 
 */
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

/**
 * @brief Wypisuje liste plikow w folderze podanym jako path
 *  entry.path() returns a path of file -> then we get only the filename with filename() -> it will return filename with quotes "" so we remove those with .string()
 */
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

/**
 * @brief Funkcja tworzy nowe obiekty na podstawie plikow z pojazdami a nastepnie dopisuje je do listy
 * 
 * @param path - sciezka do folderu z pojazdami
 * @param head - wskaznik na poczatek listy pojazdow
 */
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
/**
 * @brief Funkcja tworzy nowe obiekty na podstawie plikow z uzytkownikami a nastepnie dopisuje je do listy
 * 
 * @param path - sciezka do folderu z uzytkownika
 * @param head - wskaznik na poczatek listy uzytkownikow
 */

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

/**
 * @brief Funkcja laczy obiekty z listy uzytkownikow z lista pojazdow
 * 
 * @param head - wskaznik na poczatek listy uzytkownikow
 * @param head2 - wskaznik na poczatek listy pojazdow
 */
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
  synchronizuj("pojazdy/", &headPojazd);
  synchronizuj("users/", &headUser);
  linkUsersToCars(&headUser, &headPojazd);

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

  return 0;
}