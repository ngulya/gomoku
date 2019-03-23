// #include "class_tree.hpp"
// #include <bits/stdc++.h> 
# include <iostream>
# include <vector>
# include <iostream>
# include <stdlib.h>
# include <string>
# include <fstream>
using namespace std;


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
	bool					win;
	size_t					alpha;
	size_t					beta;
	
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
void					diagonal_left_up(node *nde, bool you);
void					diagonal_right_up(node *nde, bool you);
void					row(node *nde, bool you);
void					column(node *nde, bool you);
void					make_cross_map(node *parent);

void	most_best_variant(node *nde){
	int tmp_map, tmp_map_not_you, for_tmp;
	all_variants  tmpvar;
	for (int x = 0; x < nde->size; ++x)
		for (int y = 0; y < nde->size; ++y){
			tmp_map_not_you = nde->cross_map_not_you[x][y];
			tmp_map = nde->cross_map[x][y];
			// printf("x:%d y:%d %d %d\n",x, y,tmp_map, tmp_map_not_you );
			if (tmp_map != 0){
				for_tmp = 1;
				while(tmp_map-- > 1)
					for_tmp *= 10;
				tmp_map = for_tmp + 1;
			}
			if (tmp_map_not_you != 0){
				for_tmp = 1;
				while(tmp_map_not_you-- > 1)
					for_tmp *= 10;
				tmp_map_not_you = for_tmp;
			}
			if ((tmp_map + tmp_map_not_you) > 0){
				tmpvar.num = tmp_map + tmp_map_not_you;
				tmpvar._x = x;
				tmpvar._y = y;
				nde->variants.push_back(tmpvar);
			}		
			nde->cross_map[x][y] = tmp_map + tmp_map_not_you;
		}
			
	sort(nde->variants.begin(), nde->variants.end(), compare_variants);
}

bool	checkRules(int x, int y, int player){
	return true;
}



node *	create_node(node *parent, int x, int y){
	node *child = new node;//create template width**depth 
	child->map_in_node = parent->map_in_node;
	child->map_in_node[x][y] = parent->now_player;
	child->size = child->map_in_node.size();
	child->x = x;
	child->y = y;

	if (y > 2 and child->map_in_node[x][y - 1] != 0 and child->map_in_node[x][y - 1] == child->map_in_node[x][y - 2] and child->map_in_node[x][y - 2] != parent->now_player and child->map_in_node[x][y - 3] == parent->now_player){
		child->map_in_node[x][y-1] = 0;
		child->map_in_node[x][y-2] = 0;
	}//left
	if (y < (child->size - 3) and child->map_in_node[x][y + 1] != 0 and child->map_in_node[x][y + 1] == child->map_in_node[x][y + 2] and child->map_in_node[x][y + 2] != parent->now_player and child->map_in_node[x][y + 3] == parent->now_player){
		child->map_in_node[x][y+1] = 0;
		child->map_in_node[x][y+2] = 0;
	}//right
	if (x > 2 and child->map_in_node[x-1][y] != 0 and child->map_in_node[x-1][y] == child->map_in_node[x-2][y] and child->map_in_node[x-2][y] != parent->now_player and child->map_in_node[x-3][y] == parent->now_player){
		child->map_in_node[x-1][y] = 0;
		child->map_in_node[x-2][y] = 0;
	}//up
	if (x < (child->size - 3) and child->map_in_node[x+1][y] != 0 and child->map_in_node[x+1][y] == child->map_in_node[x+2][y] and child->map_in_node[x+2][y] != parent->now_player and child->map_in_node[x+3][y] == parent->now_player){
		child->map_in_node[x+1][y] = 0;
		child->map_in_node[x+2][y] = 0;
	}//right

	if (x > 2 and y > 2 and child->map_in_node[x-1][y-1] != 0 and child->map_in_node[x-1][y-1] == child->map_in_node[x-2][y-2] and child->map_in_node[x-2][y-2] != parent->now_player and child->map_in_node[x-3][y-3] == parent->now_player){
		child->map_in_node[x-1][y-1] = 0;
		child->map_in_node[x-2][y-2] = 0;
	}//left_up
	

	if (x < (child->size - 3) and y < (child->size - 3) and child->map_in_node[x+1][y+1] != 0 and child->map_in_node[x+1][y+1] == child->map_in_node[x+2][y+2] and child->map_in_node[x+2][y+2] != parent->now_player and child->map_in_node[x+3][y+3] == parent->now_player){
		child->map_in_node[x+1][y+1] = 0;
		child->map_in_node[x+2][y+2] = 0;
	}//right down


	if (x > 2 and y < (child->size - 3) and child->map_in_node[x-1][y+1] != 0 and child->map_in_node[x-1][y+1] == child->map_in_node[x-2][y+2] and child->map_in_node[x-2][y+2] != parent->now_player and child->map_in_node[x-3][y+3] == parent->now_player){
		child->map_in_node[x-1][y+1] = 0;
		child->map_in_node[x-2][y+2] = 0;
	}//right_up
	

	if (y > 2 and x < (child->size - 3) and child->map_in_node[x+1][y-1] != 0 and child->map_in_node[x+1][y-1] == child->map_in_node[x+2][y-2] and child->map_in_node[x+2][y-2] != parent->now_player and child->map_in_node[x+3][y-3] == parent->now_player){
		child->map_in_node[x+1][y-1] = 0;
		child->map_in_node[x+2][y-2] = 0;
	}//left down
	

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
	printf("heuristics:%d\n", sum);
	return sum;
}

