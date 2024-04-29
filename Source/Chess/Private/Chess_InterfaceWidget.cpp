// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_InterfaceWidget.h"
#include "Chess_GameMode.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"

void UChess_InterfaceWidget::NativeConstruct()
{
    Super::NativeConstruct();


  ResetButton->OnClicked.AddUniqueDynamic(this, &UChess_InterfaceWidget::Reset);
}

void UChess_InterfaceWidget::Reset()
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in ResetLevel function in OnScreenWidget"));
        return;
    }

    GameMode->ResetChess();
}
