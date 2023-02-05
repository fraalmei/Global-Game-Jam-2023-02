// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{

}

void UMyUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind delegates here.
}

void UMyUserWidget::SetPlayerHealthText(int32 Health)
{
    FString Text = FString::Printf(TEXT("Health: %s"), *FString::FromInt(Health));
    if (PlayerHealthText)
        PlayerHealthText->SetText(FText::FromString(Text));
}

void UMyUserWidget::SetDistanceText(int32 Distance)
{
    FString Text = FString::Printf(TEXT("Distance: %s"), *FString::FromInt(Distance));
    if (DistanceText)
        DistanceText->SetText(FText::FromString(Text));
}

void UMyUserWidget::ToggleRedScreen(bool bEnable)
{
    ESlateVisibility State = ESlateVisibility::Visible;

    if (!bEnable)
        State = ESlateVisibility::Hidden;
    if (RedScreen)
        RedScreen->SetVisibility(State);
}

void UMyUserWidget::ToggleYouLoseScreen(bool bEnable)
{
    ESlateVisibility State = ESlateVisibility::Visible;

    if (!bEnable)
        State = ESlateVisibility::Hidden;
    if (YouLoseText && YouLoseImage)
    {
        YouLoseText->SetVisibility(State);
        YouLoseImage->SetVisibility(State);
    }

}

void UMyUserWidget::ToggleHealthDistanceText(bool bEnable)
{
    ESlateVisibility State = ESlateVisibility::Visible;

    if (!bEnable)
        State = ESlateVisibility::Hidden;
    if (PlayerHealthText && DistanceText)
    {
        PlayerHealthText->SetVisibility(State);
        DistanceText->SetVisibility(State);
    }
}

void UMyUserWidget::ToggleStoryScreen(bool bEnable)
{
    ESlateVisibility State = ESlateVisibility::Visible;

    if (!bEnable)
        State = ESlateVisibility::Hidden;
    if (StoryText && StoryImage)
    {
        StoryText->SetVisibility(State);
        StoryImage->SetVisibility(State);
    }
}

void UMyUserWidget::SetStoryText(FString Message)
{
    if (StoryText)
        StoryText->SetText(FText::FromString(Message));
}