add_executable (homework_builder "homework_builder.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_builder PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_builder PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_builder ${Boost_LIBRARIES})