#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return (adjList.at(v.key())).size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  auto edges = list<edgeListIter>();
  adjList.insert({key, edges});
  vertexMap.insert({key, v});
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  // for (auto it : adjList.at(key)) {
  //   removeEdge(it);
  // }
  // auto index = vertexMap.find(key);
  // if (index != vertexMap.end()) {
  //   adjList.erase(key);
  //   vertexMap.erase(key);
  // }
  if (vertexMap.find(key) != vertexMap.end()) {
    for (auto it = vertexMap.begin(); it != vertexMap.end(); it++) {
      if (edgeList.front().get().directed() == false) {
        removeEdge(key, it->first);
      } else {
        removeEdge(key, it->first);
        removeEdge(it->first, key);
      }
    }
    vertexMap.erase(key);
  } else {
    return;
  }
  // for (auto i = vertexMap.begin(); i != vertexMap.end(); i++) {
  //   cout << i->first << endl;
  // }
  

}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E * e = new E(v1, v2);
  E & e_ref = *e;
  edgeList.push_front(e_ref);
  auto it = edgeList.begin();
  adjList.at(v1.key()).push_back(it);
  adjList.at(v2.key()).push_back(it);
  return e_ref;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
    if ((it->get().source()).key() == key1 && (it->get().dest()).key() == key2) {
      if (it->get().directed() == true) {
        adjList.at(key1).remove(it);
      } else {
        adjList.at(key1).remove(it);
        adjList.at(key2).remove(it);
      }
      edgeList.erase(it);
    }
    // } else if ((it->get().source()).key() == key2 && (it->get().dest()).key() == key1) {
    //   edgeList.erase(it);
    //   if ((it->get().directed() == false)) {
    //     adjList.at(key1).remove(it);
    //   }     
    //   adjList.at(key2).remove(it);
    // }
  }
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  auto e = *it;
  auto v1 = e.get().source();
  auto v2 = e.get().dest();
  removeEdge(v1.key(), v2.key());
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
    if ((it->get().source()).key() == key || (it->get().dest()).key() == key) {
      edges.push_back(*it);
    }
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  for (auto & it : adjList.at(key1)) {
    if (it->get().dest().key() == key2) {
      return true;
    }
  }
  for (auto & it : adjList.at(key2)) {
    if (it->get().dest().key() == key1 && it->get().directed() == false) {
      return true;
    }
  }
  return false;
}