// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePiece.h"
#include "ChessQueen.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessQueen : public ABasePiece
{
	GENERATED_BODY()
	
	virtual void CalculateMoves() override;
	virtual void SimulateMoves() override;
};
