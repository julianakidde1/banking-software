project(bank_app)

set(SOURCES
    app/main.cpp
)

add_subdirectory(accounts)
add_subdirectory(utils)

add_executable(bank_app ${SOURCES})

target_include_directories(
    bank_app
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/accounts
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/utils
)

target_link_libraries(bank_app
    PRIVATE 
    accounts
    utils
)