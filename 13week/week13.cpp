/***********************************************************************
* Program:
*    Week 13, Homograph Program
*    Brother Wilson, CS470
* Author:
*    Wellesley Shumway
* Summary:
*    Please include a detailed description of:
*    1. What this program is designed to do
*    This program will state whether to file paths are the same
*    2. How this program will go about solving the problem
*    This program will do this by reaching the files and comparing whether
*    they represent the same file
*    3. What assumptions about input (file or user) is made
*    The user inputs file names without quotes according to Linux standards.
*    4. Citations if the algorithm was borrowed or inspired from any source
************************************************************************/
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

/***********************************************************************
 * getFileName will ask the users for the names of the two different files
 ************************************************************************/
void getFileName(string & fileName1, string & fileName2)
{
  cout << "Specify the first filename:  ";
  cin >> fileName1;
  cout << "Specify the second filename: ";
  cin >> fileName2;
}

/***********************************************************************
 * splitFilePath will split the filePath along the forward slashes
 * algorithm source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-com
 ************************************************************************/
vector<string> splitFilePath(string stringToSplit)
{
  vector<string> vTokens;
  string delimiter = "/";
  size_t pos = 0;
  string token;

  while ((pos = stringToSplit.find(delimiter)) != string::npos) {
    token = stringToSplit.substr(0, pos);
    if (token != "")
      {
        vTokens.push_back(token);
      }
    stringToSplit.erase(0, pos + delimiter.length());
  }
  token = stringToSplit.substr(0, pos);
  vTokens.push_back(token);

  return vTokens;
}

/***********************************************************************
* convertPathToStack will make the accurate file path, without ".." and
* "." by treating the file path as a stack, popping off the last directory
* when there is a ".."
************************************************************************/
stack<string> converPathToStack(vector<string> path)
{
  stack<string> pathStack;

  for (size_t i = 0; i < path.size(); i++)
    {
      if (path[i] == "..")
        {
          if (pathStack.empty())
            {
              //do nothing
            }
          else
            {
              pathStack.pop();
            }
        }
      else if (path[i] == ".")
        {
          //do nothing
        }
      else
        {
          pathStack.push(path[i]);
        }
    }
  return pathStack;
}

/***********************************************************************
 * filesAreHomographs will compare two filepaths to see whether or not
 * they will lead to the same file
 ************************************************************************/
bool filesAreHomographs(string fileName1, string fileName2)
{
  stack<string> file1Stack;
  stack<string> file2Stack;
  vector<string> file1V;
  vector<string> file2V;

  file1V = splitFilePath(fileName1);
  file2V = splitFilePath(fileName2);

  return (converPathToStack(file1V) == converPathToStack(file2V));
}

/***********************************************************************
 * main will drive the program
 ************************************************************************/
int main()
{
  string fileName1;
  string fileName2;
  getFileName(fileName1, fileName2);
  if (filesAreHomographs(fileName1, fileName2))
    {
      cout << "The files are homographs\n";
    }
  else
    {
      cout << "The files are NOT homographs\n";
    }
  return 0;
}
