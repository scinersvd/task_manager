/*
 * SimpleTaskManager.h
 *
 *  Created on: 28 апр. 2020 г.
 *      Author: scinersvd
 */

#pragma once

#include <list>
#include <memory>

#include <task_manager/SimpleCommandLineProcessor.h>

/**
namespace task_manager
@brief Пространство имен task_manager
*/
namespace task_manager
{

/**
 * @brief Базовый абстрактный класс для представления задачи
 */
class Task
{
public:
	typedef int Id;
public:
	/**
	 * @brief Создает новую задачу с идентификатором id
	 * @param[in] id Идентификатор задачи
	 */
	Task(Id id);
	virtual ~Task() = default;
public:
	/**
	 * @brief Функция непосредственно выполняющая задание
	 */
	virtual void run() = 0;
	/**
	 * @brief Возвращает прогресс задачи
	 * @return Пара чисел, первое число - текущее значение счетчика выполнения, второе - максимальное значение счетчика
	 * Если второе значение меньше либо равно 0, то данная задача не поддерживает измерение прогресса выполнения
	 */
	virtual std::pair<int, int> getProgress() = 0;
public:
	/**
	 * @brief Возвращает идентификатор задачи
	 * @return Идентификатор задачи
	 */
	Id getId() const;
private:
	/**
	 * @brief Идентификатор задачи
	 */
	Id id;
};

/**
 * @brief Простая реализация менеджера задач
 */

class SimpleTaskManager: public SimpleCommandLineProcessor
{
public:
	SimpleTaskManager() = default;
	virtual ~SimpleTaskManager() = default;
protected:
	/**
	 * @brief Добавление задачи
	 * @param[in] cmd Строка, содержащая наименование задачи и параметры в формате [task_name] [param0] [param1] ... [paramN]
	 */
	virtual void add_task(const std::string& cmd);
	/**
	 * @brief Показывает список активных задач
	 */
	virtual void info();
	/**
	 * @brief Показывает информацию о задаче
	 * @param[in] id Идентификатор задачи
	 */
	virtual void info(Task::Id id);
	/**
	 * @brief Приостанавливает выполнение задачи
	 * @param[in] id Идентификатор задачи
	 */
	virtual void pause(Task::Id id);
	/**
	 * @brief Продолжает выполнение задачи
	 * @param[in] id Идентификатор задачи
	 */
	virtual void continue_task(Task::Id id);
	/**
	 * @brief Cнимает задачу
	 * @param[in] id Идентификатор задачи
	 */
	virtual void kill(Task::Id id);
	/**
	 * @brief Останавливает все задачи и завершает работу
	 */
	virtual void quit();
private:
	/**
	 * @brief Список задач
	 */
	std::list<std::shared_ptr<Task> > taskList;
};

} /* namespace task_manager */
