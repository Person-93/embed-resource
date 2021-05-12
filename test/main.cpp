#include <person93/resource.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>


std::string readFile( const std::filesystem::path& );
void mismatch( int number, std::string_view sample, std::string_view resource );


int main() {
    using std::filesystem::current_path;

    const auto sample1   = readFile( current_path() / "sample1.txt" );
    const auto resource1 = PERSON93_RESOURCE( sample1_txt );
    const auto sample2   = readFile( current_path() / "sample-2.txt" );
    const auto resource2 = PERSON93_RESOURCE( sample_2_txt );
    const auto sample3   = readFile( current_path() / "dir/sample3.txt" );
    const auto resource3 = PERSON93_RESOURCE( sample3_txt );

    int exitCode = 0;
    if ( sample1 != resource1 ) {
        ++exitCode;
        mismatch( 1, sample1, resource1 );
    }

    if ( sample2 != resource2 ) {
        ++exitCode;
        mismatch( 2, sample2, resource2 );
    }

    if ( sample3 != resource3 ) {
        ++exitCode;
        mismatch( 3, sample3, resource3 );
    }

    return exitCode;
}

std::string readFile( const std::filesystem::path& path ) {
    std::ifstream ifstream{ path };
    using Iter = std::istreambuf_iterator< std::ifstream::char_type,
                                           std::ifstream ::traits_type >;
    std::string contents;
    std::copy( Iter{ ifstream }, Iter{}, std::back_inserter( contents ) );
    return contents;
}

void mismatch( int number, std::string_view sample, std::string_view resource ) {
    std::cerr << "==================================\n";
    std::cerr << "mismatch in sample " << number << "\n\n";
    std::cerr << "Sample:\n" << sample << "\n\n";
    std::cerr << "Resource:\n" << resource << "\n\n";
    std::cerr << "==================================\n\n";
}
