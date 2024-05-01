// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/Chess_GameMode.h"
#include "Components/Button.h"
#include "PawnWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UPawnWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

    virtual void NativeConstruct() override;

    /*UFUNCTION()
    void QueenSelected();

    UFUNCTION()
    void RookSelected();

    UFUNCTION()
    void KnightSelected();

    UFUNCTION()
    void BishopSelected();*/


    AChess_GameMode* Gamemode;

    UPROPERTY(meta = (BindWidget))
    UButton* QueenButton;

    UPROPERTY(meta = (BindWidget))
    UButton* RookButton;

    UPROPERTY(meta = (BindWidget))
    UButton* KnightButton;

    UPROPERTY(meta = (BindWidget))
    UButton* BishopButton;
};
