cmake_minimum_required(VERSION 3.10)

project(DSA VERSION 1.0 DESCRIPTION "Advanced DSA topics")


# cmake flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# no cmake in the main project directory
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "dumbass. lol")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
  message(STATUS "Build type set to default")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Output binaries to a sub directory "bin"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable cmake testing
include(CTest)
enable_testing()

# Enable GoogleTest
include(GoogleTest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest googletest)





# ===== DIRECTORIES =====

# Add directory containing header files
include_directories(include)

# ===== END OF DIRECTORIES =====




# ===== LIBRARIES =====

# LINKED LIST
add_library(linked_list_lib STATIC src/data-structures/lists/llist.c)
target_include_directories(linked_list_lib PUBLIC src/data-structures/lists)

# BINARY SEARCH TREE
add_library(binary_search_tree_lib STATIC src/data-structures/trees/bst.c)
target_include_directories(binary_search_tree_lib PUBLIC src/data-structures/trees)

# AVL TREE
add_library(avl_tree_lib STATIC src/data-structures/trees/avl.cc)
target_include_directories(avl_tree_lib PUBLIC src/data-structures/trees)

# RED BLACK TREE
add_library(red_black_tree_lib STATIC src/data-structures/trees/rbt.cc)
target_include_directories(red_black_tree_lib PUBLIC src/data-structures/trees)

# ===== END OF LIBRARIES =====





# ===== EXECUTABLES =====

# MAIN
add_executable(
  main src/main.cc
)
target_link_libraries(
  main
  linked_list_lib
  binary_search_tree_lib
)

# LINKED LIST
add_executable(
  linked_list_test
  tests/data-structures/lists/llist_test.cc
)
target_link_libraries(
  linked_list_test
  gtest_main
  linked_list_lib
)

# BINARY SEARCH TREE
add_executable(
  binary_search_tree_test
  tests/data-structures/trees/bst_test.cc
)
target_link_libraries(
  binary_search_tree_test
  gtest_main
  binary_search_tree_lib
)

# AVL TREE
add_executable(
  avl_tree_test
  tests/data-structures/trees/avl_test.cc
)
target_link_libraries(
  avl_tree_test
  gtest_main
  avl_tree_lib
)

# ===== END OF EXECUTABLES =====





# ===== TESTS =====

gtest_discover_tests(linked_list_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data-structures/lists)
gtest_discover_tests(binary_search_tree_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data-structures/trees)
gtest_discover_tests(avl_tree_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data-structures/trees)

# ===== END OF TESTS =====



# gcovr
include(cmake/CodeCoverageReportConfig.cmake)
generate_coverage_report(
  TARGETS
    linked_list_lib
    binary_search_tree_lib
    avl_tree_lib
  TESTS
    linked_list_test
    binary_search_tree_test
    avl_tree_test
)
