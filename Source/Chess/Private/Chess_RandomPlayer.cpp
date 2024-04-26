// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_RandomPlayer.h"

// Sets default values
AChess_RandomPlayer::AChess_RandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}

// Called when the game starts or when spawned
void AChess_RandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChess_RandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_RandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
void AChess_RandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("AI (Random) Turn"));

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			TArray<ATile*> FreeCells;
			AChess_GameMode* GameMode = (AChess_GameMode*)(GetWorld()->GetAuthGameMode());
			for (auto& CurrTile : GameMode->GField->GetTileArray())
			{
				if (CurrTile->GetTileStatus() == ETileStatus::EMPTY)
				{
					FreeCells.Add(CurrTile);
				}
			}

			if (FreeCells.Num() > 0)
			{
				int32 RandIdx = FMath::Rand() % FreeCells.Num();
				FVector Location = GameMode->GField->GetRelativeLocationByXYPosition((FreeCells[RandIdx])->GetGridPosition()[0], (FreeCells[RandIdx])->GetGridPosition()[1]);
				FreeCells[RandIdx]->SetTileStatus(PlayerNumber, ETileStatus::OCCUPIED);

				GameMode->SetCellSign(PlayerNumber, Location);

			}
			//aggiunto
			GameMode->TurnNextPlayer();
		}, 3, false);
}
*/



/*
void AChess_RandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("AI (Random) Turn"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ha mosso la random player "));
	
	int32 randnumber;
	ABasePiece* temp = nullptr;
	TArray<ATile*> temporany;
	FTimerHandle TimerHandle;
	//for (auto &pieza:GameMode->GField->PieceArray) {
		//randomen number----------------

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			AChess_GameMode* GameMode = (AChess_GameMode*)(GetWorld()->GetAuthGameMode());
		
			
			randnumber = FMath::RandRange(0,GameMode->GField->PieceArray.Num()-1);

		while (!(GameMode->GField->PieceArray[randnumber]->GetPieceColor() == EPieceColor::BLACK))
		{
			 randnumber = FMath::RandRange(0,GameMode->GField->PieceArray.Num()-1);
			 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("randnumber: %d"), randnumber));

		}
		if (GameMode->GField->PieceArray[randnumber]!= nullptr)
		{

			temp = GameMode->GField->PieceArray[randnumber];
			temp->CalculateMoves(true);
			
			//if (GameMode->GField->PossibleMoves.Num() > 0){
			int32 rand2 = FMath::Rand() % (GameMode->GField->PossibleMoves.Num());

			//creo funzione in modo che mi ritorni vero quando le posizioni sono maggiore di 0

			//controllo se c'è un pezzo o se non c'è
			ATile* tile = GameMode->GField->PossibleMoves[rand2];
			if (tile->GetOccupyingChessPiece())
			{
				tile->GetGridPosition();
				int32 x = tile->GetGridPosition()[0];
				int32 y = tile->GetGridPosition()[1];

				if (ABasePiece* Piece2 = GameMode->GField->PieceMap.FindRef(FVector2D(x, y)))
				{
					GameMode->movepiece2(FVector2D(0, 0), temp, Piece2);
				}


			}
			else

			{
				GameMode->movepiece(tile, temp);

				
			}

		}
		
		
	//GameMode->TurnNextPlayer();
		}, 3, false);
}
*/


//Creazione Random Player
//Devo creare un array di pezzi neri
//Se l'array dei pezzi è di tipo nero
//scelgo una fra quelli, e eseguo le mosse disponibili
//e mi posiziono in una nuova tile dove non è occupata




void AChess_RandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("AI (Random) Turn"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ha mosso la random player "));

	int32 randnumber;
	int32 RandomMoveIndex;
	ABasePiece* SelectedPiece ;
	TArray<ATile*> temporany;
	FTimerHandle TimerHandle;
	FVector2D Location1 = FVector2D(0, 0);
	int32 x = 0;
	int32 y = 0;
	//for (auto &pieza:GameMode->GField->PieceArray) {
		//randomen number----------------

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			AChess_GameMode* GameMode = (AChess_GameMode*)(GetWorld()->GetAuthGameMode());

			while(true)
			{
				// Seleziona un pezzo casuale dall'array dei pezzi
				randnumber = FMath::RandRange(0, GameMode->GField->PieceArray.Num() - 1);

				 SelectedPiece = GameMode->GField->PieceArray[randnumber];
				 //salvo la posizione del pezzo colpito
				 
				 if(SelectedPiece != nullptr)
				 {
				  x = SelectedPiece->GetGridPosition()[0];
				   y = SelectedPiece->GetGridPosition()[1];
				 
				 Location1 = FVector2D(x, y);
				 
				 //salvo la posizione della Tile dove ho colpito il pezzo
				 
				 ATile* CTile = GameMode->GField->GetTileByLocation(Location1);

				 GameMode->GField->SelectedTile = CTile;

				// Verifica se il pezzo selezionato è di colore nero
				if (SelectedPiece->GetPieceColor() == EPieceColor::BLACK)
				{
					// Calcola le mosse possibili per il pezzo selezionato
					SelectedPiece->CalculateMoves(true);

					// Verifica se ci sono mosse possibili per il pezzo selezionato
					if (GameMode->GField->PossibleMoves.Num() > 0)
					{
						
						// Scegli una mossa casuale tra quelle disponibili
						RandomMoveIndex = FMath::RandRange(0, GameMode->GField->PossibleMoves.Num() - 1);
						ATile* SelectedMove = GameMode->GField->PossibleMoves[RandomMoveIndex];

						// Esegui la mossa
						if (SelectedMove->GetOccupyingChessPiece())
						{
							FVector2D DestinationPosition = SelectedMove->GetGridPosition();
							GameMode->movepiece2(SelectedMove->GetOccupyingChessPiece(), SelectedPiece);
						}
						else
						{
							GameMode->movepiece(SelectedMove, SelectedPiece);
						}

						// Esci dal loop dopo aver eseguito la mossa
						break;
					}
				}

				 }
			}







				//GameMode->TurnNextPlayer();
			}, 3, false);
		}




void AChess_RandomPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Wins!"));
	GameInstance->SetTurnMessage(TEXT("AI Wins!"));
	GameInstance->IncrementScoreAiPlayer();
}

void AChess_RandomPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Loses!"));
	// GameInstance->SetTurnMessage(TEXT("AI Loses!"));
}
