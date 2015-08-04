#include "Global.h"

float aspect = static_cast<float>(WIN_W) / static_cast<float>(WIN_H);
float perspective = 45.0f;

std::mutex gMutex;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 upper = glm::vec3(0.0f, 1.0f, 0.0f);

float listnerPos[] = { 0.0f, 0.0f, 0.0f };

float gravity = 0.01f;
