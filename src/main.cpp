#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        // Obtener valores de la configuración
        auto mod = Mod::get();
        std::string miTexto = mod->getSettingValue<std::string>("mi-texto-personalizado");
        float posX = mod->getSettingValue<double>("pos-x");
        float posY = mod->getSettingValue<double>("pos-y");

        // Usamos bigFont.fnt para la fuente Pusab
        auto label = TextArea::create(miTexto, "bigFont.fnt", 1.0f, 400.f, {0.5f, 0.5f}, 30.f, false);
        
        // Calcular posición basada en el tamaño de la pantalla
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        label->setPosition({ winSize.width * posX, winSize.height * posY });
        
        // Quitar el fondo oscuro
        if (auto bg = label->getChildByType<CCScale9Sprite>(0)) {
            bg->setVisible(false);
        }

        this->addChild(label, 100);

        return true;
    }
};
