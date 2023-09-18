
#define TRUE 1
#define FALSE 0


#include <cmath>
#include <iostream>
using namespace std;

static const unsigned int C = 299792458;

class Vec3 {
	public:
		Vec3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	
		Vec3() {

			this->x = 0;
			this->y = 0; 
			this->z = 0;
		}

		float get_magnitude() {
			return sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
		}

		float x;
		float y;
		float z;
};


class PointMass {
	public:
		PointMass(float rest_mass, Vec3 coords, bool is_relativistic) {
			this->coords = coords;
			this->rest_mass = rest_mass;
			this->velocity = Vec3(0,0,0);
			this->timestep = 0.1;
		}

		void change_momentum(Vec3 force) {
			float true_mass = this->rest_mass / sqrt(1 - pow(this->velocity.get_magnitude(), 2) / pow(C,2));
			this->velocity.x += this->timestep * (force.x / true_mass);
			this->velocity.y += this->timestep * (force.y / true_mass);
			this->velocity.z += this->timestep * (force.z / true_mass);
		}	

		void step() {
			this->coords.x += this->velocity.x * this->timestep;
			this->coords.y += this->velocity.y * this->timestep;
			this->coords.z += this->velocity.z * this->timestep;

		}

	
	// momentum is all you need
	float rest_mass;
	Vec3 coords; 
	Vec3 velocity; 

	float timestep;
};




int main() {
	
	Vec3 point = Vec3(0,10000000,0);
	PointMass m = PointMass(1,point, TRUE); 
	float time = 0.0;

	while(1) {
		m.change_momentum(Vec3(0, -100000000, 0));		
		m.step();
		time += m.timestep;

		cout << m.coords.y << "\n";
		if(m.coords.y <= 0) break;

	}
	

	cout << "Total time: " << time << "\n";
	return 0;


}
