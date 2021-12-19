# ❕ Baza danych warsztatu samochodowego {#mainpage}

TODO:

- ~~Clean up display functions to display data in some nicer way~~
- ~~Display owner data in car list~~
- Check how program responds to different data
- Add mileage field to car
- ~~Decompress archive with cars and users on start~~
- ~~Compress archive with cars and users on exit~~
- Add getline for better input
- ~~Add remove option~~
- Fix bug with adding function and missing car
- Update docs


## ❔ O projekcie

Projekt ma prezentować działanie bazy danych warsztatu samochodowego w oparciu o dwie struktury listy jednokierunkowej.
Struktury te wczytywane są na podstawie danych z plików w folderach pojazdy i users.

### ⚙️ Funkcje Programu

Program jest wyposażony w rozmaite funkcje związane z obsługa bazy danych: <br>
☑️ - Pozwala na podstawowe operacje na bazie danych - dodawanie, usuwanie, wyswietlanie i aktualizowanie danych <br>
☑️ - Dostęp do programu jest ograniczony dla zalogowanych użytkowników, których dane są zaszyfrowane <br>
☑️ - Dostęp jest chroniony przed metodą brute-force poprzez usypianie aplikacji po trzech nieudanych próbach logowania na określony czas <br>
☑️ - Zapisuje i odczytuje dane z plikow <br>
☑️ - Synchronizuje odczytane dane <br>
☑️ - Przechowuje baze danych w archiwum tar.gz poprzez odczyt i zapis na poczatku i końcu programu<br>
<br>

![Przyklad dzialania programu](../../img/Demo1.gif)

#### 👨‍💻 Timsort

To hybrydowy stabilny algorytm sortowania, wywodzący się z sortowania przez scalanie i sortowania przez wstawianie, zaprojektowany tak, aby dobrze działał na wielu rodzajach rzeczywistych danych. Został zaimplementowany przez Tima Petersa w 2002 roku do użytku w języku programowania Python. Algorytm wyszukuje podciągi danych, które są już uporządkowane (uruchomione) i wykorzystuje je do efektywniejszego sortowania pozostałych. Odbywa się to poprzez scalanie przebiegów, dopóki nie zostaną spełnione określone kryteria. Timsort jest standardowym algorytmem sortowania Pythona od wersji 2.3. Służy również do sortowania tablic typu nieprymitywnego w Javie SE 7, na platformie Android, w GNU Octave, na Chromium V8, Swift i Rust.

#### 🏎️ Quicksort – sortowanie szybkie

To algorytm sortowania działający w średnim przypadku w czasie liniowo-logarytmicznym. Algorytm jest oparty na metodzie dziel i zwyciężaj. Nie jest to algorytm stabilny ani wykazujący zachowanie naturalne, jednak ze względu na efektywność jest algorytmem bardzo popularnym.

<hr>

### 🛠️ Wykonany w

Projekt został wykonany całkowicie w języku C++.

<hr>

## 🚀 Uruchamianie

Poniższe instrukcje dotyczą systemu Ubuntu w wersji 20.04, jednak powinny zadziałać także na innych systemach unixowych pod warunkiem zainstalowania wcześniej kompilatora.

![Okno konsoli pokazujace interaktywnie kroki niezbedne do skompilowania i uruchomienia programu](../../img/uruchamianie.gif)

### 🔧 Uruchamianie programu

Instalujemy kompilator g++

```console
sudo apt install g++
```

Sprawdzamy poprawnosc instalacji:

```console
$ g++ --version

g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

Przechodzimy do folderu gdzie zlokalizowany jest program np.:

```console
cd ~/mojaBaza/
```

Kompilujemy program (w folderze zawarty jest Makefile, ktory kompiluje i laczy wszystkie skladowe)

```console
make
```

Uruchamiamy program:

```console
make run
```

Postepujemy zgodnie z instrukcjami na ekranie. \n Brawo - Twoja tablica jest posortowana.

![Kobieta cieszaca sie z sukcesu](https://media.giphy.com/media/kefB3xhgryQnpdhtw5/giphy.gif)

### 📄 Generowanie dokumentacji

Generowanie dokumentacji programu jest bardzo proste.
Najpierw należy zainstalować program Doxygen zgodnie z instrukcjami: <https://www.doxygen.nl/manual/install.html>

Przechodzimy do folderu gdzie zlokalizowany jest program np.:

```console
cd ~/mojaBaza/
```

Znajduje sie w nim plik z instrukcja Doxyfile. By go uruchomic wystarczy skorzystac z:

a) instrukcji make docs

```console
make docs
```

b) tylko z instrukcji doxygen:

```console
doxygen
```

Wygenerowana dokumentacja domyslnie znajduje sie w folderze ./doc/html/ \n
By ja odczytać należy uruchomić index.html znajdujacy sie w folderze ./doc/html

### 🧹 Czyszczenie

By usunac wygenerowane pliki (_.o,_.out, dokumentacje doxygen) korzystamy z instrukcji make clean

```console
make clean
```

<hr>

## 👨‍🎓 Autorzy

**Krzysztof Pańtak, Tomasz Natoniewski, Bartłomiej Mierzwa - Informatyka Zaocznie - 2021/2022 Grupa 11B**
