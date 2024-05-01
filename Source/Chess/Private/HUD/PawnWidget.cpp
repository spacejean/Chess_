// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PawnWidget.h"
#include "Managers/Chess_GameMode.h"
#include "Components/Button.h"

void UPawnWidget::NativeConstruct()
{
    Super::NativeConstruct();
    /*QueenButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::QueenSelected);
    RookButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::RookSelected);
    KnightButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::KnightSelected);
    BishopButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::BishopSelected);*/
}
