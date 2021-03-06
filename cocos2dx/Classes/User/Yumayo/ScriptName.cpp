#include "ScriptName.h"

#include "OptionalValues.h"

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
        position = origin + Vec2( visibleSize.width * 0.0,
                                  OptionalValues::stringViewSize.y + ( OptionalValues::fontSize + OptionalValues::lineSpaceSize ) * 2 );
        slideSize = visibleSize.width * 0.1;

        funcs.insert( std::make_pair( u8"in", [ this ] ( ArgumentList const& args ) { in( args ); } ) );
        funcs.insert( std::make_pair( u8"out", [ this ] ( ArgumentList const& args ) { out( args ); } ) );
    }
    ScriptName::~ScriptName( )
    {

    }
    void ScriptName::in( ArgumentList const& args )
    {
        auto label = create( );
        label->setOpacity( 0 );

        auto fade = FadeIn::create( 0.1 );
        auto slide = EaseExponentialOut::create( MoveBy::create( 0.3, Vec2( slideSize, 0.0F ) ) );
        auto fadeWithSlide = Spawn::create( fade, slide, nullptr );
        label->runAction( Spawn::create( fadeWithSlide, nullptr ) );
    }
    void ScriptName::out( ArgumentList const & args )
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
        label->setTag( (int)Tag::Name );
        label->setPosition( position.x + slideSize, position.y - label->getContentSize( ).height );
        layer->addChild( label );

        return label;
    }
}
