#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
//#include<conio.h>
#include<string.h>
#define max 9999;

using namespace std;
int parent[10], cost, u, c, visited[10], went[10], w, srcpos, destpos, ctor[10], i1, order[10], costmat[10][20], top;

void computepath(int i, char nodes[10][20]);
void computepath_dfs(int i, char nodes[10][20], char src[20], char dest[20], int n);
void insert_q_dfs(int q[10], int top, char nodes[10][20], int path[10][10], int n);
void sort_dfs(int q[10], int top, char nodes[10][20]);
void dfs(char nodes[10][20], int path[10][10], char src[20], char dest[20], int n);
void computepath_bfs(int i, char nodes[10][20], char src[20], char dest[20], int n);
void sort_bfs(int q[10], int f, int r, char nodes[10][20]);
void sort_bfs(int q[10], int f, int r, char nodes[10][20], int pathcost[10]);
void computepath_ucs(int i, char nodes[10][20], int pathcost, char dest[20], char src[20], int n);
void insert_q_ucs(int element, int q[2][10], int n, int c, int j, char nodes[10][20]);
void check_ucs(int no_queue, int path[10][10], int f, int r, int q[2][10], char nodes[10][20], char dest[20], char src[20], int n, int pcost);
void delete_q_ucs(int q[2][10], int n);
void call_dfs(char src[20], char nodes[10][20], int n);
void call_ucs(char nodes[10][20], int n, char src[20]);

