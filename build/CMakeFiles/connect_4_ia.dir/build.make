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
CMAKE_SOURCE_DIR = /home/ulysse/Project/C/Connect4-ia-Cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ulysse/Project/C/Connect4-ia-Cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/connect_4_ia.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/connect_4_ia.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/connect_4_ia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/connect_4_ia.dir/flags.make

CMakeFiles/connect_4_ia.dir/main.cpp.o: CMakeFiles/connect_4_ia.dir/flags.make
CMakeFiles/connect_4_ia.dir/main.cpp.o: /home/ulysse/Project/C/Connect4-ia-Cpp/main.cpp
CMakeFiles/connect_4_ia.dir/main.cpp.o: CMakeFiles/connect_4_ia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ulysse/Project/C/Connect4-ia-Cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/connect_4_ia.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/connect_4_ia.dir/main.cpp.o -MF CMakeFiles/connect_4_ia.dir/main.cpp.o.d -o CMakeFiles/connect_4_ia.dir/main.cpp.o -c /home/ulysse/Project/C/Connect4-ia-Cpp/main.cpp

CMakeFiles/connect_4_ia.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connect_4_ia.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ulysse/Project/C/Connect4-ia-Cpp/main.cpp > CMakeFiles/connect_4_ia.dir/main.cpp.i

CMakeFiles/connect_4_ia.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connect_4_ia.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ulysse/Project/C/Connect4-ia-Cpp/main.cpp -o CMakeFiles/connect_4_ia.dir/main.cpp.s

CMakeFiles/connect_4_ia.dir/board.cpp.o: CMakeFiles/connect_4_ia.dir/flags.make
CMakeFiles/connect_4_ia.dir/board.cpp.o: /home/ulysse/Project/C/Connect4-ia-Cpp/board.cpp
CMakeFiles/connect_4_ia.dir/board.cpp.o: CMakeFiles/connect_4_ia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ulysse/Project/C/Connect4-ia-Cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/connect_4_ia.dir/board.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/connect_4_ia.dir/board.cpp.o -MF CMakeFiles/connect_4_ia.dir/board.cpp.o.d -o CMakeFiles/connect_4_ia.dir/board.cpp.o -c /home/ulysse/Project/C/Connect4-ia-Cpp/board.cpp

CMakeFiles/connect_4_ia.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connect_4_ia.dir/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ulysse/Project/C/Connect4-ia-Cpp/board.cpp > CMakeFiles/connect_4_ia.dir/board.cpp.i

CMakeFiles/connect_4_ia.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connect_4_ia.dir/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ulysse/Project/C/Connect4-ia-Cpp/board.cpp -o CMakeFiles/connect_4_ia.dir/board.cpp.s

CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o: CMakeFiles/connect_4_ia.dir/flags.make
CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o: /home/ulysse/Project/C/Connect4-ia-Cpp/playCalculator.cpp
CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o: CMakeFiles/connect_4_ia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ulysse/Project/C/Connect4-ia-Cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o -MF CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o.d -o CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o -c /home/ulysse/Project/C/Connect4-ia-Cpp/playCalculator.cpp

CMakeFiles/connect_4_ia.dir/playCalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connect_4_ia.dir/playCalculator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ulysse/Project/C/Connect4-ia-Cpp/playCalculator.cpp > CMakeFiles/connect_4_ia.dir/playCalculator.cpp.i

CMakeFiles/connect_4_ia.dir/playCalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connect_4_ia.dir/playCalculator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ulysse/Project/C/Connect4-ia-Cpp/playCalculator.cpp -o CMakeFiles/connect_4_ia.dir/playCalculator.cpp.s

# Object files for target connect_4_ia
connect_4_ia_OBJECTS = \
"CMakeFiles/connect_4_ia.dir/main.cpp.o" \
"CMakeFiles/connect_4_ia.dir/board.cpp.o" \
"CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o"

# External object files for target connect_4_ia
connect_4_ia_EXTERNAL_OBJECTS =

connect_4_ia: CMakeFiles/connect_4_ia.dir/main.cpp.o
connect_4_ia: CMakeFiles/connect_4_ia.dir/board.cpp.o
connect_4_ia: CMakeFiles/connect_4_ia.dir/playCalculator.cpp.o
connect_4_ia: CMakeFiles/connect_4_ia.dir/build.make
connect_4_ia: CMakeFiles/connect_4_ia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ulysse/Project/C/Connect4-ia-Cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable connect_4_ia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/connect_4_ia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/connect_4_ia.dir/build: connect_4_ia
.PHONY : CMakeFiles/connect_4_ia.dir/build

CMakeFiles/connect_4_ia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/connect_4_ia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/connect_4_ia.dir/clean

CMakeFiles/connect_4_ia.dir/depend:
	cd /home/ulysse/Project/C/Connect4-ia-Cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ulysse/Project/C/Connect4-ia-Cpp /home/ulysse/Project/C/Connect4-ia-Cpp /home/ulysse/Project/C/Connect4-ia-Cpp/build /home/ulysse/Project/C/Connect4-ia-Cpp/build /home/ulysse/Project/C/Connect4-ia-Cpp/build/CMakeFiles/connect_4_ia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/connect_4_ia.dir/depend

