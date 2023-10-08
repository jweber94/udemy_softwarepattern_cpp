add_executable (Multiton "Multiton.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Multiton PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Multiton PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Multiton ${Boost_LIBRARIES})