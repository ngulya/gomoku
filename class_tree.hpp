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
	int 					who_going;	
	vector<struct node* >	nodes;
}	node;


class Tree
{
public:
	Tree(vector<vector<int> > start_map, int latitude, int depth);
	void	return_last_dep(void);
	~Tree(void);
private:
	int						latitude;
	int						depth;
	vector<vector<int> >	start_map;
	node					*first_node;
};

#endif