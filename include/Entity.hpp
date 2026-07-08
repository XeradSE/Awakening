// Cette classe est sensé faire la communication entre les composants

#pragma once

#include "./Component.hpp"
#include <memory>
#include <utility>
#include <vector>

class Entity {
  std::vector<std::unique_ptr<Component>> components;
  // unique_ptr évite de devoir écrire un delete après un new
  // Composent (donc je suppose pas besoin pour les classes où
  // pas de new ?)

public:
  // Ajoute un composant à l'entité
  template <typename T, typename... TArgs> T *AddComponent(TArgs &&...args) {
    // template <typename T> : on ne sais pas le composant qui sera donné
    //
    // T : type du composant qu'on veut créer
    //
    // typename... TArgs : je ne sais pas combien de composants on aura besoin
    // (ex: 2 pour une position, peut-être 0 pour un autre)
    //
    // TArgs... représente le nombre et le type des arguments dont le
    // constructeur de ce composant a besoin
    //
    // T* : type de retour - La fonction promet de renvoyer une "télécommande"
    // (pointeur brut) vers le composant créé.
    //
    // TArgs&& ... : On attrape tous les arguments que tu nous donnes, peu
    // importe leur nombre. Grâce au &&, on préserve leur nature exacte
    // (variables permanentes ou temporaires) sans faire aucune photocopie. On
    // stocke tout ça dans le paquet args.
    auto comp = std::make_unique<T>(
        std::forward<TArgs>(args)...); // voir discution avec AI
    // std::make_unique<T> : On fabrique le composant T de manière sécurisée
    // dans la mémoire (le Heap), et on l'enferme dans une boîte intelligente
    // (le unique_ptr comp) qui se détruira toute seule quand il le faudra.
    //
    // std::forward : On déballe le paquet args exactement dans l'état où on l'a
    // reçu, et on donne ces arguments au constructeur de notre composant T.
    comp->owner = this;
    // crucial, permet de signaler qui est le patron du composant
    //
    // comp est notre nouvelle boîte. Avec ->, on accède à l'intérieur pour
    // modifier la variable owner.
    //
    // this est un mot-clé fondamental en C++. Il veut dire "Moi". Puisqu'on est
    // à l'intérieur de la classe Entity, this est un pointeur vers l'Entité
    // elle-même.
    T *ptr = comp.get();
    // On utilise .get() pour extraire la "télécommande" (le pointeur brut T*)
    // pointée sur le composant.
    //
    // On garde cette télécommande de côté dans la variable ptr.
    components.push_back(std::move(comp));
    // components est notre tableau (std::vector).
    //
    // push_back sert à ajouter un élément à la fin du tableau.
    //
    // std::move(comp) : Comme comp est un pointeur unique (unique_ptr), il est
    // jaloux et refuse d'être copié. On utilise std::move pour forcer le
    // transfert de propriété. Le tableau devient le nouveau propriétaire
    // légitime de la boîte, et la variable locale comp devient vide.
    return ptr;
    // Le composant est bien au chaud dans le sac à dos de l'entité. On renvoie
    // la télécommande ptr qu'on avait mise de côté.
    // Ça permet de faire ça dans ton code de jeu:
    // auto position = joueur.AddComponent<TransformComponent>(300, 300);
    // position->x += 50; // On peut utiliser la télécommande immédiatement !
  }

  // un composant demande un autre composant -- Communication
  template <typename T> T *GetComponent() {
    for (auto &comp : components) {
      if (T *ptr = dynamic_cast<T *>(comp.get())) {
        return ptr;
      }
    }
    return nullptr;
  }

  void Update(float dt) {
    for (auto &comp : components)
      comp->Update(dt);
  }

  void Draw() {
    for (auto &comp : components)
      comp->Draw();
  }
};
