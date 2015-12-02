//
// Struct representing the scene.
//

#ifndef CS180_PROG4_SCENE_H
#define CS180_PROG4_SCENE_H

#include <vector>
#include "Light.h"
#include "Object.h"

typedef struct Scene {
    std::vector<const Object*> objects;
    std::vector<const Light*> lights;
} Scene;

#endif //CS180_PROG4_SCENE_H
