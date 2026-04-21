#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        auto mod = Mod::get();
        
        // Cargar configuraciones
        std::string txtPusab = mod->getSettingValue<std::string>("texto-pusab");
        std::string txtChat = mod->getSettingValue<std::string>("texto-chat");
        float posX = mod->getSettingValue<double>("pos-x");
        float posY = mod->getSettingValue<double>("pos-y");
        float escala = mod->getSettingValue<double>("escala");
        float opacidad = mod->getSettingValue<double>("opacidad") * 255.0f; // Convertir 0-1 a 0-255

        // Crear el nodo contenedor para mover ambos textos como uno solo
        auto container = CCNode::create();
        
        // Label 1: Pusab (Dorado)
        auto label1 = CCLabelBMFont::create(txtPusab.c_str(), "goldFont.fnt");
        label1->setScale(escala);
        label1->setOpacity(static_cast<GLubyte>(opacidad));
        label1->setAnchorPoint({0, 0.5f}); // Anclaje a la izquierda

        // Label 2: Chat (Blanco)
        auto label2 = CCLabelBMFont::create(txtChat.c_str(), "chatFont.fnt");
        label2->setScale(escala);
        label2->setOpacity(static_cast<GLubyte>(opacidad));
        label2->setAnchorPoint({0, 0.5f});

        // Posicionar el segundo label justo después del primero
        float spacing = 5.0f * escala; // Espacio entre palabras
        label2->setPositionX(label1->getContentSize().width * escala + spacing);

        // Añadir al contenedor
        container->addChild(label1);
        container->addChild(label2);

        // Calcular ancho total para centrar el contenedor
        float totalWidth = label2->getPositionX() + (label2->getContentSize().width * escala);
        container->setContentSize({totalWidth, label1->getContentSize().height * escala});
        
        // Posicionar contenedor en pantalla
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        container->setPosition({ winSize.width * posX - (totalWidth / 2), winSize.height * posY });

        this->addChild(container, 100);

        return true;
    }
};
