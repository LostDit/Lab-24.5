#include <iostream>
#include <ctime>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <string>

/*
Добавил макрос который указан ниже т.к выдавало ошибку по вот такой строке требуя идентификатор
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
*/
#define NOMINMAX
#include <windows.h>

//Глобальные переменные, содержищие текущею задачу и время её начала
std::string currentTask = "";
std::time_t startTime = 0;

//Карта завершённых задач: название задачи -> суммарно затраченное время в секундах (реализовал через ассоциативную хэш таблицу)
std::unordered_map<std::string, double> completedTasks;

//Функция завершения текущей задачи (если такая конечно есть)
void endCurrentTask() {
	if (!currentTask.empty()) {
		std::time_t now = std::time(nullptr);
		double elapsed = std::difftime(now, startTime);
		completedTasks[currentTask] += elapsed;
		std::cout << "Задача \"" << currentTask << "\" завершена. Затраченное время: "
			<< elapsed << " сек.\n";
		currentTask = "";
	}
}

//Функция команды begin
void handleBegin() {
	//Если уже идёт какая-то задача, завершаем её
	if (!currentTask.empty()) {
		endCurrentTask();
	}

	//Запрос названия новой задачи
	std::cout << "Введите название задачи: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем остаток строки
	std::getline(std::cin, currentTask);

	//Устанавливаем время начала работы над новой задачей
	startTime = std::time(nullptr);
	std::cout << "Начата задача \"" << currentTask << "\".\n";
}

//Функция для команды end
void handleEnd() {
	if (!currentTask.empty()) {
		endCurrentTask();
	}
	else {
		std::cout << "Нет активной задачи для завершения.\n";
	}
}

//Функция для команды status
void handleStatus() {
	std::cout << "\nСтатус выполненных задач:\n";
	if (completedTasks.empty()){
		std::cout << "Нет завершённых задач.\n";
	}else {
		//Выводим время в часах с 2 знаками после запятой
		for (const auto& task : completedTasks) {
			double hours = task.second / 3600.0;
			std::cout << "Задача: " << task.first << " | Время: " << std::fixed << std::setprecision(2) << hours << " ч.\n";
		}
	}
	if (!currentTask.empty()) {
		std::cout << "Текущая задача: " << currentTask << "\n";
	}std::cout << "\n";
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	std::string command;
	bool checkInput = true;

	while (true){
		checkInput == true? std::cout << "Менеджер учёта времени. Доступные команды: begin, end, status, exit\n": std::cout << "Доступные команды : begin, end, status, exite\n" << "\nПовторите ввод ";
		checkInput = true;
		std::cout << "> ";
		std::cin >> command;

		if (command == "begin") {
			
			handleBegin();
			system("pause");
			system("cls");
		
		}else if (command == "end") {
			
			handleEnd();
			system("pause");
			system("cls");
		
		}else if (command == "status") {
			
			handleStatus();
			system("pause");
			system("cls");
		
		}else if (command =="exit") {
			
			//Перед выходом завершается текущая задача по условию, если она есть
			if (!currentTask.empty()) {
				
				endCurrentTask();
				system("pause");
				system("cls");
			
			}
			
			std::cout << "Выход из программы.\n";
			break;
		
		}else {
			system("cls");
			checkInput = false;
		}
	}

	return 0;
}
