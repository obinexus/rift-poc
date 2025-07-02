# CMake generated Testfile for 
# Source directory: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0
# Build directory: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(QA_TruePositive "/usr/bin/cmake" "-E" "echo" "Running TruePositive tests...")
set_tests_properties(QA_TruePositive PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;235;add_test;/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;0;")
add_test(QA_TrueNegative "/usr/bin/cmake" "-E" "echo" "Running TrueNegative tests...")
set_tests_properties(QA_TrueNegative PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;235;add_test;/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;0;")
add_test(QA_FalsePositive "/usr/bin/cmake" "-E" "echo" "Running FalsePositive tests...")
set_tests_properties(QA_FalsePositive PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;235;add_test;/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;0;")
add_test(QA_FalseNegative "/usr/bin/cmake" "-E" "echo" "Running FalseNegative tests...")
set_tests_properties(QA_FalseNegative PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;235;add_test;/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/CMakeLists.txt;0;")
subdirs("tests")
