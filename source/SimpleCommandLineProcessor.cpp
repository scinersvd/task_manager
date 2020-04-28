/*
 * SimpleCommandLineProcessor.cpp
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: scinersvd
 */

#include <iostream>

#include <task_manager/SimpleCommandLineProcessor.h>
#include <task_manager/StringUtils.h>

namespace task_manager
{

SimpleCommandLineProcessor::SimpleCommandLineProcessor() : bIsExit(false)
{
}

bool SimpleCommandLineProcessor::getIsExit() const
{
	return bIsExit;
}

void SimpleCommandLineProcessor::setIsExit(bool bIsExit)
{
	this->bIsExit = bIsExit;
}

void SimpleCommandLineProcessor::processCmd(const std::string& cmd)
{
	std::string trimmed_cmd = StringUtils::trim(cmd);
	if(trimmed_cmd == "exit" || trimmed_cmd == "quit")
		setIsExit(true);
	else
		std::cout << "Setup command: " << cmd << std::endl;
}

bool SimpleCommandLineProcessor::checkIsExit()
{
	return getIsExit();
}

} /* namespace task_manager */
