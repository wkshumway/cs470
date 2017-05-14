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
#include <vector>
#include <iterator>

std::string getInput(std::string& userInput);
std::string sanitize(std::string& userInput);
std::string sanitizeTag(std::string tag);
std::string validateTag(std::string tag);
bool isValidTag(std::string tag);
std::string removeChevrons(std::string tag);

int main()
{
  std::string userInput;
  
  // std::string userInput = "<tag>Hello<a> </a> Wellesley</tag>";
  while (getInput(userInput) != "quit")
  {
  std::cout << "\t" << sanitize(userInput) << std::endl;
  }
  //std::cout << userInput << "\n";

  return 0;
}
std::string getInput(std::string& userInput)
{
  std::cout << "> ";

  std::getline(std::cin,userInput);

  return userInput;
}

std::string sanitize(std::string& userInput)
{
  int beginTagIndex = 0;
  int endTagIndex = 0;
  int j = 0;
  std::string sanitizedInput = "";

  for (int i = 0; i < userInput.length(); i++)
    {
      //std::cout << userInput[i] << " ";

      if (userInput[i] == '<' )
        {
          std::string tag = "";
          for (j = i; userInput[j - 1] != '>'; j++)
            {
              tag += userInput[j];
            }
          sanitizedInput += validateTag(tag);
          i = j - 1;
        }
      else
        {
          sanitizedInput += userInput[i];
        }
    }
  return sanitizedInput;
}

std::string validateTag(std::string tag)
{
  if (isValidTag(tag))
    return tag;
  else
    return sanitizeTag(tag);
}

std::string sanitizeTag(std::string tag)
{
  if (tag[1] == '/')
    return "&lt;/" + removeChevrons(tag) + "&gt;";
  else
    return "&lt;" + removeChevrons(tag) + "&gt;";
}

bool isValidTag(std::string tag)
{
  std::string validTags[13] = {"a", "abbr", "acronym", "b", "blockquote",
                               "cite", "code", "del", "em", "i", "q",
                               "strike", "strong"};
  std::string innerTag = removeChevrons(tag);
  for (int i =0; i < 13; i++)
    {
      if (innerTag == validTags[i])
        return true;
    }

  return false;
}

std::string removeChevrons(std::string tag)
{
  std::string innerTag;
  if (tag[1] == '/')
    {
      innerTag = tag.substr(2, (tag.length()-3));
    }
  else
    {
      int i;
      for (i = 0; tag[i] != ' ' && i < tag.length(); i++);
      if (tag[i] == ' ') {
        innerTag = tag.substr(1, (i - 1));
        std::cout << "\t Error: " << innerTag << std::endl;
      }
      else
        innerTag = tag.substr(1, (tag.length() - 2));
    }
  return innerTag;
}
