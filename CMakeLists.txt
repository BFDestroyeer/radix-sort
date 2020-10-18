cmake_minimum_required(VERSION 2.8)

project(radix-sort)

include_directories(include)

set(RADIX_SORT_SOURCE
    src/tbbsort/counter.cpp
    src/tbbsort/relocator.cpp
    src/tbbsort/sorter.cpp
    src/functions.cpp
    src/logger.cpp
    src/main.cpp
    src/mpisort.cpp
    src/ompsort.cpp
    src/recursivesequentialsort.cpp
    src/sequentialsort.cpp
    src/tbbsort.cpp
    src/threadsort.cpp
)

add_executable(radix-sort ${RADIX_SORT_SOURCE})


# pthread for Unix
if(UNIX)
    find_package(Threads REQUIRED)
    if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(radix-sort PUBLIC "-pthread")
    endif()
    if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(radix-sort "${CMAKE_THREAD_LIBS_INIT}")
    endif()
endif(UNIX)

# MPI
find_package(MPI REQUIRED)
include_directories(SYSTEM "${MPI_CXX_INCLUDE_DIRS}")
target_link_libraries(radix-sort ${MPI_CXX_LIBRARIES})

# OpenMP
if(MSVC)
    target_compile_options(radix-sort PUBLIC "/openmp")
endif()
if(UNIX)
    target_compile_options(radix-sort PUBLIC "-fopenmp")
endif()

# Intel TBB
set(TBB_DIR "D:/Libraries/TBB/cmake")
set(TBB_INCLUDE_DIRS "D:/Libraries/TBB/include")
find_package(TBB REQUIRED)
include_directories(TBB_INCLUDE_DIRS)
target_link_libraries(radix-sort ${TBB_IMPORTED_TARGETS})