// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "Tile.h"
#include "ChessKnight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessKnight : public ABasePiece
{
	GENERATED_BODY()

public:
	int32 counter = 0;
	
	virtual void CalculateMoves(bool bDrawAvailableMoves) override;
	
};
