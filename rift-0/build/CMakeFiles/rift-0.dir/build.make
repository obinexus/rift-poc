# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build

# Include any dependencies generated for this target.
include CMakeFiles/rift-0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rift-0.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rift-0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rift-0.dir/flags.make

CMakeFiles/rift-0.dir/src/cli/main.c.o: CMakeFiles/rift-0.dir/flags.make
CMakeFiles/rift-0.dir/src/cli/main.c.o: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/main.c
CMakeFiles/rift-0.dir/src/cli/main.c.o: CMakeFiles/rift-0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rift-0.dir/src/cli/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rift-0.dir/src/cli/main.c.o -MF CMakeFiles/rift-0.dir/src/cli/main.c.o.d -o CMakeFiles/rift-0.dir/src/cli/main.c.o -c /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/main.c

CMakeFiles/rift-0.dir/src/cli/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rift-0.dir/src/cli/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/main.c > CMakeFiles/rift-0.dir/src/cli/main.c.i

CMakeFiles/rift-0.dir/src/cli/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rift-0.dir/src/cli/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/main.c -o CMakeFiles/rift-0.dir/src/cli/main.c.s

CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o: CMakeFiles/rift-0.dir/flags.make
CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/lexer_command.c
CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o: CMakeFiles/rift-0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o -MF CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o.d -o CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o -c /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/lexer_command.c

CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/lexer_command.c > CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.i

CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/lexer_command.c -o CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.s

CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o: CMakeFiles/rift-0.dir/flags.make
CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/r_command.c
CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o: CMakeFiles/rift-0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o -MF CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o.d -o CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o -c /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/r_command.c

CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/r_command.c > CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.i

CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/r_command.c -o CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.s

CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o: CMakeFiles/rift-0.dir/flags.make
CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/ext_command.c
CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o: CMakeFiles/rift-0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o -MF CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o.d -o CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o -c /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/ext_command.c

CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/ext_command.c > CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.i

CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/ext_command.c -o CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.s

CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o: CMakeFiles/rift-0.dir/flags.make
CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o: /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/rift_gov_command.c
CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o: CMakeFiles/rift-0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o -MF CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o.d -o CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o -c /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/rift_gov_command.c

CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/rift_gov_command.c > CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.i

CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/src/cli/commands/rift_gov_command.c -o CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.s

# Object files for target rift-0
rift__0_OBJECTS = \
"CMakeFiles/rift-0.dir/src/cli/main.c.o" \
"CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o" \
"CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o" \
"CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o" \
"CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o"

# External object files for target rift-0
rift__0_EXTERNAL_OBJECTS =

bin/rift-0: CMakeFiles/rift-0.dir/src/cli/main.c.o
bin/rift-0: CMakeFiles/rift-0.dir/src/cli/commands/lexer_command.c.o
bin/rift-0: CMakeFiles/rift-0.dir/src/cli/commands/r_command.c.o
bin/rift-0: CMakeFiles/rift-0.dir/src/cli/commands/ext_command.c.o
bin/rift-0: CMakeFiles/rift-0.dir/src/cli/commands/rift_gov_command.c.o
bin/rift-0: CMakeFiles/rift-0.dir/build.make
bin/rift-0: lib/librift-0.so.0.1.0
bin/rift-0: CMakeFiles/rift-0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable bin/rift-0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rift-0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rift-0.dir/build: bin/rift-0
.PHONY : CMakeFiles/rift-0.dir/build

CMakeFiles/rift-0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rift-0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rift-0.dir/clean

CMakeFiles/rift-0.dir/depend:
	cd /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0 /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0 /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build /mnt/c/Users/OBINexus/Projects/github/rift-poc/rift-0/build/CMakeFiles/rift-0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rift-0.dir/depend

