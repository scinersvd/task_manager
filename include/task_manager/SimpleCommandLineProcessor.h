/*
 * SimpleCommandLineProcessor.h
 *
 *  Created on: 26 апр. 2020 г.
 *      Author: scinersvd
 */

#pragma once

#include <task_manager/CommandLineProcessor.h>

/**
namespace task_manager
@brief Пространство имен task_manager
*/
namespace task_manager
{

/**
 * @brief Минимальная реализация CommandLineProcessor
 * Реализована команда exit, остальные команды просто печатаются в консоль
 * то есть объекта отвечающего за выполнение команд и реализацию консольного интерфейса ввода команд
 */
class SimpleCommandLineProcessor: public CommandLineProcessor
{
public:
	SimpleCommandLineProcessor();
	virtual ~SimpleCommandLineProcessor() = default;
public:
	/**
	 * @brief Возвращает значение поля bIsExit
	 * @return Значение поля bIsExit
	 */
	bool getIsExit() const;
	/**
	 * @brief Устанавливает значение поля bIsExit
	 * @param[in] bIsExit Значение для поля bIsExit
	 */
	void setIsExit(bool bIsExit);
protected:
	void processCmd(const std::string& cmd) override;
	bool checkIsExit() override;
private:
	bool bIsExit;
};

} /* namespace task_manager */
