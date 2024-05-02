// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessKnight.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"



void AChessKnight::CalculateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves=temp;


    // Ottieni la posizione attuale del cavallo
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per il cavallo
    TArray<FVector2D> Directions = {
        FVector2D(1, 2), FVector2D(1, -2),
        FVector2D(-1, 2), FVector2D(-1, -2),
        FVector2D(2, 1), FVector2D(2, -1),
        FVector2D(-2, 1), FVector2D(-2, -1)
    };

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Calcola la nuova posizione del cavallo
        FVector2D NewPosition = CurrentPosition + Direction;

        // Verifica se la nuova posizione è all'interno della scacchiera
        if (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);
            int32 x1 = Tile->GetGridPosition()[0];
            int32 y1 = Tile->GetGridPosition()[1];
            // Se la casella esiste e non è occupata dallo stesso team, aggiungi la posizione ai possibili movimenti
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
                }
                
            }
        }
    }

  

        for (auto& position : GameMode->GField->PossibleMoves) {

            auto* occupyingPiece = position->GetOccupyingChessPiece();
           
          if (occupyingPiece &&occupyingPiece->GetPieceColor() != this->GetPieceColor())
            {
            position->SetMaterial(3);
            
            }
          else
            {
                position->SetMaterial(2);
            }
        }
         
        

}

void AChessKnight::SimulateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    //GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves2 = temp;


    // Ottieni la posizione attuale del cavallo
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per il cavallo
    TArray<FVector2D> Directions = {
        FVector2D(1, 2), FVector2D(1, -2),
        FVector2D(-1, 2), FVector2D(-1, -2),
        FVector2D(2, 1), FVector2D(2, -1),
        FVector2D(-2, 1), FVector2D(-2, -1)
    };

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Calcola la nuova posizione del cavallo
        FVector2D NewPosition = CurrentPosition + Direction;

        // Verifica se la nuova posizione è all'interno della scacchiera
        if (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se la casella esiste e non è occupata dallo stesso team, aggiungi la posizione ai possibili movimenti
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


                }
            }
        }
    }
}







