#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <windows.h>

/*Функция для разбора строки времени в формате MM : SS и расчёта общего количества секунд.
При неверном формате времени возвращает отрицательное значение.*/
int parseTime() {
	std::cout << "Введите время в формате MM:SS: ";
	std::string input;
	std::getline(std::cin, input);

	std::tm t = {};
	std::istringstream iss(input);
	if (!(iss >> std::get_time(&t, "%M:%S"))) {
		std::cerr << "Неверный формат ввода!\n";
		return -1;
	}

	return t.tm_min * 60 + t.tm_sec;
}

//Функция запуска обратного отсчёта таймера, в качестве параметра передаётся общее время в секундах
void runTimer(int totalSeconds) {
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::seconds(totalSeconds);

    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto remainingDuration = std::chrono::duration_cast<std::chrono::seconds>(endTime - currentTime);
        int remainingSeconds = remainingDuration.count();

        if (remainingSeconds < 0) {
            break;
        }

        // Преобразование оставшихся секунд в минуты и секунды.
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;

        // Вывод оставшегося времени с форматированием и перезаписью всей строки.
        std::cout << "\r"<< std::setw(2) << std::setfill('0') << minutes << ":"<< std::setw(2) << std::setfill('0') << seconds << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nDING! DING! DING!\a" << std::endl;
}


int main()	{
	setlocale(LC_ALL, "");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	int totalSeconds = parseTime();
	if (totalSeconds < 0) {
		return 1;
	}

	runTimer(totalSeconds);

	return 0;
}