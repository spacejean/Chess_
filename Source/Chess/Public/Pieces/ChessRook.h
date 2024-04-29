// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "Tile.h"

#include "ChessRook.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessRook : public ABasePiece
{
	GENERATED_BODY()

	virtual void CalculateMoves(bool bDrawAvailable) override;
		
};
	