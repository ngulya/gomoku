#include <bits/stdc++.h> 
# include <iostream>
# include <vector>
# include <iostream>
# include <stdlib.h>
# include <string>
# include <fstream>
# include <ctime>
using namespace std;

#define CAPTURE_NUM -2 
int NUM_NODE;

struct all_variants { 
	size_t num;
	int  _x, _y; 
};

struct numS { 
	int num_1;
	int num_2;
	int num_3;
	int num_4;
	int num_5; 
};

typedef struct			node
{
	vector<vector<int> >	map_in_node;
	vector<vector<int> >	cross_map;
	vector<vector<int> >	cross_map_not_you;
	vector<all_variants>	variants;
	vector<all_variants>	variants_capture;
	bool					win;
	size_t					alpha;
	size_t					beta;
	int 					AIcaptrue;
	int 					HUcaptrue;
	int 					sign_alpha;
	int 					sign_beta;
	int 					heuristics;
	int 					now_player;
	int 					other_player;
	int 					level_depth;
	int 					size;
	int						x;
	int						y;
	struct node*			parent;
	vector<struct node* >	nodes;
}	node;


bool compare_variants(all_variants i1, all_variants i2) 
{ 
	return (i1.num > i2.num); 
} 


vector<vector<int> >	read_from_file();
vector<int>				check_not_you(vector<int>  tmp, node *now_node);
vector<int>				check(vector<int>  tmp, node *now_node);
void					_print(	vector<vector<int> > the_vector);
void					diagonal_left_up(node *nde);
void					diagonal_right_up(node *nde);
void					row(node *nde);
void					column(node *nde);
int 					return_new_var(int tmp, int map);
void					_in_cross_maps(node *nde, int _X, int _Y, int _you, int _not_you);

void	most_best_variant(node *nde, int AI_PLAYER){
	int				tmp_map, tmp_map_not_you, for_tmp, youCap, otherCap;
	all_variants	tmpvar;

	// printf("most_best_variant\n");
	if (nde->now_player == AI_PLAYER){
		youCap = nde->AIcaptrue;
		otherCap = nde->HUcaptrue;
	}
	else{
		youCap = nde->HUcaptrue;	
		otherCap = nde->AIcaptrue;
	}
	// printf("you %d  other%d\n", youCap, otherCap);
	for (int x = 0; x < nde->size; ++x)
		for (int y = 0; y < nde->size; ++y){
			tmp_map_not_you = nde->cross_map_not_you[x][y];
			tmp_map = nde->cross_map[x][y];
			
			if (tmp_map < 0){
				tmp_map -= tmp_map;
				if (tmp_map < youCap)
					tmp_map = youCap;
			}
			if (tmp_map != 0){
				for_tmp = 1;
				while(tmp_map-- > 1)
					for_tmp *= 10;
				tmp_map = for_tmp + 1;
				if (youCap >= otherCap)
					tmp_map += 1;
			}
			// printf("x:%d y:%d %d %d\n",x, y,tmp_map, tmp_map_not_you );


			if (tmp_map_not_you < 0){
				tmp_map_not_you -= tmp_map_not_you;
				if (tmp_map_not_you < otherCap)
					tmp_map_not_you = otherCap;
			}
			if (tmp_map_not_you != 0){
				for_tmp = 1;
				while(tmp_map_not_you-- > 1)
					for_tmp *= 10;
				tmp_map_not_you = for_tmp;
				if (otherCap > youCap)
					tmp_map_not_you += 1;

			}
			if ((tmp_map + tmp_map_not_you) > 0){
				tmpvar.num = tmp_map + tmp_map_not_you;
				tmpvar._x = x;
				tmpvar._y = y;
				nde->variants.push_back(tmpvar);
			}		
			nde->cross_map[x][y] = tmp_map + tmp_map_not_you;
			// printf("%d\n", nde->cross_map[x][y]);
		}
	sort(nde->variants.begin(), nde->variants.end(), compare_variants);

	// for (int i = 0; i < nde->variants.size(); ++i)
	// {
	// 	printf("Sum %lu  x:%d y:%d\n", nde->variants[i].num, nde->variants[i]._x, nde->variants[i]._y);
	// }
}

