add_executable(Bunny "")
target_include_directories(Bunny PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
add_subdirectory(src)
add_subdirectory(vendor)
target_link_libraries(Bunny PRIVATE glad glfw fmt)

add_custom_target(BunnyDocs ALL COMMAND doxygen ./doxygen WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/docs BYPRODUCTS docs/html)