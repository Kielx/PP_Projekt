#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

/**
 * @brief Struktura obiektu bazowego
 * 
 */
class Pojazd
{
public:
  std::string numerRej;
  std::string nazwa;
  int rok;
  Pojazd *next;
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

// This function prints contents of linked list starting from
// the given node
void printList(Pojazd *n)
{
  while (n != NULL)
  {
    std::cout << n->numerRej << " " << n->nazwa << " " << n->rok << std::endl;
    n = n->next;
  }
}

/**
 * @brief list all files in directory
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

void synchronizuj(std::string path, User *user)
{
  std::array<std::string, 3> dane;
  for (const auto &entry : fs::directory_iterator(path))
  {
    if (entry.path().stem().string() == user->numerRejPojazdu)
    {
      std::string line;
      std::ifstream myfile(entry.path()); //"pojazdy/" + entry.path().filename().string());
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
      std::cout << dane.at(2) << std::endl;
      nowy->rok = std::stoi(dane.at(2));
      user->pojazd = nowy;
    }
  }
}

int main()
{
  Pojazd *head = NULL;
  Pojazd *second = NULL;
  Pojazd *third = NULL;
  head = new Pojazd();
  second = new Pojazd();
  third = new Pojazd();
  head->numerRej = "ABC-123";
  head->nazwa = "BMW";
  head->rok = 2010;
  head->next = second;
  second->numerRej = "XYZ-456";
  second->nazwa = "Audi";
  second->rok = 2012;
  second->next = third;
  third->numerRej = "PQR-789";
  third->nazwa = "Mercedes";
  third->rok = 2015;
  third->next = NULL;
  User *test = NULL;
  test = new User();
  test->imie = "Jan";
  test->nazwisko = "Kowalski";
  test->numerRejPojazdu = "ABC-123";
  test->pojazd = NULL;
  //head->next = second; // Link first node with second

  //printList(head);
  while (head != NULL)
  {
    Pojazd *temp = head;
    std::ofstream plik;
    plik.open("pojazdy/" + head->numerRej + ".txt");
    plik << head->numerRej << std::endl
         << head->nazwa << std::endl
         << head->rok << std::endl;
    head = head->next;
  }

  //listFiles("pojazdy/");
  synchronizuj("pojazdy/", test);
  return 0;
}