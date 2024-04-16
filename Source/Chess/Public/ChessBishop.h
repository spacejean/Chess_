// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "ChessBishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessBishop : public ABasePiece
{
	GENERATED_BODY()
	virtual void GenerateMoves() override;
	//Valid moves mi deve restituire un array di Tile dove tutte le pedine possono muoversi
	//virtual TArray<ATile*> CalculateAvailableMoves() override;
	TArray<FVector2D> GenerateDiagonalMoves(const FVector2D& CurrentPosition);
	virtual void CalculateMoves(bool bDrawAvailableMoves) override;
};
