#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
//#include <SDL_image.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Map.h"

enum  EntityType { PLAYER, PLATFORM, COIN, ENEMY };

enum AIState { IDLE, WALKING, PATROLING};

enum AIType { WALKER , JUMPER ,  PATROLER };


class Entity {
public:
    
    EntityType entityType;
    AIState aiState;
    AIType aiType;
    
    bool isStatic;
    bool isActive;
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    
    float width;
    float height;
    
    float speed;
    
    GLuint textureID;
    
    Entity();
    
    bool CheckCollision(Entity other, int count);
    
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckCollisionsY(Entity *objects, int objectCount);
    
    void CheckCollisionsX(Map *map);
    void CheckCollisionsY(Map *map);
    
    void Update(float deltaTime, Entity *objects, int objectCount, Map *map);
    void Render(ShaderProgram *program);
    
    void Jump();
   // void AIRunner(Entity player);
    void AIPatroler(Entity player);
    void AI(Entity player);
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
    bool collidedTopEnemy;
    bool collidedBottomEnemy;
    bool collidedLeftEnemy;
    bool collidedRightEnemy;
    bool death;
    bool win;
   
    
    int lives = -1;
    
};



