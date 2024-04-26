// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBishop.h"
#include "Tile.h"
#include "Chess_GameMode.h"

void AChessBishop::GenerateMoves()
{
}

/*
TArray<ATile*> AChessBishop::CalculateAvailableMoves()
{
	return TArray<ATile*>();
}

*/
TArray<FVector2D> AChessBishop::GenerateDiagonalMoves(const FVector2D& CurrentPosition)
{

	TArray<FVector2D> DiagonalMoves;

	// Diagonal moves towards upper-right
	for (int i = 1; CurrentPosition.X + i < 8 && CurrentPosition.Y + i < 8; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X + i, CurrentPosition.Y + i));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("upper-right"));
	}

	// Diagonal moves towards lower-right
	for (int i = 1; CurrentPosition.X + i < 8 && CurrentPosition.Y - i >= 0; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X + i, CurrentPosition.Y - i));
	}

	// Diagonal moves towards upper-left
	for (int i = 1; CurrentPosition.X - i >= 0 && CurrentPosition.Y + i < 8; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X - i, CurrentPosition.Y + i));
	}

	// Diagonal moves towards lower-left
	for (int i = 1; CurrentPosition.X - i >= 0 && CurrentPosition.Y - i >= 0; i++)
	{
		DiagonalMoves.Add(FVector2D(CurrentPosition.X - i, CurrentPosition.Y - i));
	}

	return DiagonalMoves;

}

//TArray<ATile*> AChessBishop::CalculateAvailableMoves()
//{
//	return GenerateDiagonalMoves(PieceGridPosition);
//}



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
                    //{
                    //    Tile->SetMaterial(3);
                    //}

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




TArray<FVector2D> AChessBishop::GetMovementDirections() const
{
    return {
        FVector2D(1, 1), FVector2D(1, -1), FVector2D(-1, 1), FVector2D(-1, -1)
    };
}

void AChessBishop::SetTile0Material(ATile* Tile, int32 MaterialIndex) const
{
    if (!Tile)
    {
        UE_LOG(LogTemp, Error, TEXT("Null Tile passed to SetTileMaterial"));
        return;
    }
}

bool AChessBishop::IsTileOccupiedByOpponent(ATile* Tile, const EPieceColor CColor) const
{
    if (!Tile)
    {
        UE_LOG(LogTemp, Error, TEXT("Null Tile passed to IsTileOccupiedByOpponent"));
        return false;
    }

    ABasePiece* OccupyingPiece = Tile->GetOccupyingChessPiece();
    return  OccupyingPiece->GetPieceColor() != CColor;
}

bool AChessBishop::IsTileEmpty(ATile* Tile) const
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
void AChessBishop::CalculateMoves(bool bDrawAvailableMoves)
{
    AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
    // Pulisci la lista dei possibili movimenti
    GameMode->GField->PossibleMoves.Empty();

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

            if (Tile)
            {

                // Verifica se la casella è libera o occupata da un pezzo avversario
                if (IsTileEmpty(Tile))
                {
                    // Aggiungi la posizione ai possibili movimenti
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella
                    if (bDrawAvailableMoves)
                    {
                        Tile->SetMaterial(2);
                    }
                    // Se richiesto, cambia il materiale della casella
                }
                else if (IsTileOccupiedByOpponent(Tile, this->GetPieceColor()))
                {
                    GameMode->GField->PossibleMoves.Add(Tile);

                    // Se richiesto, cambia il materiale della casella
                    if (bDrawAvailableMoves)
                    {
                        Tile->SetMaterial(3);
                    }

                    //Non è possibile muoversi oltre quella casella
                    break;

                }






            }
            // Muoviti ulteriormente nella direzione diagonale
            NewPosition += Direction;
        }
    }
}


*/