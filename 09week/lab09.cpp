/***********************************************************************
* Program:
*    Lab 09, Password Strength
*    Brother Wilson, CS470
* Author:
*    Wellesley Shumway
* Summary:
*    This program is designed to get an example password from the user
*    and return how many guesses it would take to guess the password,
*    as well as how many bits of strength it has.
*    This program loops through the characters in the password, determing
*    which alphabets are used. According to that and the length, it gives
*    the amount of combinations.
************************************************************************/
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

#define UPPER_LENGTH 26
#define LOWER_LENGTH 26
#define SYMBOLS_LENGTH 32
#define DIGITS_LENGTH 10
#define UPPER 0
#define LOWER 1
#define SYMBOLS 2
#define DIGITS 3

string getPassword();
int  calcCombinations(string password);

/***********************************************************************
* main runs the program
************************************************************************/
int main ()
{
  string password = getPassword();
  int combinations = calcCombinations(password);
  cout << "There are " << combinations << " combinations\n";
  cout << "That is equivalent to a key of " << (int)log2(combinations)<< " bits\n";
  return 0;
}

/***********************************************************************
* getPassword asks the user for a password and returns it to main
************************************************************************/
string getPassword()
{
  string password;
  cout << "Please enter the password: ";
  cin >> password;
  return password;
}

/***********************************************************************
* calcCombinations determines how many combinations must be tried to
* guess a given password
************************************************************************/
int calcCombinations(string password)
{
  int typeNums[4] = { 0, 0, 0, 0};

  // loop through the password and set any alphabet lengths present
  for (int i = 0; i < password.length(); i++)
    {
      if (isupper(password[i]))
        {
          typeNums[UPPER] = UPPER_LENGTH;
        }
      if (islower(password[i]))
        {
          typeNums[LOWER] = LOWER_LENGTH;
        }
      if (ispunct(password[i]))
        {
          typeNums[SYMBOLS] = SYMBOLS_LENGTH;
        }
      if (isdigit(password[i]))
        {
          typeNums[DIGITS] = DIGITS_LENGTH;
        }
    }

  int sum = 0;

  // sum alphabet lengths
  for (int i = 0; i <= 3; i++)
    {
      sum += typeNums[i];
    }

  return pow(sum, password.length());
}
