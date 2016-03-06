# include "index.h"

index::index(unsigned long keys){
	this->keys = keys;
}

index::index(unsigned long keys, int TreeRRN){
	this->keys = keys;
	this->treeRRN = TreeRRN;
}
unsigned long index::getKeys(){
	return this->keys;
}
void index::setKeys(unsigned long keys){
	this->keys = keys;
}

void index::setTreeRRN(int treeRRN){
	this->treeRRN = treeRRN;
}
int index::getTreeRRN(){
	return treeRRN;
}
bool index::operator ==(const index& other){
	return this->keys == other.keys;
}