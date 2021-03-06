#include "LayerIsland.h"

#include "../SceneManager.h"

#include "ui/CocosGUI.h"

#include "../Yumayo/OptionalValues.h"

USING_NS_CC;

namespace User
{
    LayerIsland::LayerIsland( )
    {

    }
    LayerIsland::~LayerIsland( )
    {

    }
    //ブロックオブジェクト作成  
    Label* LayerIsland::createLabel( std::string const& text )
    {
        Label* label = Label::createWithTTF( text, u8"res/fonts/F910MinchoW3.otf", OptionalValues::fontSize );
        label->setColor( Color3B( 0xFF, 0xFF, 0xFF ) );
        return label;
    }

    bool LayerIsland::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        this->scheduleUpdate( );

        bool ret = true;

        ret = ret && initBackground( );

        ret = ret && initIslandMap( );

        return true;
    }
    void LayerIsland::setup( )
    {

    }
    void LayerIsland::update( float delta )
    {
        //SceneManager::createYumayo( );
    }
    bool LayerIsland::initBackground( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::create( u8"res/texture/背景市場.png" );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );
        this->addChild( sprite );

        return true;
    }
    bool LayerIsland::initIslandMap( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto targetSize = Size( 64, 64 );

        Vector<MenuItem*> item;

        for ( int y = 0; y < 10; y++ )
        {
            for ( int x = 0; x < 5; x++ )
            {
                auto menu = MenuItemImage::create( "res/Image/WindowBase/WinBase_102.png", "res/Image/WindowBase/WinBase_106.png" );
                menu->setPosition( origin + Vec2( x * targetSize.width, y * targetSize.height ) );

                /*auto size = menu->getContentSize( );
                menu->setScale( targetSize.width / size.width, targetSize.height / size.height );*/
                item.pushBack( menu );
            }
        }


        auto menu = Menu::createWithArray( item );
        this->addChild( menu );
        menu->alignItemsInColumnsWithArray( ValueVector( 10, Value( 5 ) ) );

        /*Vector<MenuItem*> menuItems;

        menuItems.pushBack( MenuItemLabel::create( createLabel( u8"STARGE" ) ) );

        Menu *menu = Menu::createWithArray( menuItems );
        this->addChild( menu );*/

        //ボタンを横に整頓する  
        //menu->alignItemsHorizontallyWithPadding( 0 );

        //ボタンを縦に整頓する  
        //menu->alignItemsVerticallyWithPadding( 0 );

        //垂直方向に並べる
        //menu->alignItemsVertically( );

        //水平方向に並べる
        //menu->alignItemsHorizontally();  

        //横に何個並べるかを指定する。
        //配列の数字の合計数と、レイヤーの子供の数が一致していないとエラーになる。
        //menu->alignItemsInColumns( 4, 2, 2, 4 );

        return true;
    }
}
