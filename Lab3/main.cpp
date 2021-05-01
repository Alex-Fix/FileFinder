#include "FileFinder.h"
#include <iostream>
using namespace std;

int main() {

	string command;
	string path;
	string content;

	FileFinder fileFinder;

	while (true)
	{
		cout << "Enter 'q' to exit, 'p' to change path, 't' to change content template, 'go' to run FileFinder\nCommand: ";
		getline(cin, command);

		if (command._Equal("q"))
			break;
		else if (command._Equal("p")) {
			cout << "Enter path: ";
			getline(cin, path);
			path = "C:\lab3";
			if (!fileFinder.SetPath(path)) cout << "Incorrect path!!!" << endl;
		}
		else if (command._Equal("t"))
		{
			cout << "Enter content template: ";
			getline(cin, content);
			if (!fileFinder.SetContent(content)) cout << "Incorrect content template!!!" << endl;
		}
		else if (command._Equal("go"))
		{
			if (!fileFinder.IsValid()) {
				cout << "Incorrect path or content template!!!" << endl;
				continue;
			}

			list<string> findedFiles = fileFinder.FindFilesByContent();
			cout << "Finded files:" << endl;
			for (const auto& iterator : findedFiles)
				cout << iterator << endl;
		}
		else {
			cout << "Incorrect command!!!" << endl;
		}
	}

	return 0;
}