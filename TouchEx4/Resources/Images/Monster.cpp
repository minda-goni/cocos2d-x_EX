//
//  Monster.cpp
//  SpriteExtendEx
//
//  Created by Jaewhan Lee on 13. 11. 10.
//
//

#include "Monster.h"

USING_NS_CC;

Monster::Monster()
: _listener(nullptr)
, _fixedPriority(0)
, _useNodePriority(false)
{
    bool bOk = initWithTexture(nullptr, Rect::ZERO);
    if (bOk) {
        this->autorelease();
    }
}

void Monster::setPriority(int fixedPriority)
{
    _fixedPriority = fixedPriority;
}

void Monster::setPriorityWithThis(bool useNodePriority)
{
    _useNodePriority = useNodePriority;
}

void Monster::onEnter()
{
    Sprite::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        log("touch began...");

        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            this->setColor(Color3B::RED);
            return true;
        }
        return false;
    };

    listener->onTouchMoved = [=](Touch* touch, Event* event) {
        //this->setPosition(this->getPosition() + touch->getDelta());
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        this->setColor(Color3B::WHITE);
    };

    if (_useNodePriority)
    {
		// 객체가 그려진 순서대로 터치의 우선 순위를 가진다.
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    else
    {
		// 지정된 순서대로 터치의 우선 순위를 가진다. (작은 숫자 우선)
        _eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
    }
    _listener = listener;
}

void Monster::onExit()
{
    _eventDispatcher->removeEventListener(_listener);

    Sprite::onExit();
}
