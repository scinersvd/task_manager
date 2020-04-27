/*
 * CommandProcessor.cpp
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: scinersvd
 */

#include <iostream>

#include <task_manager/CommandLineProcessor.h>

namespace task_manager
{

void CommandLineProcessor::startCmdLine()
{
	std::string cmd;
	while(!checkIsExit())
	{
		std::cout << getCmdAuthor() + ">";
		std::cin >> cmd;
		processCmd(cmd);
	}
}

std::string CommandLineProcessor::getCmdAuthor()
{
	const static std::string author = "TASK_MANAGER";
	return author;
}

} /* namespace task_manager */
