# pragma once
# include <string>
# include <vector>
# include "index.h"

using namespace std;

class Node{
public:
	Node();
	void setKeys(vector<index>);
	vector<index> getKeys();
	void setPage(int);
	int getPage();
	void setFather(int);
	int getFather();
	void setSons(vector<int>);
	vector<int> getSons();
	string toString();
private:
	int page, father;
	vector<int> sons;
	vector<index> keys;
};