int this_win_finally(int x,int y, int AI_PLAYER, int *_x_cap , int *_y_cap){
	
	return 0;
	if (x == 4 and y == 2 and AI_PLAYER == 1){
		(*_x_cap) = 4;
		(*_y_cap) = 1;
		return 2;
	}
	return 0;
}
void	make_cross_map(node *parent){
	row(parent, false);// if we have 2 free flangs its 2 point if 1 free flang - 1 point ?
	row(parent, true);
	column(parent, false);
	column(parent, true);
	diagonal_right_up(parent, false);
	diagonal_right_up(parent, true);
	diagonal_left_up(parent, false);
	diagonal_left_up(parent, true);
}

int 	choose_best_child(node *parent, bool maximizingPlayer){
	printf("choose_best_child\n");
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

int		minimax(node *parent, int MAX_DEPTH ,int MAX_WIDTH, int AI_PLAYER, int alpha, int beta, bool maximizingPlayer){
	printf("minimax\n");
	node	*child_tmp;
	int		width = MAX_WIDTH;
	int		child_num = 0;
	int		value = 2147483000;
	int		result;
	if (maximizingPlayer)
		value = -2147483000;

	make_cross_map(parent);

	if (parent->level_depth == MAX_DEPTH)
		return return_heuristic(parent, AI_PLAYER);

	most_best_variant(parent);
	for (int i = 0; i < parent->variants.size(); ++i){
		if (width > 0 and checkRules(parent->variants[i]._y, parent->variants[i]._x, parent->now_player)){
			int		_x_cap = -1;
			int		_y_cap = -1;
			int		res = this_win_finally(parent->variants[i]._x, parent->variants[i]._y, parent->now_player, &_x_cap, &_y_cap);
			// res ->  0==not win 1==finally win     2==win but can capture this
			
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
				child_tmp = create_node(parent, parent->variants[i]._x, parent->variants[i]._y);
				width--;
				printf("\ndep = %d   x=%d y=%d\n\n", child_tmp->level_depth, parent->variants[i]._x, parent->variants[i]._y);
				_print(child_tmp->map_in_node);
				if (res == 2){
					all_variants  tmpvar;
					tmpvar.num = 10000000000;
					tmpvar._x = _x_cap;
					tmpvar._y = _y_cap;
					child_tmp->variants.push_back(tmpvar);
					printf("next must be   x:%d y:%x\n", _x_cap, _y_cap);
				}
				result = minimax(parent->nodes[child_num], MAX_DEPTH, MAX_WIDTH, AI_PLAYER, alpha, beta, !maximizingPlayer);
				child_num += 1;

				if (maximizingPlayer){
					value = max(value, result);
					alpha = max(alpha, value);
				}
				else{
					value = min(value, result);
					beta = min(beta, value);
				}
				if (alpha >= beta){
					printf("\n\nIT'S  WORK  alpha %d beta %d\n\n", alpha, beta);
					// exit(1);
					break;
				}
			}
		}
	}

	if (parent->nodes.size() <= 0)
		return parent->heuristics;
	return choose_best_child(parent, maximizingPlayer);
}

