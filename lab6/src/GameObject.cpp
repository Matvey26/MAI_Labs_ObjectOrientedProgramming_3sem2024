#pragma once

#include "../include/GameObject.hpp"

Point GameObject::GetPosition() const {
    return position_;
}

void GameObject::SetPosition(const Point& point) {
    position_ = point;
}

void GameObject::AttachObserver(std::shared_ptr<IGameObjectObserver> obs) {
    this->observers_.push_back(obs);
}

void GameObject::Notify(const std::string& message) {
    for (const auto& observer : this->observers_) {
        observer->Update(message);
    }
}

int GameObject::counter_ = 0;
