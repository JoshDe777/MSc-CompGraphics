#include "CamController.h"

namespace Maze {
    CamController::CamController(EisEngine::Game &game) {
        camera = &game.camera;
        game.onUpdate.addListener([&](Game& game){
            Update(game);
        });
    }

    void CamController::Update(EisEngine::Game &_) {
        auto moveModifier = Time::deltaTime * movementSpeed;
        if(Input::GetKeyDown(KeyCode::W))
            camera->transform->Translate(camera->transform->Forward() * moveModifier);
        if(Input::GetKeyDown(KeyCode::A))
            camera->transform->Translate(camera->transform->Right() * -moveModifier);
        if(Input::GetKeyDown(KeyCode::S))
            camera->transform->Translate(camera->transform->Forward() * -moveModifier);
        if(Input::GetKeyDown(KeyCode::D))
            camera->transform->Translate(camera->transform->Right() * moveModifier);
        if(Input::GetKeyDown(KeyCode::Space))
            camera->transform->Translate(camera->transform->Up() * moveModifier);
        if(Input::GetKeyDown(KeyCode::LeftControl))
            camera->transform->Translate(camera->transform->Up() * -moveModifier);
    }
}
