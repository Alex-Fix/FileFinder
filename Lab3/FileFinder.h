#pragma once
#include <string>
#include <list>
#include <fstream>
#include <regex>
using namespace std;

class FileFinder {
	string path, content;
	bool isPath, isContent;

	bool CheckFileContent(string filePath);
public:
	bool SetPath(string path);
	bool SetContent(string content);
	bool IsValid();
	list<string> FindFilesByContent();
};