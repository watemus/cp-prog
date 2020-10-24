#include <bits/stdc++.h>
using namespace std;
char tabl[305][305];
int dp[305][305][305];
int dp2[305][305][305];
int pred[305][305][305];
void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> tabl[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int bal = 0; bal <= n + 5; ++bal) {
                dp[i][j][bal] = -1000000000;
                dp2[i][j][bal] = 1000000000;
                pred[i][j][bal] = -1000000000;
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (tabl[n][i] == 'M') {
            dp[n][i][0] = 0;
            dp2[n][i][0] = 0;
            break;
        }
    }
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            for (int bal = 0; bal <= n + 5; ++bal) {
                if (tabl[i][j] == '.' || tabl[i][j] == '*') {
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*') {
                            dp[i][j][bal] = max(dp[i + 1][j + ind][bal], dp[i][j][bal]);
                        }
                    }
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*' && dp[i][j][bal] == dp[i + 1][j + ind][bal] && dp[i][j][bal] >= 0) {
                            if (dp2[i][j][bal] > dp2[i + 1][j + ind][bal]) {
                                dp2[i][j][bal] = dp2[i + 1][j + ind][bal];
                                pred[i][j][bal] = j + ind;
                            }
                        }
                    }
                }
                if (tabl[i][j] == ')' && bal < n) {
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*') {
                            dp[i][j][bal] = max(dp[i + 1][j + ind][bal + 1] + 1, dp[i][j][bal]);
                        }
                    }
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*' && dp[i][j][bal] == dp[i + 1][j + ind][bal + 1] + 1 && dp[i][j][bal] >= 0) {
                            if (dp2[i][j][bal] > dp2[i + 1][j + ind][bal + 1]) {
                                dp2[i][j][bal] = dp2[i + 1][j + ind][bal + 1];
                                pred[i][j][bal] = j + ind;
                            }
                        }
                    }
                }
                if (tabl[i][j] == '(' && bal >= 1) {
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*') {
                            dp[i][j][bal] = max(dp[i + 1][j + ind][bal - 1] + 1, dp[i][j][bal]);
                        }
                    }
                    int minn_pos = -1000000000, minn_res = 1000000000;
                    for (int ind = -1; ind <= 1; ++ind) {
                        if (j + ind >= 1 && j + ind <= m && tabl[i + 1][j + ind] != '*' && dp[i][j][bal] == dp[i + 1][j + ind][bal - 1] + 1 && dp[i][j][bal] >= 0) {
                            if (minn_res > dp2[i + 1][j + ind][bal - 1]) {
                                minn_res = dp2[i + 1][j + ind][bal - 1];
                                minn_pos = j + ind;
                            }
                        }
                    }
                    dp2[i][j][bal] = dp[i][j][bal];
                    pred[i][j][bal] = minn_pos;
                }
            }
        }
    }
    int ans = 0, max_i = -1, max_j = -1, now_pos = 1000000000;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (tabl[i][j] == '*' || i == 1) {
                if (ans < dp[i][j][0]) {
                    ans = dp[i][j][0];
                    max_i = i;
                    max_j = j;
                    now_pos = dp2[i][j][0];
                } else if (ans == dp[i][j][0] && now_pos > dp2[i][j][0]) {
                    ans = dp[i][j][0];
                    max_i = i;
                    max_j = j;
                    now_pos = dp2[i][j][0];
                }
            }
        }
    }
    /*cout << max_i << ' ' << max_j << ' ' << ans << ' ' << now_pos << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int bal = 0; bal <= n; ++bal) {
                cout << i << ' ' << j << ' ' << bal << ' ' << dp[i][j][bal] << ' ' << pred[i][j][bal] << ' ' << dp2[i][j][bal] << endl;
            }
        }
    }*/
    int balance = 0;
    vector<char> now;
    while (max_i < n) {
        if (tabl[max_i][max_j] == '(') {
            now.push_back(tabl[max_i][max_j]);
            int new_i = max_i + 1;
            int new_j = pred[max_i][max_j][balance];
            int new_bal = balance - 1;
            max_i = new_i;
            max_j = new_j;
            balance = new_bal;
        } else if (tabl[max_i][max_j] == ')') {
            now.push_back(tabl[max_i][max_j]);
            int new_i = max_i + 1;
            int new_j = pred[max_i][max_j][balance];
            int new_bal = balance + 1;
            max_i = new_i;
            max_j = new_j;
            balance = new_bal;
        } else {
            //now.push_back(tabl[max_i][max_j]);
            int new_i = max_i + 1;
            int new_j = pred[max_i][max_j][balance];
            int new_bal = balance;
            max_i = new_i;
            max_j = new_j;
            balance = new_bal;
        }
    }
    cout << ans << endl;
    reverse(now.begin(), now.end());
    for (auto u : now) cout << u;
    cout << endl;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    //cin >> t;
    while (t--) run();
    return 0;
}

