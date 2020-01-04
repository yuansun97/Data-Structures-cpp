#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  if (start == end) {
        return path;
  }

  std::unordered_map<std::string, std::string> predecessor;
  std::queue<std::string> q;

  predecessor[start] = "None";
  q.push(start);

  while(!q.empty()) {
        string curV = q.front();
        q.pop();
        std::list<E_byRef> inciEdges = incidentEdges(curV);
        for (auto e_ref : inciEdges) {
                std::string adjV = "None";
                Edge e = e_ref.get();
                if (e.directed()) {
                        if (e.source().key() == curV) {
                                adjV = e.dest().key();
                        }
                } else {
                        adjV = (e.source().key() == curV) 
                                ? e.dest().key() : e.source().key();
                }

                if (adjV == "None") {
                        continue;
                }

                if (adjV == end) {
                        path.push_back(adjV);
                        while (curV != "None") {
                                path.push_back(curV);
                                curV = predecessor[curV];
                        }
                        std::reverse(path.begin(), path.end());
                        return path;
                }

                if (predecessor.find(adjV) == predecessor.end()) {
                        q.push(adjV);
                        predecessor[adjV] = curV;
                }
                
        }
  }
  return path;




// Way 1 -------------------------------------------
//   std::unordered_map<string, string> babamen;
//   std::unordered_map<string, double> distances;
//   distances[start] = 0;
//   // bool short = false;        
//   auto v = vertexMap.begin();
//   while (v != vertexMap.end()) {
//     distances.insert({v->first, 100000});
//     babamen.insert({v->first, "nothing"});
//     v++;
//   }
//   std::queue<string> q;
//   q.push(start);  
//   for (;!q.empty();) {
//     string first = q.front();
//     q.pop();
//     auto edgelist = incidentEdges(first);
//     auto it = edgelist.begin();
//     while(it != edgelist.end()) {
//       string next;
//       if (it->get().dest().key() != first) {
//         next = it->get().dest().key();
//       } 
//       if (it->get().dest().key() == first) {
//         next = it->get().source().key();
//       }
//       if (distances[next] > (distances[first] + it->get().weight())) {
//         q.push(next);
//       }
//       if (distances[next] > (distances[first] + it->get().weight())) { 
//         babamen[next] = first;     
//       }
//       if (distances[next] > (distances[first] + it->get().weight())) {
//         distances[next] = distances[first] + it->get().weight();
//       }
//       it++;
//     }
//   }
//   string temp = end;
//   while (temp != "nothing") {
//         path.push_front(temp);
//         temp = babamen[temp];
//   }
//   return path;


// Way 2 ---------------------------------------------
  // std::queue<string> bfs;
  // std::unordered_map<string, string> predecessor;
  // std::unordered_map<string, bool> visited;
  // for(auto it = vertexMap.begin(); it != vertexMap.end(); it++){
  //   predecessor[it->first] = "none";
  // }
  // bfs.push(start);
  // predecessor[start] = "start";

  // while(!bfs.empty()){
  //   string temp = bfs.front();
  //   bfs.pop();
  //   //add temp's neighbor
  //   for(auto it = vertexMap.begin(); it != vertexMap.end(); it++){
  //     //write a new isNeighbor function that works slightly different from isAdjacent
  //     bool isNeighbor = false;
  //     for(edgeListIter edgeit : adjList.at(temp)){
  //       if((*edgeit).get().source().key() == it->first ||
  //          (*edgeit).get().dest().key() == it->first){
  //         isNeighbor = true;
  //       }
  //     }

  //     if(isNeighbor && predecessor[it->first] == "none"){
  //       bfs.push(it->first);
  //       predecessor[it->first] = temp;
  //     }
  //   }
  // }

  // string temp2 = end;
  // path.push_back(end);
  // while(temp2 != start){
  //   path.push_back(predecessor[temp2]);
  //   temp2 = predecessor[temp2];
  // }
  // std::reverse(path.begin(),path.end());

  // return path;
}

