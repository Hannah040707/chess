#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define X 9
#define Y 10
struct piece
{
	int id;//原id
	int x;//原座標
	int y;
};
struct position
{
	int x;//移動後座標
	int y;
	int score;//分數
};
int main(int n, char** arvg)
{
	int chess[X][Y] = { 0 };
	//---讀取裁判指令---
	int order;
	if (n >= 2) order = atoi(arvg[1]);
	//cout << "order:" << order << endl;
	//---讀取 table ----
	ifstream tablefile("table.txt");
	int i, j;
	for (i = 0; i < Y; i++)
		for (j = 0; j < X; j++)
			tablefile >> chess[j][i];
	tablefile.close();
	for (i = 0; i < Y; i++)
	{
		for (j = 0; j < X; j++)
			cout << setw(4) << chess[j][i];
		cout << endl;
	}
	//---決定下哪一步---
		//---確定棋子位置---
	struct piece pieces[16] = { 0 };
	int m = 0;
	for (i = 0; i < X; i++)
		for (j = 0; j < Y; j++)
		{
			if (chess[i][j] >= 0)
			{
				if (order == 0)
				{
					if (chess[i][j] < 100)
					{
						pieces[m].id = chess[i][j];
						pieces[m].x = i;
						pieces[m].y = j;
						m++;
					}
				}
				else if (order == 1)
				{
					if (chess[i][j] >= 100)
					{
						pieces[m].id = chess[i][j];
						pieces[m].x = i;
						pieces[m].y = j;
						m++;
					}
				}
			}
		}
	//---選擇最佳一步---
	int t;
	int u1, u2, d1, d2, r1, r2, l1, l2;//往上下左右步數
	int h1 = 0, h2 = 0, h3 = 0, h4 = 0, v1 = 0, v2 = 0, v3 = 0, v4 = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	struct position candidation[116][19] = { {10} };
	for (i = 0; i < m; i++)
	{
		t = 0;
		u1 = pieces[i].y + 1;//往上1
		u2 = pieces[i].y + 2;//往上2
		d1 = pieces[i].y - 1;//往下1
		d2 = pieces[i].y - 2;//往下2
		r1 = pieces[i].x + 1;//往右1
		r2 = pieces[i].x + 2;//往右2
		l1 = pieces[i].x - 1;//往左1
		l2 = pieces[i].x - 2;//往左2
		switch (pieces[i].id)
		{
		case 0://將
			if ((chess[pieces[i].x][u1] == -1 || chess[pieces[i].x][u1] >= 100) && (u1 <= 2))//原位置往下
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = u1;
				if (chess[pieces[i].x][u1] == 105 || chess[pieces[i].x][u1] == 106)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[pieces[i].x][u1] == 107 || chess[pieces[i].x][u1] == 108)candidation[pieces[i].id][t].score = 88;
				if (chess[pieces[i].x][u1] == 109 || chess[pieces[i].x][u1] == 110)candidation[pieces[i].id][t].score = 89;
				if (chess[pieces[i].x][u1] == 111 || chess[pieces[i].x][u1] == 112 || chess[pieces[i].x][u1] == 113 || chess[pieces[i].x][u1] == 114 || chess[pieces[i].x][u1] == 115)candidation[pieces[i].id][t].score = 98;
				if (chess[pieces[i].x][u1] == -1)candidation[pieces[i].id][t].score = 1;
				t++;
			}
			if ((chess[pieces[i].x][d1] == -1 || chess[pieces[i].x][d1] >= 100) && (d1 >= 0))//原位置往上
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = d1;
				if (chess[pieces[i].x][d1] == 105 || chess[pieces[i].x][d1] == 106)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[pieces[i].x][d1] == 107 || chess[pieces[i].x][d1] == 108)candidation[pieces[i].id][t].score = 88;
				if (chess[pieces[i].x][d1] == 109 || chess[pieces[i].x][d1] == 110)candidation[pieces[i].id][t].score = 89;
				if (chess[pieces[i].x][d1] == 111 || chess[pieces[i].x][d1] == 112 || chess[pieces[i].x][d1] == 113 || chess[pieces[i].x][d1] == 114 || chess[pieces[i].x][d1] == 115)candidation[pieces[i].id][t].score = 98;
				if (chess[pieces[i].x][d1] == -1)candidation[pieces[i].id][t].score = 2;
				t++;
			}
			if ((chess[r1][pieces[i].y] == -1 || chess[r1][pieces[i].y] >= 100) && (r1 <= 5))//原位置往右
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = pieces[i].y;
				if (chess[r1][pieces[i].y] == 105 || chess[r1][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[r1][pieces[i].y] == 107 || chess[r1][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 88;
				if (chess[r1][pieces[i].y] == 109 || chess[r1][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 89;
				if (chess[r1][pieces[i].y] == 111 || chess[r1][pieces[i].y] == 112 || chess[r1][pieces[i].y] == 113 || chess[r1][pieces[i].y] == 114 || chess[r1][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 98;
				if (chess[r1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 4;
				t++;
			}
			if ((chess[l1][pieces[i].y] == -1 || chess[l1][pieces[i].y] >= 100) && (l1 >= 3))//原位置往左
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = pieces[i].y;
				if (chess[l1][pieces[i].y] == 105 || chess[l1][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[l1][pieces[i].y] == 107 || chess[l1][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 88;
				if (chess[l1][pieces[i].y] == 109 || chess[l1][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 89;
				if (chess[l1][pieces[i].y] == 111 || chess[l1][pieces[i].y] == 112 || chess[l1][pieces[i].y] == 113 || chess[l1][pieces[i].y] == 114 || chess[l1][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 98;
				if (chess[l1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 3;
				t++;
			}
			break;
		case 1:case 2://仕
			if ((chess[l1][d1] == -1 || chess[l1][d1] >= 100) && (l1 >= 3) && (d1 >= 0))//原位置往左上
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = d1;
				if (chess[l1][d1] == 105 || chess[l1][d1] == 106)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[l1][d1] == 107 || chess[l1][d1] == 108)candidation[pieces[i].id][t].score = 78;
				if (chess[l1][d1] == 109 || chess[l1][d1] == 110)candidation[pieces[i].id][t].score = 84;
				if (chess[l1][d1] == 111 || chess[l1][d1] == 112 || chess[l1][d1] == 113 || chess[l1][d1] == 114 || chess[l1][d1] == 115)candidation[pieces[i].id][t].score = 74;
				if (chess[l1][d1] == -1)candidation[pieces[i].id][t].score = 8;
				t++;
			}
			if ((chess[r1][d1] == -1 || chess[r1][d1] >= 100) && (r1 <= 5) && (d1 >= 0))//原位置往右上
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = d1;
				if (chess[r1][d1] == 105 || chess[r1][d1] == 106)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[r1][d1] == 107 || chess[r1][d1] == 108)candidation[pieces[i].id][t].score = 78;
				if (chess[r1][d1] == 109 || chess[r1][d1] == 110)candidation[pieces[i].id][t].score = 84;
				if (chess[r1][d1] == 111 || chess[r1][d1] == 112 || chess[r1][d1] == 113 || chess[r1][d1] == 114 || chess[r1][d1] == 115)candidation[pieces[i].id][t].score = 74;
				if (chess[r1][d1] == -1)candidation[pieces[i].id][t].score = 7;
				t++;
			}
			if ((chess[l1][u1] == -1 || chess[l1][u1] >= 100) && (l1 >= 3) && (u1 <= 2))//原位置往左下
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = u1;
				if (chess[l1][u1] == 105 || chess[l1][u1] == 106)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[l1][u1] == 107 || chess[l1][u1] == 108)candidation[pieces[i].id][t].score = 78;
				if (chess[l1][u1] == 109 || chess[l1][u1] == 110)candidation[pieces[i].id][t].score = 84;
				if (chess[l1][u1] == 111 || chess[l1][u1] == 112 || chess[l1][u1] == 113 || chess[l1][u1] == 114 || chess[l1][u1] == 115)candidation[pieces[i].id][t].score = 74;
				if (chess[l1][u1] == -1)candidation[pieces[i].id][t].score = 6;
				t++;
			}
			if ((chess[r1][u1] == -1 || chess[r1][u1] >= 100) && (r1 <= 5) && (u1 >= 0))//原位置往右下
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = u1;
				if (chess[r1][u1] == 105 || chess[r1][u1] == 106)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[r1][u1] == 107 || chess[r1][u1] == 108)candidation[pieces[i].id][t].score = 78;
				if (chess[r1][u1] == 109 || chess[r1][u1] == 110)candidation[pieces[i].id][t].score = 84;
				if (chess[r1][u1] == 111 || chess[r1][u1] == 112 || chess[r1][u1] == 113 || chess[r1][u1] == 114 || chess[r1][u1] == 115)candidation[pieces[i].id][t].score = 74;
				if (chess[r1][u1] == -1)candidation[pieces[i].id][t].score = 5;
				t++;
			}
			break;
		case 3:case 4://相
			if ((chess[l2][d2] == -1 || chess[l2][d2] >= 100) && (chess[l1][d1] == -1) && (l2 >= 0) && (d2 >= 0))//原位置往左上
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = d2;
				if (chess[l2][d2] == 105 || chess[l2][d2] == 106)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[l2][d2] == 107 || chess[l2][d2] == 108)candidation[pieces[i].id][t].score = 81;
				if (chess[l2][d2] == 109 || chess[l2][d2] == 110)candidation[pieces[i].id][t].score = 75;
				if (chess[l2][d2] == 111 || chess[l2][d2] == 112 || chess[l2][d2] == 113 || chess[l2][d2] == 114 || chess[l2][d2] == 115)candidation[pieces[i].id][t].score = 71;
				if (chess[l2][d2] == -1)candidation[pieces[i].id][t].score = 12;
				t++;
			}
			if ((chess[r2][d2] == -1 || chess[r2][d2] >= 100) && (chess[r1][d1] == -1) && (r2 <= 8) && (d2 >= 0))//原位置往右上
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = d2;
				if (chess[r2][d2] == 105 || chess[r2][d2] == 106)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[r2][d2] == 107 || chess[r2][d2] == 108)candidation[pieces[i].id][t].score = 81;
				if (chess[r2][d2] == 109 || chess[r2][d2] == 110)candidation[pieces[i].id][t].score = 75;
				if (chess[r2][d2] == 111 || chess[r2][d2] == 112 || chess[r2][d2] == 113 || chess[r2][d2] == 114 || chess[r2][d2] == 115)candidation[pieces[i].id][t].score = 71;
				if (chess[r2][d2] == -1)candidation[pieces[i].id][t].score = 11;
				t++;
			}
			if ((chess[r2][u2] == -1 || chess[r2][u2] >= 100) && (chess[r1][u1] == -1) && (r2 <= 8) && (u2 <= 4))//原位置往右下
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = u2;
				if (chess[r2][u2] == 105 || chess[r2][u2] == 106)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[r2][u2] == 107 || chess[r2][u2] == 108)candidation[pieces[i].id][t].score = 81;
				if (chess[r2][u2] == 109 || chess[r2][u2] == 110)candidation[pieces[i].id][t].score = 75;
				if (chess[r2][u2] == 111 || chess[r2][u2] == 112 || chess[r2][u2] == 113 || chess[r2][u2] == 114 || chess[r2][u2] == 115)candidation[pieces[i].id][t].score = 71;
				if (chess[r2][u2] == -1)candidation[pieces[i].id][t].score = 10;
				t++;
			}
			if ((chess[l2][u2] == -1 || chess[l2][u2] >= 100) && (chess[l1][u1] == -1) && (l2 >= 0) && (u2 <= 4))//原位置往左下
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = u2;
				if (chess[l2][u2] == 105 || chess[l2][u2] == 106)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[l2][u2] == 107 || chess[l2][u2] == 108)candidation[pieces[i].id][t].score = 81;
				if (chess[l2][u2] == 109 || chess[l2][u2] == 110)candidation[pieces[i].id][t].score = 75;
				if (chess[l2][u2] == 111 || chess[l2][u2] == 112 || chess[l2][u2] == 113 || chess[l2][u2] == 114 || chess[l2][u2] == 115)candidation[pieces[i].id][t].score = 71;
				if (chess[l2][u2] == -1)candidation[pieces[i].id][t].score = 9;
				t++;
			}
			break;
		case 5:case 6://俥
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (r <= 8)
				{
					if (chess[r][pieces[i].y] >= 100 || chess[r][pieces[i].y] == -1)//原位置往右
					{
						candidation[pieces[i].id][t].x = r;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[r][pieces[i].y] == 100) candidation[pieces[i].id][t].score = 100; //吃到不同棋子的分數
						if (chess[r][pieces[i].y] == 101 || chess[r][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 77;
						if (chess[r][pieces[i].y] == 103 || chess[r][pieces[i].y] == 104) candidation[pieces[i].id][t].score = 67;
						if (chess[r][pieces[i].y] == 105 || chess[r][pieces[i].y] == 106) candidation[pieces[i].id][t].score = 97;
						if (chess[r][pieces[i].y] == 107 || chess[r][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 82;
						if (chess[r][pieces[i].y] == 109 || chess[r][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 86;
						if (chess[r][pieces[i].y] == 111 || chess[r][pieces[i].y] == 112 || chess[r][pieces[i].y] == 113 || chess[r][pieces[i].y] == 114 || chess[r][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 70;
						if (chess[r][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 19;
						t++;
						break;
					}
					if (chess[r][pieces[i].y] < 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (l >= 0)
				{
					if (chess[l][pieces[i].y] == -1 || chess[l][pieces[i].y] >= 100)//原位置往左
					{
						candidation[pieces[i].id][t].x = l;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[l][pieces[i].y] == 100)  candidation[pieces[i].id][t].score = 100; //吃到不同棋子的分數
						if (chess[l][pieces[i].y] == 101 || chess[l][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 77;
						if (chess[l][pieces[i].y] == 103 || chess[l][pieces[i].y] == 104)candidation[pieces[i].id][t].score = 67;
						if (chess[l][pieces[i].y] == 105 || chess[l][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 97;
						if (chess[l][pieces[i].y] == 107 || chess[l][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 82;
						if (chess[l][pieces[i].y] == 109 || chess[l][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 86;
						if (chess[l][pieces[i].y] == 111 || chess[l][pieces[i].y] == 112 || chess[l][pieces[i].y] == 113 || chess[l][pieces[i].y] == 114 || chess[l][pieces[i].y] == 115) candidation[pieces[i].id][t].score = 70;
						if (chess[l][pieces[i].y] == -1) candidation[pieces[i].id][t].score = 18;
						t++;
						break;
					}
					if (chess[l][pieces[i].y] < 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 9; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (u <= 9)
				{
					if (chess[pieces[i].x][u] == -1 || chess[pieces[i].x][u] >= 100)//原位置往下
					{
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = u;
						if (chess[pieces[i].x][u] == 100) candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
						if (chess[pieces[i].x][u] == 101 || chess[pieces[i].x][u] == 102)  candidation[pieces[i].id][t].score = 77;
						if (chess[pieces[i].x][u] == 103 || chess[pieces[i].x][u] == 104)  candidation[pieces[i].id][t].score = 67;
						if (chess[pieces[i].x][u] == 105 || chess[pieces[i].x][u] == 106) candidation[pieces[i].id][t].score = 97;
						if (chess[pieces[i].x][u] == 107 || chess[pieces[i].x][u] == 108)  candidation[pieces[i].id][t].score = 82;
						if (chess[pieces[i].x][u] == 109 || chess[pieces[i].x][u] == 110) candidation[pieces[i].id][t].score = 86;
						if (chess[pieces[i].x][u] == 111 || chess[pieces[i].x][u] == 112 || chess[pieces[i].x][u] == 113 || chess[pieces[i].x][u] == 114 || chess[pieces[i].x][u] == 115)  candidation[pieces[i].id][t].score = 70;
						if (chess[pieces[i].x][u] == -1)  candidation[pieces[i].id][t].score = 20;
						t++;
						break;
					}
					if (chess[pieces[i].x][u] < 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 9; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (d >= 0)
				{
					if (chess[pieces[i].x][d] == -1 || chess[pieces[i].x][d] >= 100)//原位置往上
					{
						if (chess[pieces[i].x][d] == 100)
						{
							candidation[pieces[i].id][t].x = pieces[i].x;
							candidation[pieces[i].id][t].y = d;
							if (chess[pieces[i].x][d] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
							if (chess[pieces[i].x][d] == 101 || chess[pieces[i].x][d] == 102)  candidation[pieces[i].id][t].score = 77;
							if (chess[pieces[i].x][d] == 103 || chess[pieces[i].x][d] == 104) candidation[pieces[i].id][t].score = 67;
							if (chess[pieces[i].x][d] == 105 || chess[pieces[i].x][d] == 106)  candidation[pieces[i].id][t].score = 97;
							if (chess[pieces[i].x][d] == 107 || chess[pieces[i].x][d] == 108)  candidation[pieces[i].id][t].score = 82;
							if (chess[pieces[i].x][d] == 109 || chess[pieces[i].x][d] == 110)  candidation[pieces[i].id][t].score = 86;
							if (chess[pieces[i].x][d] == 111 || chess[pieces[i].x][d] == 112 || chess[pieces[i].x][d] == 113 || chess[pieces[i].x][d] == 114 || chess[pieces[i].x][d] == 115) candidation[pieces[i].id][t].score = 70;
							if (chess[pieces[i].x][d] == -1)  candidation[pieces[i].id][t].score = 17;
							t++;
							break;
						}
						if (chess[pieces[i].x][d] < 100)
						{
							break;
						}
					}
				}
			}
			break;
		case 7:case 8://馬
			if ((chess[l1][d2] == -1 || chess[l1][d2] >= 100) && (chess[pieces[i].x][d1] == -1) && l1 >= 0 && d2 >= 0)//原位置往左上(日)
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = d2;
				if (chess[l1][d2] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l1][d2] == 101 || chess[l1][d2] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[l1][d2] == 103 || chess[l1][d2] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[l1][d2] == 105 || chess[l1][d2] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[l1][d2] == 107 || chess[l1][d2] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[l1][d2] == 109 || chess[l1][d2] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[l1][d2] == 111 || chess[l1][d2] == 112 || chess[l1][d2] == 113 || chess[l1][d2] == 114 || chess[l1][d2] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[l1][d2] == -1)candidation[pieces[i].id][t].score = 13;
				t++;
			}
			if ((chess[r1][d2] == -1 || chess[r1][d2] >= 100) && (chess[pieces[i].x][d1] == -1) && r1 <= 8 && d2 >= 0)//原位置往右上(日)
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = d2;
				if (chess[r1][d2] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r1][d2] == 101 || chess[r1][d2] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[r1][d2] == 103 || chess[r1][d2] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[r1][d2] == 105 || chess[r1][d2] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[r1][d2] == 107 || chess[r1][d2] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[r1][d2] == 109 || chess[r1][d2] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[r1][d2] == 111 || chess[r1][d2] == 112 || chess[r1][d2] == 113 || chess[r1][d2] == 114 || chess[r1][d2] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[r1][d2] == -1)candidation[pieces[i].id][t].score = 14;
				t++;
			}
			if ((chess[r2][d1] == -1 || chess[r2][d1] >= 100) && (chess[r1][pieces[i].y] == -1) && r2 <= 8 && d1 >= 0)//原位置往右上
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = d1;
				if (chess[r2][d1] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r2][d1] == 101 || chess[r2][d1] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[r2][d1] == 103 || chess[r2][d1] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[r2][d1] == 105 || chess[r2][d1] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[r2][d1] == 107 || chess[r2][d1] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[r2][d1] == 109 || chess[r2][d1] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[r2][d1] == 111 || chess[r2][d1] == 112 || chess[r2][d1] == 113 || chess[r2][d1] == 114 || chess[r2][d1] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[r2][d1] == -1)candidation[pieces[i].id][t].score = 15;
				t++;
			}
			if ((chess[r2][u1] == -1 || chess[r2][u1] >= 100) && (chess[r1][pieces[i].y] == -1) && r2 <= 8 && u1 <= 9)//原位置往右下
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = u1;
				if (chess[r2][u1] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r2][u1] == 101 || chess[r2][u1] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[r2][u1] == 103 || chess[r2][u1] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[r2][u1] == 105 || chess[r2][u1] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[r2][u1] == 107 || chess[r2][u1] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[r2][u1] == 109 || chess[r2][u1] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[r2][u1] == 111 || chess[r2][u1] == 112 || chess[r2][u1] == 113 || chess[r2][u1] == 114 || chess[r2][u1] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[r2][u1] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[r1][u2] == -1 || chess[r1][u2] >= 100) && (chess[pieces[i].x][u1] == -1) && r1 <= 8 && u2 <= 9)//原位置往右下(日)
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = u2;
				if (chess[r1][u2] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r1][u2] == 101 || chess[r1][u2] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[r1][u2] == 103 || chess[r1][u2] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[r1][u2] == 105 || chess[r1][u2] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[r1][u2] == 107 || chess[r1][u2] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[r1][u2] == 109 || chess[r1][u2] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[r1][u2] == 111 || chess[r1][u2] == 112 || chess[r1][u2] == 113 || chess[r1][u2] == 114 || chess[r1][u2] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[r1][u2] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[l1][u2] == -1 || chess[l1][u2] >= 100) && (chess[pieces[i].x][u1] == -1) && l1 >= 0 && u2 <= 9)//原位置往左下(日)
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = u2;
				if (chess[l1][u2] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l1][u2] == 101 || chess[l1][u2] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[l1][u2] == 103 || chess[l1][u2] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[l1][u2] == 105 || chess[l1][u2] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[l1][u2] == 107 || chess[l1][u2] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[l1][u2] == 109 || chess[l1][u2] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[l1][u2] == 111 || chess[l1][u2] == 112 || chess[l1][u2] == 113 || chess[l1][u2] == 114 || chess[l1][u2] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[l1][u2] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[l2][u1] == -1 || chess[l2][u1] >= 100) && (chess[l1][pieces[i].y] == -1) && l2 >= 0 && u1 <= 9)//原位置往左下
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = u1;
				if (chess[l2][u1] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l2][u1] == 101 || chess[l2][u1] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[l2][u1] == 103 || chess[l2][u1] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[l2][u1] == 105 || chess[l2][u1] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[l2][u1] == 107 || chess[l2][u1] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[l2][u1] == 109 || chess[l2][u1] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[l2][u1] == 111 || chess[l2][u1] == 112 || chess[l2][u1] == 113 || chess[l2][u1] == 114 || chess[l2][u1] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[l2][u1] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[l2][d1] == -1 || chess[l2][d1] >= 100) && (chess[l1][pieces[i].y] == -1) && l2 >= 0 && d1 >= 0)//原位置往左上
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = d1;
				if (chess[l2][d1] == 100)candidation[7][t].score = 100;//吃到不同棋子的分數
				if (chess[l2][d1] == 101 || chess[l2][d1] == 102)candidation[pieces[i].id][t].score = 76;
				if (chess[l2][d1] == 103 || chess[l2][d1] == 104)candidation[pieces[i].id][t].score = 66;
				if (chess[l2][d1] == 105 || chess[l2][d1] == 106)candidation[pieces[i].id][t].score = 91;
				if (chess[l2][d1] == 107 || chess[l2][d1] == 108)candidation[pieces[i].id][t].score = 95;
				if (chess[l2][d1] == 109 || chess[l2][d1] == 110)candidation[pieces[i].id][t].score = 85;
				if (chess[l2][d1] == 111 || chess[l2][d1] == 112 || chess[l2][d1] == 113 || chess[l2][d1] == 114 || chess[l2][d1] == 115)candidation[pieces[i].id][t].score = 69;
				if (chess[l2][d1] == -1)candidation[pieces[i].id][t].score = 16;
				t++;
			}
			break;
		case 9:case 10://炮
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (r <= 8)
				{
					if (chess[r][pieces[i].y] == -1)//原位置往右走
					{
						if (c1 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = r;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[r][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 19;
						t++;
					}
					if (chess[r][pieces[i].y] != -1)//原位置往右吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int ra = r + k;
							if ((chess[ra][pieces[i].y] >= 100) && (ra <= 8))
							{
								candidation[pieces[i].id][t].x = ra;
								candidation[pieces[i].id][t].y = pieces[i].y;
								if (chess[ra][pieces[i].y] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[ra][pieces[i].y] == 101 || chess[ra][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 100;
								if (chess[ra][pieces[i].y] == 103 || chess[ra][pieces[i].y] == 104)candidation[pieces[i].id][t].score = 87;
								if (chess[ra][pieces[i].y] == 105 || chess[ra][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 94;
								if (chess[ra][pieces[i].y] == 107 || chess[ra][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 79;
								if (chess[ra][pieces[i].y] == 109 || chess[ra][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 96;
								if (chess[ra][pieces[i].y] == 111 || chess[ra][pieces[i].y] == 112 || chess[ra][pieces[i].y] == 113 || chess[ra][pieces[i].y] == 114 || chess[ra][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 68;
								t++;
								h1++;
								break;
							}
						}
						if (h1 == 1)
						{
							break;
						}
						c1++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (l >= 0)
				{
					if (chess[l][pieces[i].y] == -1)//原位置往左走
					{
						if (c2 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = l;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[l][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 18;
						t++;
					}
					if (chess[l][pieces[i].y] != -1)//原位置往左吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int la = l - k;
							if ((chess[la][pieces[i].y] >= 100) && (la >= 0))
							{
								candidation[pieces[i].id][t].x = la;
								candidation[pieces[i].id][t].y = pieces[i].y;
								if (chess[la][pieces[i].y] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[la][pieces[i].y] == 101 || chess[la][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 100;
								if (chess[la][pieces[i].y] == 103 || chess[la][pieces[i].y] == 104)candidation[pieces[i].id][t].score = 87;
								if (chess[la][pieces[i].y] == 105 || chess[la][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 94;
								if (chess[la][pieces[i].y] == 107 || chess[la][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 79;
								if (chess[la][pieces[i].y] == 109 || chess[la][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 96;
								if (chess[la][pieces[i].y] == 111 || chess[la][pieces[i].y] == 112 || chess[la][pieces[i].y] == 113 || chess[la][pieces[i].y] == 114 || chess[la][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 68;
								t++;
								h2++;
								break;
							}
						}
						if (h2 == 1)
						{
							break;
						}
						c2++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (u <= 9)
				{
					if (chess[pieces[i].x][u] == -1)//原位置往下走
					{
						if (c3 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = u;
						if (chess[pieces[i].x][u] == -1)candidation[pieces[i].id][t].score = 20;
						t++;
					}
					if (chess[pieces[i].x][u] != -1)//原位置往下吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int ua = u + k;
							if ((chess[pieces[i].x][ua] >= 100) && (ua <= 9))
							{
								candidation[pieces[i].id][t].x = pieces[i].x;
								candidation[pieces[i].id][t].y = ua;
								if (chess[pieces[i].x][ua] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[pieces[i].x][ua] == 101 || chess[pieces[i].x][ua] == 102)candidation[pieces[i].id][t].score = 100;
								if (chess[pieces[i].x][ua] == 103 || chess[pieces[i].x][ua] == 104)candidation[pieces[i].id][t].score = 87;
								if (chess[pieces[i].x][ua] == 105 || chess[pieces[i].x][ua] == 106)candidation[pieces[i].id][t].score = 94;
								if (chess[pieces[i].x][ua] == 107 || chess[pieces[i].x][ua] == 108)candidation[pieces[i].id][t].score = 79;
								if (chess[pieces[i].x][ua] == 109 || chess[pieces[i].x][ua] == 110)candidation[pieces[i].id][t].score = 96;
								if (chess[pieces[i].x][ua] == 111 || chess[pieces[i].x][ua] == 112 || chess[pieces[i].x][ua] == 113 || chess[pieces[i].x][ua] == 114 || chess[pieces[i].x][ua] == 115)candidation[pieces[i].id][t].score = 68;
								t++;
								h3++;
								break;
							}
						}
						if (h3 == 1)
						{
							break;
						}
						c3++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (d >= 0)
				{
					if (chess[pieces[i].x][d] == -1)//原位置往上走
					{
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = d;
						if (chess[pieces[i].x][d] == -1)candidation[pieces[i].id][t].score = 17;
						t++;
						if (c4 != 0)
						{
							break;
						}
					}
					if (chess[pieces[i].x][d] != -1)//原位置往上吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int da = d - k;
							if ((chess[pieces[i].x][da] >= 100) && (da >= 0))
							{
								candidation[pieces[i].id][t].x = pieces[i].x;
								candidation[pieces[i].id][t].y = da;
								if (chess[pieces[i].x][da] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[pieces[i].x][da] == 101 || chess[pieces[i].x][da] == 102)candidation[pieces[i].id][t].score = 99;
								if (chess[pieces[i].x][da] == 103 || chess[pieces[i].x][da] == 104)candidation[pieces[i].id][t].score = 87;
								if (chess[pieces[i].x][da] == 105 || chess[pieces[i].x][da] == 106)candidation[pieces[i].id][t].score = 94;
								if (chess[pieces[i].x][da] == 107 || chess[pieces[i].x][da] == 108)candidation[pieces[i].id][t].score = 79;
								if (chess[pieces[i].x][da] == 109 || chess[pieces[i].x][da] == 110)candidation[pieces[i].id][t].score = 96;
								if (chess[pieces[i].x][da] == 111 || chess[pieces[i].x][da] == 112 || chess[pieces[i].x][da] == 113 || chess[pieces[i].x][da] == 114 || chess[pieces[i].x][da] == 115)candidation[pieces[i].id][t].score = 68;
								t++;
								h4++;
								break;
							}
						}
						if (h4 == 1)
						{
							break;
						}
						c4++;
					}
				}
			}
			break;
		case 11:case 12:case 13:case 14:case 15://兵
			if (pieces[i].y <= 4)//過河前，原位置往前走(不走回頭路)
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = u1;
				if (chess[pieces[i].x][u1] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[pieces[i].x][u1] == 101 || chess[pieces[i].x][u1] == 102)candidation[pieces[i].id][t].score = 73;
				if (chess[pieces[i].x][u1] == 103 || chess[pieces[i].x][u1] == 104)candidation[pieces[i].id][t].score = 72;
				if (chess[pieces[i].x][u1] == 105 || chess[pieces[i].x][u1] == 106)candidation[pieces[i].id][t].score = 90;
				if (chess[pieces[i].x][u1] == 107 || chess[pieces[i].x][u1] == 108)candidation[pieces[i].id][t].score = 80;
				if (chess[pieces[i].x][u1] == 109 || chess[pieces[i].x][u1] == 110)candidation[pieces[i].id][t].score = 83;
				if (chess[pieces[i].x][u1] == 111 || chess[pieces[i].x][u1] == 112 || chess[pieces[i].x][u1] == 113 || chess[pieces[i].x][u1] == 114 || chess[pieces[i].x][u1] == 115)candidation[pieces[i].id][t].score = 94;
				if (chess[pieces[i].x][u1] == -1)candidation[pieces[i].id][t].score = 9;
				t++;
			}
			if (pieces[i].y > 4)//過河後(不走回頭路)
			{
				if ((chess[pieces[i].x][u1] == -1 || chess[pieces[i].x][u1] >= 100) && u1 <= 9)//原位置往前
				{
					candidation[pieces[i].id][t].x = pieces[i].x;
					candidation[pieces[i].id][t].y = u1;
					if (chess[pieces[i].x][u1] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
					if (chess[pieces[i].x][u1] == 101 || chess[pieces[i].x][u1] == 102)candidation[pieces[i].id][t].score = 73;
					if (chess[pieces[i].x][u1] == 103 || chess[pieces[i].x][u1] == 104)candidation[pieces[i].id][t].score = 72;
					if (chess[pieces[i].x][u1] == 105 || chess[pieces[i].x][u1] == 106)candidation[pieces[i].id][t].score = 90;
					if (chess[pieces[i].x][u1] == 107 || chess[pieces[i].x][u1] == 108)candidation[pieces[i].id][t].score = 80;
					if (chess[pieces[i].x][u1] == 109 || chess[pieces[i].x][u1] == 110)candidation[pieces[i].id][t].score = 83;
					if (chess[pieces[i].x][u1] == 111 || chess[pieces[i].x][u1] == 112 || chess[pieces[i].x][u1] == 113 || chess[pieces[i].x][u1] == 114 || chess[pieces[i].x][u1] == 115)candidation[pieces[i].id][t].score = 94;
					if (chess[pieces[i].x][u1] == -1)candidation[pieces[i].id][t].score = 12;
					t++;
				}
				if ((chess[l1][pieces[i].y] == -1 || chess[l1][pieces[i].y] >= 100) && l1 >= 0)//原位置往左
				{
					candidation[pieces[i].id][t].x = l1;
					candidation[pieces[i].id][t].y = pieces[i].y;
					if (chess[l1][pieces[i].y] == 100)candidation[11][t].score = 100;//吃到不同棋子的分數
					if (chess[l1][pieces[i].y] == 101 || chess[l1][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 73;
					if (chess[l1][pieces[i].y] == 103 || chess[l1][pieces[i].y] == 104)candidation[pieces[i].id][t].score = 72;
					if (chess[l1][pieces[i].y] == 105 || chess[l1][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 90;
					if (chess[l1][pieces[i].y] == 107 || chess[l1][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 80;
					if (chess[l1][pieces[i].y] == 109 || chess[l1][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 83;
					if (chess[l1][pieces[i].y] == 111 || chess[l1][pieces[i].y] == 112 || chess[l1][pieces[i].y] == 113 || chess[l1][pieces[i].y] == 114 || chess[l1][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 94;
					if (chess[l1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 10;
					t++;
				}
				if ((chess[r1][pieces[i].y] == -1 || chess[r1][pieces[i].y] >= 100) && r1 <= 8)//原位置往右
				{
					candidation[pieces[i].id][t].x = r1;
					candidation[pieces[i].id][t].y = pieces[i].y;
					if (chess[l1][pieces[i].y] == 100)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
					if (chess[r1][pieces[i].y] == 101 || chess[r1][pieces[i].y] == 102)candidation[pieces[i].id][t].score = 73;
					if (chess[r1][pieces[i].y] == 103 || chess[r1][pieces[i].y] == 104)candidation[pieces[i].id][t].score = 72;
					if (chess[r1][pieces[i].y] == 105 || chess[r1][pieces[i].y] == 106)candidation[pieces[i].id][t].score = 90;
					if (chess[r1][pieces[i].y] == 107 || chess[r1][pieces[i].y] == 108)candidation[pieces[i].id][t].score = 80;
					if (chess[r1][pieces[i].y] == 109 || chess[r1][pieces[i].y] == 110)candidation[pieces[i].id][t].score = 83;
					if (chess[r1][pieces[i].y] == 111 || chess[r1][pieces[i].y] == 112 || chess[r1][pieces[i].y] == 113 || chess[r1][pieces[i].y] == 114 || chess[r1][pieces[i].y] == 115)candidation[pieces[i].id][t].score = 94;
					if (chess[r1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 12;
					t++;
				}
			}
			break;
		case 100://帥
			if ((chess[pieces[i].x][u1] == -1 || chess[pieces[i].x][u1] < 100) && (u1 <= 9))//原位置往下
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = u1;
				if (chess[pieces[i].x][u1] == 5 || chess[pieces[i].x][u1] == 6)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[pieces[i].x][u1] == 7 || chess[pieces[i].x][u1] == 8)candidation[pieces[i].id][t].score = 88;
				if (chess[pieces[i].x][u1] == 9 || chess[pieces[i].x][u1] == 10)candidation[pieces[i].id][t].score = 89;
				if (chess[pieces[i].x][u1] == 11 || chess[pieces[i].x][u1] == 12 || chess[pieces[i].x][u1] == 13 || chess[pieces[i].x][u1] == 14 || chess[pieces[i].x][u1] == 15)candidation[pieces[i].id][t].score = 98;
				if (chess[pieces[i].x][u1] == -1)candidation[pieces[i].id][t].score = 4;
				t++;
			}
			if ((chess[pieces[i].x][d1] == -1 || chess[pieces[i].x][d1] < 100) && (d1 >= 7))//原位置往上
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = d1;
				if (chess[pieces[i].x][d1] == 5 || chess[pieces[i].x][d1] == 6)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[pieces[i].x][d1] == 7 || chess[pieces[i].x][d1] == 8)candidation[pieces[i].id][t].score = 88;
				if (chess[pieces[i].x][d1] == 9 || chess[pieces[i].x][d1] == 10)candidation[pieces[i].id][t].score = 89;
				if (chess[pieces[i].x][d1] == 11 || chess[pieces[i].x][d1] == 12 || chess[pieces[i].x][d1] == 13 || chess[pieces[i].x][d1] == 14 || chess[pieces[i].x][d1] == 15)candidation[pieces[i].id][t].score = 98;
				if (chess[pieces[i].x][d1] == -1)candidation[pieces[i].id][t].score = 1;
				t++;
			}
			if ((chess[r1][pieces[i].y] == -1 || chess[r1][pieces[i].y] < 100) && (r1 <= 5))//原位置往右
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = pieces[i].y;
				if (chess[r1][pieces[i].y] == 5 || chess[r1][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[r1][pieces[i].y] == 7 || chess[r1][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 88;
				if (chess[r1][pieces[i].y] == 9 || chess[r1][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 89;
				if (chess[r1][pieces[i].y] == 11 || chess[r1][pieces[i].y] == 12 || chess[r1][pieces[i].y] == 13 || chess[r1][pieces[i].y] == 14 || chess[r1][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 98;
				if (chess[r1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 2;
				t++;
			}
			if ((chess[l1][pieces[i].y] == -1 || chess[l1][pieces[i].y] < 100) && (l1 >= 3) && (l1 >= 0))//原位置往左
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = pieces[i].y;
				if (chess[l1][pieces[i].y] == 5 || chess[l1][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[l1][pieces[i].y] == 7 || chess[l1][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 88;
				if (chess[l1][pieces[i].y] == 9 || chess[l1][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 89;
				if (chess[l1][pieces[i].y] == 11 || chess[l1][pieces[i].y] == 12 || chess[l1][pieces[i].y] == 13 || chess[l1][pieces[i].y] == 14 || chess[l1][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 98;
				if (chess[l1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 3;
				t++;
			}
			break;
		case 101:case 102://士
			if ((chess[l1][d1] == -1 || chess[l1][d1] < 100) && (l1 >= 3) && (d1 >= 7))//原位置往左上
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = d1;
				if (chess[l1][d1] == 5 || chess[l1][d1] == 6)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[l1][d1] == 7 || chess[l1][d1] == 8)candidation[pieces[i].id][t].score = 78;
				if (chess[l1][d1] == 9 || chess[l1][d1] == 10)candidation[pieces[i].id][t].score = 84;
				if (chess[l1][d1] == 11 || chess[l1][d1] == 12 || chess[l1][d1] == 13 || chess[l1][d1] == 14 || chess[l1][d1] == 15)candidation[pieces[i].id][t].score = 74;
				if (chess[l1][d1] == -1)candidation[pieces[i].id][t].score = 5;
				t++;
			}
			if ((chess[r1][d1] == -1 || chess[r1][d1] < 100) && (r1 <= 5) && (d1 >= 7))//原位置往右上
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = d1;
				if (chess[r1][d1] == 5 || chess[r1][d1] == 6)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[r1][d1] == 7 || chess[r1][d1] == 8)candidation[pieces[i].id][t].score = 78;
				if (chess[r1][d1] == 9 || chess[r1][d1] == 10)candidation[pieces[i].id][t].score = 84;
				if (chess[r1][d1] == 11 || chess[r1][d1] == 12 || chess[r1][d1] == 13 || chess[r1][d1] == 14 || chess[r1][d1] == 15)candidation[pieces[i].id][t].score = 74;
				if (chess[r1][d1] == -1)candidation[pieces[i].id][t].score = 6;
				t++;
			}
			if ((chess[l1][u1] == -1 || chess[l1][u1] < 100) && (l1 >= 3) && (u1 <= 9))//原位置往左下
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = u1;
				if (chess[l1][u1] == 5 || chess[l1][u1] == 6)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[l1][u1] == 7 || chess[l1][u1] == 8)candidation[pieces[i].id][t].score = 78;
				if (chess[l1][u1] == 9 || chess[l1][u1] == 10)candidation[pieces[i].id][t].score = 84;
				if (chess[l1][u1] == 11 || chess[l1][u1] == 12 || chess[l1][u1] == 13 || chess[l1][u1] == 14 || chess[l1][u1] == 15)candidation[pieces[i].id][t].score = 74;
				if (chess[l1][u1] == -1)candidation[pieces[i].id][t].score = 7;
				t++;
			}
			if ((chess[r1][u1] == -1 || chess[r1][u1] < 100) && (r1 <= 5) && (u1 <= 9))//原位置往右下
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = u1;
				if (chess[r1][u1] == 5 || chess[r1][u1] == 6)candidation[pieces[i].id][t].score = 93;//吃到不同棋子的分數
				if (chess[r1][u1] == 7 || chess[r1][u1] == 8)candidation[pieces[i].id][t].score = 78;
				if (chess[r1][u1] == 9 || chess[r1][u1] == 10)candidation[pieces[i].id][t].score = 84;
				if (chess[r1][u1] == 11 || chess[r1][u1] == 12 || chess[r1][u1] == 13 || chess[r1][u1] == 14 || chess[r1][u1] == 15)candidation[pieces[i].id][t].score = 74;
				if (chess[r1][u1] == -1)candidation[pieces[i].id][t].score = 8;
				t++;
			}
			break;
		case 103:case 104://象
			if ((chess[l2][d2] == -1 || chess[l2][d2] < 100) && (chess[l1][d1] == -1) && (l2 >= 0) && (d2 >= 5))//原位置往左上
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = d2;
				if (chess[l2][d2] == 5 || chess[l2][d2] == 6)candidation[pieces[i].id][t].score = 99;//吃到不同棋子的分數
				if (chess[l2][d2] == 7 || chess[l2][d2] == 8)candidation[pieces[i].id][t].score = 97;
				if (chess[l2][d2] == 9 || chess[l2][d2] == 10)candidation[pieces[i].id][t].score = 98;
				if (chess[l2][d2] == 11 || chess[l2][d2] == 12 || chess[l2][d2] == 13 || chess[l2][d2] == 14 || chess[l2][d2] == 15)candidation[pieces[i].id][t].score = 94;
				if (chess[l2][d2] == -1)candidation[pieces[i].id][t].score = 11;
				t++;
			}
			if ((chess[r2][d2] == -1 || chess[r2][d2] < 100) && (chess[r1][d1] == -1) && (r2 <= 8) && (d2 >= 5))//原位置往右上
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = d2;
				if (chess[r2][d2] == 5 || chess[r2][d2] == 6)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[r2][d2] == 7 || chess[r2][d2] == 8)candidation[pieces[i].id][t].score = 81;
				if (chess[r2][d2] == 9 || chess[r2][d2] == 10)candidation[pieces[i].id][t].score = 75;
				if (chess[r2][d2] == 11 || chess[r2][d2] == 12 || chess[r2][d2] == 13 || chess[r2][d2] == 14 || chess[r2][d2] == 15)candidation[pieces[i].id][t].score = 71;
				if (chess[r2][d2] == -1)candidation[pieces[i].id][t].score = 10;
				t++;
			}
			if ((chess[r2][u2] == -1 || chess[r2][u2] < 100) && (chess[r1][u1] == -1) && (r2 <= 8) && (u2 <= 9))//原位置往右下
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = u2;
				if (chess[r2][u2] == 5 || chess[r2][u2] == 6)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[r2][u2] == 7 || chess[r2][u2] == 8)candidation[pieces[i].id][t].score = 81;
				if (chess[r2][u2] == 9 || chess[r2][u2] == 10)candidation[pieces[i].id][t].score = 75;
				if (chess[r2][u2] == 11 || chess[r2][u2] == 12 || chess[r2][u2] == 13 || chess[r2][u2] == 14 || chess[r2][u2] == 15)candidation[pieces[i].id][t].score = 71;
				if (chess[r2][u2] == -1)candidation[pieces[i].id][t].score = 12;
				t++;
			}
			if ((chess[l2][u2] == -1 || chess[l2][u2] < 100) && (chess[l1][u1] == -1) && (l2 >= 0) && (u2 <= 9))//原位置往左下
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = u2;
				if (chess[l2][u2] == 5 || chess[l2][u2] == 6)candidation[pieces[i].id][t].score = 92;//吃到不同棋子的分數
				if (chess[l2][u2] == 7 || chess[l2][u2] == 8)candidation[pieces[i].id][t].score = 81;
				if (chess[l2][u2] == 9 || chess[l2][u2] == 10)candidation[pieces[i].id][t].score = 75;
				if (chess[l2][u2] == 11 || chess[l2][u2] == 12 || chess[l2][u2] == 13 || chess[l2][u2] == 14 || chess[l2][u2] == 15)candidation[pieces[i].id][t].score = 71;
				if (chess[l2][u2] == -1)candidation[pieces[i].id][t].score = 9;
				t++;
			}
			break;
		case 105:case 106://車
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (r <= 8)
				{
					if (chess[r][pieces[i].y] == -1 || chess[r][pieces[i].y] < 100)//原位置往右
					{
						candidation[pieces[i].id][t].x = r;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[r][pieces[i].y] == 0)  candidation[pieces[i].id][t].score = 100; //吃到不同棋子的分數
						if (chess[r][pieces[i].y] == 1 || chess[r][pieces[i].y] == 2)  candidation[pieces[i].id][t].score = 77;
						if (chess[r][pieces[i].y] == 3 || chess[r][pieces[i].y] == 4)  candidation[pieces[i].id][t].score = 67;
						if (chess[r][pieces[i].y] == 5 || chess[r][pieces[i].y] == 6)  candidation[pieces[i].id][t].score = 97;
						if (chess[r][pieces[i].y] == 7 || chess[r][pieces[i].y] == 8)  candidation[pieces[i].id][t].score = 82;
						if (chess[r][pieces[i].y] == 9 || chess[r][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 86;
						if (chess[r][pieces[i].y] == 11 || chess[r][pieces[i].y] == 12 || chess[r][pieces[i].y] == 13 || chess[r][pieces[i].y] == 14 || chess[r][pieces[i].y] == 15)  candidation[pieces[i].id][t].score = 70;
						if (chess[r][pieces[i].y] == -1)  candidation[pieces[i].id][t].score = 18;
						t++;
						break;
					}
					if (chess[r][pieces[i].y] >= 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (l >= 0)
				{
					if (chess[l][pieces[i].y] == -1 || chess[l][pieces[i].y] < 100)//原位置往左
					{
						candidation[pieces[i].id][t].x = l;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[l][pieces[i].y] == 0)  candidation[pieces[i].id][t].score = 100; //吃到不同棋子的分數
						if (chess[l][pieces[i].y] == 1 || chess[l][pieces[i].y] == 2)  candidation[pieces[i].id][t].score = 77;
						if (chess[l][pieces[i].y] == 3 || chess[l][pieces[i].y] == 4)  candidation[pieces[i].id][t].score = 67;
						if (chess[l][pieces[i].y] == 5 || chess[l][pieces[i].y] == 6) candidation[pieces[i].id][t].score = 97;
						if (chess[l][pieces[i].y] == 7 || chess[l][pieces[i].y] == 8)  candidation[pieces[i].id][t].score = 82;
						if (chess[l][pieces[i].y] == 9 || chess[l][pieces[i].y] == 10) candidation[pieces[i].id][t].score = 86;
						if (chess[l][pieces[i].y] == 11 || chess[l][pieces[i].y] == 12 || chess[l][pieces[i].y] == 13 || chess[l][pieces[i].y] == 14 || chess[l][pieces[i].y] == 15)  candidation[pieces[i].id][t].score = 70;
						if (chess[l][pieces[i].y] == -1)  candidation[pieces[i].id][t].score = 19;
						t++;
						break;
					}
					if (chess[l][pieces[i].y] >= 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 9; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (u <= 9)
				{
					if (chess[pieces[i].x][u] == -1 || chess[pieces[i].x][u] < 100)//原位置往下
					{
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = u;
						if (chess[pieces[i].x][u] == 0)  candidation[pieces[i].id][t].score = 100; //吃到不同棋子的分數
						if (chess[pieces[i].x][u] == 1 || chess[pieces[i].x][u] == 2)  candidation[pieces[i].id][t].score = 77;
						if (chess[pieces[i].x][u] == 3 || chess[pieces[i].x][u] == 4) candidation[pieces[i].id][t].score = 67;
						if (chess[pieces[i].x][u] == 5 || chess[pieces[i].x][u] == 6) candidation[pieces[i].id][t].score = 97;
						if (chess[pieces[i].x][u] == 7 || chess[pieces[i].x][u] == 8) candidation[pieces[i].id][t].score = 82;
						if (chess[pieces[i].x][u] == 9 || chess[pieces[i].x][u] == 10) candidation[pieces[i].id][t].score = 86;
						if (chess[pieces[i].x][u] == 11 || chess[pieces[i].x][u] == 12 || chess[pieces[i].x][u] == 13 || chess[pieces[i].x][u] == 14 || chess[pieces[i].x][u] == 15)  candidation[pieces[i].id][t].score = 70;
						if (chess[pieces[i].x][u] == -1)  candidation[pieces[i].id][t].score = 13;
						t++;
						break;
					}
					if (chess[pieces[i].x][u] >= 100)
					{
						break;
					}
				}
			}
			for (j = 1; j <= 9; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (d >= 0)
				{
					if (chess[pieces[i].x][d] == -1 || chess[pieces[i].x][d] < 100)//原位置往上
					{
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = d;
						if (chess[pieces[i].x][d] == 0) candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
						if (chess[pieces[i].x][d] == 1 || chess[pieces[i].x][d] == 2) candidation[pieces[i].id][t].score = 77;
						if (chess[pieces[i].x][d] == 3 || chess[pieces[i].x][d] == 4)  candidation[pieces[i].id][t].score = 67;
						if (chess[pieces[i].x][d] == 5 || chess[pieces[i].x][d] == 6)  candidation[pieces[i].id][t].score = 97;
						if (chess[pieces[i].x][d] == 7 || chess[pieces[i].x][d] == 8)  candidation[pieces[i].id][t].score = 82;
						if (chess[pieces[i].x][d] == 9 || chess[pieces[i].x][d] == 10) candidation[pieces[i].id][t].score = 86;
						if (chess[pieces[i].x][d] == 11 || chess[pieces[i].x][d] == 12 || chess[pieces[i].x][d] == 13 || chess[pieces[i].x][d] == 14 || chess[pieces[i].x][d] == 15)  candidation[pieces[i].id][t].score = 70;
						if (chess[pieces[i].x][d] == -1)  candidation[pieces[i].id][t].score = 20;
						t++;
						break;
					}
					if (chess[pieces[i].x][d] >= 100)
					{
						break;
					}
				}
			}
			break;
		case 107:case 108://馬
			if ((chess[l1][d2] == -1 || chess[l1][d2] < 100) && (chess[pieces[i].x][d1] == -1) && l1 >= 0 && d2 >= 0)//原位置往左上(日)
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = d2;
				if (chess[l1][d2] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l1][d2] == 1 || chess[l1][d2] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[l1][d2] == 3 || chess[l1][d2] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[l1][d2] == 5 || chess[l1][d2] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[l1][d2] == 7 || chess[l1][d2] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[l1][d2] == 9 || chess[l1][d2] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[l1][d2] == 11 || chess[l1][d2] == 12 || chess[l1][d2] == 13 || chess[l1][d2] == 14 || chess[l1][d2] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[l1][d2] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[r1][d2] == -1 || chess[r1][d2] < 100) && (chess[pieces[i].x][d1] == -1) && r1 <= 8 && d2 >= 0)//原位置往右上(日)
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = d2;
				if (chess[r1][d2] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r1][d2] == 1 || chess[r1][d2] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[r1][d2] == 3 || chess[r1][d2] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[r1][d2] == 5 || chess[r1][d2] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[r1][d2] == 7 || chess[r1][d2] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[r1][d2] == 9 || chess[r1][d2] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[r1][d2] == 11 || chess[r1][d2] == 12 || chess[r1][d2] == 13 || chess[r1][d2] == 14 || chess[r1][d2] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[r1][d2] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[r2][d1] == -1 || chess[r2][d1] < 100) && (chess[r1][pieces[i].y] == -1) && r2 <= 8 && d1 >= 0)//原位置往右上
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = d1;
				if (chess[r2][d1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r2][d1] == 1 || chess[r2][d1] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[r2][d1] == 3 || chess[r2][d1] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[r2][d1] == 5 || chess[r2][d1] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[r2][d1] == 7 || chess[r2][d1] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[r2][d1] == 9 || chess[r2][d1] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[r2][d1] == 11 || chess[r2][d1] == 12 || chess[r2][d1] == 13 || chess[r2][d1] == 14 || chess[r2][d1] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[r2][d1] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			if ((chess[r2][u1] == -1 || chess[r2][u1] < 100) && (chess[r1][pieces[i].y] == -1) && r2 <= 8 && u1 <= 9)//原位置往右下
			{
				candidation[pieces[i].id][t].x = r2;
				candidation[pieces[i].id][t].y = u1;
				if (chess[r2][u1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r2][u1] == 1 || chess[r2][u1] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[r2][u1] == 3 || chess[r2][u1] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[r2][u1] == 5 || chess[r2][u1] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[r2][u1] == 7 || chess[r2][u1] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[r2][u1] == 9 || chess[r2][u1] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[r2][u1] == 11 || chess[r2][u1] == 12 || chess[r2][u1] == 13 || chess[r2][u1] == 14 || chess[r2][u1] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[r2][u1] == -1)candidation[pieces[i].id][t].score = 13;
				t++;
			}
			if ((chess[r1][u2] == -1 || chess[r1][u2] < 100) && (chess[pieces[i].x][u1] == -1) && r1 <= 8 && u2 <= 9)//原位置往右下(日)
			{
				candidation[pieces[i].id][t].x = r1;
				candidation[pieces[i].id][t].y = u2;
				if (chess[r1][u2] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[r1][u2] == 1 || chess[r1][u2] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[r1][u2] == 3 || chess[r1][u2] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[r1][u2] == 5 || chess[r1][u2] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[r1][u2] == 7 || chess[r1][u2] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[r1][u2] == 9 || chess[r1][u2] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[r1][u2] == 11 || chess[r1][u2] == 12 || chess[r1][u2] == 13 || chess[r1][u2] == 14 || chess[r1][u2] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[r1][u2] == -1)candidation[pieces[i].id][t].score = 14;
				t++;
			}
			if ((chess[l1][u2] == -1 || chess[l1][u2] < 100) && (chess[pieces[i].x][u1] == -1) && l1 >= 0 && u2 <= 9)//原位置往左下(日)
			{
				candidation[pieces[i].id][t].x = l1;
				candidation[pieces[i].id][t].y = u2;
				if (chess[l1][u2] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l1][u2] == 1 || chess[l1][u2] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[l1][u2] == 3 || chess[l1][u2] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[l1][u2] == 5 || chess[l1][u2] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[l1][u2] == 7 || chess[l1][u2] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[l1][u2] == 9 || chess[l1][u2] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[l1][u2] == 11 || chess[l1][u2] == 12 || chess[l1][u2] == 13 || chess[l1][u2] == 14 || chess[l1][u2] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[l1][u2] == -1)candidation[pieces[i].id][t].score = 13;
				t++;
			}
			if ((chess[l2][u1] == -1 || chess[l2][u1] < 100) && (chess[l1][pieces[i].y] == -1) && l2 >= 0 && u1 <= 9)//原位置往左下
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = u1;
				if (chess[l2][u1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l2][u1] == 1 || chess[l2][u1] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[l2][u1] == 3 || chess[l2][u1] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[l2][u1] == 5 || chess[l2][u1] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[l2][u1] == 7 || chess[l2][u1] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[l2][u1] == 9 || chess[l2][u1] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[l2][u1] == 11 || chess[l2][u1] == 12 || chess[l2][u1] == 13 || chess[l2][u1] == 14 || chess[l2][u1] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[l2][u1] == -1)candidation[pieces[i].id][t].score = 14;
				t++;
			}
			if ((chess[l2][d1] == -1 || chess[l2][d1] < 100) && (chess[l1][pieces[i].y] == -1) && l2 >= 0 && d1 >= 0)//原位置往左上
			{
				candidation[pieces[i].id][t].x = l2;
				candidation[pieces[i].id][t].y = d1;
				if (chess[l2][d1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[l2][d1] == 1 || chess[l2][d1] == 2)candidation[pieces[i].id][t].score = 99;
				if (chess[l2][d1] == 3 || chess[l2][d1] == 4)candidation[pieces[i].id][t].score = 66;
				if (chess[l2][d1] == 5 || chess[l2][d1] == 6)candidation[pieces[i].id][t].score = 91;
				if (chess[l2][d1] == 7 || chess[l2][d1] == 8)candidation[pieces[i].id][t].score = 95;
				if (chess[l2][d1] == 9 || chess[l2][d1] == 10)candidation[pieces[i].id][t].score = 85;
				if (chess[l2][d1] == 11 || chess[l2][d1] == 12 || chess[l2][d1] == 13 || chess[l2][d1] == 14 || chess[l2][d1] == 15)candidation[pieces[i].id][t].score = 69;
				if (chess[l2][d1] == -1)candidation[pieces[i].id][t].score = 21;
				t++;
			}
			break;
		case 109:case 110://包
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (r <= 8)
				{
					if (chess[r][pieces[i].y] == -1)//原位置往右走
					{
						if (b1 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = r;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[r][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 19;
						t++;
					}
					if (chess[r][pieces[i].y] != -1)//原位置往右吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int ra = r + k;
							if ((chess[ra][pieces[i].y] < 100) && (chess[ra][pieces[i].y] != -1) && (ra <= 8))
							{
								candidation[pieces[i].id][t].x = ra;
								candidation[pieces[i].id][t].y = pieces[i].y;
								if (chess[ra][pieces[i].y] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[ra][pieces[i].y] == 1 || chess[ra][pieces[i].y] == 2)candidation[pieces[i].id][t].score = 100;
								if (chess[ra][pieces[i].y] == 3 || chess[ra][pieces[i].y] == 4)candidation[pieces[i].id][t].score = 87;
								if (chess[ra][pieces[i].y] == 5 || chess[ra][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 94;
								if (chess[ra][pieces[i].y] == 7 || chess[ra][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 79;
								if (chess[ra][pieces[i].y] == 9 || chess[ra][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 96;
								if (chess[ra][pieces[i].y] == 11 || chess[ra][pieces[i].y] == 12 || chess[ra][pieces[i].y] == 13 || chess[ra][pieces[i].y] == 14 || chess[ra][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 68;
								t++;
								v1++;
								break;
							}
						}
						if (v1 == 1)
						{
							break;
						}
						b1++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (l >= 0)
				{
					if (chess[l][pieces[i].y] == -1)//原位置往左走
					{
						if (b2 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = l;
						candidation[pieces[i].id][t].y = pieces[i].y;
						if (chess[l][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 18;
						t++;
					}
					if (chess[l][pieces[i].y] != -1)//原位置往左吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int la = l - k;
							if ((chess[la][pieces[i].y] < 100) && (chess[la][pieces[i].y] != -1) && (la >= 0))
							{
								candidation[pieces[i].id][t].x = la;
								candidation[pieces[i].id][t].y = pieces[i].y;
								if (chess[la][pieces[i].y] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[la][pieces[i].y] == 1 || chess[la][pieces[i].y] == 2)candidation[pieces[i].id][t].score = 100;
								if (chess[la][pieces[i].y] == 3 || chess[la][pieces[i].y] == 4)candidation[pieces[i].id][t].score = 87;
								if (chess[la][pieces[i].y] == 5 || chess[la][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 94;
								if (chess[la][pieces[i].y] == 7 || chess[la][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 79;
								if (chess[la][pieces[i].y] == 9 || chess[la][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 96;
								if (chess[la][pieces[i].y] == 11 || chess[la][pieces[i].y] == 12 || chess[la][pieces[i].y] == 13 || chess[la][pieces[i].y] == 14 || chess[la][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 68;
								t++;
								v2++;
								break;
							}
						}
						if (v2 == 1)
						{
							break;
						}
						b2++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (u <= 9)
				{
					if (chess[pieces[i].x][u] == -1)//原位置往下走
					{
						if (b3 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = u;
						if (chess[pieces[i].x][u] == -1)candidation[pieces[i].id][t].score = 13;
						t++;
					}
					if (chess[pieces[i].x][u] != -1)//原位置往下吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int ua = u + k;
							if ((chess[pieces[i].x][ua] < 100) && (chess[pieces[i].x][ua] != -1) && (ua <= 9))
							{
								candidation[pieces[i].id][t].x = pieces[i].x;
								candidation[pieces[i].id][t].y = ua;
								if (chess[pieces[i].x][ua] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[pieces[i].x][ua] == 1 || chess[pieces[i].x][ua] == 2)candidation[pieces[i].id][t].score = 100;
								if (chess[pieces[i].x][ua] == 3 || chess[pieces[i].x][ua] == 4)candidation[pieces[i].id][t].score = 87;
								if (chess[pieces[i].x][ua] == 5 || chess[pieces[i].x][ua] == 6)candidation[pieces[i].id][t].score = 94;
								if (chess[pieces[i].x][ua] == 7 || chess[pieces[i].x][ua] == 8)candidation[pieces[i].id][t].score = 79;
								if (chess[pieces[i].x][ua] == 9 || chess[pieces[i].x][ua] == 10)candidation[pieces[i].id][t].score = 96;
								if (chess[pieces[i].x][ua] == 11 || chess[pieces[i].x][ua] == 12 || chess[pieces[i].x][ua] == 13 || chess[pieces[i].x][ua] == 14 || chess[pieces[i].x][ua] == 15)candidation[pieces[i].id][t].score = 68;
								t++;
								v3++;
								break;
							}
						}
						if (v3 == 1)
						{
							break;
						}
						b3++;
					}
				}
			}
			for (j = 1; j <= 8; j++)
			{
				int r = pieces[i].x + j;
				int l = pieces[i].x - j;
				int u = pieces[i].y + j;
				int d = pieces[i].y - j;
				if (d >= 0)
				{
					if (chess[pieces[i].x][d] == -1)//原位置往上走
					{
						if (b4 != 0)
						{
							break;
						}
						candidation[pieces[i].id][t].x = pieces[i].x;
						candidation[pieces[i].id][t].y = d;
						if (chess[pieces[i].x][d] == -1)candidation[pieces[i].id][t].score = 20;
						t++;
					}
					if (chess[pieces[i].x][d] != -1)//原位置往上吃
					{
						for (int k = 1; k <= 7; k++)
						{
							int da = d - k;
							if ((chess[pieces[i].x][da] < 100) && (chess[pieces[i].x][da] != -1) && (da >= 0))
							{
								candidation[pieces[i].id][t].x = pieces[i].x;
								candidation[pieces[i].id][t].y = da;
								if (chess[pieces[i].x][da] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
								if (chess[pieces[i].x][da] == 1 || chess[pieces[i].x][da] == 2)candidation[pieces[i].id][t].score = 100;
								if (chess[pieces[i].x][da] == 3 || chess[pieces[i].x][da] == 4)candidation[pieces[i].id][t].score = 87;
								if (chess[pieces[i].x][da] == 5 || chess[pieces[i].x][da] == 6)candidation[pieces[i].id][t].score = 94;
								if (chess[pieces[i].x][da] == 7 || chess[pieces[i].x][da] == 8)candidation[pieces[i].id][t].score = 79;
								if (chess[pieces[i].x][da] == 9 || chess[pieces[i].x][da] == 10)candidation[pieces[i].id][t].score = 96;
								if (chess[pieces[i].x][da] == 11 || chess[pieces[i].x][da] == 12 || chess[pieces[i].x][da] == 13 || chess[pieces[i].x][da] == 14 || chess[pieces[i].x][da] == 15)candidation[pieces[i].id][t].score = 68;
								t++;
								v4++;
								break;
							}
						}
						if (v4 == 1)
						{
							break;
						}
						b4++;
					}
				}
			}
			break;
		case 111:case 112:case 113:case 114:case 115://卒
			if (pieces[i].y >= 5)//過河前，//原位置往前(不走回頭路)
			{
				candidation[pieces[i].id][t].x = pieces[i].x;
				candidation[pieces[i].id][t].y = d1;
				if (chess[pieces[i].x][d1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
				if (chess[pieces[i].x][d1] == 1 || chess[pieces[i].x][d1] == 2)candidation[pieces[i].id][t].score = 73;
				if (chess[pieces[i].x][d1] == 3 || chess[pieces[i].x][d1] == 4)candidation[pieces[i].id][t].score = 72;
				if (chess[pieces[i].x][d1] == 5 || chess[pieces[i].x][d1] == 6)candidation[pieces[i].id][t].score = 90;
				if (chess[pieces[i].x][d1] == 7 || chess[pieces[i].x][d1] == 8)candidation[pieces[i].id][t].score = 80;
				if (chess[pieces[i].x][d1] == 9 || chess[pieces[i].x][d1] == 10)candidation[pieces[i].id][t].score = 83;
				if (chess[pieces[i].x][d1] == 11 || chess[pieces[i].x][d1] == 12 || chess[pieces[i].x][d1] == 13 || chess[pieces[i].x][d1] == 14 || chess[pieces[i].x][d1] == 15)candidation[pieces[i].id][t].score = 94;
				if (chess[pieces[i].x][d1] == -1)candidation[pieces[i].id][t].score = 9;
				t++;
			}
			if (pieces[i].y < 5)//過河後(不走回頭路)
			{
				if ((chess[pieces[i].x][d1] == -1 || chess[pieces[i].x][d1] >= 100) && d1 >= 0)//原位置往前
				{
					candidation[pieces[i].id][t].x = pieces[i].x;
					candidation[pieces[i].id][t].y = d1;
					if (chess[pieces[i].x][d1] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
					if (chess[pieces[i].x][d1] == 1 || chess[pieces[i].x][d1] == 2)candidation[pieces[i].id][t].score = 73;
					if (chess[pieces[i].x][d1] == 3 || chess[pieces[i].x][d1] == 4)candidation[pieces[i].id][t].score = 72;
					if (chess[pieces[i].x][d1] == 5 || chess[pieces[i].x][d1] == 6)candidation[pieces[i].id][t].score = 90;
					if (chess[pieces[i].x][d1] == 7 || chess[pieces[i].x][d1] == 8)candidation[pieces[i].id][t].score = 80;
					if (chess[pieces[i].x][d1] == 9 || chess[pieces[i].x][d1] == 10)candidation[pieces[i].id][t].score = 83;
					if (chess[pieces[i].x][d1] == 11 || chess[pieces[i].x][d1] == 12 || chess[pieces[i].x][d1] == 13 || chess[pieces[i].x][d1] == 14 || chess[pieces[i].x][d1] == 15)candidation[pieces[i].id][t].score = 94;
					if (chess[pieces[i].x][d1] == -1)candidation[pieces[i].id][t].score = 12;
					t++;
				}
				if ((chess[l1][pieces[i].y] == -1 || chess[l1][pieces[i].y] >= 100) && l1 >= 0)//原位置往左
				{
					candidation[pieces[i].id][t].x = l1;
					candidation[pieces[i].id][t].y = pieces[i].y;
					if (chess[l1][pieces[i].y] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
					if (chess[l1][pieces[i].y] == 1 || chess[l1][pieces[i].y] == 2)candidation[pieces[i].id][t].score = 73;
					if (chess[l1][pieces[i].y] == 3 || chess[l1][pieces[i].y] == 4)candidation[pieces[i].id][t].score = 72;
					if (chess[l1][pieces[i].y] == 5 || chess[l1][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 90;
					if (chess[l1][pieces[i].y] == 7 || chess[l1][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 80;
					if (chess[l1][pieces[i].y] == 9 || chess[l1][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 83;
					if (chess[l1][pieces[i].y] == 11 || chess[l1][pieces[i].y] == 12 || chess[l1][pieces[i].y] == 13 || chess[l1][pieces[i].y] == 14 || chess[l1][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 94;
					if (chess[l1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 12;
					t++;
				}
				if ((chess[r1][pieces[i].y] == -1 || chess[r1][pieces[i].y] >= 100) && r1 <= 8)//原位置往右
				{
					candidation[pieces[i].id][t].x = r1;
					candidation[pieces[i].id][t].y = pieces[i].y;
					if (chess[r1][pieces[i].y] == 0)candidation[pieces[i].id][t].score = 100;//吃到不同棋子的分數
					if (chess[r1][pieces[i].y] == 1 || chess[r1][pieces[i].y] == 2)candidation[pieces[i].id][t].score = 73;
					if (chess[r1][pieces[i].y] == 3 || chess[r1][pieces[i].y] == 4)candidation[pieces[i].id][t].score = 72;
					if (chess[r1][pieces[i].y] == 5 || chess[r1][pieces[i].y] == 6)candidation[pieces[i].id][t].score = 90;
					if (chess[r1][pieces[i].y] == 7 || chess[r1][pieces[i].y] == 8)candidation[pieces[i].id][t].score = 80;
					if (chess[r1][pieces[i].y] == 9 || chess[r1][pieces[i].y] == 10)candidation[pieces[i].id][t].score = 83;
					if (chess[r1][pieces[i].y] == 11 || chess[r1][pieces[i].y] == 12 || chess[r1][pieces[i].y] == 13 || chess[r1][pieces[i].y] == 14 || chess[r1][pieces[i].y] == 15)candidation[pieces[i].id][t].score = 94;
					if (chess[r1][pieces[i].y] == -1)candidation[pieces[i].id][t].score = 11;
					t++;
				}
			}
			break;
		}
	}
	//---寫出決定-------
	if (order == 0)
	{
		if ((chess[4][2] == -1) && (chess[1][2] == 9) && (chess[2][2] == -1) && (chess[3][2] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 9 << " " << 4 << " " << 2 << endl;
			file.close();
			return 1;
		}
		else if ((chess[4][2] == 9) && (chess[1][0] == 7) && (chess[1][1] == -1) && ((chess[2][2] == -1) || (chess[2][2] >= 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 7 << " " << 2 << " " << 2 << endl;
			file.close();
			return 1;
		}
		else if ((chess[8][0] == 6) && ((chess[8][1] == -1) || (chess[8][1] >= 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 6 << " " << 8 << " " << 1 << endl;
			file.close();
			return 1;
		}
		else if ((chess[0][0] == 5) && ((chess[0][1] == -1) || (chess[0][1] >= 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 5 << " " << 0 << " " << 1 << endl;
			file.close();
			return 1;
		}
		else if ((chess[8][1] == 6) && ((chess[3][1] == -1) || (chess[3][1] >= 100)) && (chess[4][1] == -1) && (chess[5][1] == -1) && (chess[6][1] == -1) && (chess[7][1] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 6 << " " << 3 << " " << 1 << endl;
			file.close();
			return 1;
		}
		else if ((chess[3][1] == 6) && (chess[3][2] == -1) && (chess[3][3] == -1) && (chess[3][4] == -1) && (chess[3][5] == -1) && (chess[3][6] == -1) && (chess[3][7] == -1) && (chess[3][8] == -1) && (chess[3][9] == 101))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 6 << " " << 3 << " " << 9 << endl;
			file.close();
			return 1;
		}
		else if ((chess[0][1] == 5) && (chess[1][1] == -1) && (chess[2][1] == -1) && (chess[3][1] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 0 << " " << 5 << " " << 3 << " " << 1 << endl;
			file.close();
			return 1;
		}
		else
		{
			int max = 0, ni, nj;
			for (int i = 0; i <= 15; i++)
			{
				for (int j = 0; j <= t; j++)
				{
					if (candidation[i][j].score > max)
					{
						max = candidation[i][j].score;
						ni = i;
						nj = j;
					}
				}
			}
			ofstream file;
			file.open("play.txt");
			file << order << " " << ni << " " << candidation[ni][nj].x << " " << candidation[ni][nj].y << endl;
			file.close();
			return 1;
		}
	}
	else if (order == 1)
	{
		if ((chess[4][7] == -1) && (chess[1][7] == 109) && (chess[2][7] == -1) && (chess[3][7] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 109 << " " << 4 << " " << 7 << endl;
			file.close();
			return 1;
		}
		else if ((chess[4][7] == 109) && (chess[1][9] == 107) && (chess[1][8] == -1) && ((chess[2][7] == -1) || (chess[2][7] < 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 107 << " " << 2 << " " << 7 << endl;
			file.close();
			return 1;
		}
		else if ((chess[8][9] == 106) && ((chess[8][8] == -1) || (chess[8][8] < 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 106 << " " << 8 << " " << 8 << endl;
			file.close();
			return 1;
		}
		else if ((chess[0][9] == 105) && ((chess[0][8] == -1) || (chess[0][8] < 100)))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 105 << " " << 0 << " " << 8 << endl;
			file.close();
			return 1;
		}
		else if ((chess[8][8] == 106) && ((chess[3][8] == -1) || (chess[3][8] < 100)) && (chess[4][8] == -1) && (chess[5][8] == -1) && (chess[6][8] == -1) && (chess[7][8] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 106 << " " << 3 << " " << 8 << endl;
			file.close();
			return 1;
		}
		else if ((chess[3][8] == 106) && (chess[3][7] == -1) && (chess[3][6] == -1) && (chess[3][5] == -1) && (chess[3][4] == -1) && (chess[3][3] == -1) && (chess[3][2] == -1) && (chess[3][1] == -1) && (chess[3][0] == 1))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 106 << " " << 3 << " " << 0 << endl;
			file.close();
			return 1;
		}
		else if ((chess[0][8] == 105) && (chess[1][8] == -1) && (chess[2][8] == -1) && (chess[3][8] == -1))
		{
			ofstream file;
			file.open("play.txt");
			file << 1 << " " << 105 << " " << 3 << " " << 8 << endl;
			file.close();
			return 1;
		}
		else
		{
			int max = 0, ni, nj;
			for (int i = 100; i <= 115; i++)
			{
				for (int j = 0; j <= t; j++)
				{
					if (candidation[i][j].score > max)
					{
						max = candidation[i][j].score;
						ni = i;
						nj = j;
					}
				}
			}
			ofstream file;
			file.open("play.txt");
			file << order << " " << ni << " " << candidation[ni][nj].x << " " << candidation[ni][nj].y << endl;
			file.close();
			return 1;
		}
	}
}