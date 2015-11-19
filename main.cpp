#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

int main( int argc, char** argv)
{
	bool bRun = true;
	unsigned int uTimes = 0;

	if (argc > 1)
		uTimes = atoi(argv[1]);

	std::thread mLoop([&bRun, &uTimes](){
		std::vector<std::pair<int, int>> vTones = { 
			{ 1568, 200 },
			{ 1568, 200 },
			{ 1568, 200 },
			{ 1245, 1000 },
			{ 1397, 200 },
			{ 1397, 200 },
			{ 1397, 200 },
			{ 1175, 1000 }
		};

		unsigned int uCounter = 0;
		while (bRun)
		{
			for (const auto& rTone : vTones)
			{
				if (!bRun)
					break;

				Beep(rTone.first, rTone.second);
			}

			++uCounter;
			if (!bRun || (uTimes > 0 && uCounter == uTimes))
				break;

			Sleep(1000);
		}
	});

	std::thread mKey([&bRun]{
		std::cout << "Press Enter to stop" << std::endl;
		std::cin.get();
		bRun = false;
	});

	mLoop.join();
	mKey.detach();
	return 0;
}
