# CMakeLists for RIFT Stage-0 tests

add_executable(qa_assert qa_assert.c)

target_link_libraries(qa_assert PRIVATE
    rift-stage0
    Threads::Threads
)

add_test(NAME QA_All COMMAND qa_assert)
add_executable(qa_assert qa_assert.c)

add_test(NAME QA_Suite COMMAND qa_assert)
