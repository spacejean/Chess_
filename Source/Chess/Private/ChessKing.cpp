// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessKing.h"
#include "Tile.h"
#include "Chess_GameMode.h"

void AChessKing::CalculateMoves(bool bDrawAvailableMoves)
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


                      //  Tile->SetMaterial(2);

                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    // Casella occupata da un pezzo avversario
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella


                    //    Tile->SetMaterial(3);

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

bool AChessKing::IsTileEmptyOrOccupiedByOpponent(ATile* Tile, const EPieceColor CColor) const
{
    if (!Tile)
    {
        UE_LOG(LogTemp, Error, TEXT("Null Tile passed to IsTileEmptyOrOccupiedByOpponent"));
        return false;
    }

    ABasePiece* OccupyingPiece = Tile->GetOccupyingChessPiece();
    return !OccupyingPiece || OccupyingPiece->GetPieceColor() != CColor;
}

void AChessKing::SetTile0Material(ATile* Tile, int32 MaterialIndex) const
{
    if (!Tile)
    {
        UE_LOG(LogTemp, Error, TEXT("Null Tile passed to SetTileMaterial"));
        return;
    }

    Tile->SetMaterial(MaterialIndex);
}

bool AChessKing::IsTileEmpty(ATile* Tile) const
{
    if (!Tile)
    {
        UE_LOG(LogTemp, Warning, TEXT("IsTileEmpty called with nullptr Tile"));
        return true; // Trattiamo una casella nulla come vuota
    }

    // Ottieni il pezzo sulla casella, se presente
    ABasePiece* OccupyingPiece = Tile->GetOccupyingChessPiece();

    // La casella è considerata vuota se non contiene un pezzo
    return !OccupyingPiece;
}

/*
void AChessKing::CalculateMoves(bool bDrawAvailableMoves)
{
    // Assicurati di avere accesso al game mode
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get Chess Game Mode"));
        return;
    }

    // Ottieni la posizione attuale del re
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per il re
    TArray<FVector2D> Dir = GetMovementDirections();

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Dir)
    {
        // Calcola la nuova posizione del re
        FVector2D NewPosition = CurrentPosition + Direction;

        // Verifica se la nuova posizione è all'interno della scacchiera
        if (IsValidBoardPosition(NewPosition))
        {
            ATile* Tile = GameMode->GField->GetTileByLocation(NewPosition);
            if (!Tile)
            {
                UE_LOG(LogTemp, Error, TEXT("Tile not found at position (%f, %f)"), NewPosition.X, NewPosition.Y);
                continue;
            }

            // Verifica se la casella è libera o occupata da un pezzo avversario
            if (IsTileEmptyOrOccupiedByOpponent(Tile, this->GetPieceColor()) )
            {
                // Aggiungi la posizione ai possibili movimenti
                GameMode->GField->PossibleMoves.Add(Tile);

                // Se richiesto, cambia il materiale della casella
                if (bDrawAvailableMoves)
                {
                    SetTile0Material(Tile, IsTileEmpty(Tile) ? 2 : 3);
                }
                
            }
        }
    }
}

*/
/*

void AChessKing::GenerateMoves()
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Ottieni la posizione attuale del re
    FVector2D CurrentPosition = GetGridPosition();

    // Definisci le direzioni di movimento possibili per il re
    TArray<FVector2D> Directions = GetMovementDirections();

    // Scansiona ogni direzione
    for (const FVector2D& Direction : Directions)
    {
        // Calcola la nuova posizione del re
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
                    if (bDrawAvailableMoves)
                    {
                        Tile->SetMaterial(2);
                    }
                }
                else if (Tile->GetOccupyingChessPiece()->GetPieceColor() != this->GetPieceColor())
                {
                    // Casella occupata da un pezzo avversario
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella
                    if (bDrawAvailableMoves)
                    {
                        Tile->SetMaterial(3);
                    }
                }
            }
        }
    }
}

*/