bool	checkRules(int x, int y, int player){
	return true;
}



node *	create_node(node *parent, int x, int y, int AI_player){
	bool 	hasCap = false;
	node *child = new node;//create template width**depth 
	child->map_in_node = parent->map_in_node;
	child->map_in_node[x][y] = parent->now_player;
	child->size = child->map_in_node.size();
	child->x = x;
	child->y = y;

	if (y > 2 and child->map_in_node[x][y - 1] != 0 and child->map_in_node[x][y - 1] == child->map_in_node[x][y - 2] and child->map_in_node[x][y - 2] != parent->now_player and child->map_in_node[x][y - 3] == parent->now_player){
		child->map_in_node[x][y-1] = 0;
		child->map_in_node[x][y-2] = 0;
		hasCap = true;
	}//left
	if (y < (child->size - 3) and child->map_in_node[x][y + 1] != 0 and child->map_in_node[x][y + 1] == child->map_in_node[x][y + 2] and child->map_in_node[x][y + 2] != parent->now_player and child->map_in_node[x][y + 3] == parent->now_player){
		child->map_in_node[x][y+1] = 0;
		child->map_in_node[x][y+2] = 0;
		hasCap = true;
	}//right
	if (x > 2 and child->map_in_node[x-1][y] != 0 and child->map_in_node[x-1][y] == child->map_in_node[x-2][y] and child->map_in_node[x-2][y] != parent->now_player and child->map_in_node[x-3][y] == parent->now_player){
		child->map_in_node[x-1][y] = 0;
		child->map_in_node[x-2][y] = 0;
		hasCap = true;
	}//up
	if (x < (child->size - 3) and child->map_in_node[x+1][y] != 0 and child->map_in_node[x+1][y] == child->map_in_node[x+2][y] and child->map_in_node[x+2][y] != parent->now_player and child->map_in_node[x+3][y] == parent->now_player){
		child->map_in_node[x+1][y] = 0;
		child->map_in_node[x+2][y] = 0;
		hasCap = true;
	}//right

	if (x > 2 and y > 2 and child->map_in_node[x-1][y-1] != 0 and child->map_in_node[x-1][y-1] == child->map_in_node[x-2][y-2] and child->map_in_node[x-2][y-2] != parent->now_player and child->map_in_node[x-3][y-3] == parent->now_player){
		child->map_in_node[x-1][y-1] = 0;
		child->map_in_node[x-2][y-2] = 0;
		hasCap = true;
	}//left_up
	

	if (x < (child->size - 3) and y < (child->size - 3) and child->map_in_node[x+1][y+1] != 0 and child->map_in_node[x+1][y+1] == child->map_in_node[x+2][y+2] and child->map_in_node[x+2][y+2] != parent->now_player and child->map_in_node[x+3][y+3] == parent->now_player){
		child->map_in_node[x+1][y+1] = 0;
		child->map_in_node[x+2][y+2] = 0;
		hasCap = true;
	}//right down


	if (x > 2 and y < (child->size - 3) and child->map_in_node[x-1][y+1] != 0 and child->map_in_node[x-1][y+1] == child->map_in_node[x-2][y+2] and child->map_in_node[x-2][y+2] != parent->now_player and child->map_in_node[x-3][y+3] == parent->now_player){
		child->map_in_node[x-1][y+1] = 0;
		child->map_in_node[x-2][y+2] = 0;
		hasCap = true;
	}//right_up
	

	if (y > 2 and x < (child->size - 3) and child->map_in_node[x+1][y-1] != 0 and child->map_in_node[x+1][y-1] == child->map_in_node[x+2][y-2] and child->map_in_node[x+2][y-2] != parent->now_player and child->map_in_node[x+3][y-3] == parent->now_player){
		child->map_in_node[x+1][y-1] = 0;
		child->map_in_node[x+2][y-2] = 0;
		hasCap = true;
	}//left down

	child->AIcaptrue = parent->AIcaptrue;
	child->HUcaptrue = parent->HUcaptrue;

	if (hasCap){
		if (parent->now_player == AI_player)
			child->AIcaptrue += 1;
		else
			child->HUcaptrue += 1;
	}

	child->now_player = parent->other_player;
	child->other_player = parent->now_player;

	child->cross_map = child->map_in_node;
	child->level_depth = parent->level_depth + 1;
	child->win = false;
	for (int x = 0; x < child->size; ++x)
		for (int y = 0; y < child->size; ++y)
			child->cross_map[x][y] = 0;
	child->cross_map_not_you = child->cross_map;
	child->parent = parent;
	parent->nodes.push_back(child);
	return child;
}



