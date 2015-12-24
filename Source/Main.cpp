#include <functional>
#include <string>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

std::string openFilename(wchar_t *filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL)
{
	OPENFILENAME ofn;
	wchar_t filename[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";
	std::string filenameStr;
	if (GetOpenFileNameW(&ofn))
	{
		std::wstring tempString = ofn.lpstrFile;
		filenameStr = std::string(tempString.begin(), tempString.end());
	}
	return filenameStr;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Button Sound Tester");

	// test button setup
	Button testButton;
	testButton.setBackground(sf::Color::White);
	testButton.setText("Test Button");
	testButton.setPosition(100.f, 400.f);

	// on click setup
	Button onClickButton;
	onClickButton.setBackground(sf::Color::White);
	onClickButton.setText("Set OnClick Sound");
	onClickButton.setPosition(300.f, 300.f);
	std::string onClickFilename;
	sf::SoundBuffer onClickSoundBuffer;
	sf::Sound onClickSound;

	// on hover setup
	Button onHoverButton;
	onHoverButton.setBackground(sf::Color::White);
	onHoverButton.setText("Set OnHover Sound");
	onHoverButton.setPosition(300.f, 350.f);
	std::string onHoverFilename;
	sf::SoundBuffer onHoverSoundBuffer;
	sf::Sound onHoverSound;

	bool shouldPlayHover = true;

	//button event setup
	testButton.onClicked = [&]{ 
		onClickSound.play(); 
		onHoverSound.stop();
	};
	testButton.onHover = [&]{
		if (shouldPlayHover)
		{
			shouldPlayHover = false;
			onHoverSound.play();
		}
	};
	testButton.onHoverEnd = [&]{ shouldPlayHover = true; };
	onClickButton.onClicked = [&]{
		onClickFilename = openFilename();
		onClickSoundBuffer.loadFromFile(onClickFilename);
		onClickSound.setBuffer(onClickSoundBuffer);
	};
	onHoverButton.onClicked = [&]{
		onHoverFilename = openFilename();
		onHoverSoundBuffer.loadFromFile(onHoverFilename);
		onHoverSound.setBuffer(onHoverSoundBuffer);
	};

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				testButton.checkClicked(event.mouseButton.x, event.mouseButton.y);
				onClickButton.checkClicked(event.mouseButton.x, event.mouseButton.y);
				onHoverButton.checkClicked(event.mouseButton.x, event.mouseButton.y);
			}
			if (event.type == sf::Event::MouseMoved)
			{
				testButton.checkHover(event.mouseMove.x, event.mouseMove.y);
			}
		}

		window.clear();
		testButton.draw(window);
		onClickButton.draw(window);
		onHoverButton.draw(window);
		window.display();
	}

	return 0;
}
