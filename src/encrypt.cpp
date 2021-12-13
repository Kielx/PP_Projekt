#include <string>

std::string encrypt(std::string password, int ile)
{
  std::string encrypted = "";
  for (long unsigned int i = 0; i < password.length(); i++)
  {
    encrypted += password[i] + ile;
  }
  return encrypted;
}

std::string decrypt(std::string password, int ile)
{
  std::string decrypted = "";
  for (long unsigned int i = 0; i < password.length(); i++)
  {
    decrypted += password[i] - ile;
  }
  return decrypted;
}