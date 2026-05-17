

find_package(glog REQUIRED)
find_package(Boost REQUIRED COMPONENTS locale)

add_subdirectory(src)
add_subdirectory(tests)
