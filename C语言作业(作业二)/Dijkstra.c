#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005  // 最大顶点数
#define MAXM 200005  // 最大边数
#define MOD 100003   // 结果取模的基数
#define INF 0x3f3f3f3f  // 表示无穷大

// 边的结构体，用于邻接表存储图
typedef struct Node {
    int to;       // 边的终点
    int next;     // 下一条边的索引
} Edge;

Edge edges[MAXM * 2];  // 存储所有边，乘以2是因为无向图每条边存两次
int head[MAXN];       // head[u]表示顶点u的第一条边的索引
int dist[MAXN];       // dist[v]表示从起点到顶点v的最短距离
int cnt[MAXN];        // cnt[v]表示从起点到顶点v的最短路径数目
int vis[MAXN];        // vis[v]标记顶点v是否已确定最短路径
int n, m, edge_count; // n为顶点数，m为边数，edge_count为边的计数器

// 添加一条从u到v的边
void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

// Dijkstra算法计算最短路径及数目
void dijkstra() {
    // 初始化距离数组为无穷大
    memset(dist, INF, sizeof(dist));
    // 初始化路径数目数组为0
    memset(cnt, 0, sizeof(cnt));
    // 初始化访问标记数组为0
    memset(vis, 0, sizeof(vis));
    
    // 起点1的距离为0，路径数目为1
    dist[1] = 0;
    cnt[1] = 1;
    
    // 主循环，处理所有顶点
    for (int i = 1; i <= n; i++) {
        // 1. 选择未访问的距离最小的顶点u
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        // 如果找不到未访问的顶点，退出循环
        if (u == -1) break;
        vis[u] = 1;  // 标记顶点u为已访问
        
        // 2. 遍历u的所有邻接顶点v
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;  // 获取邻接顶点v
            
            // 如果通过u到达v的路径更短
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;  // 更新最短距离
                cnt[v] = cnt[u];        // 继承路径数目
            } 
            // 如果通过u到达v的路径长度相同
            else if (dist[v] == dist[u] + 1) {
                // 累加路径数目，并取模防止溢出
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
}

int main() {
    // 初始化头数组为-1，表示没有边
    memset(head, -1, sizeof(head));
    edge_count = 0;  // 初始化边计数器
    
    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // 添加双向边
        add_edge(u, v);
        add_edge(v, u);
    }
    
    // 执行Dijkstra算法计算最短路径及数目
    dijkstra();
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        printf("%d\n", cnt[i]);
    }
    
    return 0;
}