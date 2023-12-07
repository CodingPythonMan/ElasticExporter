#include <queue>
#include <vector>

class Test {
public:
	bool PutReliableData(int Data);
	
	void Print();

private:
	std::priority_queue<int, std::vector<int>, std::greater<int>> ReliableQueue;
};