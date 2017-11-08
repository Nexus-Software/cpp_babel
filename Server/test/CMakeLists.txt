cmake_minimum_required(VERSION 2.8.2)

find_library(G_TEST gtest)
if (G_TEST)
    include_directories(${gtest_SOURCE_DIR}/include)
    set(test_sources
        main.cpp
        server_protocol.cpp
        )

    list(REMOVE_ITEM SOURCE_FILES ${BASE_SE}/src/main.cpp)

    add_executable(tests ${test_sources} ${SOURCE_FILES})
    target_link_libraries(tests ${G_TEST})

    target_compile_definitions(tests PRIVATE -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)
    target_link_libraries(tests ${Boost_LIBRARIES})
else()
    message("Not GTEST install, tests is not possible")
endif()
