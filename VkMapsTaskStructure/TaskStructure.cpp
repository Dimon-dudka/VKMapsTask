#include "TaskStructure.h"

#include <iostream>

TaskStructure::TaskStructure(const std::vector<std::vector<int> > &FileData)
{
	CreateTaskStructure(FileData);
}

TaskStructure &TaskStructure::operator=(const TaskStructure &AnotherTask)
{
	bIsDataValid = AnotherTask.bIsDataValid;
	Graph = AnotherTask.Graph;
	VertexCount = AnotherTask.VertexCount;
	EdgesCount = AnotherTask.EdgesCount;
	StartVertexNumber = AnotherTask.StartVertexNumber;
	return *this;
}

TaskStructure &TaskStructure::operator=(const std::vector<std::vector<int> > &FileData)
{
	this->CreateTaskStructure(FileData);
	return *this;
}

const bool TaskStructure::IsValid()
{
	return bIsDataValid;
}

const int TaskStructure::GetEdgesCount()
{
	return EdgesCount;
}

const int TaskStructure::GetVertexCount()
{
	return VertexCount;
}

const int TaskStructure::GetStartVertexNumber()
{
	return StartVertexNumber;
}

const std::vector<std::unordered_set<int> > &TaskStructure::GetGraph()
{
	return Graph;
}

void TaskStructure::CreateTaskStructure(const std::vector<std::vector<int> > &FileData)
{
	bIsDataValid = false;

	// Data size check
	if (FileData.empty())
	{
		std::cout << "FileData is empty" << std::endl;
		return;
	}
	else if (FileData.size() < 3)
	{
		std::cout << "FileData is incomplete" << std::endl;
		return;
	}

	// Vertex check
	if (FileData.at(0).size() != 1)
	{
		std::cout << "Incorrect vertex count: " << FileData.at(0).size() << std::endl;
		return;
	}
	else if (FileData.at(0).at(0) < 0)
	{
		std::cout << "Incorrect vertex number: " << FileData.at(0).at(0) << std::endl;
		return;
	}
	else
	{
		VertexCount = FileData.at(0).at(0);
	}

	if (FileData.at(1).size() != 1)
	{
		std::cout << "Incorrect edges count: " << FileData.at(1).size() << std::endl;
		return;
	}
	else if (FileData.at(1).at(0) < 0)
	{
		std::cout << "Incorrect edges number: " << FileData.at(1).at(0) << std::endl;
		return;
	}
	else
	{
		EdgesCount = FileData.at(1).at(0);
	}

	Graph.resize(FileData.at(1).at(0) + 1);

	auto IsBetween = [this](int LowerBound, int UpperBound, int TestingNumber)-> bool
	{
		if (TestingNumber >= LowerBound && TestingNumber <= UpperBound)
		{
			return true;
		}
		return false;
	};

	for (size_t i = 2; i < FileData.size() - 1 && i < 2 + EdgesCount; i++)
	{
		// Edges description check
		if (FileData.at(i).size() != 2)
		{
			std::cout << "Incorrect edge description. Edge number: " << i - 2 << std::endl;
			return;
		}
		int StartVertex = FileData.at(i).at(0);
		int EndVertex = FileData.at(i).at(1);

		if (!IsBetween(0, VertexCount - 1, StartVertex))
		{
			std::cout << "Incorrect vertex number in edge description. Vertex number: " << StartVertex << std::endl;
			return;
		}

		if (!IsBetween(0, VertexCount - 1, EndVertex))
		{
			std::cout << "Incorrect vertex number in edge description. Vertex number: " << EndVertex << std::endl;
			return;
		}

		Graph.at(StartVertex).insert(EndVertex);
		Graph.at(EndVertex).insert(StartVertex);
	}

	int StartVertexIndex = static_cast<int>(FileData.size() - 1);

	if (FileData.at(StartVertexIndex).size() != 1)
	{
		std::cout << "Incorrect start search vertex count: " << FileData.at(StartVertexIndex).size() << std::endl;
		return;
	}
	else if (!IsBetween(0, VertexCount - 1, FileData.at(StartVertexIndex).at(0)))
	{
		std::cout << "Incorrect start search vertex number: " << FileData.at(StartVertexIndex).at(0) << std::endl;
		return;
	}
	else
	{
		StartVertexNumber = FileData.at(StartVertexIndex).at(0);
	}

	bIsDataValid = true;
}
