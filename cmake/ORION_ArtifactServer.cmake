# This file contains the CMake code required to leverage the
# ORION Artifact Server as part of a CMake project.

# Check if local repository defined
if(NOT DEFINED ENV{ORION_ARTIFACT_STORE})
	message(FATAL_ERROR "Environment variable ORION_ARTIFACT_STORE must be set to a local directory for storing artifacts.")
endif()

# Check if server defined
if(NOT DEFINED ENV{ORION_ARTIFACT_SERVER})
	message(FATAL_ERROR "Environment variable ORION_ARTIFACT_SERVER must be set to the HTTP root address of an Artifact Server.")
endif()

# Check if local repository exists
if(NOT EXISTS $ENV{ORION_ARTIFACT_STORE})
	message(FATAL_ERROR "ORION_ARTIFACT_STORE points to a non existent directory.")
endif()

# Function to unzip an archive to a specified directory.
function(ORION_UNZIP ZipFile TargetDirectory)
	if(__OS STREQUAL "win")
		execute_process(COMMAND C:/Program Files/7-Zip/7z.exe x ${ZipFile} -y -r -o${TargetDirectory})
	else()
		execute_process(COMMAND unzip ${ZipFile} -d ${TargetDirectory})
	endif()
endfunction()

# Function to declare a dependency, possibly against a target.
# If target is not NULL, then includes and libraries will be attached to the target.
# Otherwise, the dependency will just be downloaded.
function(ORION_ARTIFACT_DEPENDENCY Target Name Version)
	set(__THIS_DOWNLOAD_DEPENDENCY FALSE)

	if(NOT DEFINED ENV{ORION_ARTIFACT_OFFLINE})	
		# read server version
		file(DOWNLOAD "$ENV{ORION_ARTIFACT_SERVER}/${Name}/${Version}/latest.version" "$ENV{TMP}/latest.version" SHOW_PROGRESS STATUS __THIS_DOWNLOAD_RESULT)
		list(GET __THIS_DOWNLOAD_RESULT 0 __THIS_DOWNLOAD_STATUS)
				
		if(NOT __THIS_DOWNLOAD_STATUS EQUAL 0)
			message(FATAL_ERROR "Artifact ${Name} Version ${Version} cannot be found in the Artifact Server.")
		endif()
			
		file(READ "$ENV{TMP}/latest.version" __THIS_LATEST_VERSION)
		string(REGEX REPLACE "\n$" "" __THIS_LATEST_VERSION "${__THIS_LATEST_VERSION}")
		
		# if directories or version file do not exist, needs to be downloaded.
		if(NOT EXISTS "$ENV{ORION_ARTIFACT_STORE}/${Name}" OR NOT EXISTS "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}")
			file(MAKE_DIRECTORY "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}")
			set(__THIS_DOWNLOAD_DEPENDENCY TRUE)
		endif()
	
		if(NOT EXISTS "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/latest.version")
			set(__THIS_DOWNLOAD_DEPENDENCY TRUE)
		else()
			file(READ "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/latest.version" __THIS_CURRENT_VERSION)
			string(REGEX REPLACE "\n$" "" __THIS_CURRENT_VERSION "${__THIS_CURRENT_VERSION}")
			
			if(__THIS_LATEST_VERSION GREATER __THIS_CURRENT_VERSION)
				set(__THIS_DOWNLOAD_DEPENDENCY TRUE)
			endif()
		endif()
	else()
		message(STATUS "Artifact System Offline: using possibly missing local version for ${Name}-${Version}")
	endif()
		
	# download dependency if required - headers and libs for current compiler
	if(__THIS_DOWNLOAD_DEPENDENCY)
		# Download Packages
		file(DOWNLOAD "$ENV{ORION_ARTIFACT_SERVER}/${Name}/${Version}/${Name}-${Version}-${__THIS_LATEST_VERSION}-headers.zip" "$ENV{TMP}/current_headers.zip" SHOW_PROGRESS STATUS __THIS_DOWNLOAD_RESULT)
		file(DOWNLOAD "$ENV{ORION_ARTIFACT_SERVER}/${Name}/${Version}/${Name}-${Version}-${__THIS_LATEST_VERSION}-libs-${__OS}-${__PLATFORM}.zip" "$ENV{TMP}/current_libs.zip" SHOW_PROGRESS)
		
		# Wipe existing directories to update
		if(EXISTS "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/include")
			file(REMOVE_RECURSE "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/include")
		endif()
		
		if(EXISTS "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/libs/${__OS}-${__PLATFORM}")
			file(REMOVE_RECURSE "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/libs/${__OS}-${__PLATFORM}")
		endif()
		
		# Create directories
		file(MAKE_DIRECTORY "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/include")
		file(MAKE_DIRECTORY "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/libs/${__OS}-${__PLATFORM}")
		
		# Unzip packages into store directories
		ORION_UNZIP("$ENV{TMP}/current_headers.zip" "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/include")
		ORION_UNZIP("$ENV{TMP}/current_libs.zip" "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/libs/${__OS}-${__PLATFORM}")
		
		# Update latest version file
		file(WRITE "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/latest.version" ${__THIS_LATEST_VERSION})
	endif()
	
	# add include and link directories if a target is specified
	if(NOT ${Target} STREQUAL "NULL")
		target_include_directories(${Target} PUBLIC "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/include")
		target_link_libraries(${Target} "$ENV{ORION_ARTIFACT_STORE}/${Name}/${Version}/libs/${__OS}-${__PLATFORM}/*.lib")
	endif()
endfunction()

# Specific functions for dependencies that requires special treatment

# Declare use of boost at project level. Call only once per project.
function(ORION_USE_BOOST Version)
	if(WIN32)
		ORION_ARTIFACT_DEPENDENCY(NULL boost ${Version})
		
		if(NOT EXISTS "$ENV{ORION_ARTIFACT_STORE}/boost/${Version}")
			message(FATAL_ERROR "Boost cannot be found in the Artifact Store.")
		endif()
		
		include_directories("$ENV{ORION_ARTIFACT_STORE}/boost/${Version}/include")
		link_directories("$ENV{ORION_ARTIFACT_STORE}/boost/${Version}/libs/win-${__PLATFORM}")
		add_definitions(-D_WIN32_WINNT=0x0501)
	endif()
endfunction()

# Declare use of OpenDDS by a target.
function(ORION_USE_OPENDDS Target)
	if(WIN32)
		target_include_directories(${Target} PUBLIC "C:/opendds-3.10-win${__PLATFORM}-vc12-${CMAKE_CFG_INTDIR}")
		target_include_directories(${Target} PUBLIC "C:/opendds-3.10-win${__PLATFORM}-vc12-${CMAKE_CFG_INTDIR}/ACE_wrappers")
		target_include_directories(${Target} PUBLIC "C:/opendds-3.10-win${__PLATFORM}-vc12-${CMAKE_CFG_INTDIR}/ACE_wrappers/TAO")
			
		target_link_libraries("C:/opendds-3.10-win${__PLATFORM}-vc12-${CMAKE_CFG_INTDIR}/lib/*.lib")
		target_link_libraries("C:/opendds-3.10-win${__PLATFORM}-vc12-${CMAKE_CFG_INTDIR}/ACE_wrappers/lib/*.lib")
		
		target_compile_definitions(${Target} PUBLIC _WINSOCK_DEPRECATED_NO_WARNINGS=1)
		target_compile_definitions(${Target} PUBLIC _CRT_SECURE_NO_WARNINGS=1)
	endif()
endfunction()