// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Chess_InterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChess_InterfaceWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Reset();

	UPROPERTY(meta = (BindWidget))
	UButton* ResetButton;
};