void ucs(char nodes[10][20], int path[10][10], char src[20], char dest[20], int n)
{
	int i, q[2][10], f = 0, r = -1, no_queue,count=0;
	w = -1;
	for (i = 0; i < n; i++)
	{
		ctor[i] = -9999;
		visited[i] = 0;
		went[i] = 9999;
		q[0][i] = 0;
		q[1][i] = max;
	}

	for (i = 0; i <= n; i++)
	{
		if (strcmp(nodes[i], dest) == 0)
		{
			destpos = i;
		}
		if (strcmp(nodes[i], src) == 0)
		{
			srcpos = i;
			visited[i] = 50;
			parent[i] = 50;
			ctor[i] = 0;

			went[++w] = i;
			no_queue = 1;
			q[0][++r] = i;
			q[1][r] = 0;
		}
	}
	for (i = 0; i <= n; i++)
	{
		while (f <= r)
		{
if (q[0][0] == 0)
			{ if (count==0)
			{
				count++;
			}
			else
				call_ucs(nodes, n, src);
			}
			delete_q_ucs(q, no_queue);
			f++; no_queue--;


			for (i = 0; i < n; i++)
			{
				if ((path[u][i] >0 && visited[i] == 0) || ((ctor[i]>ctor[u] + path[u][i]) && visited[i] == 1 && parent[u] != i) && path[u][i]>0)
				{
					if ((ctor[i] > ctor[u] + path[u][i]) && visited[i] == 1)
					{
						cost = ctor[u];
						for (int temp1 = 0; temp1 <w; temp1++)
						{
							if (went[temp1] == i)
							{
								went[temp1] = 9999;
							}
						}
					}
					c = i;
					visited[i] = 1;
					parent[i] = u;
					ctor[i] = ctor[u] + path[u][i];
					insert_q_ucs(path[u][i] + cost, q, no_queue, c, i, nodes);
					r++;
					no_queue++;

					if (strcmp(dest, nodes[i]) == 0)
					{
						int costtodest = path[u][i] + cost;
						check_ucs(no_queue, path, f, r, q, nodes, dest, src, n, path[u][i] + cost);
						computepath_ucs(i, nodes, costtodest, dest, src, n);

					}
				}
			}
		}
	}
	ofstream output;
	output.open("output.txt");
	output << src;
	 i = 1;
	while (went[i]!=0 && went[i]!=9999 )
	{
		if (went[i]<n && went[i] >= 0)
		{
			output << "-" << nodes[went[i]];
		}
		i++;
	}
	output << "\nNoPathAvailable";
	output.close();
	exit(1);
}
void call_ucs(char nodes[10][20], int n, char src[20])
{
	ofstream output;
	output.open("output.txt");
	output << src;
	int i = 1;
	n=5;
	while (went[i] >0 && went[i] <50)
	{
		if (went[i]<50 && went[i] >= 0)
		{
			output << "-" << nodes[went[i]];
		}
		i++;
	}
	output << "\nNoPathAvailable";
	output.close();
	exit(1);
}
void check_ucs(int no_queue, int path[10][10], int f, int r, int q[2][10], char nodes[10][20], char dest[20], char src[20], int n, int pcost)
{
	int j = 0;
	while (j <= no_queue)
	{
		while (pcost >= q[1][j])
		{
			if (j > no_queue)
				break;
			delete_q_ucs(q, no_queue);
			f++; no_queue--;
			for (int i = 0; i <= n; i++)
			{
				if ((path[u][i] > 0 && visited[i] == 0) || ((ctor[i] > ctor[u] + path[u][i]) && visited[i] == 1 && parent[u] != i) && path[u][i] > 0)
				{
					if ((ctor[i] > ctor[u] + path[u][i]) && visited[i] == 1)
					{
						cost = ctor[u];
						for (int temp1 = 0; temp1 < w; temp1++)
						{
							if (went[temp1] == i)
							{
								went[temp1] = 9999;
							}
						}
					}
					c = i;
					visited[i] = 1;
					parent[i] = u;
					ctor[i] = ctor[u] + path[u][i];
					insert_q_ucs(path[u][i] + cost, q, no_queue, c, i, nodes);
					r++;
					no_queue++;
					if (strcmp(dest, nodes[i]) == 0 && path[u][i] + cost<pcost)
					{
						int costtodest = path[u][i] + cost;
						check_ucs(no_queue, path, f, r, q, nodes, dest, src, n, path[u][i] + cost);
						computepath_ucs(i, nodes, costtodest, dest, src, n);
					}
				}
			}
		}
		j++;
	}
}
void delete_q_ucs(int q[2][10], int n)
{
	if (q[0][0] != srcpos)
		went[++w] = q[0][0];
	u = q[0][0];
	cost = q[1][0];
	for (int i = 0; i < n; i++)
	{
		q[0][i] = q[0][i + 1];
		q[1][i] = q[1][i + 1];
	}
	n--;

}
void insert_q_ucs(int element, int q[2][10], int n, int c, int j, char nodes[10][20])
{
	int i = n - 1;
	while ((element <q[1][i] && i >= 0) || (element == q[1][i] && strcmp(nodes[q[0][i]], nodes[q[0][i + 1]]) <0))
	{
		//visited[i] = 1;
		//parent[i] = u;
		q[0][i + 1] = q[0][i];
		q[1][i + 1] = q[1][i];
		i--;
	}
	q[1][i + 1] = element;
	q[0][i + 1] = c;
	n++;

}

