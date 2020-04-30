cmake_minimum_required (VERSION 3.1)

project (task_manager)

include_directories(include)

set(SOURCES source/main.cpp
			source/CommandLineProcessor.cpp
			source/SimpleCommandLineProcessor.cpp
			source/SimpleTaskManager.cpp
			source/StringUtils.cpp
			)

add_executable(task_manager ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(task_manager Threads::Threads)
