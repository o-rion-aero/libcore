project("orion.libcore")
cmake_minimum_required(VERSION 3.4)

include("cmake/ORION_Framework.cmake")

ORION_USE_BOOST("1.63.0")

ORION_TARGET(libcore static)

ORION_ARTIFACT_DEPENDENCY(libcore geographiclib 1.46)

target_link_libraries(libcore Qt5::Widgets)