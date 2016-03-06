# include "Node.h"
# include <iostream>
# include <sstream>

using namespace std;

Node::Node(){	}
void Node::setKeys(vector<index> newKeys){
	this->keys.swap(newKeys);
}
vector<index> Node::getKeys(){
	return keys;
}
void Node::setPage(int page){
	this->page = page;
}
int Node::getPage(){
	return page;
}
void Node::setFather(int father){
	this->father = father;
}
int Node::getFather(){
	return father;
}
void Node::setSons(vector<int> sons){
	this->sons = sons;
}
vector<int> Node::getSons(){
	return sons;
}
string Node::toString(){
	stringstream ss1;
	ss1 << "{ ";
	for (int i = 0; i < keys.size(); i++){
		ss1<< keys.at(i).getKeys() <<"  ";
	}
	ss1 << "} ";
	stringstream ss2;
	ss2 << "{ ";
	for (int i = 0; i < sons.size(); i++){
		ss2 << sons.at(i) << " ";
	}
	ss2 << "} ";
	stringstream final;
	final << "Father: " << father << "\tPage: " << page << "\tKeys: " 
	<< ss1.str() << "\tSons: " << ss2.str();

	return final.str();
}