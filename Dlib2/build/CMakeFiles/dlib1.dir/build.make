# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build

# Include any dependencies generated for this target.
include CMakeFiles/dlib1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dlib1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dlib1.dir/flags.make

CMakeFiles/dlib1.dir/main.cpp.obj: CMakeFiles/dlib1.dir/flags.make
CMakeFiles/dlib1.dir/main.cpp.obj: CMakeFiles/dlib1.dir/includes_CXX.rsp
CMakeFiles/dlib1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dlib1.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\dlib1.dir\main.cpp.obj -c C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\main.cpp

CMakeFiles/dlib1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dlib1.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\main.cpp > CMakeFiles\dlib1.dir\main.cpp.i

CMakeFiles/dlib1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dlib1.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\main.cpp -o CMakeFiles\dlib1.dir\main.cpp.s

# Object files for target dlib1
dlib1_OBJECTS = \
"CMakeFiles/dlib1.dir/main.cpp.obj"

# External object files for target dlib1
dlib1_EXTERNAL_OBJECTS =

release/dlib1.exe: CMakeFiles/dlib1.dir/main.cpp.obj
release/dlib1.exe: CMakeFiles/dlib1.dir/build.make
release/dlib1.exe: C:/msys64/mingw64/lib/libfmt.a
release/dlib1.exe: C:/msys64/mingw64/lib/libdlib.dll.a
release/dlib1.exe: CMakeFiles/dlib1.dir/linklibs.rsp
release/dlib1.exe: CMakeFiles/dlib1.dir/objects1.rsp
release/dlib1.exe: CMakeFiles/dlib1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable release\dlib1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\dlib1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dlib1.dir/build: release/dlib1.exe

.PHONY : CMakeFiles/dlib1.dir/build

CMakeFiles/dlib1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\dlib1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/dlib1.dir/clean

CMakeFiles/dlib1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1 C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1 C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build C:\Users\Mario\Documents\Universidad\2\PEL\Workspace\dlib1\build\CMakeFiles\dlib1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dlib1.dir/depend
