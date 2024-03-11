#include "Framework/GameFarmework.h"

#include <iostream>


int main(int argc, char* argv[])
{
  
    if (argc == 4 && std::string(argv[1]) == "-window")
    {
        // Get the width and height of the window from the command line arguments
        int Width = atoi(argv[2]);
        int Height = atoi(argv[3]);

        return run(new GameFramework(Width, Height));
    }
    else
    {
        std::cout << "Using default width and height: " << std::endl;
        return run(new GameFramework());
    }

    

    return 0;
}