void	_find_where_go(){
	int MAX_DEPTH = 2;
	int MAX_WIDTH = 2;
	int AI_PLAYER = 1;// AI player
	int OTHER_PLAYER = 2;
	int alpha = -2147483000;
	int beta = 2147483000;

	node *first_node = new node;

	first_node->parent = nullptr;
	first_node->map_in_node = read_from_file();
	_print(first_node->map_in_node);
	// printf("---\n");
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
	minimax(first_node, MAX_DEPTH, MAX_WIDTH, AI_PLAYER, alpha, beta, true);
	printf("%d\n", first_node->heuristics);
	printf("x:%d y:%d\n", first_node->x, first_node->y);

	// make_cross_map(first_node);
	// return_heuristic(first_node, AI_PLAYER);


	// _print(first_node->cross_map);
	// _print(first_node->cross_map_not_you);

	// size_t 	sum = 0;
	// vector<int> how_many_nums(5);
	// iterate_all_variants(first_node, how_many_nums);

	// sum = how_many_nums[0] + how_many_nums[1] * 30 + 
	// how_many_nums[2]*300 + how_many_nums[3]*10000 + 
	// how_many_nums[4]*10000000;
	// printf("%lu\n", sum);
	///////////////
	// row(first_node, false);// if we have 2 free flangs its 2 point if 1 free flang - 1 point ?
	// row(first_node, true);
	// column(first_node, false);
	// column(first_node, true);
	// diagonal_right_up(first_node, false);
	// diagonal_right_up(first_node, true);
	// diagonal_left_up(first_node, false);
	// diagonal_left_up(first_node, true);
	// _print(first_node->cross_map);
	// _print(first_node->cross_map_not_you);
	///////////////
	
}

int main()
{	
	_find_where_go();
	return 0;
}














// void	minimax(node *parent, int MAX_DEPTH ,int MAX_WIDTH, int AI_PLAYER){
// 	printf("minimax\n");
// 	node *child_tmp;
// 	int width = MAX_WIDTH;
// 	make_cross_map(parent);
// 	if (parent->level_depth == MAX_DEPTH){
// 		return_heuristic(parent, AI_PLAYER);
// 		printf("return_heuristic %lu\n", parent->heuristics);
// 		return;
// 	}
// 	most_best_variant(parent);

// 	for (int i = 0; i < parent->variants.size(); ++i){
// 		if (width > 0 and checkRules(parent->variants[i]._y, parent->variants[i]._x, parent->now_player)){
// 			int _x_cap = -1;
// 			int _y_cap = -1;
// 			int res = this_win_finally(parent->variants[i]._x, parent->variants[i]._y, parent->now_player, &_x_cap, &_y_cap);

// 			// res == 0  not win
// 			// res == 1  finally win
// 			// res == 2  win but can capture this
			
// 			if (res == 1){
// 				// printf("FINALYY\n");
// 				if (parent->now_player == AI_PLAYER)
// 					parent->heuristics = 200000000;
// 				else
// 					parent->heuristics = -200000000;
// 				parent->x = parent->variants[i]._x;
// 				parent->y = parent->variants[i]._y;
// 				return;
// 			}
// 			else {
// 				child_tmp = create_node(parent, parent->variants[i]._x, parent->variants[i]._y);
// 				width--;
// 				printf("\ndep = %d   x=%d y=%d\n\n", child_tmp->level_depth, parent->variants[i]._x, parent->variants[i]._y);
// 				_print(child_tmp->map_in_node);
// 				if (res == 2){
// 					all_variants  tmpvar;
// 					tmpvar.num = 10000000000;
// 					tmpvar._x = _x_cap;
// 					tmpvar._y = _y_cap;
// 					child_tmp->variants.push_back(tmpvar);
// 					printf("next must be   x:%d y:%x\n", _x_cap, _y_cap);
// 				}
// 			}
// 		}
// 	}
// 	// exit(1);
// 	for (int i = 0; i < parent->nodes.size(); ++i){
// 		printf("in parent child num %d\n", i);
// 		// _print(parent->nodes[i]->map_in_node);
// 		minimax(parent->nodes[i], MAX_DEPTH, MAX_WIDTH, AI_PLAYER);
// 	}
// 	printf("----\n");
// 	bool maximaze = true;
// 	int limit_tmp, tmpx, tmpy;
// 	int limit = parent->nodes[0]->heuristics;
// 	int x = parent->nodes[0]->x;
// 	int y = parent->nodes[0]->y;


