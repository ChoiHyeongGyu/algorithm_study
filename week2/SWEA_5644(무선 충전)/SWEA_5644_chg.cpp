#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. �����б�
	- �ùķ��̼� ���� (�̻����� ���)
	- 11*11 2���� ���� Map ���� (1~10 ���)
	  �� ���� ���ΰ�, ���� ���� ���� ���� �־��� ��
	  ��ġ�� �κ� ó���ϱ� ���� vector
	- floodfill�� map ä���
	- 1�ʸ��� �� �̿��ڸ� �̵��ϸ� ��Ȳ ó��
*/


struct player {
	int x;
	int y;
	int dir[101]; // 0�ʺ��� �̵����� ���
};

struct Node {
	int y;
	int x;
};

struct land {
	int power;
	int type;
};

bool cmp(land left, land right) {
	if (left.power > right.power)
		return true;
	if (left.power < right.power)
		return false;
	return false;
}

// ������: 0, ��: 1, ��: 2, ��: 3, ��: 4
int diry[] = { 0,-1,0,1,0 };
int dirx[] = { 0,0,1,0,-1 };

// �ʿ� ���ڵ�
int M, A; // �̵��ð�, BC����
vector<land> map[11][11]; // ���� -> ��°� ��� ���͸� ���
player a, b; // ����� a, b
int sum;

void reset() {
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			map[i][j].clear();
		}
	}
	sum = 0;
}

void bfs(int x, int y, int c, int p, int idx) {
	
	queue<Node>q;
	q.push({ y, x });

	int visited[11][11] = { 0, };
	visited[y][x] = 1;
	map[y][x].push_back({p,idx});

	int xdir[] = { 0, 0, -1, 1 };
	int ydir[] = { -1, 1, 0, 0 };

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 1 || nx < 1 || ny >= 11 || nx >= 11)
				continue;

			if (visited[ny][nx] != 0)
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			// bc�� ��� ���������� ä����
			if (visited[ny][nx] > c+1)
				continue;

			map[ny][nx].push_back({p,idx});
			q.push({ ny, nx });
		}
	}
}


void input() {
	cin >> M >> A;
	// �ʱⰪ ����
	a = { 1,1,{0, } }, b = { 10,10,{0, } };
	for (int i = 1; i <= M; i++) {
		cin >> a.dir[i];
	}
	for (int i = 1; i <= M; i++) {
		cin >> b.dir[i];
	}
	// BC input
	for (int i = 1; i <= A; i++) {
		// x��ǥ, y��ǥ, ����, ����
		int x, y, c, p;
		cin >> x >> y >> c >> p;
		bfs(x, y, c, p, i);
	}
}

void move(int time) {
	a.y += diry[a.dir[time]];
	a.x += dirx[a.dir[time]];
	b.y += diry[b.dir[time]];
	b.x += dirx[b.dir[time]];
}

void solve() {
	// �÷��̾��� ��ġ�� ���� ��Ȳ ����
	// 1. �Ѵ� ���� ���
	if (!map[a.y][a.x].size() && !map[b.y][b.x].size())
		return;
	// 2. b�� ���°���
	else if (!map[a.y][a.x].size() && map[b.y][b.x].size()) {
		// �����ؼ� �ִ��Ŀ�
		sort(map[b.y][b.x].begin(), map[b.y][b.x].end(), cmp);
		sum += map[b.y][b.x][0].power;
	}
	// 3. a�� ���°���
	else if (map[a.y][a.x].size() && !map[b.y][b.x].size()) {
		// �����ؼ� �ִ��Ŀ�
		sort(map[a.y][a.x].begin(), map[a.y][a.x].end(), cmp);
		sum += map[a.y][a.x][0].power;
	}
	// 4. a,b �Ѵ� ���°���
	else if (map[a.y][a.x].size() && map[b.y][b.x].size()) {
		// ���� Ÿ������ �Ǵ�
		int flag = 0;
		for (int i = 0; i < map[a.y][a.x].size(); i++) {
			for (int j = 0; j < map[b.y][b.x].size(); j++) {
				if (map[a.y][a.x][i].type == map[b.y][b.x][j].type)
					flag++;
			}
		}
		// 4-1. �ٸ� Ÿ���϶�, ���� sum�� ������
		if (flag == 0) {
			sort(map[a.y][a.x].begin(), map[a.y][a.x].end(), cmp);
			sort(map[b.y][b.x].begin(), map[b.y][b.x].end(), cmp);
			sum += map[a.y][a.x][0].power;
			sum += map[b.y][b.x][0].power;
		}
		// 4-2. ���� Ÿ���� ������ ��, �ִ��� ��츦 ���ؼ� ������
		else {
			int max = -21e8, tmp;
			for (int i = 0; i < map[a.y][a.x].size(); i++) {
				for (int j = 0; j < map[b.y][b.x].size(); j++) {
					tmp = 0;
					if (map[a.y][a.x][i].type == map[b.y][b.x][j].type) {
						tmp = map[a.y][a.x][i].power;
					}
					else {
						tmp = map[a.y][a.x][i].power + map[b.y][b.x][j].power;
					}
					if (tmp > max)
						max = tmp;
				}
			}
			sum += max;
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

		// solve -> 1�ʸ��� �����ϸ� �÷��̾� �̵�
		for (int T = 0; T <= M; T++) {
			move(T);
			solve();
		}

		// output
		cout << "#" << tc << " " << sum << endl;
	}

	return 0;
}