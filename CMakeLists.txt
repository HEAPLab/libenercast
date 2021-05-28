cmake_minimum_required(VERSION 3.10.2)

project(libEnTris)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(Test)








#list(APPEND EXTRA_LIBS Calculator)
#list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Calculator")

#target_link_libraries(test1 PUBLIC ${EXTRA_LIBS})
#target_include_directories(test1 PUBLIC "${PROJECT_BINARY_DIR}"${EXTRA_INCLUDES})




