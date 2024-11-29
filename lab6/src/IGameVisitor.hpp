#pragma once

class IGameVisitor {
public:
    virtual void Visit(class Game& element) = 0;
    virtual ~IGameVisitor() = default;
};