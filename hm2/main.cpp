#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <iostream>

int main(int argc, char** argv) 
{
    if(argc < 3)
    {
        std::cout << "Files are not given by arguments." << std::endl;
        exit(1);
    }

    char* src = argv[1];
    char* dest = argv[2];

    // open source file
    int src_fd = open(src, O_RDONLY);
    if(src_fd == -1)
    {
        std::cout << "Could not open source file." << std::endl;
        exit(errno);
    }

    // calculate logical size of source
    off_t srcLogSize = lseek(src_fd, 0, SEEK_END);
    std::cout << "Source file logical size - " << srcLogSize << std::endl;
    lseek(src_fd, 0, SEEK_SET);

    char* buffer = new char[1];
    int readBytes;

    // calculate physical size of source
    long srcPhysSize = 0;

    while(true)
    {
        readBytes = read(src_fd, buffer, 1);

        if(readBytes == -1)
        {
            std::cout << "Could not read bytes from source" << std::endl;
            exit(errno);
        }

        // end of file
        if(readBytes == 0)
        {
            break;
        }

        // actual data
        if(buffer[0] != '\0')
        {
            ++srcPhysSize;
        }
    }
    
    std::cout << "Source file physical size - " << srcPhysSize << std::endl;

    // open destination file
    int dest_fd = open(dest, O_CREAT | O_TRUNC | O_RDWR);
    if(dest_fd == -1)
    {
        std::cout << "Could not open destination file." << std::endl;
        exit(errno);
    }

    lseek(src_fd, 0, SEEK_SET);
    lseek(dest_fd, 0, SEEK_SET);

    // copy file
    while(true)
    {
        readBytes = read(src_fd, buffer, 1);

        if(readBytes == -1)
        {
            std::cout << "Could not read bytes from source" << std::endl;
            exit(errno);
        }

        // end of file
        if(readBytes == 0)
        {
            break;
        }

        // seek in case of hole
        if(buffer[0] == '\0')
        {
            lseek(dest_fd, 1 , SEEK_CUR);
        }
        else
        {
            write(dest_fd, buffer, readBytes);
        }
    }

    // calculate logical size of destination
    off_t destLSize = lseek(dest_fd, 0, SEEK_END);
    std::cout << "Destination file logical size - " << destLSize << std::endl;
    lseek(dest_fd, 0, SEEK_SET);

    // calculate physical size of destination
    long destPhysSize = 0;

    while(true)
    {
        readBytes = read(dest_fd, buffer, 1);

        if(readBytes == -1)
        {
            std::cout << "Could not read bytes from destination" << std::endl;
            exit(errno);
        }

        // end of file
        if(readBytes == 0)
        {
            break;
        }

        // actual data
        if(buffer[0] != '\0')
        {
            ++destPhysSize;
        }
    }
    
    std::cout << "Destination file physical size - " << destPhysSize << std::endl;

    delete [] buffer;

    close(src_fd);
    close(dest_fd);

    return 0;
}
