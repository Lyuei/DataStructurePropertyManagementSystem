#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 1) {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    // Get the absolute path of the current executable (the C++ program)
    fs::path executablePath = fs::canonical(fs::path(argv[0]));

    // Get the directory containing the executable (current working directory)
    fs::path currentDirectory = executablePath.parent_path();

    std::cout << "Current directory of the file: " << currentDirectory << std::endl;

    return 0;
}