// 	if (parent->now_player == AI_PLAYER)
// 		maximaze = false;
// 	// printf("find maxH\n");
// 	for (int i = 0; i < parent->nodes.size(); ++i){
// 		// check have we heuristics
// 		limit_tmp = parent->nodes[i]->heuristics;
// 		tmpx = parent->nodes[i]->x;
// 		tmpy = parent->nodes[i]->y;
// 		if (maximaze){
// 			if (limit_tmp > limit){
// 				limit = limit_tmp;
// 				x = tmpx;
// 				y = tmpy;
// 			}
// 		}
// 		else{
// 			if (limit_tmp < limit){
// 				limit = limit_tmp;
// 				x = tmpx;
// 				y = tmpy;
// 			}
// 		}
// 	}
// 	// printf("limit %d %d %d\n", limit, x, y);
// 	parent->heuristics = limit;
// 	if (parent->level_depth == 0){
// 		parent->x = x;
// 		parent->y = y;
// 	}
// }







































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
					_new[i] = num;
					if (i > 2 and left_i == -1 and num == 2){//need for -1 1 1 0, if we have flang not our
						_new[i] = -3;
					} 
				}
				if (left_i != -1){
					_new[left_i] = num;
					if (tmp[i] != 0 and tmp[i] == now_node->now_player and num == 2){//need for 0 1 1 -1, if we have flang not our
						_new[left_i] = -3;
					}
				}
			}
			left_i = -1;
			num = 0;
		}
	}
	if(num and left_i != -1)
		_new[left_i] = num;
	return _new;
}

vector<int>	check(vector<int>  tmp, node *now_node){
	int num = 0;
	int left_i = -1;
	vector<int>  _new(tmp.size());

	// printf("\nuold:\n");
	// for (int i = 0; i < tmp.size(); ++i)
	// {
	// 	printf("%d ", tmp[i]);
	// }
	// printf("\n");
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
					_new[i] = num;
					if (i > 2 and left_i == -1 and num == 2){//need for -1 1 1 0, if we have flang not our
						_new[i] = -3;
					}
				}
				if (left_i != -1){
					_new[left_i] = num;
					if (tmp[i] != 0 and tmp[i] != now_node->now_player and num == 2){
						_new[left_i] = -3;
					}
				}
			}
			left_i = -1;
			num = 0;
		}
	}

	if(num and left_i != -1){
		_new[left_i] = num;
	}
	// for (int i = 0; i < tmp.size(); ++i)
	// {
	// 	printf("%d ", _new[i]);
	// }
	// printf("\n");
	return _new;
}


void	diagonal_left_up(node *nde, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = x; y >= 0; --y)
			tmp.push_back(nde->map_in_node[x-y][y]);
		i = 0;
		if (you){
			_new = check(tmp, nde);

			for (int y = x; y >= 0; --y, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[x-y][y] = -_new[i] > nde->cross_map_not_you[x-y][y] ? -_new[i] : nde->cross_map_not_you[x-y][y];
					_new[i] = 2;
				}
				nde->cross_map[x-y][y] = _new[i] > nde->cross_map[x-y][y] ? _new[i] : nde->cross_map[x-y][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int y = x; y >= 0; --y, i++){
				if (_new[i] == -3){
					nde->cross_map[x-y][y] = -_new[i] > nde->cross_map[x-y][y] ? -_new[i] : nde->cross_map[x-y][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[x-y][y] = _new[i] > nde->cross_map_not_you[x-y][y] ? _new[i] : nde->cross_map_not_you[x-y][y];
			}
		}
	}

	for (int x = 1; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = nde->size - 1; y >= x; --y)
			tmp.push_back(nde->map_in_node[nde->size - 1 + x - y][y]);

		i = 0;
		if (you){
			_new = check(tmp, nde);
			for (int y = nde->size - 1; y >= x; --y, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[nde->size - 1 + x - y][y] = -_new[i] > nde->cross_map_not_you[nde->size - 1 + x - y][y] ? -_new[i] : nde->cross_map_not_you[nde->size - 1 + x - y][y];
					_new[i] = 2;
				}
				nde->cross_map[nde->size - 1 + x - y][y] = _new[i] > nde->cross_map[nde->size - 1 + x - y][y] ? _new[i] : nde->cross_map[nde->size - 1 + x - y][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int y = nde->size - 1; y >= x; --y, i++){
				if (_new[i] == -3){
					nde->cross_map[nde->size - 1 + x - y][y] = -_new[i] > nde->cross_map[nde->size - 1 + x - y][y] ? -_new[i] : nde->cross_map[nde->size - 1 + x - y][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[nde->size - 1 + x - y][y] = _new[i] > nde->cross_map_not_you[nde->size - 1 + x - y][y] ? _new[i] : nde->cross_map_not_you[nde->size - 1 + x - y][y];
			}
		}

	}
}


void	diagonal_right_up(node *nde, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = nde->size - 1 - x; y <= nde->size - 1; ++y)
			tmp.push_back(nde->map_in_node[x - (nde->size - 1 - y)][y]);

		i = 0;
		if (you){
			_new = check(tmp, nde);
			for (int y = nde->size - 1 - x; y <= nde->size - 1; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[x - (nde->size - 1 - y)][y] = -_new[i] > nde->cross_map_not_you[x - (nde->size - 1 - y)][y] ? -_new[i] : nde->cross_map_not_you[x - (nde->size - 1 - y)][y];
					_new[i] = 2;
				}
				nde->cross_map[x - (nde->size - 1 - y)][y] = _new[i] > nde->cross_map[x - (nde->size - 1 - y)][y] ? _new[i] : nde->cross_map[x - (nde->size - 1 - y)][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int y = nde->size - 1 - x; y <= nde->size - 1; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map[x - (nde->size - 1 - y)][y] = -_new[i] > nde->cross_map[x - (nde->size - 1 - y)][y] ? -_new[i] : nde->cross_map[x - (nde->size - 1 - y)][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[x - (nde->size - 1 - y)][y] = _new[i] > nde->cross_map_not_you[x - (nde->size - 1 - y)][y] ? _new[i] : nde->cross_map_not_you[x - (nde->size - 1 - y)][y];
			}
		}

	}
	for (int x = 1; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y <= nde->size - 1 - x; ++y)
			tmp.push_back(nde->map_in_node[x+y][y]);
		i = 0;
		if (you){
			_new = check(tmp, nde);
			for (int y = 0; y <= nde->size - 1 - x; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[x+y][y] = -_new[i] > nde->cross_map_not_you[x+y][y] ? -_new[i] : nde->cross_map_not_you[x+y][y];
					_new[i] = 2;
				}
				nde->cross_map[x+y][y] = _new[i] > nde->cross_map[x+y][y] ? _new[i] : nde->cross_map[x+y][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int y = 0; y <= nde->size - 1 - x; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map[x+y][y] = -_new[i] > nde->cross_map[x+y][y] ? -_new[i] : nde->cross_map[x+y][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[x+y][y] = _new[i] > nde->cross_map_not_you[x+y][y] ? _new[i] : nde->cross_map_not_you[x+y][y];
			}
		}
	}
}


