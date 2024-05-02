// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/Chess_RandomPlayer.h"

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



//Creazione Random Player
//Devo creare un array di pezzi neri
//Se l'array dei pezzi è di tipo nero
//scelgo una fra quelli, e eseguo le mosse disponibili
//mi posiziono in una nuova tile


void AChess_RandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("AI (Random) Turn"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ha mosso la random player "));

	int32 randnumber;
	int32 RandomMoveIndex;
	ABasePiece* SelectedPiece ;
	TArray<ATile*> temporany;
	FTimerHandle TimerHandle;
	FVector2D Location1 = FVector2D(0, 0);
	int32 x = 0;
	int32 y = 0;


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
				 
				 //posizione pezzo colpito
				 Location1 = FVector2D(x, y);
				 
				 //salvo la posizione della Tile dove ho colpito il pezzo
				 ATile* CTile = GameMode->GField->GetTileByLocation(Location1);

				 GameMode->GField->SelectedTile = CTile;

				// Verifica se il pezzo selezionato è di colore nero
				if (SelectedPiece->GetPieceColor() == EPieceColor::BLACK)
				{
					// Calcola le mosse possibili per il pezzo selezionato
					SelectedPiece->CalculateMoves();

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
				 //TODO: devo controllare se esistono ancora mosse possibili, altrimenti è scacco matto
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
