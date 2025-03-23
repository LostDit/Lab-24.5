#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <iomanip>

#define NOMINMAX
#include<windows.h>

struct FriendBirthday {

	std::string name;
	int month;
	int day;

};


/*Функция для парсинга даты в формате "год/месяц/день"
Здесь год сохраняется, но в дальнейшем не используется - нас интересуют только месяц и день*/
bool parseDate(const std::string& dateStr, int& year, int& month, int& day) {

	std::istringstream iss(dateStr);
	char sep;
	if (!(iss >> year >> sep >> month >> sep >> day)) {
		return false;
	}
	return true;
}


//Функция для ввода иформации о днях рождения друзей
std::vector<FriendBirthday> readBirthdays() {
	std::vector<FriendBirthday> friends;
	std::string inputName;
	std::string inputDate;

	while (true)	{
		std::cout << "Введите данные о дне рождения друзей.\n";
		std::cout << "Сначала имя, затем дата рождения в формате год(2001)/месяц(01-12)/день(01-30)\n";
		std::cout << "Для завершения ввода введите \"end\" вместо имени.\n";
		
		std::cout << "Имя: ";
		std::cin >> inputName;
		
		if (inputName == "end")	break;
	
		std::cout << "Дата(год/месяц/день): ";
		std::cin >> inputDate;
		
		int year, month, day;
		
		if (!parseDate(inputDate, year, month, day)) {
			std::cout << "Неверный формат даты. Попробуйте ещё раз.\n";
			system("pause");
			system("cls");
			continue;
		}

		FriendBirthday fb;
		fb.name = inputName;
		fb.month = month;
		fb.day = day;
		friends.push_back(fb);
		
		system("pause");
		system("cls");
	}

	return friends;
}


/*Функция котороя отвечает за формирование даты дня рождения для друга в текущем году,
так же возвращает time_t текущего дня (если точнее, то в полночь)*/
std::time_t makeBirthdayTime(const FriendBirthday& fb, const std::tm& currentTm) {
	
	std::tm birthdayTm = currentTm;	    //Копирую текущую дату
	birthdayTm.tm_mon = fb.month - 1;	//Корректирую месяц (от 0 до 11)
	birthdayTm.tm_mday = fb.day;
	birthdayTm.tm_hour = 0;
	birthdayTm.tm_min = 0;
	birthdayTm.tm_sec = 0;

	//mktime заполнит другие поля структуры tm (tm_wday и tm_yday)
	return std::mktime(&birthdayTm);
}


/*Функция для вычисления ближайщих предстоящих дней рождения, 
если день рождения уже прошёл в текущем году, запись пропускается, 
если несколько друзей имеют одинаковый ближайщий день, то они все добавляются*/
std::vector<FriendBirthday> computeUpcomingBirthdays(const std::vector<FriendBirthday>& friends) {
	std::vector <FriendBirthday> result;
	
	//Получаем текущий момент времени и структуру tm
	std::time_t now = std::time(nullptr);
	std::tm currentTm = *std::localtime(&now);

	double minDiff = std::numeric_limits<double>::max();

	//Определяю ближайщую разницу во времени в секундах.
	for (const auto &fb:friends)	{
		std::time_t btime = makeBirthdayTime(fb, currentTm);
		//Вычисляем текущую разницу между днём рождения и текущим временем
		double diff = std::difftime(btime, now);

		//Если день рождения уже прошёл,пропускаем запись.
		if (diff < 0)
			continue;
		
		//Если нашли более ранний день рождения, обновляем минимальную разницу и очищаем результат
		if (diff< minDiff) {
			minDiff = diff;
			result.clear();
			result.push_back(fb);
		}else if (diff==minDiff)	{		//Если разница равна текущей минимальной разнице, добавляем друга в список
			result.push_back(fb);
		}
	}

	return result;
}


//Функция для форматированного вывода результатов
void printUpcomingBirthdays(const std::vector<FriendBirthday>& upcoming){
	if (upcoming.empty()) {
		std::cout << "Нет предстоящих дней рождения в этом году.\n";
		return;
	}

	//Получаю текущий момент времени и структуру tm
	std::time_t now = std::time(nullptr);
	std::tm currentTm = *std::localtime(&now);

	for (const auto& fb : upcoming) {
		
		//Форматируем дату: месяц/день с ведущими нулями
		std::ostringstream oss;
		oss << std::setfill('0') << std::setw(2) << fb.month << "/" << std::setfill('0') << std::setw(2) << fb.day;
	
		//Вычисление разницы чтобы узнать есть ли "сегодня" др
		std::time_t btime = makeBirthdayTime(fb, currentTm);
		double diff = std::difftime(btime, now);

		if (diff <= 0.0) {
			std::cout << "Сегодня день рождения у: " << fb.name << " (" << oss.str() << ")\n";
		}else {
			std::cout << "Ближайщий день рождения у: " << fb.name << " (" << oss.str() << ")\n";
		}
	}
}

int main()	{
	setlocale(LC_ALL, "");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	std::vector<FriendBirthday> friends = readBirthdays();

	if (friends.empty()) {
		std::cout << "Нет введённых данных. Завершение.\n";
		return 0;
	}

	//Вычисление ближайщих дней рождения
	std::vector<FriendBirthday> upcoming = computeUpcomingBirthdays(friends);

	//Вывод полученных результатов
	printUpcomingBirthdays(upcoming);

	return 0;
}