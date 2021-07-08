#include "Shell.h"
#include <sys/wait.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string>
#include <cerrno>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> split(const char* s, const char delimiter)
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

std::string lookup(const std::vector<std::string> &paths, const std::string program)
{
    for (int i = 0; i < paths.size(); ++i)
    {
       std::string temp = paths[i] + "/" + program;

       if (access(temp.c_str(), F_OK) == 0) 
       {
           return temp;
       }
    }

    return("");
}

void Shell::run()
{
    while(true)
    {
        std::cout << "Shell is running..." << std::endl;

        std::string command;
        getline(std::cin, command); 

        // get program name and args
        std::vector<std::string> parts = split(command.c_str(), ' ');

        // extra room for sentinel
        const char** argv = new const char* [parts.size() + 1];   

        // get filepath
        std::string filepath = parts[0].c_str();

        // if filepath is program name
        if(filepath.find_first_of('/') == -1)
        {
            // get all paths from env variables
            char* pathStr = getenv("PATH");

            // split into array
            std::vector<std::string> paths = split(pathStr, ':');

            // lookup path of given program
            filepath = lookup(paths, filepath);
        }

        argv[0] = filepath.c_str();

        // copy args
        for(int i = 1; i < parts.size(); ++i)
        {
            argv[i] = parts[i].c_str();
        }

        argv[parts.size() + 1] = NULL;

        // create process
        pid_t child = fork();

        // exit on failure
        if(child == -1)
        {
            exit(errno);
        }

        if(child == 0)
        {
            const char* outPath = "/opt/silentshell/out.std";
            const char* inPath = "/opt/silentshell/in.std";

            std::fstream fsout;
            std::fstream fsin;

            fsout.open(outPath, std::ios::out);
            fsout.open(inPath, std::ios::in);
          
            std::streambuf* outFile = fsout.rdbuf();
            std::streambuf* inFile = fsin.rdbuf();

            std::cout.rdbuf(outFile);
            std::cin.rdbuf(inFile);
            
            execv(argv[0], (char **)argv);
            // std::cout << argv[0] << std::endl;

            fsout.close();
            fsin.close();

            exit(0);
        }
        else
        {
            // waiting for child
            int status = -1;
            waitpid(child, &status, 0);
        }
    }
}