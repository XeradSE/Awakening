#pragma once

#include "./Component.hpp"
#include <memory>
#include <utility>
#include <vector>

class Entity {
  std::vector<std::unique_ptr<Component>> components;

public:
  template <typename T, typename... TArgs> T *AddComponent(TArgs &&...args) {
    auto comp = std::make_unique<T>(std::forward<TArgs>(args)...);
    comp->owner = this;
    T *ptr = comp.get();
    components.push_back(std::move(comp));
    return ptr;
  }

  template <typename T> T *GetComponent() {
    for (auto &comp : components) {
      if (T *ptr = dynamic_cast<T *>(comp.get())) {
        return ptr;
      }
    }
    return nullptr;
  }

  void Update(float dt);
  void Draw();
};
