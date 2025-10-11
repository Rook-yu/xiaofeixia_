#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001  // 顶点最大1e6+1
#define MAXM 4000001  // 边最大2e6*2（无向图）
#define MOD 100003

// 邻接表存储边
typedef struct Edge {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN];  // 头节点数组
int dist[MAXN];  // 距离数组（-1表示未访问）
int cnt[MAXN];   // 路径计数数组
int q[MAXN];     // BFS队列
int n, m, edge_cnt;

// 添加无向边
void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int main() {
    memset(head, -1, sizeof(head));
    edge_cnt = 0;

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);  // 无向图双向添加
    }

    memset(dist, -1, sizeof(dist));
    int front = 0, rear = 0;
    q[rear++] = 1;
    dist[1] = 0;
    cnt[1] = 1;

    // BFS核心逻辑
    while (front < rear) {
        int u = q[front++];  // 出队
        // 遍历所有邻接边
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (dist[v] == -1) {  // 首次访问，更新距离和计数
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                q[rear++] = v;    // 入队
            } else if (dist[v] == dist[u] + 1) {  // 同最短距离，累加计数
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", cnt[i] % MOD);
    }

    return 0;
}
