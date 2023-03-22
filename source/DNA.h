#include <glm/glm.hpp>
#include <vector>
using namespace std;
using namespace glm;
class DNA {
public:
	DNA();
	DNA(vector<vec2>const& gene);
	~DNA();
	vector<vec2> gene;
	
	vector<vec2> CrossOver(vector<vec2> const& waifu);
	vector<vec2> Mutation();
};

DNA::DNA() {

}

DNA::DNA(vector<vec2>const &gene) {
	this->gene = gene;
}

DNA::~DNA() {
}