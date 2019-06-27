#include "src/vector.cpp"

int main(int argc, char **argv) {
	Vec3f vec = Vec3f(1,2,3);

	std::cout << vec << "\n" << std::endl;

	std::cout << vec.length() << std::endl;
}

