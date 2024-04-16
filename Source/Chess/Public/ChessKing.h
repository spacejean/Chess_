// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "ChessKing.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessKing : public ABasePiece
{
	GENERATED_BODY()
	virtual void GenerateMoves() override;
	//virtual void CalculateMoves(bool bDrawAvailableMoves) override;
};
