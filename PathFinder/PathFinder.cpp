
#include "PathFinder.h"

#include <iostream>
#include <ostream>
#include <queue>

PathFinder::PathFinder(const std::vector<std::vector<int> > &FileContent) : TaskInfo(FileContent)
{
	CalculatePaths();
}

void PathFinder::SetNewTaskInfo(const std::vector<std::vector<int> > &FileContent)
{
	TaskInfo = FileContent;
	CalculatePaths();
}

const std::vector<int> PathFinder::GetPathsToAllVertexes()
{
	if (CalculatedPathsToAllVertexes.empty())
	{
		std::cout << "Paths to all vertexes was not calculated" << std::endl;
		return {};
	}

	return CalculatedPathsToAllVertexes;
}


void PathFinder::CalculatePaths()
{
	if (!TaskInfo.IsValid())
	{
		std::cout << "TaskInfo is invalid" << std::endl;
		return;
	}

	std::vector<int> PathsToAllVertexes(TaskInfo.GetVertexCount(), 0);
	std::vector<bool> ProofVertexChecked(TaskInfo.GetVertexCount(), false);

	PathsToAllVertexes.at(TaskInfo.GetStartVertexNumber()) = 0;
	ProofVertexChecked.at(TaskInfo.GetStartVertexNumber()) = true;

	int CurrentPathLength = 0;

	std::queue<int> VertexesToCheck;
	VertexesToCheck.push(TaskInfo.GetStartVertexNumber());

	size_t CurrentVertexesToCheckCount = VertexesToCheck.size();

	while (!VertexesToCheck.empty())
	{
		for (size_t i = 0; i < CurrentVertexesToCheckCount; i++)
		{
			int CurrentVertex = VertexesToCheck.front();
			VertexesToCheck.pop();

			if (TaskInfo.GetGraph().size() <= CurrentVertex)
			{
				std::cout << "Not all paths are added into graph structure" << std::endl;
				return;
			}

			for (const auto &VertexByEdge: TaskInfo.GetGraph().at(CurrentVertex))
			{
				if (ProofVertexChecked.at(VertexByEdge))
				{
					continue;
				}

				PathsToAllVertexes.at(VertexByEdge) = CurrentPathLength + 1;
				VertexesToCheck.push(VertexByEdge);
				ProofVertexChecked.at(VertexByEdge) = true;
			}
		}
		CurrentPathLength += 1;
		CurrentVertexesToCheckCount = VertexesToCheck.size();
	}

	CalculatedPathsToAllVertexes = std::move(PathsToAllVertexes);
}
