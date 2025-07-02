add_executable(qa_assert qa_assert.c)

add_test(NAME QA_Suite COMMAND qa_assert)
