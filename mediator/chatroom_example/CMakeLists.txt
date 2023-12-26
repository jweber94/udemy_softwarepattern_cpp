add_executable (chatroom_mediator_example "main.cpp" "ChatRoom.cpp" "ChatRoom.hpp" "Person.cpp" "Person.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chatroom_mediator_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(chatroom_mediator_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(chatroom_mediator_example ${Boost_LIBRARIES})