void computepath_ucs(int i, char nodes[10][20], int pathcost, char dest[20], char src[20], int n)
{
	ofstream output;
	output.open("output.txt");
	int temp, q1[10], r = -1;
	q1[++r] = i;
	while (parent[i] != 50)
	{
		temp = parent[i];
		q1[++r] = temp;
		i = temp;

	}
	i = 0;
	for (i = 0; i < w; i++)
	{
		for (int j = i + 1; j <= w; j++)
		{
			if (went[i] == went[j] || went[j] == destpos)
			{
				went[j] = 9999;
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		if (went[i] >= 0 && went[i]<50)
		{
			output << nodes[went[i]] << "-";
		}
	}
	output << dest;
	output << "\n";
	while (r > 0)
	{
		temp = q1[r--];
		output << nodes[temp] << "-";

	}
	output << dest;
	output << "\n" << pathcost;
	output.close();
	//_getch();
	exit(1);
}
void bfs(char nodes[10][20], int path[10][10], char src[20], char dest[20], int n)
{
	int i, q[10], f = 0, r = -1, u, j,pathcost[10];
	i = 0;
	for (i = 0; i < n; i++)
	{
		visited[i] = 0;
		order[i] = 9999;
		pathcost[i] = 9999;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (path[i][j] > 0)
			{
				costmat[i][j] = path[i][j];
				path[i][j] = 1;
			}
		}

	}
	for (i = 0; i <n; i++)
	{
		if (strcmp(nodes[i], src) == 0)
		{
			parent[i] = 50;
			srcpos = i;
			visited[i] = 1;
			order[i1++] = i;
			q[++r] = i;
			pathcost[i] = 0;
		}

	}
	for (i = 0; i <= n; i++)
	{
		while (f <= r)
		{
			u = q[f++];

			for (i = 0; i < n; i++)
			{
				if (path[u][i] == 1 && visited[i] == 0)
				{
					pathcost[i] = pathcost[u] + 1;
					parent[i] = u;
					q[++r] = i;
					order[i1++] = i;
					sort_bfs(q, f, r, nodes,pathcost);
					visited[i] = 1;

					if (strcmp(dest, nodes[i]) == 0)
					{
						for (int l = 0; l < n; l++)
						{
							if (path[u][l] == 1 && strcmp(nodes[i], nodes[l]) < 0 && visited[l] == 1 && parent[l] == u)
							{
								for (int t = 0; t < i1; t++)
								{
									if (order[t] == l)
									{
										order[t] = 9999;
										i1--;
									}
								}
							}
						}
						for (int k = i + 1; k < n; k++)
						{
							if (path[u][k] == 1 && strcmp(nodes[i], nodes[k]) > 0 && visited[k] == 0)
							{
								int temp = order[i1 - 1];
								parent[k] = u;
								q[++r] = k;
								order[i1 - 1] = k;
								order[i1++] = temp;
								visited[k] = 1;
							}
						}
						/*	for (int l = 0; k < n; k++)
						{
						if (path[u][l] == 1 && strcmp(nodes[i], nodes[l]) < 0 && visited[l] == 1)
						{
						for (int t = 0; t < i1; i++)
						{
						if (order[t] == l)
						order[t] = 9999;
						}
						}
						}*/

						sort_bfs(q, f, r, nodes,pathcost);
						computepath_bfs(i, nodes, src, dest, n);

					}
				}

			}
		}
	}
	ofstream output;
	output.open("output.txt");
	output << src;
	for (i = 1; i < n; i++)
	{
		if (order[i] < 50 && order[i] >= 0)
		{
			output << "-" << nodes[order[i]];
		}
	}
	output << "\nNoPathAvailable";
	output.close();
	exit(1);
}
void sort_bfs(int q[10], int f, int r, char nodes[10][20],int pathcost[10])
{
	while (f <r)
	{
		int temp;
		if ((parent[q[f]] == parent[q[f + 1]] && strcmp(nodes[q[f]], nodes[q[f + 1]]) > 0) || pathcost[f] == pathcost[f + 1] && strcmp(nodes[q[f]], nodes[q[f + 1]]) > 0)
		{
			temp = q[f];
			q[f] = q[f + 1];
			q[f + 1] = temp;
			for (int i = 0; i < 10; i++)
			{
				if (order[i] == q[f + 1])
				{
					order[i] = q[f];
					order[i1 - 1] = q[f + 1];
				}
			}
		}
		f++;
	}
}
void computepath_bfs(int i, char nodes[10][20], char src[20], char dest[20], int n)
{
	ofstream output("output.txt");
	int temp, q1[10], r = -1, pathcost = 0, count = 0, j = 0, fcost = 0;
	q1[++r] = i;
	while ((parent[i] != 0 || (count == 0 && parent[i] == 0)) && j<n && parent[i] != 50)
	{
		if (parent[i] == 0)
		{
			count++;
		}
		temp = parent[i];
		fcost = fcost + costmat[temp][i];
		q1[++r] = temp;
		i = temp;
		pathcost++;
		j++;

	}

	count = 0;
	for (int i = 0; i <n; i++)
	{
		if (order[i] >= 0 && order[i]< 20 && strcmp(dest, nodes[order[i]]) != 0)
		{
			if (order[i] == 0 && count == 0)
			{
				output << nodes[order[i]] << "-";
				count++;
			}
			else if (order[i] > 0)
			{
				output << nodes[order[i]] << "-";
			}
		}
		if (strcmp(dest, nodes[order[i]]) == 0)
			break;
	}
	output << dest;
	output << "\n";
	output << src << "-";
	while (r > 1)
	{
		temp = q1[--r];
		output << nodes[temp] << "-";

	}
	output << dest;
	output << "\n" << fcost;
	output.close();
	//_getch();
	exit(1);
}
void dfs(char nodes[10][20], int path[10][10], char src[20], char dest[20], int n)
{

	int i, q[10], u, j;
	top = -1;
	for (i = 0; i < n; i++)
	{
		visited[i] = 0;
		order[i] = 999999;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (path[i][j] > 0)
			{
				costmat[i][j] = path[i][j];
				path[i][j] = 1;
			}
		}
	}
	for (i = 0; i <= n; i++)
	{
		if (strcmp(nodes[i], src) == 0)
		{
			parent[i] = 50;
			srcpos = i;
			visited[i] = 1;
			//order[i1++] = i;
			q[++top] = i;
		}
	}
	for (i = 0; i <= n; i++)
	{
		while (top >= 0)
		{

			for (i = 0; i < n; i++)
			{
				u = q[top--];
if (u < 0 || u > 9999)
				{
					call_dfs(src, nodes,n);
				}
				order[i1++] = u;

				if (strcmp(dest, nodes[u]) == 0)
				{
					insert_q_dfs(q, top, nodes, path, n);
					computepath_dfs(u, nodes, src, dest, n);
					//computepath(i, nodes);
				}
				
				for (j = 0; j < n; j++)
				{
					if (path[u][j] == 1 && visited[j] == 0)
					{
						parent[j] = u;
						q[++top] = j;

						visited[j] = 1;
						//ret = insert_q_dfs(q, nodes, i, u, path, n);
						sort_dfs(q, top, nodes);
						//visited[ret] = 1;
						//parent[ret] = u;
						//order[i1++] = ret;
						
					}
				}
			}
			//if (q[top] == u)

			//top--;

		}
	}
	ofstream output;
	output.open("output.txt");
	output << src;
	for (i = 1; i < n; i++)
	{
		if (order[i] < 50 && order[i]>=0)
		{
			output << "-" << nodes[order[i]];
		}
	}
	output << "\nNoPathAvailable";
	output.close();
	exit(1);
}
void call_dfs(char src[20],char nodes[10][20],int n)

