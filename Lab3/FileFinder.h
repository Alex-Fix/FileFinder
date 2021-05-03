#pragma once
#include <string>
#include <list>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

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