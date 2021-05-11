#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


int main( int argc, char** argv ) {
    if ( argc < 3 ) {
        std::cerr << "USAGE: " << *argv
                  << " {sym} {rsrc}\n\n"
                     "  Creates {sym}.c from the contents of {rsrc}\n";
        return EXIT_FAILURE;
    }

    const auto dst = std::filesystem::path{ argv[ 1 ] };
    const auto src = std::filesystem::path{ argv[ 2 ] };

    std::string sym = src.filename().string();
    replace( sym.begin(), sym.end(), '.', '_' );
    replace( sym.begin(), sym.end(), '-', '_' );

    create_directories( dst.parent_path() );

    std::ofstream ofs{ dst };
    std::ifstream ifs{ src };

    ofs << "#include <stdlib.h>\n";
    ofs << "const char _resource_" << sym << "[] = {\n";

    size_t lineCount = 0;
    while ( !ifs.eof() ) {
        char c;
        ifs.get( c );
        ofs << "0x" << std::hex << ( c & 0xff ) << ", ";
        if ( ++lineCount == 10 ) {
            ofs << '\n';
            lineCount = 0;
        }
    }


    ofs << "\n};\n";
    ofs << "const size_t _resource_" << sym << "_len = sizeof(_resource_" << sym
        << ");\n";

    return EXIT_SUCCESS;
}
