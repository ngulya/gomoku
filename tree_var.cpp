#include "class_tree.hpp"
vector<vector<int> >	read_from_file();
vector<int>				check(vector<int>  tmp, int who_going);
void					_print(	vector<vector<int> > the_vector);


vector< vector<int> >	diagonal_left_up(vector< vector<int> > now_map, int size, int who_going, vector< vector<int> > cross_map){
	vector<int>  _new;
	int i;
	for (int x = 0; x < size ; ++x)
	{
		vector<int> tmp;
		for (int y = x; y >= 0; --y)
			tmp.push_back(now_map[x-y][y]);

		_new = check(tmp, who_going);
		i = 0;
		for (int y = x; y >= 0; --y)
			cross_map[x-y][y] += _new[i++];

	}
	for (int x = 1; x < size ; ++x)
	{
		vector<int> tmp;
		for (int y = size - 1; y >= x; --y)
			tmp.push_back(now_map[size - 1 + x - y][y]);
		_new = check(tmp, who_going);
		i = 0;
		for (int y = size - 1; y >= x; --y)
			cross_map[size - 1 + x - y][y] += _new[i++];

	}
	return cross_map;
}


vector< vector<int> >	diagonal_right_up(vector< vector<int> > now_map, int size, int who_going, vector< vector<int> > cross_map){
	vector<int>  _new;
	int i;
	for (int x = 0; x < size ; ++x)
	{
		vector<int> tmp;
		for (int y = size - 1 - x; y <= size - 1; ++y)
			tmp.push_back(now_map[x - (size - 1 - y)][y]);

		_new = check(tmp, who_going);
		i = 0;
		for (int y = size - 1 - x; y <= size - 1; ++y)
			cross_map[x - (size - 1 - y)][y] += _new[i++];

	}
	for (int x = 1; x < size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y <= size - 1 - x; ++y)
			tmp.push_back(now_map[x+y][y]);

		_new = check(tmp, who_going);
		i = 0;
		for (int y = 0; y <= size - 1 - x; ++y)
			cross_map[x+y][y] += _new[i++];

	}
	return cross_map;
}


vector< vector<int> >	row(vector< vector<int> > now_map, int size, int who_going, vector< vector<int> > cross_map){
	vector<int>  _new;
	int i;
	for (int x = 0; x < size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y < size ; ++y)
			tmp.push_back(now_map[x][y]);
		_new = check(tmp, who_going);
		i = 0;
		for (int y = 0; y < size ; ++y)
			cross_map[x][y] += _new[i++];

	}
	return cross_map;

}

vector< vector<int> >	column(vector< vector<int> > now_map, int size, int who_going, vector< vector<int> > cross_map){
	vector<int>  _new;
	int i;
	for (int y = 0; y < size ; ++y)
	{
		vector<int> tmp;
		for (int x = 0; x < size ; ++x)
			tmp.push_back(now_map[x][y]);
		_new = check(tmp, who_going);
		i = 0;
		for (int x = 0; x < size ; ++x)
			cross_map[x][y] += _new[i++];
	}
	return cross_map;
}



int main()
{	
	vector< vector<int> > now_map;
	vector< vector<int> > cross_map;
	int size;
	now_map = read_from_file();
	cross_map = now_map;
	size = now_map.size();
	for (int x = 0; x < size; ++x)
		for (int y = 0; y < size; ++y)
			cross_map[x][y] = 0;

	printf("\n");
	_print(now_map);
	cross_map = column(now_map, size, 1, cross_map);
	cross_map = row(now_map, size, 1, cross_map);
	cross_map = diagonal_right_up(now_map, size, 1, cross_map);
	cross_map = diagonal_left_up(now_map, size, 1, cross_map);

	printf("\n");
	_print(cross_map);

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

vector<int>	check(vector<int>  tmp, int who_going){
	int num = 0;
	int left_i = -1;
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

	return _new;
}