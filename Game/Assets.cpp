#include "Assets.h"

using namespace nu;

namespace assets {

    Mesh body{ { Vector2{2, 0},
                 Vector2{0, 1}, 
                 Vector2{ -2, 3},
                 Vector2{ -1, 0}, 
                 Vector2{ -3, -3}, Vector2{ 0, -1}, Vector2{2, 0}}, Color{ 1.0f, 0.0f, 1.0f } };
    Mesh wings{ { Vector2{1, 3}, Vector2{0, 1}, Vector2{ 0, -1}, Vector2{1, -3}, Vector2{1, 3}}, Color{1.0f, 0.5f, 1.0f} };

    Model model{ std::vector<Mesh>{ body } };
    //model.AddMesh(wings);


	nu::Model playerModel;

    Mesh enemyBody{ { Vector2{2, 0},
                 Vector2{0, 1},
                 Vector2{ -2, 3},
                 Vector2{ -1, 0},
                 Vector2{ -3, -3}, Vector2{ 0, -1}, Vector2{2, 0}}, Color{ 1.0f, 0.0f, 1.0f } };
    Mesh enemyWings{ { Vector2{1, 3}, Vector2{0, 1}, Vector2{ 0, -1}, Vector2{1, -3}, Vector2{1, 3}}, Color{0.0f, 1.0f, 1.0f} };

    Model enemyModel{ std::vector<Mesh>{ enemyBody } };
    //model.AddMesh(wings);


    nu::Model enemyModel;
}
