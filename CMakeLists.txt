cmake_minimum_required( VERSION 3.14 )
project( itertools CXX )

set( CMAKE_CXX_STANDARD 17 )

add_library( itertools INTERFACE )
target_sources( itertools INTERFACE include/itertools.h )
target_include_directories( itertools INTERFACE include )

enable_testing()
# cmake integration with catch2.
# see https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#top
find_package( Catch2 REQUIRED )

# include necessary cmake modules.
include( CTest )
include( Catch )

# target for test runner.
add_executable( test_itertools )
target_sources( test_itertools PRIVATE
                test/test_main.cpp
                test/test_wrapper_base.cpp
                test/test_itertools.cpp )
target_link_libraries( test_itertools itertools Catch2::Catch2 )

# automatically install tests.
catch_discover_tests( test_itertools )

#install( TARGETS itertools DESTINATION include )
install(FILES include/itertools.h DESTINATION include)
