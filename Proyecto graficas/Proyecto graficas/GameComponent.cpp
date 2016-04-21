#pragma once
#include "GameComponent.h"
#include "GameObject.h"

void GameComponent::SetParent( GameObject* parent ) { 
	this->parent = parent; 
}

Transform * GameComponent::GetTransform(){
	return &(parent->transform);
}