{
	ofstream output;
	output.open("output.txt");
	output << src;
	for (int i = 1; i < n; i++)
	{
		if (order[i] < 50 && order[i] >= 0)
		{
			output << "-" << nodes[order[i]];
		}
	}
	output << "\nNoPathAvailable";
	output.close();
	exit(1);

}
void sort_dfs(int q[10], int top1, char nodes[10][20])
{
	while (top1>0)
	{
		int temp;
		if (parent[q[top1]] == parent[q[top1 - 1]] && strcmp(nodes[q[top1]], nodes[q[top1 - 1]]) > 0)
		{
			temp = q[top1];
			q[top1] = q[top1 - 1];
			q[top1 - 1] = temp;
			for (int i = 0; i < 10; i++)
			{
				if (order[i] == q[top - 1])
				{
					order[i] = q[top1];
					order[i1 - 1] = q[top1 - 1];
				}
			}

		}
		top1--;
	}

}
void insert_q_dfs(int q[10], int top, char nodes[10][20], int path[10][10], int n)
{
	int temp;
	for (int j = 1; j <= n; j++)
	{
		if (path[u][j] == 1 && visited[j] == 0 && strcmp(nodes[q[top]], nodes[j]) > 0)

		{
			q[++top] = j;
			parent[j] = u;
			visited[j] = 1;
			temp = order[i1];
			order[i1] = j;
			order[i1++] = temp;
			sort_dfs(q, top, nodes);
		}
	}
}
void computepath_dfs(int i, char nodes[10][20], char src[20], char dest[20], int n)
{
	ofstream output;
	output.open("output.txt");
	int temp, q1[10], r = -1, pathcost = 0, count = 0, j = 0, fcost = 0;
	q1[++r] = i;
	while ((parent[i] != 0 || (count == 0 && parent[i] == 0)) && j<n && parent[i] != 50)
	{
		if (parent[i] == 0)
		{
			count++;
		}
		temp = parent[i];
		fcost = fcost + costmat[temp][i];

		q1[++r] = temp;
		i = temp;
		pathcost++;
		j++;

	}

	count = 0;
	for (int i = 0; i <n; i++)
	{
		if (order[i] >= 0 && order[i]< 20 && strcmp(dest, nodes[order[i]]) != 0)
		{
			if (order[i] == 0 && count == 0)
			{
				output << nodes[order[i]] << "-";
				count++;
			}
			else if (order[i] > 0)
			{
				output << nodes[order[i]] << "-";
			}
		}
	}
	output << dest;
	output << "\n";
	output << src << "-";
	while (r > 1)
	{
		temp = q1[--r];
		output << nodes[temp] << "-";

	}
	output << dest;
	output << "\n" << fcost;
	output.close();
	//_getch();
	exit(1);
}
void computepath(int i, char nodes[10][20])
{
	ofstream output;
	output.open("output.txt");
	int temp, q1[10], r = -1, pathcost = 1;
	q1[++r] = i;

	while (parent[i] != 0)
	{
		temp = parent[i];
		q1[++r] = temp;
		i = temp;
		pathcost++;
	}
	output << nodes[0];
	for (int i = 1; i < 10; i++)
	{
		if (visited[i] == 1)
		{
			output << "-" << nodes[i];
		}
	}

	output << "\n" << nodes[0];
	while (r >= 0)
	{
		temp = q1[r--];
		output << "-" << nodes[temp];

	}

	output << "\n" << pathcost;
	//_getch();
	exit(1);
}
//ofstream output;
int main()
{
	int a, noofinputs, i, j, path[10][10];
	char src[20], dest[20];
	ifstream input;
	//ofstream output;
	//output.open("output.txt");
	input.open("input.txt");
	//output.open("output.txt");
	input >> a >> src >> dest >> noofinputs;
	char nodes[10][20];
	for (i = 0; i < noofinputs; i++)
	{
		input >> nodes[i];
	}
	for (i = 0; i < noofinputs; i++)
	{
		for (j = 0; j < noofinputs; j++)
		{
			input >> path[i][j];
		}
	}
	input.close();
	/*output << a << "\n";
	puts(src);
	puts(dest);
	for (i = 0; i < noofinputs; i++)
	{
	puts(nodes[i]);
	}
	for (i = 0; i < noofinputs; i++)
	{
	for (j = 0; j < noofinputs; j++)
	{
	output << path[i][j] << " ";
	}
	output << "\n";
	}*/
	switch (a)
	{
	case 1:
		bfs(nodes, path, src, dest, noofinputs);
		break;
	case 2:
		dfs(nodes, path, src, dest, noofinputs);
		break;

	case 3:
		ucs(nodes, path, src, dest, noofinputs);
		break;

	}

	//_getch();

	return 0;
}
