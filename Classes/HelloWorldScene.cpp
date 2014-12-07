#include "HelloWorldScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    // --- Cocos Studio v2読み込み ---
    
    CSLoader::getInstance()->setRecordProtocolBuffersPath(true); // .csbを読み込んだディレクトリを保持してリソースを探す指定
    auto mainScene = CSLoader::getInstance()->createNodeFromProtocolBuffers("res/MainScene.csb");
    this->addChild(mainScene);
    
    // --- Animation ---
    
    auto action = timeline::ActionTimelineCache::getInstance()->createActionFromProtocolBuffers("res/MainScene.csb");
    if(action) {
        action->setTimeSpeed(action->getTimeSpeed() / 2);
        mainScene->runAction(action);
        action->gotoFrameAndPlay(0, false);
    }

    // --- ボタンイベント ---
    
    // 変更するラベルを取得（Panel_1/Text_1）
    auto textLabel = mainScene->getChildByName("Panel_1")->getChildByName<ui::Text*>("Text_1");
    // ボタンを取得してクリックイベントを設定
    mainScene->getChildByName<ui::Button*>("Button_1")->addClickEventListener([textLabel, action](Ref *ref) {
        // ボタン押した時の処理
        
        // ラベルの内容を書き換える
        textLabel->setString("Test !!!!!!!!!!!!");
        
        //
        action->gotoFrameAndPlay(0, false);
    });
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
