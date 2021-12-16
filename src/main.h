#ifndef MAIN
#define MAIN

#include "pojazd.h"
#include "user.h"

/**
 * @file src/main.h
 *
 * Główny plik programu.
 */

/**
 * @brief Funkcja dodaje pojazd i tworzy nowy plik z danymi
 *
 * @param head_ref - wskaznik na poczatek listy
 */
void addCar(Pojazd **head_ref);

/**
 * @brief Dodaje element na poczatku listy
 *
 * @param head_ref - wskaznik na poczatek listy
 * @param pojazd - wskaznik nowego element
 */
void push(Pojazd **head_ref, Pojazd *pojazd);

/**
 * @brief Funkcja dodaje uzytkownika i tworzy nowy plik z danymi
 *
 */
void addUser(User **head_ref);

/**
 * @brief Funkcja pozwala na dodanie opisu do pojazdu
 *
 */
void addOpis();

/**
 * @brief Wypisuje liste plikow w folderze podanym jako path
 *  entry.path() returns a path of file -> then we get only the filename with filename() -> it will return filename with quotes "" so we remove those with .string()
 */
void listFiles(std::string path);

/**
 * @brief Funkcja tworzy nowe obiekty na podstawie plikow z pojazdami a nastepnie dopisuje je do listy
 *
 * @param path - sciezka do folderu z pojazdami
 * @param head - wskaznik na poczatek listy pojazdow
 */
void synchronizuj(std::string path, Pojazd **head);

/**
 * @brief Funkcja tworzy nowe obiekty na podstawie plikow z uzytkownikami a nastepnie dopisuje je do listy
 *
 * @param path - sciezka do folderu z uzytkownika
 * @param head - wskaznik na poczatek listy uzytkownikow
 */

void synchronizuj(std::string path, User **head);

/**
 * @brief Funkcja laczy obiekty z listy uzytkownikow z lista pojazdow
 *
 * @param head - wskaznik na poczatek listy uzytkownikow
 * @param head2 - wskaznik na poczatek listy pojazdow
 */
void linkUsersToCars(User **head, Pojazd **head2);

#endif