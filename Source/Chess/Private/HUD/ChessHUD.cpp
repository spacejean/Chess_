// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/ChessHUD.h"
#include "Hud/Chess_InterfaceWidget.h"
#include "Components/WidgetComponent.h"

AChessHUD::AChessHUD()
{
}

void AChessHUD::BeginPlay()
{

    Super::BeginPlay();

    if (BP_InterfaceWidget)
    {
        InterfaceWidget = CreateWidget<UChess_InterfaceWidget>(GetWorld(), BP_InterfaceWidget);
        InterfaceWidget->AddToViewport();
    }

}
