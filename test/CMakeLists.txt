set(target "${PRACTICE1_TESTS}")

FILE(GLOB hdrs "*.h*")
FILE(GLOB srcs "*.cpp")

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/gtest")

ADD_EXECUTABLE(${target} ${srcs} ${hdrs})
TARGET_LINK_LIBRARIES(${target} gtest ${PRACTICE1_LIBRARY})

add_custom_command(
    TARGET ${PRACTICE1_TESTS}
    POST_BUILD
    COMMAND ln -fns "${CMAKE_SOURCE_DIR}/testdata" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/testdata"
    COMMENT "Adding a symbolic link to testdata"
)
