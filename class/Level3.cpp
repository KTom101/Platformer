#include "Level3.h"


#define LEVEL3_WIDTH 11
#define LEVEL3_HEIGHT 8


unsigned int level3_data[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void Level3::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
    
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(2, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.player.lives = 3;
    
    state.nextLevel = -1;
    state.enemy.textureID = Util::LoadTexture("evilred.png");
    state.enemy.entityType = ENEMY;
    state.enemy.isStatic = false;
    state.enemy.width = 1.0f;
    state.enemy.position = glm::vec3(9, -5, 0);
    state.enemy.acceleration = glm::vec3(0, -9.81f, 0);
    
}

void Level3::Update(float deltaTime) {
    state.player.Update(deltaTime, &state.enemy, 1, state.map);
   
    if (state.player.lives >= 0){
        state.player.death = true;
    }
    
    
    if (state.enemy.death && state.player.death == false){
        state.player.win = true;
    }
    
    if (state.enemy.position.x == 9.0f) state.enemy.velocity.x = -1.0f;
    else if (state.enemy.position.x == 1.0f) state.enemy.velocity.x = 1.0f;

    state.enemy.Update(deltaTime, &state.player, 1, state.map);


}

void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    if (state.enemy.death != true) state.enemy.Render(program);
}
