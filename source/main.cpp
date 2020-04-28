/*
 * main.cpp
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: scinersvd
 */

#include <iostream>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <memory>

#include <task_manager/SimpleTaskManager.h>

int main()
{
	std::exception_ptr exceptionPtr;
	try
	{
		std::shared_ptr<task_manager::CommandLineProcessor> commandLineProcessor_ptr = std::make_shared<task_manager::SimpleTaskManager>();
		commandLineProcessor_ptr->startCmdLine();
	}
	catch(...)
	{
		exceptionPtr = std::current_exception();
	}

	try
	{
		if(exceptionPtr)
		{
			rethrow_exception(exceptionPtr);
	    }
	}
	catch(const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		const std::type_info& t = typeid(e);
		std::cout << "Exception name: " << t.name() << std::endl;
	}

	return EXIT_SUCCESS;
}

