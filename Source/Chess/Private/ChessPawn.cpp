// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessPawn.h"
#include "Tile.h"
#include "Chess_GameMode.h"



AChessPawn::AChessPawn()
{
	PType = EPieceType::PAWN;
}

void AChessPawn::GenerateMoves()
{
}

void AChessPawn::CalculateMoves(bool bDrawAvailableMove)
{
    int loopIndex = 1 ; // Numero di spazi che il pedone può muoversi in avanti
    int newX = PieceGridPosition.X;
    int newY = PieceGridPosition.Y;
    ATile* NewTile;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());

    for (int i = 0; i < loopIndex; i++)
    {   
        newX += 1; // Aggiorna la posizione X del pedone
        NewTile = GameMode->GField->GetTileByLocation(FVector2D(newX, PieceGridPosition.Y));

        if (NewTile)
        {
            if (bDrawAvailableMove){
                NewTile->SetMaterial(3);
                GameMode->GField->PossibleMoves.Add(NewTile);
        }
        }
        else
        {
            break; // Esci dal loop se la casella non è vuota o non esiste
        }
    }
}

