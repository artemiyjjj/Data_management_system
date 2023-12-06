cmake_minimum_required(VERSION 3.17)

project(lab1Make
    VERSION 1.0
    LANGUAGES C)

set(CMAKE_C_STANDARD)
## Add tasks subprojects
#include(cmake/utils.cmake)
#add_subprojects(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        src/*.c
        src/*.h
        include/*.h
)

add_executable(data_storage ${sources}
        test/src/common/data_structures_tests/tree_test.c)
target_include_directories(data_storage PRIVATE src include)

#list(FILTER sources EXCLUDE REGEX A.c)
#add_library(dataStorage_lib STATIC ${sources})
#target_include_directories(dataStorage_lib PUBLIC include)
#
#if(EXISTS A.c)
#    add_executable(dataStorage_exe A.c)
#    target_link_libraries(dataStorage_exe PRIVATE dataStorage_lib)
#    set_target_properties(dataStorage_exe PROPERTIES OUTPUT_NAME dataStorage)
#endif()


#option(BUILD_TESTING "Enable tests" ON)
#if(BUILD_TESTING)
#    enable_testing()
#    add_subdirectory(test)
#endif()
