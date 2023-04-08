add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(events)

target_sources(Bunny PRIVATE
  ./core.h
)
