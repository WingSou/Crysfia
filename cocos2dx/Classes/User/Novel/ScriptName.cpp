#include "ScriptName.h"

#include "OptionalValues.h"

#include "../../Lib/Utility/Utilitys.h"

USING_NS_CC;

namespace User
{
    ScriptName::ScriptName( cocos2d::Layer* layer, std::string characterName, std::string fontPath )
        : ScriptBase( layer )
        , characterName( characterName )
        , fontPath( fontPath )
        , position( )
        , slideSize( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        auto size = Sprite::create( u8"res/texture/system/message.window.png" )->getContentSize( );
        auto mul = size.width / visibleSize.width;

        position = origin + Vec2( 0, 330.0F / mul * scale );
        slideSize = 270.0F / mul * scale;

        REGIST_FUNC( ScriptName, in );
        REGIST_FUNC( ScriptName, out );
    }
    ScriptName::~ScriptName( )
    {

    }
    SCRIPT( ScriptName::in )
    {
        auto label = create( );
        if ( !label ) return;

        label->setOpacity( 0 );

        auto fade = FadeIn::create( 0.1 );
        auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( slideSize, 0.0F ) ) );
        auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
        label->runAction( Spawn::create( fadeWithSlide, nullptr ) );
    }
    SCRIPT( ScriptName::out )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Name ) )
        {
            auto fade = FadeOut::create( 0.1 );
            auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( slideSize, 0.0F ) ) );
            auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fadeWithSlide, remove, nullptr ) );
        }
    }
    cocos2d::Label * ScriptName::create( )
    {
        layer->removeChildByTag( (int)Tag::Name );

        auto label = Label::createWithTTF( characterName, "res/fonts/" + fontPath, OptionalValues::fontSize );
        if ( !label ) return nullptr;

        label->setTag( (int)Tag::Name );
        label->setTextColor( Color4B( 39, 39, 39, 255 ) );
        label->setPosition( position );
        layer->addChild( label );

        return label;
    }
}
