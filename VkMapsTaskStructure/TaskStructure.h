#pragma	once
#include <unordered_set>
#include <vector>

class TaskStructure
{
public:
	explicit TaskStructure(const std::vector<std::vector<int> > &FileData);

	TaskStructure &operator =(const TaskStructure &AnotherTask);

	TaskStructure &operator =(const std::vector<std::vector<int> > &FileData);

	const bool IsValid();

	const int GetEdgesCount();

	const int GetVertexCount();

	const int GetStartVertexNumber();

	const std::vector<std::unordered_set<int> > &GetGraph();

private:
	bool bIsDataValid = false;

	// Task info
	int EdgesCount = -1;
	int VertexCount = -1;
	int StartVertexNumber = -1;
	std::vector<std::unordered_set<int> > Graph;

	void CreateTaskStructure(const std::vector<std::vector<int> > &FileData);
};
