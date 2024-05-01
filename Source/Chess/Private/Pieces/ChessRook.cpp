// Fill out your copyright notice in the Description page of Project Settings.


#include "Pieces/ChessRook.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"




void AChessRook::CalculateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves = temp;

    // Ottieni la posizione attuale della torre
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per la torre
    TArray<FVector2D> Directions = { FVector2D(0, 1), FVector2D(0, -1), FVector2D(1, 0), FVector2D(-1, 0) };

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Parti dalla posizione attuale della torre
        FVector2D NewPosition = CurrentPosition + Direction;

        // Continua a muoverti nella direzione finché sei sulla scacchiera
        while (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se non c'è una casella o se la casella è vuota, aggiungi la posizione ai possibili movimenti
            if (Tile && !Tile->GetOccupyingChessPiece())
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

void AChessRook::SimulateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    //GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves2 = temp;

    // Ottieni la posizione attuale della torre
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per la torre
    TArray<FVector2D> Directions = { FVector2D(0, 1), FVector2D(0, -1), FVector2D(1, 0), FVector2D(-1, 0) };

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Parti dalla posizione attuale della torre
        FVector2D NewPosition = CurrentPosition + Direction;

        // Continua a muoverti nella direzione finché sei sulla scacchiera
        while (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);

            // Se non c'è una casella o se la casella è vuota, aggiungi la posizione ai possibili movimenti
            if (Tile && !Tile->GetOccupyingChessPiece())
            {
                GameMode->GField->PossibleMoves2.Add(Tile);


            }
            // Se c'è una pedina sulla casella, aggiungi la posizione ai possibili movimenti solo se la pedina è avversaria
            else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
            {
                GameMode->GField->PossibleMoves2.Add(Tile);


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




}