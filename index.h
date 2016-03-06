#ifndef INDEX_H
#define INDEX_H
# include <string>

using namespace std;

class index{
public:
	index(unsigned long);
	index(unsigned long, int);
	unsigned long getKeys();
	void setKeys(unsigned long);
	int getTreeRRN();
	void setTreeRRN(int);
	virtual bool operator ==(const index&);	
private: 
	unsigned long keys;// llaves correspondiente al indice primario
	int treeRRN;//offset en donde se encuentra el registro
};

#endif