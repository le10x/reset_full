#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
    if (!PlayLayer::init(level, useReplay, dontSave)) return false;

    std::string miTexto = Mod::get()->getSettingValue<std::string>("mi-texto-personalizado");

    // TextArea nativo: usa "chatFont.fnt" para que los colores funcionen bien
    auto label = TextArea::create(miTexto, "chatFont.fnt", 1.0f, 300.f, {0.5f, 0.5f}, 20.f, false);
    
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    label->setPosition({winSize.width / 2, winSize.height - 30.f});
    
    // Aquí sí funciona getBGSprite() en la mayoría de versiones o puedes buscarlo:
    if (label->getBGSprite()) {
        label->getBGSprite()->setVisible(false);
    }

    this->addChild(label, 100);
    return true;
}
