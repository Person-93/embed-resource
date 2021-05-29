#include <algorithm>
#include <cstddef>
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

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    const auto dst = std::filesystem::path{ argv[ 1 ] } += ".c";
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    const auto src = std::filesystem::path{ argv[ 2 ] };

    std::string sym = src.filename().string();
    replace( sym.begin(), sym.end(), '.', '_' );
    replace( sym.begin(), sym.end(), '-', '_' );

    if ( const auto parent = dst.parent_path(); !parent.empty() )
        create_directories( parent );

    std::ofstream ofs{ dst };
    std::ifstream ifs{ src };

    ofs << std::hex;
    ofs << "#include <stdlib.h>\n";
    ofs << "const char _resource_" << sym << "_data[] = {\n";

    constexpr std::size_t lineLength = 10;
    std::size_t lineCount            = 0;
    while ( !ifs.eof() ) {
        char c;// NOLINT(cppcoreguidelines-init-variables) initialized next line
        ifs.get( c );
        ofs << "0x" << static_cast< int >( c ) << ", ";
        if ( ++lineCount == lineLength ) {
            ofs << '\n';
            lineCount = 0;
        }
    }


    ofs << "\n};\n";
    ofs << "const size_t _resource_" << sym << "_len = sizeof(_resource_" << sym
        << "_data);\n";

    return EXIT_SUCCESS;
}