int			return_heuristic(node *child, int AI_PLAYER){

	int 	sum = 0;
	int 	tmp_ai = 0;
	int 	tmp_rival = 0;
	vector<int> AI_player(5);
	vector<int> rival_player(5);
	for (int i = 0; i < 5; ++i)
	{
		AI_player[i] = 0;
		rival_player[i] = 0;
	}
	for (int i = 0; i < child->cross_map.size(); ++i){
		for (int j = 0; j < child->cross_map.size(); ++j){
			if (child->now_player == AI_PLAYER){
				tmp_ai = child->cross_map[i][j];
				tmp_rival = child->cross_map_not_you[i][j];
			}
			else{
				tmp_ai = child->cross_map_not_you[i][j];
				tmp_rival = child->cross_map[i][j];
			}

			tmp_ai = -tmp_ai ? tmp_ai < 0 : tmp_ai;
			tmp_rival = -tmp_rival ? tmp_rival < 0 : tmp_rival;

			if (tmp_ai > 0){
				if (tmp_ai > 5)
					AI_player[4] += 1;
				else
					AI_player[tmp_ai - 1] += 1;

			}
			if (tmp_rival > 0){
				if (tmp_rival > 5)
					rival_player[4] += 1;
				else
					rival_player[tmp_rival - 1] += 1;
			}
		}
	}

	if (child->AIcaptrue <= 5)
		AI_player[child->AIcaptrue - 1] += 1;

	if (child->HUcaptrue <= 5)
		rival_player[child->HUcaptrue - 1] += 1;

	for (int i = 0; i < 5; ++i)
		AI_player[i] = AI_player[i] - rival_player[i];
	sum = AI_player[0] +
	AI_player[1] * 15 + 
	AI_player[2] * 300 + 
	AI_player[3] * 6000 + 
	AI_player[4] * 1000000;
	if (child->now_player == AI_PLAYER){
		if (AI_player[4] > 0)
			child->win = true;
	}
	else{
		if (AI_player[4] < 0)
			child->win = true;
	}
	child->heuristics = sum;
	// printf("heuristics:%d\n", sum);
	return sum;
}

int this_win_finally(int x,int y, int AI_PLAYER, int *_x_cap , int *_y_cap){
	
	return 0;
	// if (x == 4 and y == 2 and AI_PLAYER == 1){
	// 	(*_x_cap) = 4;
	// 	(*_y_cap) = 1;
	// 	return 2;
	// }
	// return 0;
}


int 	choose_best_child(node *parent, bool maximizingPlayer){
	// printf("choose_best_child\n");
	int tmp_heur, tmpx, tmpy;
	int heur = parent->nodes[0]->heuristics;
	int x = parent->nodes[0]->x;
	int y = parent->nodes[0]->y;

	
	for (int i = 0; i < parent->nodes.size(); ++i){
		tmp_heur = parent->nodes[i]->heuristics;
		tmpx = parent->nodes[i]->x;
		tmpy = parent->nodes[i]->y;
		if (maximizingPlayer){
			if (tmp_heur > heur){
				heur = tmp_heur;
				x = tmpx;
				y = tmpy;
			}
		}
		else{
			if (tmp_heur < heur){
				heur = tmp_heur;
				x = tmpx;
				y = tmpy;
			}
		}
	}
	// printf("heur %d %d %d\n", heur, x, y);
	parent->heuristics = heur;
	if (parent->level_depth == 0){
		parent->x = x;
		parent->y = y;
	}
	return heur;
}

