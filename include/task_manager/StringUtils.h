/*
 * StringUtils.h
 *
 *  Created on: 27 апр. 2020 г.
 *      Author: scinersvd
 */

#pragma once

#include <string>
#include <vector>
#include <limits>

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
	/**
	 * @brief Разбивает строку на слова
	 * @param[in] str Входная строка для отбработки
	 * @param[out] str_list Массив строк для записи слов
	 * @param[in] max_count максимальное кол-во слов для выборки, если не указано то выбираются все слова
	 * @return Итератор в исходной строке на котором остановилась работа функции
	 */
	static std::string::const_iterator split(const std::string& str, std::vector<std::string>& str_list, int max_count = std::numeric_limits<int>::max());
};

} /* namespace task_manager */
