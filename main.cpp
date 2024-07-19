#include <iostream>
#include "Vec3.h"
#include "Color.h"
#include "Camera.h"
#include <map>

int main(){
    Camera camera;
    camera.setup();
    camera.render();
    // std::map<double, std::vector<double>> m;
    // for (int i = 0; i < 500; i++){
    //     double d = random_double();
    //     int index = int(d * 10);
    //     m[index].push_back(d);
    // }

    // for (auto e : m){
    //     std::cout << e.first << " :" << e.second.size();
    //     // for (auto d : e.second){
    //     //     std::cout << d << " ";
    //     // }
    //     std::cout << std::endl;
    // }
}