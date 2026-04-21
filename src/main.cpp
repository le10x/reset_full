#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        std::string miTexto = Mod::get()->getSettingValue<std::string>("mi-texto-personalizado");

        // MDTextArea soporta etiquetas de color automáticamente
        auto label = MDTextArea::create(miTexto, {200.f, 50.f});
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        label->setPosition({winSize.width / 2, winSize.height - 30.f});
        
        // Esto quita el fondo oscuro que trae por defecto
        label->getBGSprite()->setVisible(false); 
        
        this->addChild(label, 100);

        return true;
    }
};
