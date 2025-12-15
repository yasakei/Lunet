cmake_minimum_required(VERSION 3.10)
project(Lunet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(fmt QUIET)

if(NOT fmt_FOUND)
    # If fmt is not found, include the local version
    include_directories(src/include)
endif()

# Define source files
set(SOURCES
    src/Main.cpp
    src/lunet/Lexer.cpp
    src/lunet/Error.cpp
)

# Define headers
set(HEADERS
    src/Lunet.h
    src/lunet/Lexer.h
    src/lunet/Token.h
    src/lunet/Error.h
)

# Create executable
add_executable(Lunet ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Lunet PRIVATE src)

# Link fmt if available as a package, otherwise rely on header inclusion
if(fmt_FOUND)
    target_link_libraries(Lunet fmt::fmt)
else()
    # If fmt is not available as a package, we still define the macro that the source expects
    target_compile_definitions(Lunet PRIVATE FMT_HEADER_ONLY)
endif()

# Platform-specific configurations
if(WIN32)
    # Windows-specific settings
    target_compile_definitions(Lunet PRIVATE WIN32_LEAN_AND_MEAN)
else()
    # Linux-specific settings
endif()