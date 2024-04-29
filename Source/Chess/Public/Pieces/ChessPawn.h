// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "ChessPawn.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessPawn : public ABasePiece
{
	GENERATED_BODY()
	AChessPawn();
	
	virtual void CalculateMoves() override;
};
