#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        
        // 1. Localizar el menú de botones
        auto menu = this->getChildByID("right-button-menu"); // O el ID correspondiente
        
        // 2. Crear el sprite y el botón
        auto spr = ButtonSprite::create("TOTAL RESET", "goldFont.fnt", "GJ_button_01.png", .8f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(MyPauseLayer::onFullReset)
        );
        
        // 3. Añadir al menú
        menu->addChild(btn);
        menu->updateLayout();
    }

    void onFullReset(CCObject* sender) {
        auto pl = PlayLayer::get();
        if (!pl) return;

        // Obtener los datos del nivel actual
        auto level = pl->m_level;

        // Resetear intentos manualmente en los datos del nivel
        level->m_attempts = 0; 
        
        // Crear una nueva escena de PlayLayer con el nivel "limpio"
        auto newScene = PlayLayer::scene(level, false, false);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, newScene));
    }
};
