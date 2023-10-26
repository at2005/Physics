
#include <cmath>
#include <iostream>
using namespace std;

static const unsigned int C = 299792458;


// Newtonian 3-vector
class Vec3 {
	public:
		Vec3(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	
		Vec3() {

			this->x = 0;
			this->y = 0; 
			this->z = 0;
		}

		double get_magnitude() {
			return sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
		}

		
		Vec3 operator+(Vec3 b) {
			Vec3 res(this->x + b.x, this->y + b.y, this->z + b.z);
			return res;

		}


		Vec3 operator-(Vec3 b) {
			Vec3 res(this->x - b.x, this->y - b.y, this->z - b.z);
			return res;

		}

		double x;
		double y;
		double z;



};



// newtonian point-mass with Einstein special relativistic support
class PointMass {
	public:
		PointMass(float rest_mass, Vec3 coords, bool is_relativistic, Vec3 init_velocity) {
			this->coords = coords;
			this->rest_mass = rest_mass;
			this->velocity = init_velocity; 

			this->true_mass = is_relativistic ? rest_mass / sqrt(1.0 - (pow(this->velocity.get_magnitude(), 2) / pow(C, 2))) : rest_mass;
			// hard-coded timestep for now
			this->timestep = 1e-11;
			
			

		}


		void change_momentum(Vec3 force) {
			this->velocity.x += this->timestep * (force.x / this->true_mass);
			this->velocity.y += this->timestep * (force.y / this->true_mass);
			this->velocity.z += this->timestep * (force.z / this->true_mass);
		}	

		void step() {
			//this->true_mass = is_relativistic ? rest_mass / sqrt(1.0 - (pow(this->velocity.get_magnitude(), 2) / pow(C, 2))) : rest_mass;
			this->coords.x += this->velocity.x * this->timestep;
			this->coords.y += this->velocity.y * this->timestep;
			this->coords.z += this->velocity.z * this->timestep;

		}

		
		void set_break_cond(bool (*bc)(PointMass*)) {
			(*break_cond)(PointMass*) = (*bc);
		} 
		
		bool breaking_condition() {
			if(this->velocity.y >= 4.0) return true;
			return false;
			
		}

		
	
	// momentum is all you need (for now)
	float rest_mass;
	float true_mass;
	Vec3 coords; 
	Vec3 velocity; 
	
	bool (*break_cond)(PointMass*);

	double timestep;
};



double random_force(double time) {
	// just some random force to test motion of particles
	return time * time * 3 * sqrt(time) + time * 12 - 1/(2*time);		

}

int main() {
	

	// acrobatic frog
	Vec3 point = Vec3(0,0,0);
	PointMass m = PointMass(12.3e-3,point, false, Vec3(0, 0, 0)); 
	double time = 0.0;
	
	Vec3 ground_force = Vec3(0, (m.rest_mass * 4009.8) /*- (m.rest_mass * 9.8)*/, 0);
	Vec3 gravity = Vec3(0, m.rest_mass * -9.8, 0);
	Vec3 total_force = ground_force + gravity;
	
//	double weight = m.rest_mass * 9.8;
//	double alt_force_mag = weight * (4000/9.8 + 1.0);

//	Vec3 alt_force = Vec3(0, alt_force_mag, 0) + gravity; 

	while(true) {
		if(time >= 1e-3) break;
		m.change_momentum(total_force);
		m.step();
		time += m.timestep;

	}
	
	cout << "Final Velocity: " << m.velocity.y << "\n";
	cout << "Total time: " << time << " seconds\n";

	return 0;


}
