#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        // Leer el texto de la configuración
        std::string miTexto = Mod::get()->getSettingValue<std::string>("mi-texto-personalizado");

        // Creamos el TextArea. "chatFont.fnt" es ideal para colores.
        // Parámetros: texto, fuente, escala, ancho máximo, alineación, altura línea, disableColor
        auto label = TextArea::create(miTexto, "chatFont.fnt", 1.0f, 300.f, {0.5f, 0.5f}, 20.f, false);
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        label->setPosition({winSize.width / 2, winSize.height - 30.f});
        
        // Ocultar el fondo (buscando el sprite de fondo por tipo)
        if (auto bg = label->getChildByType<CCScale9Sprite>(0)) {
            bg->setVisible(false);
        }

        this->addChild(label, 100);

        return true;
    }
}; // <-- Faltaba el punto y coma aquí
