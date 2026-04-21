#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        // 1. Obtener el texto de la configuración
        std::string texto = Mod::get()->getSettingValue<std::string>("mi-texto-personalizado");

        // 2. Crear el label (usando RichText o múltiples labels para colores)
        auto label = CCLabelBMFont::create(texto.c_str(), "goldFont.fnt");
        
        // Posicionamiento (ejemplo: esquina superior izquierda)
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        label->setPosition({winSize.width / 2, winSize.height - 20});
        
        this->addChild(label, 100);

        return true;
    }
};
