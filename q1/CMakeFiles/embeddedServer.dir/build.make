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
include CMakeFiles/embeddedServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/embeddedServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/embeddedServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/embeddedServer.dir/flags.make

CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o: CMakeFiles/embeddedServer.dir/flags.make
CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o: src/embeddedServer.cpp
CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o: CMakeFiles/embeddedServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mahdi/jazaery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o -MF CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o.d -o CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o -c /home/mahdi/jazaery/src/embeddedServer.cpp

CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mahdi/jazaery/src/embeddedServer.cpp > CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.i

CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mahdi/jazaery/src/embeddedServer.cpp -o CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.s

# Object files for target embeddedServer
embeddedServer_OBJECTS = \
"CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o"

# External object files for target embeddedServer
embeddedServer_EXTERNAL_OBJECTS =

bin/embeddedServer: CMakeFiles/embeddedServer.dir/src/embeddedServer.cpp.o
bin/embeddedServer: CMakeFiles/embeddedServer.dir/build.make
bin/embeddedServer: /usr/local/lib/libopencv_gapi.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_highgui.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_ml.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_objdetect.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_photo.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_stitching.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_video.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_videoio.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_dnn.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_calib3d.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_features2d.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_flann.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_imgproc.so.4.8.0
bin/embeddedServer: /usr/local/lib/libopencv_core.so.4.8.0
bin/embeddedServer: CMakeFiles/embeddedServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mahdi/jazaery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/embeddedServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/embeddedServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/embeddedServer.dir/build: bin/embeddedServer
.PHONY : CMakeFiles/embeddedServer.dir/build

CMakeFiles/embeddedServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/embeddedServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/embeddedServer.dir/clean

CMakeFiles/embeddedServer.dir/depend:
	cd /home/mahdi/jazaery && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery /home/mahdi/jazaery/CMakeFiles/embeddedServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/embeddedServer.dir/depend
