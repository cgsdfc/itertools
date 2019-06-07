cmake_minimum_required( VERSION 3.5 )
project( itertools CXX )

set( CMAKE_CXX_STANDARD 17 )

# Setup conan and include everything.
include( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
conan_basic_setup()

add_library( itertools INTERFACE )
#target_sources( itertools INTERFACE
#                include/itertools.h
#                include/itertools/zip.h
#                include/itertools/enumerate.h
#                include/itertools/range.h
#                include/itertools/detail.h )
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
                test/test_iterable_wrapper.cpp
                test/test_enumerate.cpp
                test/test_zip.cpp
                test/test_range.cpp
                test/test_rvalue_ref_to_array.cpp
                test/test_map.cpp )
target_link_libraries( test_itertools itertools ${CONAN_LIBS} )

# automatically install tests.
catch_discover_tests( test_itertools )

#install( TARGETS itertools DESTINATION include )
install( FILES include/itertools.h DESTINATION include )
install( DIRECTORY include/itertools DESTINATION include )
