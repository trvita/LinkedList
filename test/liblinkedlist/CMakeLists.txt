add_executable(linkedlistUnitTests
    liblinkedlist/linkedlist.cpp
)
target_link_libraries(
    linkedlistUnitTests
    PRIVATE
    GTest::gtest_main
    linkedlist
)

include(GoogleTest)
gtest_discover_tests(linkedlistUnitTests)
