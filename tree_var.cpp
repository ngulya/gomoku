// #include "class_tree.hpp"
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
	vector<vector<int> >	cross_map_not_you;
	vector<int> 			nums_vector;
	int 					who_going;
	int 					level_depth;
	int 					size;
	vector<struct node* >	nodes;
}	node;

vector<vector<int> >	read_from_file();
vector<int>				check_not_you(vector<int>  tmp, node *now_node);
vector<int>				check(vector<int>  tmp, node *now_node);
void					_print(	vector<vector<int> > the_vector);


void	diagonal_left_up(node *now_node, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < now_node->size ; ++x)
	{
		vector<int> tmp;
		for (int y = x; y >= 0; --y)
			tmp.push_back(now_node->map_in_node[x-y][y]);
		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int y = x; y >= 0; --y)
				now_node->cross_map[x-y][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int y = x; y >= 0; --y)
				now_node->cross_map_not_you[x-y][y] += _new[i++];
		}


	}
	for (int x = 1; x < now_node->size ; ++x)
	{
		vector<int> tmp;
		for (int y = now_node->size - 1; y >= x; --y)
			tmp.push_back(now_node->map_in_node[now_node->size - 1 + x - y][y]);

		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int y = now_node->size - 1; y >= x; --y)
				now_node->cross_map[now_node->size - 1 + x - y][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int y = now_node->size - 1; y >= x; --y)
				now_node->cross_map_not_you[now_node->size - 1 + x - y][y] += _new[i++];
		}

	}
}


void	diagonal_right_up(node *now_node, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < now_node->size ; ++x)
	{
		vector<int> tmp;
		for (int y = now_node->size - 1 - x; y <= now_node->size - 1; ++y)
			tmp.push_back(now_node->map_in_node[x - (now_node->size - 1 - y)][y]);

		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int y = now_node->size - 1 - x; y <= now_node->size - 1; ++y)
				now_node->cross_map[x - (now_node->size - 1 - y)][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int y = now_node->size - 1 - x; y <= now_node->size - 1; ++y)
				now_node->cross_map_not_you[x - (now_node->size - 1 - y)][y] += _new[i++];
		}

	}
	for (int x = 1; x < now_node->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y <= now_node->size - 1 - x; ++y)
			tmp.push_back(now_node->map_in_node[x+y][y]);

		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int y = 0; y <= now_node->size - 1 - x; ++y)
				now_node->cross_map[x+y][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int y = 0; y <= now_node->size - 1 - x; ++y)
				now_node->cross_map_not_you[x+y][y] += _new[i++];
		}
	}
}


void	row(node *now_node, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < now_node->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y < now_node->size ; ++y)
			tmp.push_back(now_node->map_in_node[x][y]);
		
		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int y = 0; y < now_node->size ; ++y)
				now_node->cross_map[x][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int y = 0; y < now_node->size ; ++y)
				now_node->cross_map_not_you[x][y] += _new[i++];
		}

	}
}

void	column(node *now_node, bool you){
	vector<int>  _new;
	int i;
	for (int y = 0; y < now_node->size ; ++y)
	{
		vector<int> tmp;
		for (int x = 0; x < now_node->size ; ++x)
			tmp.push_back(now_node->map_in_node[x][y]);
		i = 0;
		if (you){
			_new = check(tmp, now_node);
			for (int x = 0; x < now_node->size ; ++x)
				now_node->cross_map[x][y] += _new[i++];
		}
		else{
			_new = check_not_you(tmp, now_node);
			for (int x = 0; x < now_node->size ; ++x)
				now_node->cross_map_not_you[x][y] += _new[i++];
		}
	}
}


int main()
{	
	vector<int>  tmp(5);
	node *first_node = new node;
	first_node->nums_vector = tmp;
	first_node->map_in_node = read_from_file();
	first_node->size = first_node->map_in_node.size();
	first_node->who_going = 1;
	first_node->cross_map = first_node->map_in_node;
	for (int x = 0; x < first_node->size; ++x)
		for (int y = 0; y < first_node->size; ++y)
			first_node->cross_map[x][y] = 0;
	first_node->cross_map_not_you = first_node->cross_map;

	row(first_node, false);
	row(first_node, true);
	column(first_node, false);
	column(first_node, true);
	diagonal_right_up(first_node, false);
	diagonal_right_up(first_node, true);
	diagonal_left_up(first_node, false);
	diagonal_left_up(first_node, true);
	
	_print(first_node->map_in_node);
	printf("\ncross_map_not_you:");
	_print(first_node->cross_map_not_you);
	printf("\ncross_map:");
	_print(first_node->cross_map);

	// printf("\n");
	// _print(cross_map);

	// Tree* 	p = new Tree();
	// (*p).return_last_dep();
	// node *first_node = new node;
	// tmp_node->who_going = 1;
	// tmp_node->nodes.push_back(new node);
	// printf("%d\n", tmp_node->who_going);
	// printf("%lu\n", tmp_node->nodes.size());
	// // tmp_node->nodes[0]->who_going = 2;
	// // printf("%d\n", tmp_node->nodes[0]->who_going);

	return 0;
}


vector<vector<int> > 	read_from_file()
{

	vector<vector<int> > the_vector;
	string s;
	string tmp_int;
	string tmp_s;
	
	ifstream file("map.txt");
	while(getline(file, s)){
		vector<int> tmp;
		tmp_s = "";
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] != ' '){
				tmp_s += s[i];
			}
			else{
				tmp.push_back(stoi(tmp_s));
				tmp_s = "";
			}
		}
		tmp.push_back(stoi(tmp_s));
		tmp_s = "";
		the_vector.push_back(tmp);

	}

	file.close();
	return the_vector;
}

void 	_print(	vector<vector<int> > the_vector){
	int size;
	printf("\n");
	size = the_vector.size();
	for (int i = 0; i < size; ++i)
	{
		printf("%d| ", i);
		for (int i2 = 0; i2 < size; ++i2)
			printf("%2d", the_vector[i][i2]);
		printf("\n");
	}
	
}


vector<int>	check_not_you(vector<int>  tmp, node *now_node){
	int num = 0;
	int left_i = -1;
	vector<int>  _new(tmp.size());

	for (int i = 0; i < tmp.size(); ++i){
		if (tmp[i] != 0 and tmp[i] != now_node->who_going)
		{
			if (i > 0 and tmp[i-1] == 0)
				left_i = i-1;
			num++;
		}
		else
		{
			if(num)
			{
				if (tmp[i] == 0)
					_new[i] += num;
				if (left_i != -1)
					_new[left_i] += num;
			}
			left_i = -1;
			num = 0;
		}
	}

	if(num and left_i != -1)
		_new[left_i] += num;
	return _new;
}

vector<int>	check(vector<int>  tmp, node *now_node){
	int num = 0;
	int left_i = -1;
	vector<int>  _new(tmp.size());

	for (int i = 0; i < tmp.size(); ++i){
		if (tmp[i] == now_node->who_going)
		{
			if (i > 0 and tmp[i-1] == 0)
				left_i = i-1;
			num++;
		}
		else
		{
			if(num)
			{
				if (num <= 5)
					now_node->nums_vector[num - 1] += 1;
				if (tmp[i] == 0)
					_new[i] += num;
				if (left_i != -1)
					_new[left_i] += num;
			}
			left_i = -1;
			num = 0;
		}
	}

	if(num and left_i != -1){
		if (num <= 5)
			now_node->nums_vector[num - 1] += 1;
		_new[left_i] += num;
	}
	return _new;
}