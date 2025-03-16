#include <iostream>

#include "FileReader/FileReader.h"
#include "PathFinder/PathFinder.h"

int main()
{
	const auto FileContent = FileReader::GetInstance().GetFileContent("graph.txt");
	PathFinder PathHandler(FileContent);
	const auto DistanceToAllVertexes = PathHandler.GetPathsToAllVertexes();

	for (const auto &DistanceToVertex: DistanceToAllVertexes)
	{
		std::cout << DistanceToVertex << std::endl;
	}

	return 0;
}
