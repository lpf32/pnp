project(pnp)

include_directories(include)
file(GLOB LIBSOURCES "lib/*.cc")
add_executable(ttcp bin/ttcp.cc ${LIBSOURCES})
target_link_libraries(ttcp boost_program_options)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(roundtrip_udp bin/roundtrip_udp.cc ${LIBSOURCES})
target_link_libraries(roundtrip_udp boost_program_options)
