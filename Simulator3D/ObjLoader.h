#include <vector>
#include <string>


bool loadOBJ(const std::string& path,
	std::vector<float>& outVertices,
	std::vector<unsigned int>& outIndices);