#ifndef BRUTE_FORCE_VERTEX_COVER_H
#define BRUTE_FORCE_VERTEX_COVER_H

#include <vector>

bool isVertexCover(const std::vector<std::vector<int>>& graph, const std::vector<int>& cover);
std::vector<int> findMinimalVertexCover(const std::vector<std::vector<int>>& graph);

#endif // BRUTE_FORCE_VERTEX_COVER_H