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
/*
void AChessPawn::CalculateMoves(bool bDrawAvailableMove)
{

    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->PossibleMoves = temp;

    // Ottieni la posizione attuale del pedone
    FVector2D CurrentPosition = GetGridPosition();

    // Determina la direzione di avanzamento del pedone basata sul suo colore
    int32 ForwardDirection = (GetPieceColor() == EPieceColor::WHITE) ? 1 : -1;

    // Calcola la posizione del quadrato davanti al pedone
    FVector2D ForwardSquare = CurrentPosition + FVector2D(0, ForwardDirection);

    // Verifica le mosse di attacco del pedone
    TArray<FVector2D> AttackDirections = { FVector2D(1, ForwardDirection), FVector2D(-1, ForwardDirection) };


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
*/

void AChessPawn::CalculateMoves(bool bDrawAvailableMoves)
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves = temp;

    // Ottieni la posizione attuale del pedone
    FVector2D CurrentPosition = GetGridPosition();

    // Determina la direzione di avanzamento del pedone basata sul suo colore
    int32 ForwardDirection = (GetPieceColor() == EPieceColor::WHITE) ? 1 : -1;

    // Calcola la posizione del quadrato davanti al pedone
    FVector2D ForwardSquare = CurrentPosition + FVector2D(ForwardDirection,0);

    // Verifica se il quadrato davanti al pedone è libero
    ATile* ForwardTile = GameMode->GField->GetTileByLocation(ForwardSquare);
    if (ForwardTile && !ForwardTile->GetOccupyingChessPiece())
    {
        GameMode->GField->PossibleMoves.Add(ForwardTile);
        ForwardTile->SetMaterial(2);
        // Se richiesto, cambia il materiale della casella
        // if (bDrawAvailableMoves)
        // {
        //     ForwardTile->SetMaterial(2);
        // }

        // Se il pedone è nella posizione iniziale, verifica se può avanzare di due caselle
        if ((GetPieceColor() == EPieceColor::WHITE && CurrentPosition.X == 1) ||
            (GetPieceColor() == EPieceColor::BLACK && CurrentPosition.X == 6))
        {
            FVector2D DoubleForwardSquare = CurrentPosition + FVector2D(2 * ForwardDirection,0);
            ATile* DoubleForwardTile = GameMode->GField->GetTileByLocation(DoubleForwardSquare);
            if (DoubleForwardTile && !DoubleForwardTile->GetOccupyingChessPiece())
            {
                GameMode->GField->PossibleMoves.Add(DoubleForwardTile);
                DoubleForwardTile->SetMaterial(2);

                // Se richiesto, cambia il materiale della casella
                // if (bDrawAvailableMoves)
                // {
                //     DoubleForwardTile->SetMaterial(2);
                // }
            }
        }
    }

    // Verifica le mosse di attacco del pedone
    TArray<FVector2D> AttackDirections = { FVector2D(ForwardDirection,1), FVector2D(ForwardDirection,-1) };
    for (const FVector2D& Direction : AttackDirections)
    {
        FVector2D AttackPosition = CurrentPosition + Direction;
        ATile* AttackTile = GameMode->GField->GetTileByLocation(AttackPosition);
        if (AttackTile && AttackTile->GetOccupyingChessPiece() &&
            AttackTile->GetOccupyingChessPiece()->GetPieceColor() != GetPieceColor())
        {
            GameMode->GField->PossibleMoves.Add(AttackTile);
            AttackTile->SetMaterial(3);
            // Se richiesto, cambia il materiale della casella
            // if (bDrawAvailableMoves)
            // {
            //     AttackTile->SetMaterial(3);
            // }
        }
    }
}