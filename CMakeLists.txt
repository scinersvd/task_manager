cmake_minimum_required (VERSION 2.6)

project (task_manager)

include_directories(include)

set(SOURCES source/main.cpp
			source/CommandLineProcessor.cpp
			source/SimpleCommandLineProcessor.cpp
			source/SimpleTaskManager.cpp
			source/StringUtils.cpp
			)

add_executable(task_manager ${SOURCES})
