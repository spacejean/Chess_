// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "Tile.h"
#include "ChessBishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessBishop : public ABasePiece
{
	GENERATED_BODY()
	
	
	virtual void CalculateMoves(bool bDrawAvailableMoves) override;


	

};