int		minimax(node *parent, int MAX_DEPTH ,int MAX_WIDTH, int AI_PLAYER, int alpha, int beta, bool maximizingPlayer, bool USE_OPTIMIZATION){
	// printf("minimax\n");
	node	*child_tmp;
	int		width = MAX_WIDTH;
	int		child_num = 0;
	int		value = 2147483000;
	int		result;
	if (maximizingPlayer)
		value = -2147483000;

	// printf("%d\n", parent->level_depth);
		
	row(parent);// if we have 2 free flangs its 2 point if 1 free flang - 1 point ?
	column(parent);
	diagonal_left_up(parent);
	diagonal_right_up(parent);
	// printf("\nparent->cross_map");
	// _print(parent->cross_map);
	// printf("\nparent->cross_map_not_you");
	// _print(parent->cross_map_not_you);
	// exit(1);
	NUM_NODE += 1;
	if (parent->level_depth == MAX_DEPTH)
		return return_heuristic(parent, AI_PLAYER);

	most_best_variant(parent, AI_PLAYER);
	for (int i = 0; i < parent->variants.size(); ++i){
		if (width > 0 and checkRules(parent->variants[i]._y, parent->variants[i]._x, parent->now_player)){
			int		_x_cap = -1;
			int		_y_cap = -1;
			int		res = this_win_finally(parent->variants[i]._x, parent->variants[i]._y, parent->now_player, &_x_cap, &_y_cap);
			// res ->  0==not win 1==finally win     2==win but can capture this
			// printf("VAR X%d VAR y%d\n", parent->variants[i]._x, parent->variants[i]._y);
			if (res == 1){
				if (maximizingPlayer)
					parent->heuristics = 200000000;
				else
					parent->heuristics = -200000000;
				parent->x = parent->variants[i]._x;
				parent->y = parent->variants[i]._y;
				return parent->heuristics;
			}
			else {
				child_tmp = create_node(parent, parent->variants[i]._x, parent->variants[i]._y, AI_PLAYER);
				// printf("x%d y%d\n", parent->variants[i]._x, parent->variants[i]._y);
				// printf("AI: %d    HU: %d\n", child_tmp->AIcaptrue, child_tmp->HUcaptrue);
				if (child_tmp->other_player == AI_PLAYER && child_tmp->AIcaptrue >= 5){
					// printf("AI win\n");
					// printf("maximizingPlayer %d\n", maximizingPlayer);
					// exit(1);
					parent->heuristics = 200000000;
					parent->x = parent->variants[i]._x;
					parent->y = parent->variants[i]._y;
					return parent->heuristics;
				}
				if (child_tmp->other_player != AI_PLAYER && child_tmp->HUcaptrue >= 5){
					// printf("HU win\n");
					// exit(1);
					parent->heuristics = -200000000;
					parent->x = parent->variants[i]._x;
					parent->y = parent->variants[i]._y;
					return parent->heuristics;
				}
				// exit(1);
				width--;
				// printf("\ndep = %d   x=%d y=%d\n\n", child_tmp->level_depth, parent->variants[i]._x, parent->variants[i]._y);
				// _print(child_tmp->map_in_node);
				if (res == 2){
					all_variants  tmpvar;
					tmpvar.num = 10000000000;
					tmpvar._x = _x_cap;
					tmpvar._y = _y_cap;
					child_tmp->variants.push_back(tmpvar);
					// printf("next must be   x:%d y:%x\n", _x_cap, _y_cap);
				}
				result = minimax(parent->nodes[child_num], MAX_DEPTH, MAX_WIDTH, AI_PLAYER, alpha, beta, !maximizingPlayer, USE_OPTIMIZATION);
				child_num += 1;

				if (maximizingPlayer){
					value = max(value, result);
					alpha = max(alpha, value);
				}
				else{
					value = min(value, result);
					beta = min(beta, value);
				}
				if (USE_OPTIMIZATION)
					if (alpha >= beta)
						break;
			}
		}
	}

	if (parent->nodes.size() <= 0)
		return parent->heuristics;
	return choose_best_child(parent, maximizingPlayer);
}

void	free_nodes(node *parent)
{
	if (parent->nodes.size() <= 0)
		return;
	for (int i = 0; i < parent->nodes.size(); ++i){
		free_nodes(parent->nodes[i]);
		delete parent->nodes[i];
	}
}

