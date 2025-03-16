#pragma once

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileReader
{
public:
	static FileReader &GetInstance();

	std::vector<std::vector<int> > GetFileContent(const std::string &FilePath);

	FileReader(const FileReader &) = delete;

	FileReader(FileReader &&) = delete;

	FileReader &operator=(const FileReader &) = delete;

	FileReader &operator=(FileReader &&) = delete;

private:
	static FileReader *FileReaderInstance;

	fs::path FindFileInProject(const fs::path &SearchDirectory, const std::string &FileName);

	std::vector<std::vector<int> > ReadFile(const fs::path &FilePath);

	FileReader() = default;

	~FileReader() = default;
};

