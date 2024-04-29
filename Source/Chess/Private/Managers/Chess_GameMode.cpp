// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Chess_GameMode.h"
#include "Players/Chess_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Players/Chess_HumanPlayer.h"
#include "Players/Chess_RandomPlayer.h"
#include "Hud/ChessHUD.h"
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


	m_ChessHUD = Cast<AChessHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (m_ChessHUD == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chess HUD was null in Gamemode"));
	}

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
	float CameraPosX = ((GField->TileSize * (FieldSize ) )/ 2) - (GField->TileSize / 2);;
	//float CameraPosX = ((GField->TileSize * (GField->Size + ((GField->Size - 1) * GField->NormalizedCellPadding) - (GField->Size - 1))) / 2) - (GField->TileSize / 2);
	FVector CameraPos(CameraPosX, CameraPosX, 1250.0f);
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

	

	CurrentPlayer = 0;
	MoveCounter += 1;
	Players[CurrentPlayer]->OnTurn();
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
	//TArray<ATile*> PMoves = GField->PossibleMoves;
	for (auto* elem : GField->PossibleMoves) {


		if (tile->GetGridPosition() == elem->GetGridPosition()) {
			int32 x = tile->GetGridPosition()[0];
			int32 y = tile->GetGridPosition()[1];
			
			int32 px = piece->GetGridPosition()[0];
			int32 py = piece->GetGridPosition()[1];

			FVector2D positionb = FVector2D(px, py);
			
			FVector position = FVector(x * 120, y * 120, 0.3);
			piece->SetActorLocation(position);
			GField->SelectedTile->SetOccupyingChessPiece(nullptr);
			piece->SetPiecePosition(x,y);
			tile->SetOccupyingChessPiece(piece);
			GField->PieceMap.Add(FVector2D(x,y), piece);
			GField->PieceMap.Remove(positionb);
		}

	}

	GField->ResetTilesColor();
	_IsMyTurn_ = false;
	TurnNextPlayer();

}

void AChess_GameMode::movepiece2(ABasePiece* PieceB, ABasePiece* MyPiece)
{
	bool tempr = false;
	 
	for (auto* elem : GField->PossibleMoves)
	{
		if (PieceB->GetGridPosition() == elem->GetGridPosition())
		{
			tempr = true;
		}
		
	}

	
	if (tempr == false)
	{
		GField->ResetTilesColor();
	}

	if (tempr)
	{
		if(PieceB != nullptr)
		{
		if (GField->PieceMap.Contains(PieceB->GetGridPosition()))
		{
		MyPiece->SetActorLocation(PieceB->GetActorLocation());
		int32 x = PieceB->GetGridPosition()[0];
		int32 y = PieceB->GetGridPosition()[1];
		
		GField->PieceMap.Remove(PieceB->GetGridPosition());
		PieceB->Destroy();
		GField->PieceArray.Remove(PieceB);
		
		
		MyPiece->SetPiecePosition(x, y);
		GField->PieceMap.Add(MyPiece->GetGridPosition(), MyPiece);
		GField->SelectedTile->SetOccupyingChessPiece(nullptr);
		ATile* Tile = GField->GetTileByLocation(FVector2D(x, y));
		Tile->SetOccupyingChessPiece(MyPiece);
		GField->PieceMap.Shrink();
		GField->PieceMap.Compact();

		}
		GField->ResetTilesColor();

		
		_IsMyTurn_ = false;

		TurnNextPlayer();
		}
	}
}

void AChess_GameMode::ResetChess()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