all_variants	_find_where_go(int AI_PLAYER, int MAX_DEPTH, int MAX_WIDTH, vector<vector<int> > map, bool USE_OPTIMIZATION, int AIcaptrue, int HUcaptrue){
	// ????????????????
	int 	OTHER_PLAYER = 2;
	// ????????????????
	// int 	OTHER_PLAYER = AI_PLAYER * -1;
	int 	alpha = -2147483000;
	int 	beta = 2147483000;
	all_variants ret;

	NUM_NODE = 0;
	node *first_node = new node;
	first_node->parent = nullptr;
	first_node->map_in_node = map;
	_print(first_node->map_in_node);
	first_node->AIcaptrue = AIcaptrue;
	first_node->HUcaptrue = HUcaptrue;

	first_node->size = first_node->map_in_node.size();
	first_node->level_depth = 0;
	first_node->x = -1;
	first_node->y = -1;
	first_node->now_player = AI_PLAYER;
	first_node->other_player = OTHER_PLAYER;
	first_node->win = false;
	first_node->cross_map = first_node->map_in_node;
	for (int x = 0; x < first_node->size; ++x)
		for (int y = 0; y < first_node->size; ++y)
			first_node->cross_map[x][y] = 0;
	first_node->cross_map_not_you = first_node->cross_map;
	minimax(first_node, MAX_DEPTH, MAX_WIDTH, AI_PLAYER, alpha, beta, true, USE_OPTIMIZATION);

	ret.num = NUM_NODE;
	ret._x = first_node->y;
	ret._y = first_node->x;


	free_nodes(first_node);
	delete first_node;

	return ret;
}

int main()
{	
	int 	MAX_DEPTH = 5;
	int 	MAX_WIDTH = 3;
	int 	AI_PLAYER = 1;
	int 	AIcaptrue = 4;
	int 	HUcaptrue = 0;
	bool 	USE_OPTIMIZATION = true;
	all_variants tmp;

	tmp = _find_where_go(AI_PLAYER, MAX_DEPTH, MAX_WIDTH, read_from_file(), USE_OPTIMIZATION, AIcaptrue, HUcaptrue);
	printf("%lu\n", tmp.num);
	printf("x:%d y:%d\n", tmp._y, tmp._x);
	return 0;
}






int 	return_new_var(int tmp, int map)
{
	if (tmp < 0)
	{
		if (map > 0)
			return min(tmp, -map);
		if (map < 0)
			return min(tmp, map);
		return tmp;
	}
	if (tmp > 0)
	{
		if (map > 0)
			return max(tmp, map);
		if (map < 0)
			return min(-tmp, map);
		return tmp;
	}
	return map;
}


void	_in_cross_maps(node *nde, int _X, int _Y, int _you, int _not_you)
{
	if (_you < 0){
		nde->cross_map_not_you[_X][_Y] = return_new_var(_you, nde->cross_map_not_you[_X][_Y]);
		_you = -1 * _you;
	}
	nde->cross_map[_X][_Y] = return_new_var(_you, nde->cross_map[_X][_Y]);

	if (_not_you < 0){
		nde->cross_map[_X][_Y] = return_new_var(_not_you, nde->cross_map[_X][_Y]);
		_not_you = -1 * _not_you;
	}
	nde->cross_map_not_you[_X][_Y] = return_new_var(_not_you, nde->cross_map_not_you[_X][_Y]);
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
			printf("%4d", the_vector[i][i2]);
		printf("\n");
	}
	
}


vector<int>	check_not_you(vector<int>  tmp, node *now_node){
	int num = 0;
	int left_i = -1;
	vector<int>  _new(tmp.size());

	for (int i = 0; i < tmp.size(); ++i){
		if (tmp[i] != 0 and tmp[i] != now_node->now_player)
		{
			if (i > 0 and tmp[i-1] == 0)
				left_i = i-1;
			num++;
		}
		else
		{
			if(num)
			{
				if (tmp[i] == 0){
					_new[i] = num > _new[i] ? num : _new[i];
					if (i > 2 and left_i == -1 and num == 2){//need for -1 1 1 0, if we have flang not our
						_new[i] = CAPTURE_NUM;
					} 
				}
				if (left_i != -1){
					_new[left_i] = num > _new[left_i] ? num : _new[left_i];
					if (tmp[i] != 0 and tmp[i] == now_node->now_player and num == 2){//need for 0 1 1 -1, if we have flang not our
						_new[left_i] = CAPTURE_NUM;
					}
				}
			}
			left_i = -1;
			num = 0;
		}
	}
	if(num and left_i != -1)
		_new[left_i] = num > _new[left_i] ? num : _new[left_i];
	return _new;
}

