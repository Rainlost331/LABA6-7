#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <locale.h>

#define EVENT_UNIQUE_ID L"FIGURES"
#define APP_EXIT_KEYCODE 27

int main()
{
	setlocale(LC_ALL, "ru");

	HANDLE figures_app_event = OpenEvent(
		EVENT_ALL_ACCESS,
		TRUE,
		EVENT_UNIQUE_ID
	);

	char getch_result;

	if (figures_app_event == 0) {
		std::cout << "Ошибка: не удалось создать связь между приложениями!" << std::endl;
		getch_result = _getch();
		return getch_result;
	}

	std::cout << "Приложение успешно связано!" << std::endl;

	bool is_app_running = false;

	do
	{
		getch_result = _getch();

		switch (getch_result)
		{
		case APP_EXIT_KEYCODE:
			std::cout << "Приложение успешно завершило свою работу!" << std::endl;
			CloseHandle(figures_app_event);
			return 0;
			break;
		default:
			if (SetEvent(figures_app_event) && !is_app_running) {
				is_app_running = true;
				std::cout << "Приложение работает" << std::endl;
				break;
			}

			if (ResetEvent(figures_app_event) && is_app_running) {
				is_app_running = false;
				std::cout << "Приложение остановлено" << std::endl;
				break;
			}
			
			break;
		}
	} while (true);
}