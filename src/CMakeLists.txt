add_executable(2001 2001.cpp)
add_executable(2002 2002.cpp)
add_executable(2003 2003.cpp)
add_executable(2003p 2003_parallel.cpp)
add_executable(2004 2004.cpp)
add_executable(2005 2005.cpp)
add_executable(2005a 2005_alt.cpp)
add_executable(2006 2006.cpp)

if(UNIX)
    set(THREADS_PREFER_PTHREAD ON)
    find_package(Threads REQUIRED)

    target_link_libraries(2003p PRIVATE Threads::Threads)
endif()

