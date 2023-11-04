# concepts
add_executable (concepts "concepts.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET concepts PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(concepts PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(concepts ${Boost_LIBRARIES})

# traits class
add_executable (traits_class "traits_class.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET traits_class PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(traits_class PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(traits_class ${Boost_LIBRARIES})