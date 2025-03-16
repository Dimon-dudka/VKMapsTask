#pragma once

#include <vector>

#include "VkMapsTaskStructure/TaskStructure.h"

class PathFinder
{
public:
	explicit PathFinder(const std::vector<std::vector<int> > &FileContent);

	void SetNewTaskInfo(const std::vector<std::vector<int> > &FileContent);

	const std::vector<int> GetPathsToAllVertexes();

private:
	TaskStructure TaskInfo;

	std::vector<int> CalculatedPathsToAllVertexes;

	void CalculatePaths();
};
