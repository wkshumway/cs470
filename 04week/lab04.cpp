/***********************************************************************
* Program:
*    Week 04, Sanitization Program
*    Brother Helfrich, CS470
* Author:
*    Wellesley Shumway
* Summary:
*    Please include a detailed description of:
*    1. What this program is designed to do
*    2. How this program will go about solving the problem
*    3. What assumptions about input (file or user) is made
*    4. Citations if the algorithm was borrowed or inspired from any source
************************************************************************/
#include <iostream>
#include <string>

void getInput(std::string userInput[]);
void sanitize(std::string userInput[]);

int main()
{
  std::string userInput[1000];

  getInput(userInput);
  sanitize(userInput);

  //std::cout << userInput << "\n";

  return 0;
}

void getInput(std::string userInput[])
{
  std::cout << ">";
  std::string element;

  int i = 0;
  while (std::cin >> userInput[i])
    {
      i++;
    }
  // for (int i = 0; std::cin >> element; i++)
  //   {
  //     userInput[i] = element;
  // }
  //std::getline(std::cin,userInput);
}

void sanitize(std::string userInput[])
{
  // for (int i = 0; i < userInput.length(); i++)
  //   {
  //     std::cout << userInput[i] << " ";
  //     // if (userInput[i] == '<' &&
  //     //     (userInput[i++] !=  ))

  //   }
}

