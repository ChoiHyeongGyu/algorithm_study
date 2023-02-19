#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/*
1. �����б�
	- ��Ÿ�� 7���� �ϵ��ڵ��� ���� �ʿ��ҰŰ�
	- �־��� ������ ���� ����Ʈ�� �����
	- bfs�� ���۳����� �� �� �ִ� ��� �����鼭 ����ɵ�
*/

struct Node {
	int y;
	int x;
};

// �ʿ� ���ڵ�
int N = 0, M = 0; // ���� ũ��, ���� ũ��
int sy, sx; // ���� ��Ȧ ��ġ
int L; // Ż�� �� �ҿ�� �ð�
int ans;
int map[50][50];
vector<Node> al[50][50];

// ������ Ÿ�� �ϵ��ڵ�
// �� �� �� ��
int diry[] = { -1, 1, 0, 0 };
int dirx[] = { 0, 0, -1, 1 };

int type[8][4] = {
	// �� �� �� �� ���� �� �� �ִ���
	{0, 0, 0, 0,},
	{1, 1, 1, 1,},
	{1, 1, 0, 0,},
	{0, 0, 1, 1,},
	{1, 0, 0, 1,},
	{0, 1, 0, 1,},
	{0, 1, 1, 0,},
	{1, 0, 1, 0,},
};


void reset() {
	ans = 0;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			al[i][j].clear();
		}
	}
}

void input() {
	cin >> N >> M >> sy >> sx >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void makeAl(int y, int x) {
	int ntype = map[y][x];
	if (ntype == 0)
		return;
	// �����¿� üũ�ϸ鼭 �� �� �ִ��� Ȯ��
	for (int i = 0; i < 4; i++) {

		if (type[ntype][i] == 0)
			continue;

		int ny = y + diry[i];
		int nx = x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= M)
			continue;

		// �°� ����Ǿ� �ִ��� üũ
		if (i == 0) {
			if (type[map[ny][nx]][1] == 0)
				continue;
		}
		else if (i == 1) {
			if (type[map[ny][nx]][0] == 0)
				continue;
		}
		else if (i == 2){
			if (type[map[ny][nx]][3] == 0)
				continue;
		}
		else if (i == 3){
			if (type[map[ny][nx]][2] == 0)
				continue;
		}

		// ��� ����ϸ� ������ ��, ����
		al[y][x].push_back({ ny,nx });
	}
}

void bfs(int sy, int sx) {

	queue<Node>q;
	q.push({ sy, sx });

	int visited[50][50] = { 0, };
	visited[sy][sx] = 1;
	ans++;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < al[now.y][now.x].size(); i++) {
			Node next = al[now.y][now.x][i];

			if (visited[next.y][next.x] != 0)
				continue;

			int time = visited[now.y][now.x] + 1;
			if (time > L)
				continue;

			ans++;
			visited[next.y][next.x] = time;
			q.push(next);
		}
	}
}


int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// �׽�Ʈ ���̽����� �ʱ�ȭ
		reset();

		// input
		input();

		// solve -> 1.al �����, 2.bfs ������
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				makeAl(i, j);
			}
		}
		bfs(sy, sx);

		// output
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}