#include "../include/GameObject.hpp"

GameObject::GameObject() : id_(++counter_), position_(0) {}

GameObject::GameObject(const Point& position) : id_(++counter_), position_(position) {}

int GameObject::GetId() const {
    return this->id_;
}

Point GameObject::GetPosition() const {
    return position_;
}

void GameObject::SetPosition(const Point& point, double min, double max) {
    position_ = Point{
        std::min(max, std::max(min, point.GetX())),
        std::min(max, std::max(min, point.GetY()))
    };
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
