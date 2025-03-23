#include <iostream>
#include <ctime>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <string>

/*
������� ������ ������� ������ ���� �.� �������� ������ �� ��� ����� ������ ������ �������������
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
*/
#define NOMINMAX
#include <windows.h>

//���������� ����������, ���������� ������� ������ � ����� � ������
std::string currentTask = "";
std::time_t startTime = 0;

//����� ����������� �����: �������� ������ -> �������� ����������� ����� � �������� (���������� ����� ������������� ��� �������)
std::unordered_map<std::string, double> completedTasks;

//������� ���������� ������� ������ (���� ����� ������� ����)
void endCurrentTask() {
	if (!currentTask.empty()) {
		std::time_t now = std::time(nullptr);
		double elapsed = std::difftime(now, startTime);
		completedTasks[currentTask] += elapsed;
		std::cout << "������ \"" << currentTask << "\" ���������. ����������� �����: "
			<< elapsed << " ���.\n";
		currentTask = "";
	}
}

//������� ������� begin
void handleBegin() {
	//���� ��� ��� �����-�� ������, ��������� �
	if (!currentTask.empty()) {
		endCurrentTask();
	}

	//������ �������� ����� ������
	std::cout << "������� �������� ������: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������� ������
	std::getline(std::cin, currentTask);

	//������������� ����� ������ ������ ��� ����� �������
	startTime = std::time(nullptr);
	std::cout << "������ ������ \"" << currentTask << "\".\n";
}

//������� ��� ������� end
void handleEnd() {
	if (!currentTask.empty()) {
		endCurrentTask();
	}
	else {
		std::cout << "��� �������� ������ ��� ����������.\n";
	}
}

//������� ��� ������� status
void handleStatus() {
	std::cout << "\n������ ����������� �����:\n";
	if (completedTasks.empty()){
		std::cout << "��� ����������� �����.\n";
	}else {
		//������� ����� � ����� � 2 ������� ����� �������
		for (const auto& task : completedTasks) {
			double hours = task.second / 3600.0;
			std::cout << "������: " << task.first << " | �����: " << std::fixed << std::setprecision(2) << hours << " �.\n";
		}
	}
	if (!currentTask.empty()) {
		std::cout << "������� ������: " << currentTask << "\n";
	}std::cout << "\n";
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	std::string command;
	bool checkInput = true;

	while (true){
		checkInput == true? std::cout << "�������� ����� �������. ��������� �������: begin, end, status, exit\n": std::cout << "��������� ������� : begin, end, status, exite\n" << "\n��������� ���� ";
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
			
			//����� ������� ����������� ������� ������ �� �������, ���� ��� ����
			if (!currentTask.empty()) {
				
				endCurrentTask();
				system("pause");
				system("cls");
			
			}
			
			std::cout << "����� �� ���������.\n";
			break;
		
		}else {
			system("cls");
			checkInput = false;
		}
	}

	return 0;
}