// #include <iostream>
#include "class_tree.hpp"
// using namespace std;

Tree::Tree(vector<vector<int> > map_in_node, int latitude, int depth){
	this->latitude = latitude;
	this->depth = depth;
	this->start_map = start_map;
	// start find decision
	return;
}

Tree::~Tree(void){
	return;
}

void	Tree::return_last_dep(void){
	cout << latitude << "-lat    dep-" << depth << endl;
	return;
}


// void	TreeOnTheHeap(int w, int h, std::string n)
// {
// 	Tree* 	p = new Tree(w, h, n);
// 	std::cout<<"TreeOnTheHeap"<<std::endl;
// 	(*p).name_Tree();
// 	(*p).w_h_Tree();
// 	delete p;
// }