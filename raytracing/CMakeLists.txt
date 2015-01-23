cmake_minimum_required(VERSION 2.8)

PROJECT( raytracing )

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -std=c++11")
    set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
endif()


SET( raytracing_SRCS
     main.cpp
     scene.cpp
     sceneobject.cpp
     scene.h
     sceneobject.h
     myimage.h
     mymath.h
   )


ADD_EXECUTABLE( raytracingBIN ${raytracing_SRCS}  )
