// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessKing.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"

void AChessKing::CalculateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves = temp;

    // Ottieni la posizione attuale del re
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per il re
    TArray<FVector2D> Directions = GetMovementDirections();

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Calcola la nuova posizione del re
        FVector2D NewPosition = CurrentPosition + Direction;

        // Verifica se la nuova posizione � all'interno della scacchiera
        if (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se la casella esiste e non � occupata dallo stesso team, aggiungi la posizione ai possibili movimenti
            if (Tile)
            {
                if (!Tile->GetOccupyingChessPiece())
                {
                    // Casella libera
                    GameMode->GField->PossibleMoves.Add(Tile);

                  

                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    // Casella occupata da un pezzo avversario
                    GameMode->GField->PossibleMoves.Add(Tile);


                }
            }
        }
    }


    // if (counter%2!=0)
    //{
    //    for (auto& position : GameMode->GField->PossibleMoves) {


    //        position->SetMaterial(4);
    //    }
       // GameMode->GField->GetTileByLocation(this->GetGridPosition())->SetMaterial(4);
    //}
    //else
    //{
    for (auto& position : GameMode->GField->PossibleMoves) {

        auto* occupyingPiece = position->GetOccupyingChessPiece();

        if (occupyingPiece && occupyingPiece->GetPieceColor() != this->GetPieceColor())
        {
            position->SetMaterial(3);

        }
        else
        {
            position->SetMaterial(2);
        }
    }


    //   }


  // counter++;



}

TArray<FVector2D> AChessKing::GetMovementDirections() const
{
    // Definisci le direzioni di movimento possibili per il re
    return {
        FVector2D(0, 1), FVector2D(0, -1), FVector2D(1, 0), FVector2D(-1, 0), // Mosse in orizzontale e verticale
        FVector2D(1, 1), FVector2D(1, -1), FVector2D(-1, 1), FVector2D(-1, -1) // Mosse in diagonale
    };
}

