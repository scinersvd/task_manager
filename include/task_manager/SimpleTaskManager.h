/*
 * SimpleTaskManager.h
 *
 *  Created on: 28 апр. 2020 г.
 *      Author: scinersvd
 */

#pragma once

#include <list>
#include <memory>
#include <thread>
#include <atomic>
#include <chrono>

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
	/**
	 * @brief Тип данных для идентификатора задачи
	 */
	typedef int Id;

	/**
	 * @brief Класс-исключение
	 * Обрабатывает ситуацию когда введена строка, которую невозможно преобразовать в идентификатор задачи
	 */
	class bad_cast_str_to_task_id : public std::exception
	{
	public:
		bad_cast_str_to_task_id() = default;
	};

	/**
	 * @brief Неопределенный идентификатор
	 */
	const static Id unknown_task_id = -1;

	/**
	 * @brief Первый идентификатор
	 */
	const static Id first_task_id = 1;
public:
	/**
	 * @brief Создает новую задачу с идентификатором id
	 * @param[in] id Идентификатор задачи
	 */
	Task(Id id);
	virtual ~Task();
public:
	/**
	 * @brief Стартует задачу асинхронно в другом потоке
	 */
	virtual void startAsync();
	/**
	 * @brief Досрочно завершает задачу
	 */
	virtual void stop() = 0;
	/**
	 * @brief Приостанавливает задачу
	 */
	virtual void pause() = 0;
	/**
	 * @brief Продолжает выполнение приостановленной задачи
	 */
	virtual void resume() = 0;
	/**
	 * @brief Печатает в консоль информацию о задаче в виде одной строки
	 */
	virtual void info();
	/**
	 * @brief Возвращает прогресс задачи
	 * @return Пара чисел, первое число - текущее значение счетчика выполнения, второе - максимальное значение счетчика
	 * Если второе значение меньше либо равно 0, то данная задача не поддерживает измерение прогресса выполнения
	 */
	virtual std::pair<int, int> getProgress();
protected:
	/**
	 * @brief Функция непосредственно выполняющая задание
	 */
	virtual void run() = 0;
public:
	/**
	 * @brief Возвращает идентификатор задачи
	 * @return Идентификатор задачи
	 */
	Id getId() const;
	/**
	 * @brief Возвращает задержку старта
	 * @return Задержка старта в секундах
	 */
	std::chrono::seconds getStartDelay() const;
	/**
	 * @brief Устанавливает задержку старта
	 * @param[in] Задержка старта в секундах
	 * @return Ссылку на текущий экземпляр задачи
	 */
	Task& setStartDelay(std::chrono::seconds sec);
private:
	/**
	 * @brief Идентификатор задачи
	 */
	Id id;
	/**
	 * @brief Указатель на поток в котором задача выполняется асинхронно
	 */
	std::shared_ptr<std::thread> thread_ptr;
	/**
	 * @brief Интервал в секундах, через который запуститься задача после ввода команды
	 */
	std::chrono::seconds startDelay;
public:
	/**
	 * @brief Преобразовывает строку в значение для типа данных идентификатора задачи
	 * @param[in] Строка с идентификатором задачи
	 */
	static Id strToId(const std::string& str);
	/**
	 * @brief Генерирует следующий идентификатор на основе предыдущего
	 * @param[in] id Идентификатор задачи
	 * @return Сгенерированый идентификатор задачи
	 */
	static Id generateNextId(const Id& id);
};

/**
 * @brief Задача таймер
 * Выдает текущее время через интервалы времени
 */
class TimerTask : public Task
{
public:
	/**
	 * @brief Создает задачу-таймер
	 * @param[in] id идентификатор задачи
	 */
	TimerTask(Id id);
	virtual ~TimerTask() = default;
public:
	std::pair<int, int> getProgress() override;
	void stop() override;
	void pause() override;
	void resume() override;
	void info() override;
protected:
	void run() override;
public:
	/**
	 * @brief Возвращает интервал таймера
	 * @return Интервал таймера
	 */
	std::chrono::seconds getInterval() const;
	/**
	 * @brief Устанавливает интервал таймера
	 * @param[in] Интервал таймера
	 * @return Ссылку на текущий экземпляр задачи
	 */
	TimerTask& setInterval(std::chrono::seconds sec);
	/**
	 * @brief Возвращает время работы таймера
	 * @return Время работы таймера
	 */
	std::chrono::seconds getWorkTime() const;
	/**
	 * @brief Устанавливает время работы таймера
	 * @param[in] Время работы таймера
	 * @return Ссылку на текущий экземпляр задачи
	 */
	TimerTask& setWorkTime(std::chrono::seconds sec);
private:
	std::atomic<bool> isStop;
	std::atomic<bool> isPause;
	std::chrono::seconds interval;
	std::chrono::seconds workTime;
};

/**
 * @brief Простая реализация менеджера задач
 */

class SimpleTaskManager: public SimpleCommandLineProcessor
{
public:
	SimpleTaskManager() = default;
	virtual ~SimpleTaskManager();
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
protected:
	void processCmd(const std::string& cmd) override;
// Internal functions
protected:
	/**
	 * @brief Получает идентификатор задачи из командной строки
	 * @param[cmd] Строка содержащая командную строку
	 */
	virtual Task::Id getIdFromCmd(const std::string& cmd);
	/**
	 * @brief Проверяет - является ли строка именем команды
	 * @param[cmd] Строка имя команды
	 * @return true если строка является именем команды и false в обратном случае
	 */
	virtual bool isCmdName(const std::string& cmd_name);
	/**
	 * @brief Находит задачу в списке по идентификатору
	 * @param[cmd] Строка имя команды
	 * @return true если строка является именем команды и false в обратном случае
	 */
	virtual bool findTask(const Task::Id& id, std::shared_ptr<Task>& task);
};

} /* namespace task_manager */
