// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessQueen.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"



void AChessQueen::CalculateMoves(bool bDrawAvailableMoves)
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves = temp;

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

        // Continua a muoverti nella direzione finché sei sulla scacchiera
        while (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se non c'è una casella o se la casella è vuota, aggiungi la posizione ai possibili movimenti
            if (!Tile || !Tile->GetOccupyingChessPiece())
            {
                GameMode->GField->PossibleMoves.Add(Tile);

               
            }
            // Se c'è una pedina sulla casella, aggiungi la posizione ai possibili movimenti solo se la pedina è avversaria
            else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
            {
                GameMode->GField->PossibleMoves.Add(Tile);

                

                // Non è possibile muoversi oltre questa casella
                break;
            }
            else
            {
                // C'è una pedina dello stesso team sulla casella, quindi non è possibile muoversi oltre
                break;
            }

            // Muoviti ulteriormente nella direzione
            NewPosition += Direction;
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
