// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBishop.h"

void AChessBishop::GenerateMoves()
{
}

/*
TArray<ATile*> AChessBishop::CalculateAvailableMoves()
{
	return TArray<ATile*>();
}

*/
TArray<FVector2D> AChessBishop::GenerateDiagonalMoves(const FVector2D& CurrentPosition)
{

	TArray<FVector2D> DiagonalMoves;

	// Diagonal moves towards upper-right
	for (int i = 1; CurrentPosition.X + i < 8 && CurrentPosition.Y + i < 8; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X + i, CurrentPosition.Y + i));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("upper-right"));
	}

	// Diagonal moves towards lower-right
	for (int i = 1; CurrentPosition.X + i < 8 && CurrentPosition.Y - i >= 0; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X + i, CurrentPosition.Y - i));
	}

	// Diagonal moves towards upper-left
	for (int i = 1; CurrentPosition.X - i >= 0 && CurrentPosition.Y + i < 8; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X - i, CurrentPosition.Y + i));
	}

	// Diagonal moves towards lower-left
	for (int i = 1; CurrentPosition.X - i >= 0 && CurrentPosition.Y - i >= 0; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X - i, CurrentPosition.Y - i));
	}

	return DiagonalMoves;

}

//TArray<ATile*> AChessBishop::CalculateAvailableMoves()
//{
//	return GenerateDiagonalMoves(PieceGridPosition);
//}


