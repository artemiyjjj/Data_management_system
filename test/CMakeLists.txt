#message("Test Cmake file")
#file(GLOB_RECURSE common_sources CONFIGURE_DEPENDS
#        ../src/*.c
#        ../include/*.h
#)
#
#file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS
#        test/*.c
#)
#
#add_library(tests OBJECT ${common_sources})
#target_include_directories(tests PUBLIC src)
#target_link_libraries(tests PUBLIC dataStorage)
#
##add_test(NAME Greeting COMMAND echo 'Hello, deployer!')
##add_test(NAME All_tests COMMAND Test_start)
#
#foreach(test_source IN LISTS test_sources)
#    string(REPLACE "/" ";" name_components ${test_source})
#    list(GET name_components -1 name)
#    string(REGEX REPLACE "\.c$" "" name ${name})
#    list(APPEND test_targets test_${name})
#
#    add_executable(test_${name} ${test_source})
#    target_link_libraries(test_${name} PRIVATE test_stubs)
#    add_test(NAME test_${name} COMMAND test_${name})
#endforeach()
#
#set(CMAKE_CTEST_ARGUMENTS)
#
#add_custom_target(check
#        COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_CTEST_ARGUMENTS}
#        DEPENDS ${test_targets})