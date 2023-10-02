add_executable (abstract_factory "main.cpp" "HotDrink.hpp" "HotDrinkFactory.hpp" "DrinkFactory.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET abstract_factory PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(abstract_factory PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(abstract_factory ${Boost_LIBRARIES})