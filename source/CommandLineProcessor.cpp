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

CommandLineProcessor::unknown_cmd::unknown_cmd(const std::string& cmd) : cmd(cmd)
{
}
const char* CommandLineProcessor::unknown_cmd::what() const noexcept
{
	static std::string str;
	str = "Unknown command: " + cmd;
	return str.c_str();
}

void CommandLineProcessor::startCmdLine()
{
	std::string cmd;
	while(!checkIsExit())
	{
		std::cout << getCmdAuthor() + ">";
		std::getline(std::cin, cmd);
		try
		{
			processCmd(cmd);
		}
		catch(const unknown_cmd& exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}
}

std::string CommandLineProcessor::getCmdAuthor()
{
	const static std::string author = "TASK_MANAGER";
	return author;
}

} /* namespace task_manager */
