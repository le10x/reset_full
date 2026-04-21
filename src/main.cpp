#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        auto mod = Mod::get();
        
        // Cargar valores y convertir de escala 0-100 a lo que necesita el código
        std::string txtBlanco = mod->getSettingValue<std::string>("texto-blanco");
        std::string txtDorado = mod->getSettingValue<std::string>("texto-dorado");
        float posX = mod->getSettingValue<double>("pos-x") / 100.0f;
        float posY = mod->getSettingValue<double>("pos-y") / 100.0f;
        float escala = mod->getSettingValue<double>("escala") / 100.0f;
        float opacidad = (mod->getSettingValue<double>("opacidad") / 100.0f) * 255.0f;
        bool invertir = mod->getSettingValue<bool>("invertir-orden");
        bool detras = mod->getSettingValue<bool>("detras-bloques");

        auto container = CCNode::create();
        
        // Crear ambos labels con fuente Pusab (bigFont es blanca, goldFont es dorada)
        auto labelB = CCLabelBMFont::create(txtBlanco.c_str(), "bigFont.fnt");
        auto labelD = CCLabelBMFont::create(txtDorado.c_str(), "goldFont.fnt");

        labelB->setScale(escala);
        labelD->setScale(escala);
        labelB->setOpacity(static_cast<GLubyte>(opacidad));
        labelD->setOpacity(static_cast<GLubyte>(opacidad));

        // Determinar quién va primero
        CCLabelBMFont* primero = invertir ? labelB : labelD;
        CCLabelBMFont* segundo = invertir ? labelD : labelB;

        primero->setAnchorPoint({0, 0.5f});
        segundo->setAnchorPoint({0, 0.5f});

        float spacing = 10.0f * escala;
        segundo->setPositionX(primero->getContentSize().width * escala + spacing);

        container->addChild(primero);
        container->addChild(segundo);

        // Centrado y Posición
        float totalWidth = segundo->getPositionX() + (segundo->getContentSize().width * escala);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        container->setPosition({ winSize.width * posX - (totalWidth / 2), winSize.height * posY });

        // Z-Order: -1 para estar detrás de los bloques, o 100 para estar al frente (UI)
        int zOrder = detras ? -1 : 100;
        this->addChild(container, zOrder);

        return true;
    }
};
