cmake_minimum_required(VERSION 3.10)
project(AVLTreeProject C)


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


set(TEST_SOURCES
        Tests/BonusTask/SingleLinkedList/TestSingleLinkedList.c
        Tests/MainTask/AVL-Tree/TestAVL-Tree.c
)

foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} SingleLinkedList AVLTree)
    get_filename_component(TEST_DIR ${TEST_SRC} DIRECTORY)
    set_property(TARGET ${TEST_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${TEST_DIR})
endforeach()

enable_testing()
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    get_filename_component(TEST_DIR ${TEST_SRC} DIRECTORY)
    set(FULL_TEST_DIR ${CMAKE_SOURCE_DIR}/${TEST_DIR})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${FULL_TEST_DIR})
endforeach()