// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessKnight.h"
#include "Tile.h"
#include "Chess_GameMode.h"

void AChessKnight::GenerateMoves()
{
}


void AChessKnight::CalculateMoves(bool bDrawAvailableMoves)
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->PossibleMoves.Empty();

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
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella
                    //if (bDrawAvailableMoves)
                    //{
                    //    Tile->SetMaterial(2);
                    //}
                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    // Casella occupata da un pezzo avversario
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella
                   // if (bDrawAvailableMoves)
                   // {
                   //     Tile->SetMaterial(3);
                   // }
                }
            }
        }
    }
    if (counter%2!=0)
    {
        for (auto& position : GameMode->GField->PossibleMoves) {


            position->SetMaterial(4);
        }
        GameMode->GField->GetTileByLocation(this->GetGridPosition())->SetMaterial(4);
    }
    else
    {
        for (auto& position : GameMode->GField->PossibleMoves) {

            auto* occupyingPiece = position->GetOccupyingChessPiece();
            //ATile* Tile = GameMode->GField->GetTileByLocation(position);
          if (occupyingPiece &&occupyingPiece->GetPieceColor() != this->GetPieceColor())
            {
            position->SetMaterial(3);
            
            }
          else
            {
                position->SetMaterial(2);
            }
        }
            //ATile* Tile = GameMode->GField->GetTileByLocation(position);
         
        //if (position->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
         //   {
         //   position->SetMaterial(2);
            
          //  }
            //else
            //{
              //  position->SetMaterial(2);
            //}
        }

    
    counter++;
}

/*
void AChessKnight::movepiece(ATile* tile) 
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    for (auto* elem : GameMode->GField->PossibleMoves) {

        
        if (tile->GetGridPosition() == elem->GetGridPosition()) {
            int32 x = tile->GetGridPosition()[0];
            int32 y = tile->GetGridPosition()[1];
            FVector posicion = FVector(x * 120, y * 120, 0.2);
            this->SetActorLocation(posicion);
        }

    }
}
*/
