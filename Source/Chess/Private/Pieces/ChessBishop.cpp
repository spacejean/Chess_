// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessBishop.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"






void AChessBishop::CalculateMoves()
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
            int32 x1 = Tile->GetGridPosition()[0];
            int32 y1 = Tile->GetGridPosition()[1];
            // Se la casella esiste e non è occupata dallo stesso team, aggiungi la posizione ai possibili movimenti dell'alfiere
            if (Tile)
            {
                if (!Tile->GetOccupyingChessPiece())
                {
                    if (!GameMode->IsPlayerInCheckAfterMove(this, FVector2D(x1, y1)))
                    {
                        // Casella libera
                        GameMode->GField->PossibleMoves.Add(Tile);
                    }
                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    if (!GameMode->IsPlayerInCheckAfterMove(this, FVector2D(x1, y1)))
                    {
                        // Casella occupata da un pezzo avversario
                        GameMode->GField->PossibleMoves.Add(Tile);
                    }

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


  


}


void AChessBishop::SimulateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    //GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves2 = temp;

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
                    GameMode->GField->PossibleMoves2.Add(Tile);

                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    // Casella occupata da un pezzo avversario
                    GameMode->GField->PossibleMoves2.Add(Tile);


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

}


