#pragma once

#include <string_view>


#define PERSON93_RESOURCE( RESOURCE )                                                  \
    []() {                                                                             \
        extern const char _resource_##RESOURCE##_data[];                               \
        extern const ::std::size_t _resource_##RESOURCE##_len;                         \
        return ::std::string_view{ _resource_##RESOURCE##_data,                        \
                                   _resource_##RESOURCE##_len - 1 };                   \
    }()
