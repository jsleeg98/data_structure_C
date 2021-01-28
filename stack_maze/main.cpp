#include <stdio.h>
#include "stack.h"
#include "pos.h"

#define MAX 100
#define PATH 0 // ������ �� �ִ� ��ġ
#define WALL 1 // ������ �� ���� ��ġ
#define VISITED 2 // �̹� �湮�� ��ġ
#define BACKTRACKED 3 // �湮�ߴٰ� �ǵ��� ���� ��ġ

int maze[MAX][MAX];
int n;

void read_maze();
void print_maze();
bool movable(Position pos, int dir);

int main() {
	read_maze();

	Stack s = create();
	Position cur;
	cur.x = 0;
	cur.y = 0;

	int init_dir = 0;

	while (1) {
		maze[cur.x][cur.y] = VISITED;
		if (cur.x == n - 1 && cur.y == n - 1) {
			printf("Found the path.\n");
			break;
		}

		bool forwarded = false; // 4���� �� �� ������ �����ϴµ� �������� 
		for (int dir = init_dir; dir < 4; dir++) {
			if (movable(cur, dir)) {
				push(s, dir);
				cur = move_to(cur, dir);
				forwarded = true;
				init_dir = 0;
				break;
			}
		}
		if (!forwarded) {
			maze[cur.x][cur.y] = BACKTRACKED;
			if (is_empty(s)) {
				printf("No path exists.\n");
				break;
			}

			int d = pop(s);
			cur = move_to(cur, (d + 2) % 4);
			init_dir = d + 1;
		}
	}

	print_maze();
}

