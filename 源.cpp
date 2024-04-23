#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MVNum 100 

//最大顶点数 
typedef struct ArcNode {                        //表结点 
    int adjvex;                                    //邻接点的位置 
    struct ArcNode* nextarc;      //指向下一个表结点的指针 
}ArcNode;
typedef struct VNode {
    char data;                                    //顶点信息 
    ArcNode* firstarc;         //指向第一个表结点的指针 
}VNode, AdjList[MVNum];                 //AdjList表示邻接表类型 
typedef struct {
    AdjList vertices;              //头结点数组
    int vexnum, arcnum;     //图的当前顶点数和边数 
}ALGraph;

int used[MVNum];//DFS用以判断是否访问过
int pre[MVNum];//记录结点的前驱结点
int v[MVNum][MVNum]; // 存入环
int len[MVNum]; // 每个环的长度
int cnt; // 环的数量
int index; // 临时记录下标用

void CreatMGraph(ALGraph* G);/* 创建图 */
void getPath(ALGraph G);/*输出简单回路*/
void DFS(ALGraph G, int i, int x);/*遍历图*/
void find(ALGraph G, int x, int a[]);/*递归查看路径*/
int check(int a[], int size);/*查重*/
void printPath(ALGraph G);/*打印路径*/

int main()
{
    ALGraph G;
    CreatMGraph(&G);
    getPath(G);
    printf("一共有%d条简单回路\n", cnt);
    printPath(G);
    system("pause");
    return 0;
}

void CreatMGraph(ALGraph* G) // 读入图
{
    int i, j, k;
    ArcNode* s;
    printf("请输入有向图的顶点数:");
    scanf_s("%d", &G->vexnum); // 结点数和边数
    printf("请输入有向图的边数:");
    scanf_s("%d", &G->arcnum); // 结点数和边数
    getchar();
    printf("请依次输出有向图的各个顶点:");
    for (i = 0; i < G->vexnum; i++)
        scanf_s(" %c", &G->vertices[i].data);
    for (i = 0; i < G->vexnum; i++) G->vertices[i].firstarc = NULL;
    printf("请输入各条边(一行一条 空格分隔):\n");
    for (k = 0; k < G->arcnum; k++) {
        scanf_s("%d%d", &i, &j);
        // 在邻接表中添加一条i到j的有向边
        s = (ArcNode*)malloc(sizeof(ArcNode)); // 链表的插入操作
        s->adjvex = j;
        s->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = s;
    }
    printf("有向图邻接表创建成功\n");
}


void getPath(ALGraph G)
{
    memset(pre, -1, sizeof(pre));
    printf("\n简单回路:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        memset(pre, -1, sizeof(pre)); // 将所有点的前驱设为-1
        used[i] = 1; // 标记为已经用过
        DFS(G, i, i); // 寻找以i开始的简单回路
        used[i] = 0; // 还原现场
    }
}

void find(ALGraph G, int x, int a[]) // 递归的打印结点
{
    if (pre[x] == -1) //代表遇到头结点 没有前驱结点
    {
        a[index++] = x;
        return;
    }
    find(G, pre[x], a);
    a[index++] = x;
}

int check(int a[], int size)
{
    for (int i = 0; i < cnt; i++)
    {
        if (len[i] != size) continue; // 元素数量相同才比较
        int count = 0, begin = 0;
        //为方便比较，找到起点
        for (int k = 0; k < size; k++)
            if (a[0] == v[i][k])
                begin = k;
        //j指针从待添加结果集的loop数组的头部开始扫描
        //k指针从上述所找出的与loop数组比较的起点开始扫描
        for (int j = 0, k = begin; j < size; j++, k = (k + 1) % size)
            if (a[j] == v[i][k])
                count++;
        if (count == size) return 0;
    }
    return 1;
}


void DFS(ALGraph G, int i, int x)
{
    ArcNode* p;
    for (p = G.vertices[i].firstarc; p; p = p->nextarc)
    {
        int j = p->adjvex;
        if (!used[j])
        {
            pre[j] = i; // 有边并且没访问过就那前驱结点设为i
            used[j] = 1;//标记为用过
            DFS(G, j, x);
            used[j] = 0;// 还原现场
        }
        else if (used[j] && j == x) { //结点重复了并且是最开始进入DFS的结点才打印 防止重复打印
            int a[MVNum] = { 0 };
            index = 0;
            find(G, i, a);//因为是记录前驱结点 所以要用递归逆序打印之前的结点
            if (check(a, index))
            {
                len[cnt] = index;
                for (int k = 0; k < index; k++)
                    v[cnt][k] = a[k];
                cnt++;
            }
        }
    }

}

void printPath(ALGraph G)
{
    for (int i = 0; i < cnt; i++)
    {
        printf("第%d条简单回路: ", i + 1);
        for (int j = 0; j < len[i]; j++)
            printf("%c ", G.vertices[v[i][j]].data);
        printf("%c\n", G.vertices[v[i][0]].data);
    }
}