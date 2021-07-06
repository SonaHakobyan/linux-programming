#include "Shell.h"
#include <sys/wait.h>
#include <unistd.h> 
#include <string.h>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <vector>

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void Shell::run()
{
    while(true)
    {
        std::cout << "Shell is running...";

        std::string command;
        std::cin >> command;

        if(command.empty())
        {
            continue;
        }

        // program name and args
        std::vector<std::string> parts = split(command, ' ');

        // extra room sentinel
        const char **argv = new const char* [parts.size() + 1];   

        // handle pathname in case of name
        // TODO

        argv[0] = parts[0].c_str();

        // copy args
        for(int i = 1; i < parts.size(); ++i)
        {
            argv[i+1] = parts[i+1].c_str();
        }

        argv[parts.size() + 1] = NULL;

        // create process
        pid_t pid = fork();

        // exit on failure
        if(pid == -1)
        {
            exit(errno);
        }

        if(pid == 0)
        {
            // exec command
            execv(argv[0], (char **)argv);
        }
        else
        {
            // wait for child
            wait(NULL);
        }
    }
}