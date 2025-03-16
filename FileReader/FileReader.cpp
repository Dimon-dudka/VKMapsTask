#include "FileReader.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>

FileReader *FileReader::FileReaderInstance = nullptr;

FileReader &FileReader::GetInstance()
{
	if (!FileReaderInstance)
	{
		FileReaderInstance = new FileReader();
	}
	return *FileReaderInstance;
}

std::vector<std::vector<int> > FileReader::GetFileContent(const std::string &FilePath)
{
	const std::regex RegexExpr(R"(.*\.txt$)");

	if (!std::regex_search(FilePath, RegexExpr))
	{
		std::cout << "File isn't .txt file: " << FilePath << std::endl;
		return {};
	}

	auto SearchDir = fs::current_path().parent_path();
	auto PathToFile = FindFileInProject(SearchDir, FilePath);

	if (PathToFile.empty())
	{
		std::cout << "File not found: " << FilePath << std::endl;
		return {};
	}

	if (!fs::exists(PathToFile))
	{
		std::cout << "File not exists: " << PathToFile.string() << std::endl;
		return {};
	}

	return std::move(ReadFile(PathToFile));
}

fs::path FileReader::FindFileInProject(const fs::path &SearchDirectory, const std::string &FileName)
{
	if (!fs::exists(SearchDirectory))
	{
		std::cout << "Directory Not Found " << SearchDirectory << std::endl;
	}

	try
	{
		for (const auto &Entry: fs::recursive_directory_iterator(SearchDirectory))
		{
			if (Entry.is_regular_file() && Entry.path().filename() == FileName)
			{
				return Entry.path();
			}
		}
	}
	catch (std::exception &Exception)
	{
		std::cout << "Exception occurred by searching file: " << Exception.what() << std::endl;
		return fs::path();
	}

	return fs::path();
}

std::vector<std::vector<int> > FileReader::ReadFile(const fs::path &FilePath)
{
	std::vector<std::vector<int> > FileContent;

	std::ifstream File(FilePath);
	if (!File.is_open())
	{
		std::cout << "Error occurred by opening file: " << FilePath << std::endl;
		return {};
	}

	std::string Line;
	while (std::getline(File, Line))
	{
		if (Line.empty())
		{
			continue;
		}

		std::vector<int> Row;
		std::istringstream IsStream(Line);
		int CurrentNumber;

		while (IsStream >> CurrentNumber)
		{
			Row.push_back(CurrentNumber);
		}

		if (!Row.empty())
		{
			FileContent.push_back(Row);
		}
	}

	File.close();

	return std::move(FileContent);
}

