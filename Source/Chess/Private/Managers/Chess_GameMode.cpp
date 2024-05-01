// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Chess_GameMode.h"
#include "Players/Chess_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Players/Chess_HumanPlayer.h"
#include "Players/Chess_RandomPlayer.h"
#include "HUD/ChessHUD.h"
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

	
	/*ChessHUD = Cast<AChessHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (ChessHUD == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chess HUD was null in Gamemode"));
	}*/

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

void AChess_GameMode::ResetChess()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}


void AChess_GameMode::movepiece(ATile* tile, ABasePiece* piece)
{
	// Ottieni un puntatore al GameMode di scacchi attuale
	AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
	//TArray<ATile*> PMoves = GField->PossibleMoves;

	// Itera attraverso la lista di mosse possibili per la pedina selezionata
	for (auto* elem : GField->PossibleMoves) 
	{

		// Controlla se la posizione della tile corrente coincide con la posizione della tile selezionata per il movimento
		if (tile->GetGridPosition() == elem->GetGridPosition()) 
		{
			//coordinate della nuova posizione della pedina
			int32 x = tile->GetGridPosition()[0];
			int32 y = tile->GetGridPosition()[1];
			
			//coordinate della posizione  precedente della pedina

			int32 px = piece->GetGridPosition()[0];
			int32 py = piece->GetGridPosition()[1];

			// Salva la posizione precedente della pedina
			FVector2D positionb = FVector2D(px, py);
			
			// Calcola la nuova posizione della pedina in termini di coordinate del mondo
			FVector position = FVector(x * 120, y * 120, 0.3);
			// Imposta la posizione della pedina
			piece->SetActorLocation(position);
			// Rimuovi la pedina dalla casella precedente
			GField->SelectedTile->SetOccupyingChessPiece(nullptr);
			// Imposta la nuova posizione della pedina sulla nuova casella
			piece->SetPiecePosition(x,y);
			tile->SetOccupyingChessPiece(piece);
			// Aggiorna la mappa delle pedine con la nuova posizione
			GField->PieceMap.Add(FVector2D(x,y), piece);
			GField->PieceMap.Remove(positionb);
		}

	}
	// Ripristina i colori delle caselle a quelli predefiniti
	GField->ResetTilesColor();
	// Imposta il turno dell'altro giocatore
	_IsMyTurn_ = false;
	TurnNextPlayer();

}

void AChess_GameMode::movepiece2(ABasePiece* PieceB, ABasePiece* MyPiece)
{
	bool tempr = false;
	 
	for (auto* elem : GField->PossibleMoves)
	{
		// Controlla se la posizione della destinazione del movimento coincide con una delle mosse possibili
		if (PieceB->GetGridPosition() == elem->GetGridPosition())
		{
			tempr = true;
		}
		
	}

	// Se la destinazione del movimento non è valida, resetta i colori delle caselle
	if (!tempr)
	if (tempr == false)
	{
		GField->ResetTilesColor();
	}

	if (tempr)
	{
		if(PieceB != nullptr)
		{
			// Controlla se c'è una pedina nella posizione di destinazione
		if (GField->PieceMap.Contains(PieceB->GetGridPosition()))
		{
			//Muovi pedina attacante nella posizione della pedina avversaria
		MyPiece->SetActorLocation(PieceB->GetActorLocation());
		int32 x = PieceB->GetGridPosition()[0];
		int32 y = PieceB->GetGridPosition()[1];
		// Rimuovi la pedina avversaria dalla mappa delle pedine e distruggila
		GField->PieceMap.Remove(PieceB->GetGridPosition());
		PieceB->Destroy();
		GField->PieceArray.Remove(PieceB);
		
		// Imposta la posizione della pedina attacante nella nuova posizione
		MyPiece->SetPiecePosition(x, y);
		GField->PieceMap.Add(MyPiece->GetGridPosition(), MyPiece);
		GField->SelectedTile->SetOccupyingChessPiece(nullptr);

		ATile* Tile = GField->GetTileByLocation(FVector2D(x, y));
		Tile->SetOccupyingChessPiece(MyPiece);

		GField->PieceMap.Shrink();
		GField->PieceMap.Compact();

		}

		//resetta i colori delle tile
		GField->ResetTilesColor();

		
		// Passa il turno al prossimo giocatore
		_IsMyTurn_ = false;

		TurnNextPlayer();
		}
	}
}



