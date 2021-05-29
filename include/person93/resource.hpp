#pragma once

#include <string_view>

#ifndef __clang_analyzer__
#define PERSON93_RESOURCE( RESOURCE )                                                  \
    []() {                                                                             \
        extern const char _resource_##RESOURCE##_data[];                               \
        extern const ::std::size_t _resource_##RESOURCE##_len;                         \
        return ::std::string_view{                                                     \
                static_cast< const char* >( _resource_##RESOURCE##_data ),             \
                _resource_##RESOURCE##_len - 1 };                                      \
    }()
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define PERSON93_RESOURCE( RESOURCE )                                                  \
    ::std::string_view {}
#endif
