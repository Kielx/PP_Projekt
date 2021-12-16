#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief Funkcja wypisuje zawartośc listy
 *
 * @param n - wskaznik na poczatek listy
 */
void printList(Pojazd *n);

/**
 * @brief Funkcja wypisuje na ekran liste uzytkownikow
 *
 * @param n - wskaznik na poczatek listy uzytkownikow
 */
void printList(User *n);

/**
 * @brief Funkcja ktora wypisuje informacje o pojezdzie
 *
 * @param head - wskaznik na poczatek listy pojazdow
 *
 */
void wyswietlDanePojazdu(Pojazd *head);

/**
 * @brief Wyswietla dane użytkownika
 *
 * @param head - wskaznik na poczatek listy uzytkownikow
 *
 */
void wyswietlDaneUzytkownika(User *head);

#endif