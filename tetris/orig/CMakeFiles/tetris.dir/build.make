# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cdoucet/local/formations/mds/tetris/orig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cdoucet/local/formations/mds/tetris/orig

# Include any dependencies generated for this target.
include CMakeFiles/tetris.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tetris.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tetris.dir/flags.make

CMakeFiles/tetris.dir/tetris.c.o: CMakeFiles/tetris.dir/flags.make
CMakeFiles/tetris.dir/tetris.c.o: tetris.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cdoucet/local/formations/mds/tetris/orig/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/tetris.dir/tetris.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tetris.dir/tetris.c.o   -c /home/cdoucet/local/formations/mds/tetris/orig/tetris.c

CMakeFiles/tetris.dir/tetris.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tetris.dir/tetris.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/cdoucet/local/formations/mds/tetris/orig/tetris.c > CMakeFiles/tetris.dir/tetris.c.i

CMakeFiles/tetris.dir/tetris.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tetris.dir/tetris.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/cdoucet/local/formations/mds/tetris/orig/tetris.c -o CMakeFiles/tetris.dir/tetris.c.s

CMakeFiles/tetris.dir/tetris.c.o.requires:
.PHONY : CMakeFiles/tetris.dir/tetris.c.o.requires

CMakeFiles/tetris.dir/tetris.c.o.provides: CMakeFiles/tetris.dir/tetris.c.o.requires
	$(MAKE) -f CMakeFiles/tetris.dir/build.make CMakeFiles/tetris.dir/tetris.c.o.provides.build
.PHONY : CMakeFiles/tetris.dir/tetris.c.o.provides

CMakeFiles/tetris.dir/tetris.c.o.provides.build: CMakeFiles/tetris.dir/tetris.c.o

# Object files for target tetris
tetris_OBJECTS = \
"CMakeFiles/tetris.dir/tetris.c.o"

# External object files for target tetris
tetris_EXTERNAL_OBJECTS =

tetris: CMakeFiles/tetris.dir/tetris.c.o
tetris: /usr/lib/x86_64-linux-gnu/libfreetype.so
tetris: /usr/lib/x86_64-linux-gnu/libglib-2.0.so
tetris: /usr/lib/x86_64-linux-gnu/libgobject-2.0.so
tetris: /usr/lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so
tetris: /usr/lib/x86_64-linux-gnu/libgdk-x11-2.0.so
tetris: /usr/lib/x86_64-linux-gnu/libgtk-x11-2.0.so
tetris: /usr/lib/x86_64-linux-gnu/libcairo.so
tetris: /usr/lib/x86_64-linux-gnu/libpango-1.0.so
tetris: /usr/lib/x86_64-linux-gnu/libatk-1.0.so
tetris: CMakeFiles/tetris.dir/build.make
tetris: CMakeFiles/tetris.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable tetris"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tetris.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tetris.dir/build: tetris
.PHONY : CMakeFiles/tetris.dir/build

CMakeFiles/tetris.dir/requires: CMakeFiles/tetris.dir/tetris.c.o.requires
.PHONY : CMakeFiles/tetris.dir/requires

CMakeFiles/tetris.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tetris.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tetris.dir/clean

CMakeFiles/tetris.dir/depend:
	cd /home/cdoucet/local/formations/mds/tetris/orig && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cdoucet/local/formations/mds/tetris/orig /home/cdoucet/local/formations/mds/tetris/orig /home/cdoucet/local/formations/mds/tetris/orig /home/cdoucet/local/formations/mds/tetris/orig /home/cdoucet/local/formations/mds/tetris/orig/CMakeFiles/tetris.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tetris.dir/depend
