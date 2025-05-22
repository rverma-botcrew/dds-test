cmake_minimum_required(VERSION 3.15)
project(my_dds_app LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure install prefixes are set
if(NOT DEFINED ENV{CYCLONE_INSTALL} OR NOT DEFINED ENV{CXX_INSTALL})
  message(FATAL_ERROR
    "Please set CYCLONE_INSTALL (CycloneDDS core) and CXX_INSTALL (CycloneDDS-CXX) in your environment")
endif()

# Add both CycloneDDS core and C++ binding to the prefix path
list(APPEND CMAKE_PREFIX_PATH
     "$ENV{CYCLONE_INSTALL}"
     "$ENV{CXX_INSTALL}")

# Find CycloneDDS-CXX package
find_package(CycloneDDS-CXX REQUIRED)

# Where your IDL files live
set(IDL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/idl")

# Generate C++ types from IDL
idlcxx_generate(
  TARGET example_types
  FILES "${IDL_DIR}/StringMessage.idl"
)

# Define the application
add_executable(my_dds_app
  src/main.cpp
)

add_executable(yapper src/yapper.cpp)
target_link_libraries(yapper PRIVATE example_types CycloneDDS-CXX::ddscxx)

add_executable(lethimcook src/lethimcook.cpp)
target_link_libraries(lethimcook PRIVATE example_types CycloneDDS-CXX::ddscxx)


# Link against the generated types and CycloneDDS-CXX
target_link_libraries(my_dds_app
  PRIVATE
    example_types
    CycloneDDS-CXX::ddscxx
)

# Optional: install the executable
install(TARGETS my_dds_app RUNTIME DESTINATION bin)
