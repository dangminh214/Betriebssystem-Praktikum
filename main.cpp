#include <cstring>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cctype>

//We can use return option for a better and cleaner code
bool findStringIC(const std::string & strHaystack, const std::string & strNeedle)
{
  auto it = std::search(
    strHaystack.begin(), strHaystack.end(),
    strNeedle.begin(),   strNeedle.end(),
    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
  );
  return (it != strHaystack.end() );
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}
void printAllVariablesWithNameAndValues(int argc, char** argv, char** envp) {
    for (char **env = envp; *env != 0; env++)
      {
        char *thisEnv = *env;
        std::cout<<thisEnv<<std::endl;
      }
}

void printAllVariablesWithoutValues(int argc, char** argv, char** envp) {
    while(*envp!=NULL) {
            char *p = *envp;
            while(*p && *p != '=') {
                putc(*p, stdout);
                //return p -> return option type: char*
                p++;
            }
            puts("");
            envp++;
    }

}

void printfindPath(int argc, char** argv, char** envp, char** findChar) {

    char* pattern1 = *findChar;

    std::string pattern(pattern1);
    for (char **env = envp; *env != 0; env++)
      {
        char *thisEnv = *env;
        std::string Var(thisEnv);
        if (Var.find(pattern) != std::string::npos) {
            std::cout << Var << std::endl;
            //return thisEnv -> return option type char*
        }
      }
}


int main(int argc, char **argv, char **envp) {

char ch = '=';

//defaults  ->done
    if (argc == 1) {
        for (char **env = envp; *env != 0; env++)
          {
            char *thisEnv = *env;
            std::cout<<thisEnv<<std::endl;
          }
    }

//2 Arguments: ex: ./envgrep -n OR ./envgrep PATH
    if (argc == 2) {
        if (cmdOptionExists(argv, argv+argc, "-n")) {
            printAllVariablesWithoutValues(argc, argv, envp);
        }

        else
            printfindPath(argc, argv, envp, &argv[1]);
    }

    //example: ./envgrep -n PATH or ./envgrep -i PATH ->done  (need to fix "Dont Ignore Case")
    if (argc==3) {

        std::string pattern(argv[2]);

        if (cmdOptionExists(argv, argv+argc, "-i")) {
            for (char **env = envp; *env != 0; env++)
              {
                char *thisEnv = *env;

                std::string Var(thisEnv);

                //substring, delete everything behind "="
                std::size_t pos = Var.find(ch);
                Var = Var.substr(0,pos);

                if (findStringIC(Var, pattern)) {
                    std::cout << thisEnv << std::endl;
                }
              }
        }
        if (cmdOptionExists(argv, argv+argc, "-n")) {
            for (char **env = envp; *env != 0; env++){
            char *thisEnv = *env;
            std::string Var(thisEnv);
            if (Var.find(pattern) != std::string::npos) {
                char* p = thisEnv;
                while(*p && *p != '=') {
                    putc(*p, stdout);
                    p++;
                }
                puts("");
                envp++;
            }
           }
        }
    }

    //example: ./envgrep -n -i PATH     full of arguments
    if (argc == 4)
    {
        std::string pattern(argv[3]);
        for (char **env = envp; *env != 0; env++){
        char *thisEnv = *env;
        std::string Var(thisEnv);

        //substring, delete everything behind "="
        std::size_t pos = Var.find(ch);
        Var = Var.substr(0,pos);

        if(findStringIC(Var,pattern)) {
            char* p = thisEnv;
            while(*p && *p != '=') {
                putc(*p, stdout);
                p++;
            }
            puts("");
            envp++;
        }
       }
    }
  return 0;
}
