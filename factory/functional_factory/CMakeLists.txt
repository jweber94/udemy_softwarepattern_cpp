add_executable (functional_factory "main.cpp" "HotDrink.hpp" "HotDrinkFactory.hpp" "DrinkFactory.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET functional_factory PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(functional_factory PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(functional_factory ${Boost_LIBRARIES})