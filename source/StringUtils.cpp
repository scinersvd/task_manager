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

std::string::const_iterator StringUtils::split(const std::string& str, std::vector<std::string>& str_list, int max_count)
{
	auto it = str.begin();
	if(max_count < 1) return it;
	const static auto isspace_f = [](const char& c)
			{
				static const std::locale default_loc;
				return std::isspace(c, default_loc);
			};
	while(max_count-- && it != str.end())
	{
		auto it_w = find_if_not(it, str.end(), isspace_f);
		it = find_if(it_w, str.end(), isspace_f);
		if(it == it_w) continue;
		str_list.emplace_back();
		std::copy(it_w, it, std::inserter(str_list.back(), str_list.back().begin()));
	}
	return it;
}

} /* namespace task_manager */
