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

/************************************************************************
 * main - the function that runs the program
 ***********************************************************************/
int main()
{
  std::string userInput;

  while (getInput(userInput) != "quit")
  {
  std::cout << "\t" << sanitize(userInput) << std::endl;
  }

  return 0;
}

/************************************************************************
 * getInput gets input from the user and returns it to main
 ***********************************************************************/
std::string getInput(std::string& userInput)
{
  std::cout << "> ";

  std::getline(std::cin,userInput);

  return userInput;
}

/************************************************************************
 * sanitize - takes the user input and sanitizes the malicious tags
 ***********************************************************************/
std::string sanitize(std::string& userInput)
{
  int beginTagIndex = 0;
  int endTagIndex = 0;
  int j = 0;
  std::string sanitizedInput = "";

  for (int i = 0; i < userInput.length(); i++)
    {
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

/************************************************************************
 * validateTag - returns the tag if it is valid and the sanitized tag if
 * it is invalid
 ***********************************************************************/
std::string validateTag(std::string tag)
{
  if (isValidTag(tag))
    return tag;
  else
    return sanitizeTag(tag);
}

/************************************************************************
 * sanitizeTag - sanitizes malicious tags
 ***********************************************************************/
std::string sanitizeTag(std::string tag)
{
  if (tag[1] == '/')
    return "&lt;/" + removeChevrons(tag) + "&gt;";
  else
    return "&lt;" + removeChevrons(tag) + "&gt;";
}

/************************************************************************
 * isValidTag - checks the tag against a whitelist to see if it is valid
 ***********************************************************************/
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

/************************************************************************
 * removeChevrons - takse the punction off of a tag so that we can check
 * it against the whitelist
 ***********************************************************************/
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
