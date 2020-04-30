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
#include <algorithm>

#include <task_manager/SimpleTaskManager.h>
#include <task_manager/StringUtils.h>

namespace task_manager
{

Task::Task(Task::Id id) : id(id), startDelay{0}
{
}

Task::~Task()
{
	if(thread_ptr && thread_ptr->joinable())
		thread_ptr->join();
}

void Task::startAsync()
{
	thread_ptr = std::make_shared<std::thread>([this](){run();});
}

void Task::info()
{
	std::pair<int, int> progress = getProgress();
	if(progress.second != 0)
		std::cout << "task " << getId() << ": " << float(progress.first) / float(progress.second);
	else
		std::cout << "task " << getId() << ": progress not supported";
}

std::pair<int, int> Task::getProgress()
{
	return std::pair<int, int>(0, 0);
}

Task::Id Task::getId() const
{
	return id;
}

std::chrono::seconds Task::getStartDelay() const
{
	return startDelay;
}

Task& Task::setStartDelay(std::chrono::seconds sec)
{
	startDelay = sec;
	return *this;
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

Task::Id Task::generateNextId(const Task::Id& id)
{
	return id + 1;
}

TimerTask::TimerTask(Id id)
	: Task(id),
	  isStop(false),
	  isPause(false),
	  interval{5},
	  workTime{300}
{
}

std::pair<int, int> TimerTask::getProgress()
{
	std::lock_guard<std::mutex> lk(count_mutex);
	long f = currentTimerCount.count();
	long s = workTime.count();
	return std::pair<int, int>(f, s);
}

void TimerTask::stop()
{
	isStop = true;
}

void TimerTask::pause()
{
	isPause = true;
}

void TimerTask::resume()
{
	isPause = false;
}

void TimerTask::info()
{
	std::cout << "task " << getId() << ": ";
	{
		std::lock_guard<std::mutex> lk(count_mutex);
		if(workTime.count() != 0)
			std::cout << float(currentTimerCount.count()) / float(workTime.count());
	}
	std::cout << " stopped = " << isStop.load() << " paused = " << isPause.load() << std::endl;
}

void TimerTask::run()
{
	std::this_thread::sleep_for(getStartDelay());
	if(!isStop.load())
		std::cout << std::endl << "Timer task "<< getId() <<" was started" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start_time_point = std::chrono::system_clock::now();
	while(!isStop.load())
	{
		if(isPause.load())
			std::this_thread::yield();
		else
		{
			std::chrono::time_point<std::chrono::system_clock> current_time_point = std::chrono::system_clock::now();
			std::time_t ttp = std::chrono::system_clock::to_time_t(current_time_point);
			std::cout << std::endl <<"Timer " << getId() << ": " << std::ctime(&ttp);
			{
				std::lock_guard<std::mutex> lk(count_mutex);
				currentTimerCount = std::chrono::duration_cast<std::chrono::seconds>(current_time_point - start_time_point);
			}
			if(currentTimerCount >= workTime)
			{
				std::cout << std::endl <<"Timer " << getId() << " work time ends" << std::endl;
				stop();
				break;
			}
			std::this_thread::sleep_for(interval);
		}
	}
	std::cout << "Timer " << getId() << " stopped" << std::endl;
}

std::chrono::seconds TimerTask::getInterval() const
{
	return interval;
}

TimerTask& TimerTask::setInterval(std::chrono::seconds sec)
{
	interval = sec;
	return *this;
}

std::chrono::seconds TimerTask::getWorkTime() const
{
	return workTime;
}

TimerTask& TimerTask::setWorkTime(std::chrono::seconds sec)
{
	workTime = sec;
	return *this;
}

SimpleTaskManager::~SimpleTaskManager()
{
	std::for_each(taskList.begin(), taskList.end(), [](auto& task){task->stop();});
}

void SimpleTaskManager::add_task(const std::string& cmd)
{
	Task::Id id = Task::first_task_id;
	if(!taskList.empty())
		id = Task::generateNextId(taskList.front()->getId());
	std::shared_ptr<TimerTask> new_task = std::make_shared<TimerTask>(id);

	std::vector<std::string> str_list;
	auto it = StringUtils::split(cmd, str_list, 3);
	try
	{
		if(str_list.size() > 0)
			new_task->setStartDelay(std::chrono::seconds(std::stoi(str_list[0])));
		if(str_list.size() > 1)
			new_task->setInterval(std::chrono::seconds(std::stoi(str_list[1])));
		if(str_list.size() > 2)
			new_task->setWorkTime(std::chrono::seconds(std::stoi(str_list[2])));
	}
	catch(const std::invalid_argument& e)
	{
		std::cout << "Bad arguments" << std::endl;
		return;
	}
	catch(const std::out_of_range& e)
	{
		std::cout << "Bad arguments" << std::endl;
		return;
	}

	taskList.push_front(new_task);
	std::cout << "Added task with Id " << new_task->getId() << std::endl;

	new_task->startAsync();
}

void SimpleTaskManager::info()
{
	std::for_each(taskList.begin(), taskList.end(), [](auto& task){task->info();});
}

void SimpleTaskManager::info(Task::Id id)
{
	std::shared_ptr<Task> task;
	if(findTask(id, task))
		task->info();
	else
		std::cout << "Task not found" << std::endl;
}

void SimpleTaskManager::pause(Task::Id id)
{
	std::shared_ptr<Task> task;
	if(findTask(id, task))
		task->pause();
	else
		std::cout << "Task not found" << std::endl;
}

void SimpleTaskManager::continue_task(Task::Id id)
{
	std::shared_ptr<Task> task;
	if(findTask(id, task))
		task->resume();
	else
		std::cout << "Task not found" << std::endl;
}

void SimpleTaskManager::kill(Task::Id id)
{
	std::shared_ptr<Task> task;
	if(findTask(id, task))
		task->stop();
	else
		std::cout << "Task not found" << std::endl;
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

bool SimpleTaskManager::findTask(const Task::Id& id, std::shared_ptr<Task>& task)
{
	auto it = std::find_if(taskList.begin(), taskList.end(), [&id](const auto& task)
			{
				return id == task->getId();
			});
	if(it != taskList.end())
	{
		task = *it;
		return true;
	}
	else
	{
		task = nullptr;
		return false;
	}
}

} /* namespace task_manager */
