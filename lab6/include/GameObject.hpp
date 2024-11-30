#pragma once

#include "Point.hpp"
#include <utility>
#include <memory>
#include <vector>
#include <IGameObjectObserver.hpp>

// Класс игрового объекта

class GameObject {
private:
    static int counter_;
    int id_;
    Point position_;
    std::vector<std::shared_ptr<IGameObjectObserver>> observers_;

protected:
    GameObject();
    GameObject(const Point& position);

public:
    int GetId() const;

    virtual void Save() const = 0;
    virtual void Print() const = 0;

    Point GetPosition() const;
    void SetPosition(const Point& point);

    void AttachObserver(std::shared_ptr<IGameObjectObserver> obs);
    void Notify(const std::string& message);
};
