/*
 * StringUtils.cpp
 *
 *  Created on: 27 апр. 2020 г.
 *      Author: scinersvd
 */

#include <algorithm>
#include <locale>

#include <task_manager/StringUtils.h>

namespace task_manager
{

std::string StringUtils::trim(const std::string& str)
{
	static const auto spaces = [](char ch)
	{
	    static std::locale loc("");
	    return std::isspace(ch, loc);
	};

	std::string str_rez(str);
	const auto it_l = std::find_if_not(str_rez.begin(), str_rez.end(), spaces);
	str_rez.erase(str_rez.begin(), it_l);
	const auto it_r = std::find_if_not(str_rez.rbegin(), str_rez.rend(), spaces).base();
	str_rez.erase(it_r, str_rez.end());
	return str_rez;
}

} /* namespace task_manager */
