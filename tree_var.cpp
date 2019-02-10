#include "class_tree.hpp"
// using namespace std;


vector<vector<int> > 	read_from_file(){

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
	size = the_vector.size();
	for (int i = 0; i < size; ++i)
	{
		printf("%d| ", i);
		for (int i2 = 0; i2 < size; ++i2)
			printf("%2d", the_vector[i][i2]);
		printf("\n");
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


// use for variant who going other side

void	check(vector<int>  tmp, int who_going){
	for (int i = 0; i < tmp.size(); ++i){
		printf("%d ", tmp[i]);
	}
	printf("\n");

	int num = 0;
	int left_i = -1;
	int right_i = -1;
	vector<int>  _new(tmp.size());

	for (int i = 0; i < tmp.size(); ++i){
		if (tmp[i] == who_going)
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

	for (int i = 0; i < _new.size(); ++i){
		printf("%d ", _new[i]);
	}
	printf("\n");
	printf("\n");
}

void	row(vector< vector<int> > now_map, int size, int who_going){


	vector< vector<int> > tmp;	
	tmp = now_map;
	for (int x = 0; x < size ; ++x)
		for (int y = 0; y < size ; ++y)
			tmp[x][y] = 0;

	int num = 0;
	int left_x = -1;
	int left_y = -1;

	for (int x = 0; x < size ; ++x)
	{

		left_y = -1;
		left_x = -1;
		num = 0;
		for (int y = 0; y < size ; ++y){
			if (now_map[x][y] == who_going)
			{
				if (y > 0 and now_map[x][y-1] == 0){
					left_x = x;
					left_y = y-1;
				}
				num++;
			}
			else
			{
				if(num)
				{
					if (now_map[x][y] == 0)
						tmp[x][y] = num;
					if (left_y != -1)
						tmp[left_x][left_y] = num;
				}
				left_y = -1;
				left_x = -1;
				num = 0;
			}
		}
		if(num and left_y != -1)
			tmp[left_x][left_y] = num;

	}
	for (int x = 0; x < size ; ++x){
		printf("map ");
		for (int y = 0; y < size ; ++y)
			printf("%d ", now_map[x][y]);
		printf("\ntmp ");
		for (int y = 0; y < size ; ++y)
			printf("%d ", tmp[x][y]);
		printf("\n\n");
	}
}

void	column(vector< vector<int> > map, int size, int who_going){

	for (int y = 0; y < size ; ++y)
	{
		for (int x = 0; x < size ; ++x)
		{ 
			printf("%d ", map[x][y]);
		}
		printf("\n");
	}
}

int main()
{	
	vector< vector<int> > now_map;
	now_map = read_from_file();
	_print(now_map);
	printf("\n");
	row(now_map, now_map.size(), 1);




	// Tree* 	p = new Tree(now_map, 3, 5);
	// (*p).return_last_dep();


	// node *first_node = new node;	
	// tmp_node->who_going = 1;
	// // tmp_node->nodes.push_back(new node);
	// printf("%d\n", tmp_node->who_going);
	// printf("%lu\n", tmp_node->nodes.size());
		
	// // tmp_node->nodes[0]->who_going = 2;
	// // printf("%d\n", tmp_node->nodes[0]->who_going);

	return 0;
}