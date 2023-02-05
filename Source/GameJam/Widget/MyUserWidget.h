// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* PlayerHealthText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DistanceText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* RedScreen;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* YouLoseText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* YouLoseImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* StoryText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* StoryImage;
	UFUNCTION()
		void ToggleHealthDistanceText(bool bEnable);
	UFUNCTION()
		void SetPlayerHealthText(int32 Health);
	UFUNCTION()
		void SetDistanceText(int32 Distance);
	UFUNCTION()
		void ToggleRedScreen(bool bEnable);
	UFUNCTION()
		void ToggleYouLoseScreen(bool bEnable);
	UFUNCTION()
		void ToggleStoryScreen(bool bEnable);
	UFUNCTION()
		void SetStoryText(FString Message);
	
};
