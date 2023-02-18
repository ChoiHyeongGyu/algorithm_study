#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


/*
1. �����б�
	- �׳� �ܼ� �����ϸ� �ɰŰ���.
	1) �̻��� ������ ����ü (y,x,�̻�����,�̵�����)
	2) ���� ��Ȳ ������ 2�������� map
	3) ���⺤��
	4) �������� ����ٲ�� ���� ����
	5) �������°� ó��
*/

struct micro {
	// ������ġ, ������ġ, �̻��� ��, �̵�����
	int y, x, num, dir;
};
vector<micro> com; // ���� ������ ����
queue<micro> map[100][100]; // �� ����
// �� map�� priority queue�� �����ߴ��� ��������

// ��: 1, ��: 2, ��: 3, ��: 4
int diry[] = { 0,-1,1,0,0 };
int dirx[] = { 0,0,0,-1,1 };

// �ʿ� ���ڵ�
int N, K, M; // ���� ũ��, ���� ������ ����, �ݸ� �ð�

void reset() {
	com.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			while (!map[i][j].empty())
				map[i][j].pop();
	}
}

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		micro tmp;
		cin >> tmp.y >> tmp.x >> tmp.num >> tmp.dir;
		com.push_back(tmp);
	}
	// ù ��Ȳ map�� �ʿ������ ���� ���� ���� �־���
	for (int i = 0; i < com.size(); i++) {
		map[com[i].y][com[i].x].push(com[i]);
	}
}

void move() {
	for (int i = 0; i < com.size(); i++) {
		map[com[i].y][com[i].x].pop(); // map���� �̻��� ����
		com[i].y += diry[com[i].dir];
		com[i].x += dirx[com[i].dir];
		map[com[i].y][com[i].x].push(com[i]); // ���ο� �ڸ��� �ٽ� �־���
	}
}

void merge() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int len = map[i][j].size();
			// cell ����� 2�̻��̸� �̻��� ��ģ��
			if (len >= 2) {
				// �̻��� �����ְ� ���� �ִ� �̻�����
				micro tmp = {i,j,0,0};
				int maxnum = -21e8;
				for (int k = 0; k < len; k++) {
					tmp.num += map[i][j].front().num;
					if (map[i][j].front().num > maxnum) {
						maxnum = map[i][j].front().num;
						tmp.dir = map[i][j].front().dir;
					}
					map[i][j].pop();
				}
				for (int k = 0; k < com.size(); k++) {
					if (com[k].y == i && com[k].x == j) {
						com.erase(com.begin() + k);
						k--;
					}
				}
				map[i][j].push(tmp);
				com.push_back(tmp);
			}
		}
	}
}

void checkBorder() {
	for (int i = 0; i < com.size(); i++) {
		// ���� ���� ���
		if (com[i].y == 0) {
			com[i].num /= 2;
			com[i].dir = 2;
		}

		// �Ʒ��� ���� ���
		else if (com[i].y == N - 1) {
			com[i].num /= 2;
			com[i].dir = 1;
		}

		// ���ʿ� ���� ���
		else if (com[i].x == 0) {
			com[i].num /= 2;
			com[i].dir = 4;
		}

		// �����ʿ� ���� ���
		else if (com[i].x == N - 1) {
			com[i].num /= 2;
			com[i].dir = 3;
		}

		// ���ڰ� 0�� �Ǹ� ����
		if (com[i].num == 0) {
			map[com[i].y][com[i].x].pop();
			com.erase(com.begin() + i);
			i--;
		}
	}
}

int sum() {

	int total = 0;
	for (int i = 0; i < com.size(); i++) {
		total += com[i].num;
	}
	return total;
}

int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// �׽�Ʈ ���̽����� �ʱ�ȭ
		reset();

		// input
		input();

		// solve -> 1�ʸ��� ����
		for (int i = 1; i <= M; i++) {
			move(); // ���� ���� �̻��� ������
			merge(); // ��ġ�� �̻��� Ȯ�� �� �պ�
			checkBorder(); // �����ڸ� ó��
		}

		// output
		int result = sum();
		cout << "#" << tc << " " << result << endl;
	}

	return 0;
}
