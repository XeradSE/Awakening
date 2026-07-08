// Ceci est une classe (qui sert de/serait une interface en Java par exemple)
// qui dicte quels class les composants devront implémenter

#pragma once

class Entity; // Déclaration anticipé pour que le composant connaisse l'entité

class Component {
public:
  Entity *owner = nullptr; // Pointe vers l'entité qui possède le composant

  virtual ~Component() =
      default; // Destructeur  de base pour tous les composants
  virtual void Update(float dt) {};
  virtual void Draw() {};
};