bool AChess_GameMode::IsPlayerInCheck(EPieceColor PlayerColor)
{

	AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
	// setto il re del giocatore corrente
	ABasePiece* King = nullptr;
	if (GameMode->GField->WhiteKing->GetPieceType() == EPieceType::KING && GameMode->GField->WhiteKing->GetPieceColor() == PlayerColor)
	{
		King = GameMode->GField->WhiteKing;
	}
	else if (GameMode->GField->BlackKing->GetPieceType() == EPieceType::KING && GameMode->GField->BlackKing->GetPieceColor() == PlayerColor)
	{
		King = GameMode->GField->BlackKing;
	}



	if (!King)
	{
		// Il re non è stato trovato, quindi il giocatore non può essere in scacco
		return false;
	}

	// Scansiona tutti i pezzi dell'altro giocatore

	for (auto& Piece : GField->PieceArray)
	{

		if (Piece->GetPieceColor() != PlayerColor)
		{
			// Calcola le mosse possibili per il pezzo avversario
			//Piece->CalculateMoves();
			//creo una simulazione delle mosse 
			Piece->SimulateMoves();

			
			// Controlla se una delle mosse possibili minaccia il re del giocatore corrente
			for (auto& Move : GField->PossibleMoves2)
			{
				if (Move->GetGridPosition() == King->GetGridPosition())
				{
					// Il re è minacciato, quindi il giocatore è in scacco
					return true;
				}
			}
			//GField->ResetTilesColor();
		}
	}

	// Nessuna minaccia al re è stata trovata, quindi il giocatore non è in scacco
	return false;
}


bool AChess_GameMode::IsPlayerInCheckAfterMove(ABasePiece* MovedPiece, FVector2D NewPosition)
{
	// Salva lo stato attuale del gioco
	// Trova il pezzo nella copia

	//salvo la posizione attuale del pezzo
	int32 mpx = MovedPiece->GetGridPosition()[0];
	int32 mpy = MovedPiece->GetGridPosition()[1];
	FVector2D OriginalPositionMovedPiece = FVector2D(mpx, mpy);


	TArray<ABasePiece*> CopiedArray = GField->PieceArray;
	ABasePiece* CopiedPiece = nullptr;
	for (ABasePiece* Piece : GField->PieceArray)
	{
		if (Piece == MovedPiece)
		{
			CopiedPiece = Piece;
			break;
		}
	}

	int32 px = CopiedPiece->GetGridPosition()[0];
	int32 py = CopiedPiece->GetGridPosition()[1];

	FVector2D PositionCopiedPiece = FVector2D(px, py);
	// Simula la mossa del pezzo sulla copia
	if (CopiedPiece)
	{

		//ATile* OriginalTile = GField->GetTileByLocation(CopiedPiece->GetGridPosition());
		ATile* OriginalTile = GField->GetTileByLocation(OriginalPositionMovedPiece);

		ATile* NewTile = GField->GetTileByLocation(NewPosition);

		OriginalTile->SetOccupyingChessPiece(nullptr);
		NewTile->SetOccupyingChessPiece(CopiedPiece);
		CopiedPiece->SetPiecePosition(NewPosition[0], NewPosition[1]);
	}

	// Controlla se il re del giocatore corrente è in scacco dopo la mossa
	bool InCheckAfterMove = IsPlayerInCheck(MovedPiece->GetPieceColor());

	// Ripristina lo stato precedente del gioco
	if (CopiedPiece)
	{
		//ATile* OriginalTile = CopiedPiece->GetCurrentTile();
		ATile* OriginalTile = GField->GetTileByLocation(OriginalPositionMovedPiece);
		ATile* NewTile = GField->GetTileByLocation(NewPosition);
		NewTile->SetOccupyingChessPiece(nullptr);
		OriginalTile->SetOccupyingChessPiece(MovedPiece);
		CopiedPiece->SetPiecePosition(OriginalTile->GetGridPosition()[0], OriginalTile->GetGridPosition()[1]);
	}
	GField->PieceArray = CopiedArray;

	return InCheckAfterMove;
}