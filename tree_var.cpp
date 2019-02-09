#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string> // подключаем строки
#include <fstream> // подключаем файлы
using namespace std;

typedef struct			node
{
	vector<vector<int> >	map_in_node;
	int 					who_going;	
	vector<struct node* >	nodes;
}	node;

vector<vector<int> > 	read_from_file(){

	vector<vector<int> > the_vector;
	string s;
	string tmp_int;
	string tmp_s;
	
	ifstream file("map.txt");
	while(getline(file, s)){ // пока не достигнут конец файла класть очередную строку в переменную (s)
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
	size = the_vector.size();
	for (int i = 0; i < size; ++i)
	{
		for (int i2 = 0; i2 < size; ++i2)
			cout<<the_vector[i][i2]<<"  ";
		cout<<endl;
	}
	
}

void	diagonal_left_up(vector< vector<int> > map, int size, int who_going){
	for (int x = 0; x < size ; ++x)
	{

		for (int y = x; y >= 0; --y)
		{
			printf("%d ", map[x-y][y]);
		}
		printf("\n");
	
	
	}
	for (int x = 1; x < size ; ++x)
	{

		for (int y = size - 1; y >= x; --y)
		{
			printf("%d ", map[size - 1 + x - y][y]);
		}
		printf("\n");
	
	
	}

}


void	diagonal_right_up(vector< vector<int> > map, int size, int who_going){

	for (int x = 0; x < size ; ++x)
	{
		for (int y = size - 1 - x; y <= size - 1; ++y)
		{
			printf("%d ", map[x - (size - 1 - y)][y]);
		}
		printf("\n");
	}
	for (int x = 1; x < size ; ++x)
	{
		for (int y = 0; y <= size - 1 - x; ++y)
		{
			printf("%d ", map[x+y][y]);
		}
		printf("\n");
	}
	
}

int main()
{	
	// int size;
	vector< vector<int> > now_map;
	now_map = read_from_file();
	_print(now_map);
	printf("\n");

	diagonal_right_up(now_map, now_map.size(), 1);

	// node *first_node = new node;
	
	// tmp_node->who_going = 1;
	// // tmp_node->nodes.push_back(new node);
	// printf("%d\n", tmp_node->who_going);
	// printf("%lu\n", tmp_node->nodes.size());
		
	// // tmp_node->nodes[0]->who_going = 2;
	// // printf("%d\n", tmp_node->nodes[0]->who_going);

	return 0;
}