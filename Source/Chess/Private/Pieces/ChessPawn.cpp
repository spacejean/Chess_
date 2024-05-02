// Fill out your copyright notice in the Description page of Project Settings.

#include "Pieces/ChessPawn.h"
#include "Tile.h"
#include "Managers/Chess_GameMode.h"



AChessPawn::AChessPawn()
{
	PType = EPieceType::PAWN;
}


void AChessPawn::CalculateMoves()
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
        //controllo se 
        int32 x1 = ForwardTile->GetGridPosition()[0];
        int32 y1 = ForwardTile->GetGridPosition()[1];

        if (!GameMode->IsPlayerInCheckAfterMove(this, FVector2D(x1, y1)))
        {
        GameMode->GField->PossibleMoves.Add(ForwardTile);
       
      
        // Se il pedone è nella posizione iniziale, verifica se può avanzare di due caselle
        if ((GetPieceColor() == EPieceColor::WHITE && CurrentPosition.X == 1) ||
            (GetPieceColor() == EPieceColor::BLACK && CurrentPosition.X == 6))
        {
            FVector2D DoubleForwardSquare = CurrentPosition + FVector2D(2 * ForwardDirection,0);
            ATile* DoubleForwardTile = GameMode->GField->GetTileByLocation(DoubleForwardSquare);
            if (DoubleForwardTile && !DoubleForwardTile->GetOccupyingChessPiece())
            {
                int32 x2 = DoubleForwardTile->GetGridPosition()[0];
                int32 y2 = DoubleForwardTile->GetGridPosition()[1];
                if (!GameMode->IsPlayerInCheckAfterMove(this, FVector2D(x2, y2)))
                {
                    GameMode->GField->PossibleMoves.Add(DoubleForwardTile);
                }
              
            }
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
            int32 x0 = AttackTile->GetGridPosition()[0];
            int32 y0 = AttackTile->GetGridPosition()[1];
            if (!GameMode->IsPlayerInCheckAfterMove(this, FVector2D(x0, y0)))
            {
                GameMode->GField->PossibleMoves.Add(AttackTile);
            }
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


void AChessPawn::SimulateMoves()
{
    TArray<ATile*> temp;
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    //GameMode->GField->ResetTilesColor();
    GameMode->GField->PossibleMoves2 = temp;

    // Ottieni la posizione attuale del pedone
    FVector2D CurrentPosition = GetGridPosition();

    // Determina la direzione di avanzamento del pedone basata sul suo colore
    int32 ForwardDirection = (GetPieceColor() == EPieceColor::WHITE) ? 1 : -1;

    // Calcola la posizione del quadrato davanti al pedone
    FVector2D ForwardSquare = CurrentPosition + FVector2D(ForwardDirection, 0);

    // Verifica se il quadrato davanti al pedone è libero
    ATile* ForwardTile = GameMode->GField->GetTileByLocation(ForwardSquare);
    if (ForwardTile && !ForwardTile->GetOccupyingChessPiece())
    {
        GameMode->GField->PossibleMoves2.Add(ForwardTile);


        // Se il pedone è nella posizione iniziale, verifica se può avanzare di due caselle
        if ((GetPieceColor() == EPieceColor::WHITE && CurrentPosition.X == 1) ||
            (GetPieceColor() == EPieceColor::BLACK && CurrentPosition.X == 6))
        {
            FVector2D DoubleForwardSquare = CurrentPosition + FVector2D(2 * ForwardDirection, 0);
            ATile* DoubleForwardTile = GameMode->GField->GetTileByLocation(DoubleForwardSquare);
            if (DoubleForwardTile && !DoubleForwardTile->GetOccupyingChessPiece())
            {
                GameMode->GField->PossibleMoves2.Add(DoubleForwardTile);

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
            GameMode->GField->PossibleMoves2.Add(AttackTile);

        }
    }




}