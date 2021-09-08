add_executable(testTriStar testTriStar.cpp)
target_link_libraries(testTriStar PUBLIC tristar epever)

add_executable(testEpever testEpever.cpp)
target_link_libraries(testEpever PUBLIC tristar epever)






