# CMakeList.txt: CMake-Projekt f�r "design_pattern_modern_cpp". Schlie�en Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# F�gen Sie der ausf�hrbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (liskov_subst "liskov_subst.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET liskov_subst PROPERTY CXX_STANDARD 20)
endif()

# TODO: F�gen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
target_include_directories(liskov_subst PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(liskov_subst ${Boost_LIBRARIES})