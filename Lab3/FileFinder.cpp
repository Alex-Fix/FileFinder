#include "FileFinder.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

bool FileFinder::SetPath(string path) {
	if (fs::exists(path) && fs::is_directory(fs::status(path)))
	{
		this->path = path;
		this->isPath = true;
	}
	else
		this->isPath = false;

	return this->isPath;
}

bool FileFinder::SetContent(string content) {
	if (content.empty())
		this->isContent = false;
	else {
		this->isContent = true;
		/*content = regex_replace(content, regex("{*}"), ".*?");
		content = regex_replace(content, regex("*"), ".");*/
		this->content = content;
	}

	return this->isContent;
}

bool FileFinder::IsValid() {
	return this->isContent && this->isPath;
}

list<string> FileFinder::FindFilesByContent() {
	list<string> findedFiles;

	for (const auto& entry : fs::directory_iterator(path))
		if (entry.is_regular_file())
		{
			bool containsContent = CheckFileContent(entry.path().string());
			if (containsContent) findedFiles.push_back(entry.path().filename().string());
		}

	return findedFiles;
}

bool FileFinder::CheckFileContent(string filePath) {
	std::ifstream file;
	file.open(filePath);

	if (!file.is_open()) return false;

	string fileContent((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
	file.close();

	cmatch match;
	bool isMatch = regex_search(fileContent.c_str(), match, regex("\\d"));

	return isMatch;
}