# This file contains functions to create standardized CMake
# projects that follow the ORION automated convention.

include_directories("include")

# Name: name of the target
# Type: [exe,static,shared]
function(ORION_TARGET Name Type)
	# Grab Source Files
	file(GLOB_RECURSE ${Name}_SRC
		"include/orion/${Name}/*.h"
		"src/${Name}/*.h"
		"src/${Name}/*.cpp"
	)
	
	if(${Type} STREQUAL "exe")
		add_executable(${Name} ${${Name}_SRC})
	elseif(${Type} STREQUAL "static")
		add_library(${Name} ${${Name}_SRC})
	elseif(${Type} STREQUAL "shared")
		add_library(${Name} SHARED ${${Name}_SRC})
	endif()
endfunction()

# Function to sort files in source groups to follow the
# file system structure. Usually for heavy applications.
set(LAST_DIR "")
function(GROUP_TARGET_SOURCE target_name)
	foreach(src_file ${${target_name}_SRC})
		file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR}/src/${target_name} ${src_file})
		get_filename_component(dir_name ${relative_path} DIRECTORY)
		if(NOT dir_name STREQUAL LAST_DIR)
			file(GLOB this_files "src/${target_name}/${dir_name}/*.*")
			string(REPLACE "/" "\\" group_name ${dir_name})
			source_group(${group_name} FILES ${this_files})
			set(LAST_DIR ${dir_name})
		endif()
	endforeach()
endfunction()