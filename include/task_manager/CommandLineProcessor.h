/*
 * CommandProcessor.h
 *
 *  Created on: 26 апр. 2020 г.
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
 * @brief Базовый абстрактный класс для консольного процессора команд,
 * то есть объекта отвечающего за выполнение команд и реализацию консольного интерфейса ввода команд
 */
class CommandLineProcessor
{
public:
	/**
	 * @brief Класс-исключение
	 * Обрабатывает ситуацию когда введена неизвестная команда
	 */
	class unknown_cmd : public std::exception
	{
	public:
		unknown_cmd() = default;
		unknown_cmd(const std::string& cmd);
		const char* what() const noexcept override;
	private:
		std::string cmd;
	};
public:
	CommandLineProcessor() = default;
	virtual ~CommandLineProcessor() = default;
public:
	/**
	 * @brief Стартует командную консоль
	 */
	virtual void startCmdLine();
protected:
	/**
	 * @brief Обрабатывает одну команду
	 * @param[in] cmd Строка, содержащая наименование команды и парамеры
	 */
	virtual void processCmd(const std::string& cmd) = 0;
	/**
	 * @brief Проверка - нужно ли завершать ввод и выполнение команд
	 * @return Признак завершения
	 */
	virtual bool checkIsExit() = 0;
	/**
	 * @brief Возвращает наименование автора команды, которое пишется перед строкой ввода
	 * @return Наименование автора команды
	 */
	virtual std::string getCmdAuthor();
};

} /* namespace task_manager */
