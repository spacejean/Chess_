// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Chess_InterfaceWidget.h"
#include "ChessHUD.generated.h"

/**
 * 
 */


UCLASS()
class CHESS_API AChessHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
public:

	AChessHUD();
	UChess_InterfaceWidget* InterfaceWidget;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> BP_InterfaceWidget;
	
	
};