vector<int>	check(vector<int>  tmp, node *now_node){
	int num = 0;
	int left_i = -1;
	vector<int>  _new(tmp.size());



	for (int i = 0; i < tmp.size(); ++i){
		if (tmp[i] == now_node->now_player)
		{
			if (i > 0 and tmp[i-1] == 0)
				left_i = i-1;
			num++;
		}
		else
		{
			if(num)
			{
				if (tmp[i] == 0){
					_new[i] = num > _new[i] ? num : _new[i];
					if (i > 2 and left_i == -1 and num == 2){//need for -1 1 1 0, if we have flang not our
						_new[i] = CAPTURE_NUM;
					}
				}
				if (left_i != -1){
					_new[left_i] = num > _new[left_i] ? num : _new[left_i];
					if (tmp[i] != 0 and tmp[i] != now_node->now_player and num == 2){
						_new[left_i] = CAPTURE_NUM;
					}
				}
			}
			left_i = -1;
			num = 0;
		}
	}
	if(num and left_i != -1){
		_new[left_i] = num > _new[left_i] ? num : _new[left_i];;
	}
	return _new;
}


void	diagonal_left_up(node *nde){
	vector<int>		_you;
	vector<int>		_not_you;
	int 			i;

	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = x; y >= 0; --y)
			tmp.push_back(nde->map_in_node[x-y][y]);

		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int y = x; y >= 0; --y, i++)
			_in_cross_maps(nde, x-y, y, _you[i], _not_you[i]);

	}

	for (int x = 1; x < nde->size ; ++x)
	{

		vector<int> tmp;
		for (int y = nde->size - 1; y >= x; --y){
			// printf("%4d", nde->map_in_node[nde->size - 1 + x - y][y]);
			tmp.push_back(nde->map_in_node[nde->size - 1 + x - y][y]);
		}
		// printf("\n");
		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int y = nde->size - 1; y >= x; --y, i++)
			_in_cross_maps(nde, nde->size - 1 + x - y, y, _you[i], _not_you[i]);

	}
}


void	diagonal_right_up(node *nde){
	vector<int> 	_you;
	vector<int> 	_not_you;
	int				i;

	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = nde->size - 1 - x; y <= nde->size - 1; ++y)
			tmp.push_back(nde->map_in_node[x - (nde->size - 1 - y)][y]);

		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int y = nde->size - 1 - x; y <= nde->size - 1; ++y, i++)
			_in_cross_maps(nde,  x - (nde->size - 1 - y), y, _you[i], _not_you[i]);
	}

	for (int x = 1; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y <= nde->size - 1 - x; ++y)
			tmp.push_back(nde->map_in_node[x+y][y]);

		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int y = 0; y <= nde->size - 1 - x; ++y, i++)
			_in_cross_maps(nde, x+y, y, _you[i], _not_you[i]);
	}
}


void	row(node *nde){
	vector<int>		_you;
	vector<int>		_not_you;
	int 			i;
	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y < nde->size ; ++y)
			tmp.push_back(nde->map_in_node[x][y]);
		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int y = 0; y < nde->size ; ++y, i++)
			_in_cross_maps(nde, x, y, _you[i], _not_you[i]);
	}
}


void	column(node *nde){
	vector<int>		_not_you;
	vector<int>		_you;
	int				i;

	for (int y = 0; y < nde->size ; ++y)
	{
		vector<int> tmp;
		for (int x = 0; x < nde->size ; ++x)
			tmp.push_back(nde->map_in_node[x][y]);

		i = 0;
		_you = check(tmp, nde);
		_not_you = check_not_you(tmp, nde);
		for (int x = 0; x < nde->size ; ++x, i++){
			_in_cross_maps(nde, x, y, _you[i], _not_you[i]);
		}
	}
}
