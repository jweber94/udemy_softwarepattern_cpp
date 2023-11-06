add_executable (static_decorator "static_decorator.cpp" "concepts/concepts.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET static_decorator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(static_decorator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(static_decorator ${Boost_LIBRARIES})

add_subdirectory("concepts")
add_subdirectory("traits_classes")