cmake_minimum_required(VERSION 3.5)
project(project4 CXX)

# Require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create unit tests 
#   In the following, notice that ArrayBag.cpp is NOT listed.  
#   Instead, ArrayBag.cpp is #included by NewArrayBag.h to support templates.
add_executable(unit_tests hw4_test.cpp treeNode.h hw4_datarecord.h treeNode.cpp prefixTree.h prefixTree.cpp hw4_datarecord.cpp catch.hpp)
add_executable(instructor_tests .github/instructor_tests.cpp treeNode.h hw4_datarecord.h treeNode.cpp prefixTree.h prefixTree.cpp hw4_datarecord.cpp catch.hpp)

# The following will not be graded at the autograder. 
#  It is primarily for your convenience 
#  to experiment with your own main() function in hw1_main.cpp.
add_executable(hw4_main hw4_main.cpp treeNode.h hw4_datarecord.h treeNode.cpp prefixTree.h prefixTree.cpp hw4_datarecord.cpp)


# Unit tests 
enable_testing(unittest hw4_test)



