add_library(utils)

target_sources(
    utils
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
)

target_include_directories(
    utils
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/accounts
)