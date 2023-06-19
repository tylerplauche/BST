#include <iostream>
#include <fstream>
#include <sstream>

#include "BST.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char *argv[]) 
{
  VS_MEM_CHECK;
  if (argc < 3)
  {
    cerr << "Please provide name of input and output files";
    return 1;
  }
  ifstream in(argv[1]);
  if (!in)
  {
    cerr << "Unable to open " << argv[1] << " for input";
    return 1;
  }
  ofstream out(argv[2]);
  if (!out)
  {
    in.close();
    cerr << "Unable to open " << argv[2] << " for output";
  }

  string prevLine;
  while(!in.eof())
  {
    string line;
    string item1, item2;
    if (prevLine.empty()) 
    {
      getline(in, line);
      if (line.size() == 0) continue;
      istringstream iss(line);
      iss >> item1;
      out << item1;
    }
    else
    {
      istringstream iss(prevLine);
      iss >> item1;
    }

    if(item1 == "INT")
    {
      BST <int> IntBST;
      out << " OK" << endl;
      string item3, item4;
      while(item3 != "INT" && item3 != "STRING" && !in.eof())
      {
        string line2;
        getline(in, line2);
        istringstream iss2(line2);
        if (line2.size() == 0) continue;
        iss2 >> item3;
        out << item3;

        if(item3 == "add")
        {
          iss2 >> item4;
          out << " " << item4;
          stringstream ss(item4);
          int x = 0;
          ss >> x;
          if(IntBST.addNode(x))
          {
            out << " OK";
          }
          else
          {
            out << " Error";
          }
        }

        if(item3 == "print")
        {
          out << IntBST.toString();
        }

        if(item3 == "find")
        {
          iss2 >> item4;
          out << " " << item4;
          stringstream ss(item4);
          int x = 0;
          ss >> x;
          if(IntBST.Find(x))
          {
            out << " found";
          }
          else
          {
            out << " not found";
          }
        }

        if(item3 == "size")
        {
          out << " " << IntBST.FindSize();
        }

        if(item3 != "INT" && item3 != "STRING")
        {
          out << endl;
        }
        prevLine = line2;
      }
      continue;
    }
    else if(item1 == "STRING")
    {
      BST <string> StringBST;
      out << " OK" << endl;
      string item3, item4;
      while(item3 != "INT" && item3 != "STRING" && !in.eof())
      {
        string line2;
        getline(in, line2);
        istringstream iss2(line2);
        if (line2.size() == 0) continue;
        iss2 >> item3;
        out << item3;
        
        if(item3 == "add")
        {
          iss2 >> item4;
          out << " " << item4;

          if(StringBST.addNode(item4))
          {
            out << " OK";
          }
          else
          {
            out << " Error";
          }
        }

        if(item3 == "print")
        {
          out << StringBST.toString();
        }

        if(item3 == "find")
        {
          iss2 >> item4;
          out << " " << item4;
          if(StringBST.Find(item4))
          {
            out << " found";
          }
          else
          {
            out << " not found";
          }
        }
        if(item3 == "size")
        {
          out << " " << StringBST.FindSize();
        }

        if(item3 != "INT" && item3 != "STRING")
        {
          out << endl;
        }
        prevLine = line2;
      }
      continue;
    }
    else
    {
      out << " Error" << endl;
    }
  }

  return 0;
}