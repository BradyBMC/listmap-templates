// $Id: main.cpp,v 1.13 2021-02-01 18:58:18-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <regex>
#include <cassert>
#include <fstream>


using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

void catfile(istream& infile, const string& filename) {
  cout << filename << endl;
  for(;;) {
    string line;
    getline(infile,line);
    if(infile.eof()) break;
    cout << line << endl;
  }
}

int main (int argc, char** argv) {
  int status = 0;
  string progname(basename(argv[0]));
  vector<string> filenames(&argv[1], &argv[argc]);
  if(filenames.size()==0) filenames.push_back("-");
  for(const auto& filename: filenames) {
    if(filename == "-") catfile(cin,filename);
    else {
      ifstream infile (filename);
      if(infile.fail()) {
        status = 1;
      } else {
        catfile(infile,filename);
        infile.close();
      }
    }
  }



   /*
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"};
   int run = 0;
   str_str_map test;
   for (;;) {
      string line;
      getline (cin, line);
      if (cin.eof()) break;
      cout << "input: \"" << line << "\"" << endl;
      smatch result;
      if (regex_search (line, result, comment_regex)) {
         cout << "Comment or empty line." << endl;
      }else if (regex_search (line, result, key_value_regex)) {
         cout << "key  : \"" << result[1] << "\"" << endl;
         cout << "value: \"" << result[2] << "\"" << endl;
         string temp = result[1];
         string temp2= result[2];
         str_str_pair pair (result[1], result[2]);
         cout << pair << endl;
         test.insert(pair);
      }else if (regex_search (line, result, trimmed_regex)) {
         cout << "query: \"" << result[1] << "\"" << endl;
      }else {
         assert (false and "This can not happen.");
      }
      run++;
      if(run == 3) break;
   }
   */

   /*
   str_str_map test;
   cout << test << endl;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      str_str_pair pair (*argp, to_string<int> (argp - argv));
      cout << "Before insert: " << pair << endl;
      test.insert (pair);
   }

   cout << test.empty() << endl;
   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   test.erase (itor);
   */
   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

