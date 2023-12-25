add_executable (coroutines_explained "coroutines_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET coroutines_explained PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(coroutines_explained PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(coroutines_explained ${Boost_LIBRARIES})