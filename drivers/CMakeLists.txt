# The include is set in the project base CMakeLists.txt as there is only one
# level of indirection

set(DRIVER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Peripherals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Time_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/USART_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/_write.c
    PARENT_SCOPE)
