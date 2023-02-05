// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void AMyHUD::DrawHUD()
{
	if (MainWidget)
		MainWidget->AddToViewport();
}