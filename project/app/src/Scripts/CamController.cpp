#include "CamController.h"

namespace Maze {
    CamController::CamController(EisEngine::Game &game, Entity* objectToFocus) :
    game(game) {
        camera = &game.camera;
        focusTransform = objectToFocus->transform;
        game.onUpdate.addListener([&](Game& game){
            Update(game);
        });
    }

    void CamController::Update(EisEngine::Game &_) {
        auto moveModifier = Time::deltaTime * movementSpeed;
        if(Input::GetKeyDown(KeyCode::W)) {
            auto moveVector = -camera->transform->Forward();
            moveVector.y = 0;
            camera->transform->Translate(moveVector * moveModifier);
        }
        if(Input::GetKeyDown(KeyCode::A)) {
            auto moveVector = -camera->transform->Right();
            moveVector.y = 0;
            camera->transform->Translate(moveVector * moveModifier);
        }
        if(Input::GetKeyDown(KeyCode::S)) {
            auto moveVector = camera->transform->Forward();
            moveVector.y = 0;
            camera->transform->Translate(moveVector * moveModifier);
        }
        if(Input::GetKeyDown(KeyCode::D)) {
            auto moveVector = camera->transform->Right();
            moveVector.y = 0;
            camera->transform->Translate(moveVector * moveModifier);
        }
        if(Input::GetKeyDown(KeyCode::Space)) {
            auto moveVector = Vector3::up;
            camera->transform->Translate(moveVector * flyModifier * moveModifier);
        }
        if(Input::GetKeyDown(KeyCode::LeftControl)) {
            auto moveVector = -Vector3::up;
            camera->transform->Translate(moveVector * flyModifier * moveModifier);
        }

        if(Input::GetKeyDown(KeyCode::F)){
            camera->transform->SetGlobalPosition(focusTransform->GetLocalPosition() + Vector3(1, 2, 5));
            camera->transform->SetLocalRotation(Vector3(-15, -15, 0));
        }
        else if(Input::GetLeftMouseButtonDown()){
            auto mousePos = Input::MousePos();
            // offset from centre
            auto size = game.context.GetWindowSize();
            auto normalizedMousePos = Vector2(mousePos.x / size.x, mousePos.y / size.y);
            auto centre = Vector2(0.5f, 0.5f);
            auto centreOffset = normalizedMousePos - centre;

            auto result = Vector2(-centreOffset.y * rotationSpeed, -centreOffset.x * rotationSpeed);
            if(abs(result.x) > maxRotationDeg)
                result.x = result.x > 0 ? maxRotationDeg : -maxRotationDeg;
            if(abs(result.y) > maxRotationDeg)
                result.y = result.y > 0 ? maxRotationDeg : -maxRotationDeg;

            camera->transform->Rotate(result * Time::deltaTime);
        }
    }
}
