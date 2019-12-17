/*
 * graph_link.h
 *
 *  Created on: 2019��7��9��
 *      Author: xiaow
 */

#ifndef SRC_VEINS_MODULES_UTILITY_GRAPH_LINK_H_
#define SRC_VEINS_MODULES_UTILITY_GRAPH_LINK_H_


#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <memory.h>

#define default_vertex_size 10
#define T char

//�ߵĽṹ
typedef struct Edge{
  //������±�
  int idx;
  //ָ����һ���ߵ�ָ��
  struct Edge* link;
}Edge;

//����Ľṹ
typedef struct Vertex{
  //�����ֵ
  T data;
  //��
  Edge* adj;
}Vertex;

//ͼ�Ľṹ
typedef struct GraphLink{
  int MaxVertices;
  int NumVertices;
  int NumEdges;

  Vertex* nodeTable;
}GraphLink;

//��ʼ��ͼ
void init_graph_link(GraphLink* g);
//��ʾͼ
void show_graph_link(GraphLink* g);
//���붥��
void insert_vertex(GraphLink* g, T v);
//�����β��
void insert_edge_tail(GraphLink* g, T v1, T v2);
//�����ͷ��
void insert_edge_head(GraphLink* g, T v1, T v2);
//ȡ��ָ������ĵ�һ�����򶥵�
int get_first_neighbor(GraphLink* g, T v);
//ȡ��ָ������v1���ٽֶ���v2�ĵ�һ�����򶥵�
int get_next_neighbor(GraphLink* g, T v1, T v2);

//��������
void topo_sort(GraphLink* g);


#endif /* SRC_VEINS_MODULES_UTILITY_GRAPH_LINK_H_ */
