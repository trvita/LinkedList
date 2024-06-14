
add_library(linkedlist
    linkedlist/linkedlist.cpp
    linkedlist/linkedlist.hpp
)
target_include_directories(linkedlist
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/linkedlist
)