void	row(node *nde, bool you){
	vector<int>  _new;
	int i;
	for (int x = 0; x < nde->size ; ++x)
	{
		vector<int> tmp;
		for (int y = 0; y < nde->size ; ++y)
			tmp.push_back(nde->map_in_node[x][y]);
		
		i = 0;
		if (you){
			_new = check(tmp, nde);
			for (int y = 0; y < nde->size ; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[x][y] = -_new[i] > nde->cross_map_not_you[x][y] ? -_new[i] : nde->cross_map_not_you[x][y];
					_new[i] = 2;
				}
				nde->cross_map[x][y] = _new[i] > nde->cross_map[x][y] ? _new[i] : nde->cross_map[x][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int y = 0; y < nde->size ; ++y, i++){
				if (_new[i] == -3){
					nde->cross_map[x][y] = -_new[i] > nde->cross_map[x][y] ? -_new[i] : nde->cross_map[x][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[x][y] = _new[i] > nde->cross_map_not_you[x][y] ? _new[i] : nde->cross_map_not_you[x][y];
			}
		}

	}
}


void	column(node *nde, bool you){
	vector<int>  _new;
	int i;
	for (int y = 0; y < nde->size ; ++y)
	{
		vector<int> tmp;
		for (int x = 0; x < nde->size ; ++x)
			tmp.push_back(nde->map_in_node[x][y]);
		i = 0;
		if (you){
			_new = check(tmp, nde);
			for (int x = 0; x < nde->size ; ++x, i++){
				if (_new[i] == -3){
					nde->cross_map_not_you[x][y] = -_new[i] > nde->cross_map_not_you[x][y] ? -_new[i] : nde->cross_map_not_you[x][y];
					_new[i] = 2;
				}
				nde->cross_map[x][y] = _new[i] > nde->cross_map[x][y] ? _new[i] : nde->cross_map[x][y];
			}
		}
		else{
			_new = check_not_you(tmp, nde);
			for (int x = 0; x < nde->size ; ++x, i++){
				if (_new[i] == -3){
					nde->cross_map[x][y] = -_new[i] > nde->cross_map[x][y] ? -_new[i] : nde->cross_map[x][y];
					_new[i] = 2;
				}
				nde->cross_map_not_you[x][y] = _new[i] > nde->cross_map_not_you[x][y] ? _new[i] : nde->cross_map_not_you[x][y];
			}
		}
	}
}





