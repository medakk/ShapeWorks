
cmake_policy(SET CMP0020 NEW)

FILE(GLOB SRCS *.cpp)
FILE(GLOB HDRS *.h)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/Groom )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/Optimize )
include_directories(${CMAKE_SOURCE_DIR}/ParticleShapeworks/include)

ADD_EXECUTABLE(ShapeworksCLT ${SRCS} ${HDRS})

TARGET_LINK_LIBRARIES(ShapeworksCLT
  ${ITK_LIBRARIES}
  ${VTK_LIBRARIES} 
  tinyxml
  ShapeWorksGroom
  ShapeWorksOptimize)
