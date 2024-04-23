#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MVNum 100 

//��󶥵��� 
typedef struct ArcNode {                        //���� 
    int adjvex;                                    //�ڽӵ��λ�� 
    struct ArcNode* nextarc;      //ָ����һ�������ָ�� 
}ArcNode;
typedef struct VNode {
    char data;                                    //������Ϣ 
    ArcNode* firstarc;         //ָ���һ�������ָ�� 
}VNode, AdjList[MVNum];                 //AdjList��ʾ�ڽӱ����� 
typedef struct {
    AdjList vertices;              //ͷ�������
    int vexnum, arcnum;     //ͼ�ĵ�ǰ�������ͱ��� 
}ALGraph;

int used[MVNum];//DFS�����ж��Ƿ���ʹ�
int pre[MVNum];//��¼����ǰ�����
int v[MVNum][MVNum]; // ���뻷
int len[MVNum]; // ÿ�����ĳ���
int cnt; // ��������
int index; // ��ʱ��¼�±���

void CreatMGraph(ALGraph* G);/* ����ͼ */
void getPath(ALGraph G);/*����򵥻�·*/
void DFS(ALGraph G, int i, int x);/*����ͼ*/
void find(ALGraph G, int x, int a[]);/*�ݹ�鿴·��*/
int check(int a[], int size);/*����*/
void printPath(ALGraph G);/*��ӡ·��*/

int main()
{
    ALGraph G;
    CreatMGraph(&G);
    getPath(G);
    printf("һ����%d���򵥻�·\n", cnt);
    printPath(G);
    system("pause");
    return 0;
}

void CreatMGraph(ALGraph* G) // ����ͼ
{
    int i, j, k;
    ArcNode* s;
    printf("����������ͼ�Ķ�����:");
    scanf_s("%d", &G->vexnum); // ������ͱ���
    printf("����������ͼ�ı���:");
    scanf_s("%d", &G->arcnum); // ������ͱ���
    getchar();
    printf("�������������ͼ�ĸ�������:");
    for (i = 0; i < G->vexnum; i++)
        scanf_s(" %c", &G->vertices[i].data);
    for (i = 0; i < G->vexnum; i++) G->vertices[i].firstarc = NULL;
    printf("�����������(һ��һ�� �ո�ָ�):\n");
    for (k = 0; k < G->arcnum; k++) {
        scanf_s("%d%d", &i, &j);
        // ���ڽӱ������һ��i��j�������
        s = (ArcNode*)malloc(sizeof(ArcNode)); // ����Ĳ������
        s->adjvex = j;
        s->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = s;
    }
    printf("����ͼ�ڽӱ����ɹ�\n");
}


void getPath(ALGraph G)
{
    memset(pre, -1, sizeof(pre));
    printf("\n�򵥻�·:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        memset(pre, -1, sizeof(pre)); // �����е��ǰ����Ϊ-1
        used[i] = 1; // ���Ϊ�Ѿ��ù�
        DFS(G, i, i); // Ѱ����i��ʼ�ļ򵥻�·
        used[i] = 0; // ��ԭ�ֳ�
    }
}

void find(ALGraph G, int x, int a[]) // �ݹ�Ĵ�ӡ���
{
    if (pre[x] == -1) //��������ͷ��� û��ǰ�����
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
        if (len[i] != size) continue; // Ԫ��������ͬ�űȽ�
        int count = 0, begin = 0;
        //Ϊ����Ƚϣ��ҵ����
        for (int k = 0; k < size; k++)
            if (a[0] == v[i][k])
                begin = k;
        //jָ��Ӵ���ӽ������loop�����ͷ����ʼɨ��
        //kָ����������ҳ�����loop����Ƚϵ���㿪ʼɨ��
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
            pre[j] = i; // �б߲���û���ʹ�����ǰ�������Ϊi
            used[j] = 1;//���Ϊ�ù�
            DFS(G, j, x);
            used[j] = 0;// ��ԭ�ֳ�
        }
        else if (used[j] && j == x) { //����ظ��˲������ʼ����DFS�Ľ��Ŵ�ӡ ��ֹ�ظ���ӡ
            int a[MVNum] = { 0 };
            index = 0;
            find(G, i, a);//��Ϊ�Ǽ�¼ǰ����� ����Ҫ�õݹ������ӡ֮ǰ�Ľ��
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
        printf("��%d���򵥻�·: ", i + 1);
        for (int j = 0; j < len[i]; j++)
            printf("%c ", G.vertices[v[i][j]].data);
        printf("%c\n", G.vertices[v[i][0]].data);
    }
}