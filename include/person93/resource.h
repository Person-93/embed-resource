#pragma once

#include <array>
#include <cstddef>


namespace person93::resource {
    class Resource {
    public:
        Resource( const std::byte* start, const std::size_t len )
            : resource_data{ start }, data_len{ len } {}

        const std::byte* data() const { return resource_data; }
        std::size_t size() const { return data_len; }

        const char* begin() const { return resource_data; }
        const char* end() const { return resource_data + data_len; }

    private:
        const std::byte* resource_data;
        std::size_t data_len;
    };
}// namespace person93::resource

#define LOAD_RESOURCE( RESOURCE )                                                      \
    ( []() {                                                                           \
        extern const std::byte* const _resource_##RESOURCE;                            \
        extern const std::size_t _resource_##RESOURCE##_len;                           \
        return ::person93::resource::Resource( _resource_##RESOURCE,                   \
                                               _resource_##RESOURCE##_len );           \
    } )()
