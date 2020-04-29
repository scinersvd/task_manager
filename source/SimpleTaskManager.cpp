/*
 * SimpleTaskManager.cpp
 *
 *  Created on: 28 апр. 2020 г.
 *      Author: scinersvd
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <set>

#include <task_manager/SimpleTaskManager.h>
#include <task_manager/StringUtils.h>

namespace task_manager
{

Task::Task(Task::Id id) : id(id)
{
}

Task::Id Task::getId() const
{
	return id;
}

Task::Id Task::strToId(const std::string& str)
{
	try
	{
		return std::stoi(str);
	}
	catch(const std::invalid_argument& e)
	{
		throw bad_cast_str_to_task_id();
	}
	catch(const std::out_of_range& e)
	{
		throw bad_cast_str_to_task_id();
	}
}

void TimerTask::run()
{
	while(true)
	{
		std::chrono::time_point<std::chrono::system_clock> current_time_point = std::chrono::system_clock::now();
		std::time_t ttp = std::chrono::system_clock::to_time_t(current_time_point);
		std::cout << "time: " << std::ctime(&ttp);
		std::this_thread::sleep_for(std::chrono::minutes{1});
	}
}

void SimpleTaskManager::add_task(const std::string& cmd)
{
}

void SimpleTaskManager::info()
{
}

void SimpleTaskManager::info(Task::Id id)
{
}

void SimpleTaskManager::pause(Task::Id id)
{
}

void SimpleTaskManager::continue_task(Task::Id id)
{
}

void SimpleTaskManager::kill(Task::Id id)
{
}

void SimpleTaskManager::quit()
{
	setIsExit(true);
}

void SimpleTaskManager::processCmd(const std::string& cmd)
{
	try
	{
		std::vector<std::string> str_list;
		auto it = StringUtils::split(cmd, str_list, 1);
		if(str_list.empty()) return;
		std::string& command_name = str_list.front();
		std::string str_remain_cmd;
		std::copy(it, cmd.cend(), std::inserter(str_remain_cmd, str_remain_cmd.begin()));
		if(!isCmdName(command_name))
			throw unknown_cmd(command_name);
		if(command_name == "add_task")
		{
			add_task(str_remain_cmd);
			return;
		}
		if(command_name == "info")
		{
			Task::Id task_id = getIdFromCmd(str_remain_cmd);
			if(task_id != Task::unknown_task_id)
				info(task_id);
			else
				info();
		}
		if(command_name == "pause")
		{
			Task::Id task_id = getIdFromCmd(str_remain_cmd);
			pause(task_id);
		}
		if(command_name == "continue")
		{
			Task::Id task_id = getIdFromCmd(str_remain_cmd);
			continue_task(task_id);
		}
		if(command_name == "kill")
		{
			Task::Id task_id = getIdFromCmd(str_remain_cmd);
			kill(task_id);
		}
		if(command_name == "quit")
		{
			quit();
		}
	}
	catch(const Task::bad_cast_str_to_task_id& e)
	{
		std::cout << "Task id not valid" << std::endl;
	}
}

Task::Id SimpleTaskManager::getIdFromCmd(const std::string& cmd)
{
	std::vector<std::string> str_list;
	StringUtils::split(cmd, str_list, 1);
	if(!str_list.empty())
		return Task::strToId(str_list.front());
	else
		return Task::unknown_task_id;
}

bool SimpleTaskManager::isCmdName(const std::string& cmd_name)
{
	const static std::set<std::string> allowed_cmd_names = {"add_task", "info", "pause", "continue", "kill", "quit"};
	return allowed_cmd_names.find(cmd_name) != allowed_cmd_names.end();
}

} /* namespace task_manager */
