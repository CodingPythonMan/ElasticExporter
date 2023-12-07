#include <queue>
#include <vector>
using namespace std;

class Test {
public:
	Test();
	virtual ~Test();

	bool PutReliableData(int Data);
	
	void Print();

private:
	vector<int> ReliableList;
};