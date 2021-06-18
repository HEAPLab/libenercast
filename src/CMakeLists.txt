add_library(tristar tristar.cpp)
add_library(epever epever.cpp)


target_link_libraries(tristar PUBLIC modbus)
target_link_libraries(epever PUBLIC modbus)
message(STATUS "Searching modbus.h....")
find_path(MODBUS_INCLUDE NAMES modbus/modbus.h)
if(NOT MODBUS_INCLUDE)
    message(FATAL_ERROR "libmodbus headers not found")
endif(NOT MODBUS_INCLUDE)
message(STATUS "-> Found " ${MODBUS_INCLUDE}/modbus/modbus.h)

# Use it as target_include_directories(target PUBLIC "${MODBUS_INCLUDE}/modbus/")

target_include_directories(tristar PUBLIC "${MODBUS_INCLUDE}/modbus/")
target_include_directories(epever PUBLIC "${MODBUS_INCLUDE}/modbus/")