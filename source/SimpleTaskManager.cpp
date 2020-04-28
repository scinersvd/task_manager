/*
 * SimpleTaskManager.cpp
 *
 *  Created on: 28 апр. 2020 г.
 *      Author: scinersvd
 */

#include <task_manager/SimpleTaskManager.h>

namespace task_manager
{

Task::Task(Task::Id id) : id(id)
{
}

Task::Id Task::getId() const
{
	return id;
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
}

} /* namespace task_manager */
