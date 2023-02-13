#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/*
1. �����б�
	- dfs
	- ���� �پ��ִ� core���� �Ǵ����� �ʾƵ� �ɵ�
	- ����� 0, core�� 1, ������ 2�� ǥ���� ��ȹ
	- ������ �����ϴ� ����� �� 5����,
		-> �����¿� + �ƾ� ���� X
*/


struct pos {
	int y;
	int x;
} tmp;


// �ʿ� ���ڵ�
int N; // cell�� ũ��
int map[12][12]; // cell�� ����
int maxCore; // �ִ��� ���� Core
int minLen; // �ִ��� ���� Core�϶� ���� ������ �� �ּ�
vector<pos> core; // core�� ��ġ ���
int diry[] = { -1,0,1,0 };
int dirx[] = { 0,-1,0,1 };



// �ھ��, ����� �ھ�, ���������� �� �Ѱ��� ��
void dfs(int lv, int coreNum, int lenSum) {

	// 2. ���� ���� -> �ھ� �� üũ�ϸ� return
	if (lv == core.size()) {
		
		// 4. �ִ� �ּ� ��
		if (coreNum > maxCore) {
			maxCore = coreNum;
			minLen = lenSum;
		}

		if (coreNum == maxCore) {
			minLen = min(lenSum, minLen);
		}

		return;
	}

	// 1. ���� ��ͷ� ���
	// �����¿� + ����ġ�� �� �ھ�� ����
	// ���±濡 core(1)�� ����(2)������ break;
	for (int i = 0; i < 5; i++) {
		// ����ġ�� ���
		if (i == 4) {
			dfs(lv + 1, coreNum, lenSum);
			continue;
		}
		
		int ny = core[lv].y, nx = core[lv].x; // üũ�ϴ� cell
		int cnt = 0; // �̹� ���࿡�� ��ġ�Ǵ� ��������
		while (1) {
			ny += diry[i];
			nx += dirx[i];
			cnt++;

			// �����߿� core�� ������ ������ break
			if (map[ny][nx] == 1 || map[ny][nx] == 2) {
				cnt = 0;
				break;
			}

			// ���� �����ϸ� break
			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				break;
			}	
		}

		// ������ �� �� �ִ� ��쿡�� ������ ��ġ�Ѵ�
		// 3. ���Ⱑ ��ϰ� dfs�� ���� �κ�
		if (cnt > 0) {

			ny = core[lv].y, nx = core[lv].x;
			while (1) {
				ny += diry[i];
				nx += dirx[i];

				if (ny < 0 || nx < 0 || ny > N - 1 || nx > N - 1)
					break;

				map[ny][nx] = 2;
			}
			dfs(lv + 1, coreNum + 1, lenSum + cnt);
			ny = core[lv].y, nx = core[lv].x;
			while (1) {
				ny += diry[i];
				nx += dirx[i];

				if (ny < 0 || nx < 0 || ny > N - 1 || nx > N - 1)
					break;

				map[ny][nx] = 0;
			}
		}
	}
}


int main() {
	
	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// �׽�Ʈ ���̽����� �ʱ�ȭ
		maxCore = -1;
		minLen = 21e8;
		memset(map, 0, sizeof(map));
		core.clear();

		// input
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];

				if (map[i][j] == 1) {
					// �����ڸ� ������ core ���Ϳ� �ֱ�
					if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
						continue;

					tmp.y = i, tmp.x = j;
					core.push_back(tmp);
				}
			}
		}

		// solve -> dfs�� Ž��
		// �ھ��, ����� �ھ�, ���������� ��
		dfs(0, 0, 0);

		// output
		cout << "#" << tc << " " << minLen << endl;
	}

	return 0;
}