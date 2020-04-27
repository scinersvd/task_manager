/*
 * StringUtils.h
 *
 *  Created on: 27 апр. 2020 г.
 *      Author: scinersvd
 */

#pragma once

#include <string>

/**
namespace task_manager
@brief Пространство имен task_manager
*/
namespace task_manager
{

/**
 * @brief Класс-утилита для работы со строками
 */
class StringUtils
{
public:
	StringUtils() = default;
	virtual ~StringUtils() = default;
	StringUtils(const StringUtils &other) = default;
	StringUtils(StringUtils &&other) = default;
	StringUtils& operator=(const StringUtils &other) = default;
	StringUtils& operator=(StringUtils &&other) = default;
public:
	/**
	 * @brief Удаляет пробельные символы с начала и с конца строки
	 * @param[in] str Входная строка для отбработки
	 * @return Обработанная строка после удаления пробельных символов
	 */
	static std::string trim(const std::string& str);
};

} /* namespace task_manager */
