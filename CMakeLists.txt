cmake_minimum_required(VERSION 3.10)
project(AVLTreeProject C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")

add_library(SingleLinkedList STATIC
        src/BonusTask/SingleLinkedList/SingleLinkedList.c
        src/BonusTask/UtilitySingleLinkedList.c
)
target_include_directories(SingleLinkedList PUBLIC src/BonusTask/SingleLinkedList)


add_library(AVLTree STATIC
        src/MainTask/AVL-Tree/AVL-Tree.c
        src/MainTask/UtilityAVLTree.c
)
target_include_directories(AVLTree PUBLIC src/MainTask/AVL-Tree)

add_executable(airport_tree src/MainTask/UtilityAVLTree.c)
target_link_libraries(airport_tree AVLTree)

add_executable(airport_list src/BonusTask/UtilitySingleLinkedList.c)
target_link_libraries(airport_list SingleLinkedList)

set(TEST_SOURCES
        Tests/BonusTask/SingleLinkedList/TestSingleLinkedList.c
        Tests/MainTask/AVL-Tree/TestAVL-Tree.c
)

enable_testing()

foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SRC})

    target_link_libraries(${TEST_NAME} SingleLinkedList AVLTree)

    get_filename_component(TEST_DIR ${TEST_SRC} DIRECTORY)
    set_property(TARGET ${TEST_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${TEST_DIR}")

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${TEST_DIR}")
endforeach()

# Профилирование
if(EXISTS "${CMAKE_SOURCE_DIR}/src/Benchmarks/bench_list.c")
    add_executable(bench_list src/Benchmarks/bench_list.c)
    target_link_libraries(bench_list SingleLinkedList)

    add_executable(bench_avl src/Benchmarks/bench_avl.c)
    target_link_libraries(bench_avl AVLTree)
endif()