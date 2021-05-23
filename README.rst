========
Resource
========

Embed binary files and resources into c++ projects.

Usage
-----

Add this module as a git submodule.

.. code-block:: bash

  git submodule add https://github.com/Person-93/embed-resource.git vendor/embed-resource

In your ``CMakeLists.txt`` nclude this project as a subdirectory.

.. code-block:: cmake

  add_subdirectory(vendor/embed-resource)

There are two ways to add resources to binaries.

1.  Create a resource library:

.. code-block:: cmake

   add_resource_library(my_lib some_file.txt some_other_file.frag ...)
   target_link_library(some_exe PRIVATE my_lib)

2.  Add resources directly to a target:

.. code-block:: cmake

  target_add_resources(some_exe some_file.txt some_other_file.frag ...)

Then in your source c++ file:

.. code-block:: c++

  #include <iostream>
  #include <person93/resource.hpp>

  int main() {
    std::string_view file = PERSON93_RESOURCE(some_file_txt);
    std::cout << file << '\n';
  }
