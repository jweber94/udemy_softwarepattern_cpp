add_executable (multi_builder "./src/main.cpp" "./include/PersonBuilder.hpp" "./include/PersonAddressBuilder.hpp" "./include/PersonJobBuilder.hpp" "./include/Person.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET multi_builder PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(multi_builder PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(multi_builder ${Boost_LIBRARIES})