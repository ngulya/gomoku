#ifndef CLASS_TREE_H
# define CLASS_TREE_H
# include <iostream>
# include <vector>
# include <iostream>
# include <stdlib.h>
# include <string>
# include <fstream>
using namespace std;


typedef struct			node
{
	vector<vector<int> >	map_in_node;
	vector<vector<int> >	cross_map;
	int 					who_going;
	int 					level_depth;
	vector<struct node* >	nodes;
}	node;


class Tree
{
public:
	Tree();
	void			 	read_from_file();
	void			 	_print(vector<vector<int> > the_vector);
	void			 	_prepare_map(vector<vector<int> > the_vector);
// vector< vector<int> >	diagonal_left_up(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);
// vector< vector<int> >	diagonal_right_up(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);
vector< vector<int> >	column(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);
vector< vector<int> >	row(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);

	~Tree(void);

private:
	vector<vector<int> >	start_map;
	node					*first_node;
	int 					size_map;
};

#endif