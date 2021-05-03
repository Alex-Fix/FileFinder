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

	list<int> anySymbPos;
	int startPos = 0;
	string currContent = this->content;
	while (true)
	{
		int pos = currContent.find("{*}", startPos);
		if (pos == -1) break;
		anySymbPos.push_back(pos);
		currContent.replace(pos, sizeof("{*}") - 1, "");
	}

	bool isMatch = false;
	int fcLength = fileContent.length();
	bool isAny = false;
	for (int i = 0, j = 0; i < fcLength; ++i) {
		if (j == currContent.length()) {
			isMatch = true;
			break;
		}

		if (!anySymbPos.empty() && j == *anySymbPos.begin()) {
			isAny = true;
			anySymbPos.pop_front();
		}

		if (fileContent[i] == currContent[j]) {
			isAny = false;
			j++;
		}
		else if (currContent[j] == '*') {
			isAny = false;
			j++;
		}
		else if (isAny) {
			
		}
		else {
			j = 0;
		}
	}

	return isMatch;
}