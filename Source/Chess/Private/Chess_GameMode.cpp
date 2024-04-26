// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameMode.h"
#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_RandomPlayer.h"
//#include "TTT_MinimaxPlayer.h"
#include "EngineUtils.h"



AChess_GameMode::AChess_GameMode()
{
	PlayerControllerClass = AChess_PlayerController::StaticClass();
	DefaultPawnClass = AChess_HumanPlayer::StaticClass();
	FieldSize = 8;
}


void AChess_GameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	MoveCounter = 0;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));

	if (GameFieldClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGameField>(GameFieldClass);
		GField->Size = FieldSize;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	//float CameraPosX = ((GField->TileSize * (FieldSize + ((FieldSize - 1) * GField->NormalizedCellPadding) - (FieldSize - 1))) / 2) - (GField->TileSize / 2);
	float CameraPosX = ((GField->TileSize * (FieldSize ) )/ 2) ;
	FVector CameraPos(CameraPosX, CameraPosX, 950.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	// Human player = 0
	Players.Add(HumanPlayer);
	// Random Player
	auto* AI = GetWorld()->SpawnActor<AChess_RandomPlayer>(FVector(), FRotator());

	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	this->ChoosePlayerAndStartGame();
}

void AChess_GameMode::ChoosePlayerAndStartGame()
{

	//CurrentPlayer = FMath::RandRange(0, Players.Num() - 1);

	CurrentPlayer = 0;

	for (int32 i = 0; i < Players.Num(); i++)
	{
		Players[i]->PlayerNumber = i;
		Players[i]->Sign = i == CurrentPlayer ? ESign::X : ESign::O;
	}
	MoveCounter += 1;
	Players[CurrentPlayer]->OnTurn();
}

void AChess_GameMode::SetCellSign(const int32 PlayerNumber, const FVector& SpawnPosition)
{
	if (IsGameOver || PlayerNumber != CurrentPlayer)
	{
		return;
	}

	UClass* SignActor = Players[CurrentPlayer]->Sign == ESign::X ? SignXActor : SignOActor;
	FVector Location = GField->GetActorLocation() + SpawnPosition + FVector(0, 0, 10);
	GetWorld()->SpawnActor(SignActor, &Location);

	if (GField->IsWinPosition(GField->GetXYPositionByRelativeLocation(SpawnPosition)))
	{
		IsGameOver = true;
		Players[CurrentPlayer]->OnWin();
		for (int32 i = 0; i < Players.Num(); i++)
		{
			if (i != CurrentPlayer)
			{
				Players[i]->OnLose();
			}
		}
	}
	else if (MoveCounter == (FieldSize * FieldSize))
	{
		// add a timer (3 seconds)
		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				// function to delay
				GField->ResetField();
			}, 3, false);
	}
	else
	{
		//TurnNextPlayer();
	}
}

int32 AChess_GameMode::GetNextPlayer(int32 Player)
{
	Player++;
	if (!Players.IsValidIndex(Player))
	{
		Player = 0;
	}
	return Player;
}

void AChess_GameMode::TurnNextPlayer()
{
	MoveCounter += 1;
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	Players[CurrentPlayer]->OnTurn();
}

AGameField* AChess_GameMode::GetGameField() const
{
	return GField;
}

void AChess_GameMode::movepiece(ATile* tile, ABasePiece* piece)
{
	AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
	TArray<ATile*> PMoves = GField->PossibleMoves;
	for (auto* elem : PMoves) {


		if (tile->GetGridPosition() == elem->GetGridPosition()) {
			int32 x = tile->GetGridPosition()[0];
			int32 y = tile->GetGridPosition()[1];
			FVector position = FVector(x * 120, y * 120, 0.3);
			
			GField->SelectedTile->SetOccupyingChessPiece(nullptr);
			piece->SetPiecePosition(x,y);
			piece->SetActorLocation(position);
			tile->SetOccupyingChessPiece(piece);
			
		}

	}

	GField->ResetTilesColor();

	TurnNextPlayer();

}

void AChess_GameMode::movepiece2(ABasePiece* PieceB, ABasePiece* MyPiece)
{
	bool tempr = false;
	TArray<ATile*> PMoves = GField->PossibleMoves;
	for (auto* elem : PMoves)
	{
		if (PieceB->GetGridPosition() == elem->GetGridPosition())
		{
			tempr = true;
		}
	}
	if (tempr)
	{
		if (GField->PieceMap.Contains(PieceB->GetGridPosition()))
		{
		MyPiece->SetActorLocation(PieceB->GetActorLocation());
		int32 x = PieceB->GetGridPosition()[0];
		int32 y = PieceB->GetGridPosition()[1];
		
		PieceB->Destroy();
		
		GField->PieceMap.Remove(PieceB->GetGridPosition());
		MyPiece->SetPiecePosition(x, y);
		GField->PieceMap.Add(MyPiece->GetGridPosition(), MyPiece);
		GField->SelectedTile->SetOccupyingChessPiece(nullptr);
		ATile* Tile = GField->GetTileByLocation(FVector2D(x, y));
		Tile->SetOccupyingChessPiece(MyPiece);
		GField->PieceMap.Shrink();
		GField->PieceMap.Compact();

		}
		GField->ResetTilesColor();
		
		TurnNextPlayer();

	}
}
