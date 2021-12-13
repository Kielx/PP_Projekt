#ifndef ENCRYPT_H
#define ENCRYPT_H

/**
 * @brief Funkcja ktora szyfruje podany ciag znakow
 *
 * @param password - ciag znakow do zaszyfrowania
 * @param ile - o ile przesunac ciag znakow
 * @return std::string - zaszyfrowany ciag znakow
 */
std::string encrypt(std::string password, int ile);

/**
 * @brief Funkcja ktora deszyfruje podany ciag znakow
 *
 * @param password - ciag znakow do odszyfrowania
 * @param ile - o ile przesunac ciag znakow
 * @return std::string - odszyfrowany ciag znakow
 */
std::string decrypt(std::string password, int ile);

#endif