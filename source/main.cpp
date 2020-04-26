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

int main()
{
	std::exception_ptr exceptionPtr;
	try
	{
		std::string cmd;
		while(cmd != "exit")
		{
			std::cout << "TASK_MANAGER>";
			std::cin >> cmd;
			std::cout << "Command " << cmd << std::endl;
		}
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

