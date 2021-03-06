#ifndef DELETE_H
#define DELETE_H

#include "pojazd.h"
#include "user.h"

/**
 * @brief Funkcja usuwająca użytkownika
 *
 * @param head - wskaznik na poczatek listy uzytkownikow
 */
void deleteUser(User **head);

/**
 * @brief Funkcja usuwajaca pojazd
 *
 * @param head - wskaznik na poczatek listy pojazdow
 *
 */
void deleteCar(Pojazd **head);

#endif