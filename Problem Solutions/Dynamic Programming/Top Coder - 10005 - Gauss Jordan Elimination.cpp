/*
	Problem Link: https://c...content-available-to-author-only...r.com/stat?c=problem_statement&pm=10005
*/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 52;
int cellId[N][N];

const double eps = 1e-15;
int cmp(const double&x, const double&y){
    if (fabs(x - y) < eps){
        return 0;
    }
    return (x > y) * 2 - 1;
}

bool make_nonZero(vector<valarray< double>> &eq, int i){
    for (int j = i + 1; j < eq.size(); ++j) {
        if (cmp(eq[j][i], 0.0) != 0){
            swap(eq[i], eq[j]);
            return true;
        }
    }
    return false;
}
bool solve(vector<valarray<double>> &eq){
    for (int i = 0; i < eq.size(); ++i) {
        // check if current row = zeros --> swap(current row, back()) then pop_back()
        if (cmp(eq[i][i], 0.0) == 0){
            if (!make_nonZero(eq, i)){
                return false;
            }
        }
        double cur = eq[i][i];
        eq[i] /= cur;

        for (int j = 0; j < eq.size(); ++j) {
            if (i == j) continue;
            if (cmp(eq[j][i], 0.0) == 0){
                continue;
            }

            cur = eq[j][i];
            eq[j] += -cur * eq[i];
        }
    }
    return true;
}

class MazeWandering{
public:
    double expectedTime(vector<string> input){
        int cnt = 0, gi, gj;
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].length(); ++j){
                if (input[i][j] != 'X'){
                    cellId[i][j] = cnt++;
                }
                if (input[i][j] == '*'){
                    gi = i; gj = j;
                }
            }
        }

        vector<valarray<double>> eq(cnt, valarray<double>(0.0, cnt + 1));

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].length(); ++j) {
                if (input[i][j] == 'X'){
                    continue;
                }
                if (i == gi and j == gj){
                    continue;
                }

                int di = 0, dj = -1;
                vector<int> vec;
                for (int k = 0; k < 4; ++k) {

                    int ni = i + di, nj = j + dj;
                    if (!(ni < 0 or nj < 0 or ni >= input.size() or nj >= input.front().length() or input[ni][nj] == 'X')){
                        vec.push_back(cellId[ni][nj]);
                    }

                    swap(di, dj);
                    if (k == 1){
                        di *= -1;
                        dj *= -1;
                    }
                }

                int x = cellId[i][j];
                eq[x][x] = -1;
                eq[x][cnt] = -1;

                for (auto itr : vec){
                    eq[x][itr] = 1.0 / vec.size();
                }
            }
        }

        eq[cellId[gi][gj]][cellId[gi][gj]] = 1;
        solve(eq);

        double ret = 0.0;
        for (auto &e : eq){
            ret += e[cnt];
        }
        ret /= cnt;
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef CLion
    freopen("input.txt" , "r" , stdin);
#endif

    MazeWandering obj;
    cout << fixed << setprecision(10) << obj.expectedTime(
            {"*........",
             "XXX.XXXX.",
             ".XX.X....",
             ".....XX.X"});
    return 0;
}
