// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "Tile.h"
#include "ChessKing.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessKing : public ABasePiece
{
	GENERATED_BODY()
	virtual void CalculateMoves(bool bDrawAvailableMoves) override;

	//definisci le direzione di movimento possibili per i pezzi
	virtual TArray<FVector2D> GetMovementDirections() const override;
	void SetTile0Material(ATile* Tile, int32 MaterialIndex) const;
	bool IsTileEmptyOrOccupiedByOpponent(ATile* Tile, const EPieceColor CColor) const;
	bool IsTileEmpty(ATile* Tile) const;
};


