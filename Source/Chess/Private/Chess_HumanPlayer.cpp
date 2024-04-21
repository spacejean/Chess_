// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_HumanPlayer.h"
#include "GameField.h"
//aggiunto 12 04
#include "Tile.h"
#include "Chess_GameMode.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AChess_HumanPlayer::AChess_HumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// create a camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//set the camera as RootComponent
	SetRootComponent(Camera);
	// get the game instance reference
	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// default init values
	PlayerNumber = -1;
	Sign = ESign::E;
}

// Called when the game starts or when spawned
void AChess_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChess_HumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_HumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChess_HumanPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

void AChess_HumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	GameInstance->IncrementScoreHumanPlayer();
}

void AChess_HumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}

void AChess_HumanPlayer::OnClick()
{
	// Struttura che contiene informazioni su un colpo di traccia, come punto di impatto e normale superficie in quel punto
	FHitResult Hit = FHitResult(ForceInit);
	// GetHitResultUnderCursor function sends a ray from the mouse position and gives the corresponding hit results
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	//Verifica se il colpo ha colpito qualcosa
	if (Hit.bBlockingHit && IsMyTurn)
	{
		
			AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
			AGameField* GField = GameMode->GetGameField(); 
			
			if (Hit.GetActor()->IsA<ABasePiece>()) {

		}
		//Verifico se l'oggetto colpito è di tipo BasePiece
		if (ABasePiece* ClickedBasePiece = Cast<ABasePiece>(Hit.GetActor()))
		{
			//salvo la posizione del pezzo colpito
			FVector2D Location = ClickedBasePiece->GetGridPosition();
			//stampo la posizione del pezzo colpito(riscordati di cancellare)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), Location[0], Location[1]));
			
			//salvo la posizione della Tile dove ho colpito il pezzo
			ATile* CTile = GField->GetTileByLocation(Location);
			
			//salvo il colore del pezzo colpito
			EPieceColor PieceColor = ClickedBasePiece->GetPieceColor();
			
			//salvo il tipo del pezzo colpito
			EPieceType PieceType = ClickedBasePiece->GetPieceType();

			if (!CTile) {
				FString Message = FString::Printf(TEXT("Error: ChessPiece not on Tile"));
			}

			

			if (PieceColor == EPieceColor::WHITE)  
			{
				//if(CurrPiece->GetPieceType() == EPieceType::BISHOP){
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("bianco"));
				
				//memorizza la Tile selezionata e il suo materiale originale
				//GField->SelectedTile = CTile;
				//GField->SelectedTileMaterial = CTile->GetMaterial(4);
				CTile->SetMaterial(2);
				//CurrPiece->CalculateMoves(true);
				ClickedBasePiece->CalculateMoves(true);

				//IsMyTurn = false;

				//GameMode->TurnNextPlayer();
				
				//CurrPiece->CalculateAvailableMoves();
				// Devo salvarmi il risultato, avrò le mosse valide per quel pezzo
				// Chiamare SetMaterial per le Tile
				//}
			
			}
			

			/*if (CurrTile->GetTileStatus() == ETileStatus::EMPTY)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clicked"));
				CurrTile->SetTileStatus(PlayerNumber, ETileStatus::OCCUPIED);
				FVector SpawnPosition = CurrTile->GetActorLocation();
				AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
				GameMode->SetCellSign(PlayerNumber, SpawnPosition);
				IsMyTurn = false;
			}
			*/
			memPiece = ClickedBasePiece;
		}
		
		//verifico se l'oggeto colpito è di tipo Tile
		if (ATile* ClickedTile = Cast<ATile>(Hit.GetActor()))
		{
			
				if (ClickedTile->GetTileStatus() == ETileStatus::EMPTY)
				{
					//if(CurrPiece->GetPieceType() == EPieceType::BISHOP){
					GameMode->movepiece(ClickedTile, memPiece);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("bianco"));
					GField->ResetPossibleMoves();
					//ATile* Obj = nullptr;
					//Obj->SetMaterial(3);
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker"));
					//Obj->GetGridPosition(); 
					//Obj->SetMaterial(Material);


					//CurrPiece->CalculateAvailableMoves();
					// Devo salvarmi il risultato, avrò le mosse valide per quel pezzo
					// Chiamare SetMaterial per le Tile
					//}

				}
				//else if (CurrPiece->GetPieceColor() == EPieceColor::BLACK)
				//{
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("bLACK"));


				//}

			/*if (CurrTile->GetTileStatus() == ETileStatus::EMPTY)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clicked"));
				CurrTile->SetTileStatus(PlayerNumber, ETileStatus::OCCUPIED);
				FVector SpawnPosition = CurrTile->GetActorLocation();
				AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
				GameMode->SetCellSign(PlayerNumber, SpawnPosition);
				IsMyTurn = false;
			}
			*/
		}
	}
}






