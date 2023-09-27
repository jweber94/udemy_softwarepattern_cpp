add_executable(uniform_init_builder "uniform_init_builder.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
set_property(TARGET uniform_init_builder PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(uniform_init_builder PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(uniform_init_builder ${Boost_LIBRARIES})