#include <iostream>

#include "pojazd.h"
#include "user.h"

void deleteUser(User **head)
{
  std::string imie;
  std::string nazwisko;
  std::cout << "Podaj imie: ";
  std::cin >> imie;
  std::cout << "Podaj nazwisko: ";
  std::cin >> nazwisko;
  User *current = *head;
  User *previous = NULL;
  while (current != NULL)
  {
    if (current->imie == imie && current->nazwisko == nazwisko)
    {
      std::string filename = "users/" + imie + "-" + nazwisko + ".txt";
      if (previous == NULL)
      {
        *head = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      delete current;
      if (remove(filename.c_str()) != 0)
        std::cout << "Wystąpił błąd podczas próby usunięcia pliku" << std::endl;
      else
        std::cout << "Użytkownik został poprawnie usunięty z bazy" << std::endl;
      return;
    }
    previous = current;
    current = current->next;
  }
  std::cout << "Nie ma takiego uzytkownika" << std::endl;
};
