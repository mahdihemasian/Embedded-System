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
CMAKE_SOURCE_DIR = /home/mahdi/jazaery

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mahdi/jazaery

# Include any dependencies generated for this target.
include CMakeFiles/webServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/webServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/webServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webServer.dir/flags.make

CMakeFiles/webServer.dir/src/webServer.cpp.o: CMakeFiles/webServer.dir/flags.make
CMakeFiles/webServer.dir/src/webServer.cpp.o: src/webServer.cpp
CMakeFiles/webServer.dir/src/webServer.cpp.o: CMakeFiles/webServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mahdi/jazaery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webServer.dir/src/webServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webServer.dir/src/webServer.cpp.o -MF CMakeFiles/webServer.dir/src/webServer.cpp.o.d -o CMakeFiles/webServer.dir/src/webServer.cpp.o -c /home/mahdi/jazaery/src/webServer.cpp

CMakeFiles/webServer.dir/src/webServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webServer.dir/src/webServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mahdi/jazaery/src/webServer.cpp > CMakeFiles/webServer.dir/src/webServer.cpp.i

CMakeFiles/webServer.dir/src/webServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webServer.dir/src/webServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mahdi/jazaery/src/webServer.cpp -o CMakeFiles/webServer.dir/src/webServer.cpp.s

# Object files for target webServer
webServer_OBJECTS = \
"CMakeFiles/webServer.dir/src/webServer.cpp.o"

# External object files for target webServer
webServer_EXTERNAL_OBJECTS =

bin/webServer: CMakeFiles/webServer.dir/src/webServer.cpp.o
bin/webServer: CMakeFiles/webServer.dir/build.make
bin/webServer: CMakeFiles/webServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mahdi/jazaery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/webServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webServer.dir/build: bin/webServer
.PHONY : CMakeFiles/webServer.dir/build

CMakeFiles/webServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webServer.dir/clean

CMakeFiles/webServer.dir/depend:
	cd /home/mahdi/jazaery && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery/CMakeFiles/webServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webServer.dir/depend

