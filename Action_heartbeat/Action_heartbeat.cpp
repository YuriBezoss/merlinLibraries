#include "Action_heartbeat.h"

void Action_heartbeat::update(float deltaTime) {
    led->flipState();
}