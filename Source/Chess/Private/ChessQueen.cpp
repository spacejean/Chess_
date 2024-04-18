// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessQueen.h"
#include "Tile.h"
#include "Chess_GameMode.h"

void AChessQueen::GenerateMoves()
{
}

void AChessQueen::CalculateMoves(bool bDrawAvailableMoves)
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());

    // Ottieni la posizione attuale della regina
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per la regina (combinando le direzioni della torre e dell'alfiere)
    TArray<FVector2D> Directions = {
        FVector2D(0, 1), FVector2D(0, -1), FVector2D(1, 0), FVector2D(-1, 0), // Mosse della torre
        FVector2D(1, 1), FVector2D(1, -1), FVector2D(-1, 1), FVector2D(-1, -1) // Mosse dell'alfiere
    };

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Parti dalla posizione attuale della regina
        FVector2D NewPosition = CurrentPosition + Direction;

        // Continua a muoverti nella direzione finch� sei sulla scacchiera
        while (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se non c'� una casella o se la casella � vuota, aggiungi la posizione ai possibili movimenti
            if (!Tile || !Tile->GetOccupyingChessPiece())
            {
                GameMode->GField->PossibleMoves.Add(Tile);

                // Se richiesto, cambia il materiale della casella
                if (bDrawAvailableMoves && Tile)
                {
                    Tile->SetMaterial(2);
                }
            }
            // Se c'� una pedina sulla casella, aggiungi la posizione ai possibili movimenti solo se la pedina � avversaria
            else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
            {
                GameMode->GField->PossibleMoves.Add(Tile);

                // Se richiesto, cambia il materiale della casella
                if (bDrawAvailableMoves)
                {
                    Tile->SetMaterial(3);
                }

                // Non � possibile muoversi oltre questa casella
                break;
            }
            else
            {
                // C'� una pedina dello stesso team sulla casella, quindi non � possibile muoversi oltre
                break;
            }

            // Muoviti ulteriormente nella direzione
            NewPosition += Direction;
        }
    }
}
