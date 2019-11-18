#include "Level1.h"
#define LEVEL1_WIDTH 25
#define LEVEL1_HEIGHT 8

unsigned int level1_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    3, 1, 1, 1, 1, 1, 1, 2, 0, 0, 2, 0, 0, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 2, 2, 0, 0, 2, 3, 0, 0, 2, 2
};

void Level1::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(5, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("me.png");
    state.player.lives = 3;

    
    state.nextLevel = -1;
    state.enemy.textureID = Util::LoadTexture("evilred.png");
    state.enemy.entityType = ENEMY;
    state.enemy.isStatic = false;
    state.enemy.width = 1.0f;
    state.enemy.position = glm::vec3(15, -4, 0);
    state.enemy.acceleration = glm::vec3(0, -9.81f, 0);
}

void Level1::Update(float deltaTime) {
    state.player.Update(deltaTime, NULL, 0, state.map);

    
    if (state.player.position.x > 24){
        state.nextLevel = 2;
    }
    if (state.enemy.position.x == 15.0f && (glm::distance(state.enemy.position, state.player.position) < 6.0f)) state.enemy.velocity.x = 1.0f;
    else if (state.enemy.position.x == 1.0f) state.enemy.velocity.x = 1.0f;

    state.enemy.Update(deltaTime, &state.player, 1, state.map);
}

void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    if (state.enemy.death != true) state.enemy.Render(program);
}
