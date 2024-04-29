// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBishop.h"
#include "Tile.h"
#include "Chess_GameMode.h"






void AChessBishop::CalculateMoves(bool bDrawAvailableMoves)
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves = temp;

    // Ottieni la posizione attuale dell'alfiere
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento diagonali possibili per l'alfiere
    TArray<FVector2D> DiagonalDirections = {
        FVector2D(1, 1), FVector2D(1, -1), FVector2D(-1, 1), FVector2D(-1, -1)
    };

    // Scansiona ogni direzione diagonale
    for (const FVector2D& Direction : DiagonalDirections)
    {
        // Parti dalla posizione attuale dell'alfiere
        FVector2D NewPosition = CurrentPosition + Direction;

        // Continua a muoverti nella direzione finché sei sulla scacchiera
        while (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se la casella esiste e non è occupata dallo stesso team, aggiungi la posizione ai possibili movimenti dell'alfiere
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


                    //Non è possibile muoversi oltre quella casella
                    break;
                }
                else
                {
                    break;
                }
            }

            // Muoviti ulteriormente nella direzione diagonale
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



