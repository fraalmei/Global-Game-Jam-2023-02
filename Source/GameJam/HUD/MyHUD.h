// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Widget/MyUserWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:

	void DrawHUD();

	UPROPERTY(EditAnywhere, Category = "Widget")
		UMyUserWidget* MainWidget;


	
};
