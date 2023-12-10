add_executable (pointer_cor "pointer_cor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pointer_cor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(pointer_cor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(pointer_cor ${Boost_LIBRARIES})