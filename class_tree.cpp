#include "class_tree.hpp"

Tree::Tree(){
	read_from_file();
	size_map = start_map.size();
	_print(start_map);

	first_node = new node;
	first_node->who_going = 1;
	first_node->level_depth = 0;
	first_node->map_in_node = start_map;
	first_node->cross_map = start_map;

	for (int x = 0; x < size_map; ++x)
		for (int y = 0; y < size_map; ++y)
			first_node->cross_map[x][y] = 0;
	_print(first_node->cross_map);
	return;
}

Tree::~Tree(void){
	return;
}


// vector< vector<int> >	diagonal_left_up(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);
// vector< vector<int> >	diagonal_right_up(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going);
vector< vector<int> >	Tree::column(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going){
	vector<int>  _new;
	int i;
	vector<int>  nums_vector(5);
	for (int y = 0; y < size ; ++y)
	{
		vector<int> tmp;
		for (int x = 0; x < size ; ++x)
			tmp.push_back(now_map[x][y]);
		_new = check(tmp, who_going, nums_vector);
		i = 0;
		for (int x = 0; x < size ; ++x)
			cross_map[x][y] += _new[i++];
	}
	return cross_map;
}

vector< vector<int> >	Tree::row(vector< vector<int> > now_map, vector< vector<int> > cross_map, int who_going){
	vector<int>  _new;
	int i;
	vector<int>  nums_vector(5);
	for (int x = 0; x < size_map ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y < size_map ; ++y)
			tmp.push_back(now_map[x][y]);
		_new = check(tmp, who_going, nums_vector);
		i = 0;
		for (int y = 0; y < size_map ; ++y)
			cross_map[x][y] += _new[i++];

	}
	return cross_map;

}


vector<int>	check(vector<int>  tmp, int who_going, vector<int>  nums_vector){
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
				if (num <= 5)
					nums_vector[num - 1] += 1;
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
			nums_vector[num - 1] += 1;
		_new[left_i] += num;
	}
	printf("[[[num_1 = %d\n", nums_vector[0]);

	return _new;
}

void 	Tree::_print(	vector<vector<int> > the_vector){
	printf("\n");
	for (int i = 0; i < size_map; ++i)
	{
		printf("%d| ", i);
		for (int i2 = 0; i2 < size_map; ++i2)
			printf("%2d", the_vector[i][i2]);
		printf("\n");
	}
	
}


void Tree::read_from_file(){
	string s;
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
		start_map.push_back(tmp);

	}
	file.close();
}


// void	TreeOnTheHeap(int w, int h, std::string n)
// {
// 	Tree* 	p = new Tree(w, h, n);
// 	std::cout<<"TreeOnTheHeap"<<std::endl;
// 	(*p).name_Tree();
// 	(*p).w_h_Tree();
// 	delete p;
// }