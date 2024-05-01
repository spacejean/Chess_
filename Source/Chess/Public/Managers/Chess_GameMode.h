// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Players/Chess_PlayerInterface.h"
#include "GameField.h"
#include "BasePiece.h"
#include "Hud/ChessHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Chess_GameMode.generated.h"

class AActor;

struct FPosition;

/**
 * 
 */
UCLASS()
class CHESS_API AChess_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	// tracks if the game is over
	bool IsGameOver;
	// array of player interfaces
	TArray<IChess_PlayerInterface*> Players;
	int32 CurrentPlayer;
	// tracks the number of moves in order to signal a drawn game
	int32 MoveCounter;

	// keeps track of turn
	bool _IsMyTurn_ = false;

	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GameFieldClass;

	// field size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FieldSize;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere)
	AGameField* GField;


	AChess_GameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the start of the game
	void ChoosePlayerAndStartGame();


	// get the next player index
	int32 GetNextPlayer(int32 Player);

	// called at the end of the game turn
	void TurnNextPlayer();

	// return the game field object
	AGameField* GetGameField() const;
	
	//move a piece to tile
	void movepiece(ATile* tile, ABasePiece* piece);
	
	//move a piece to kill a piece opponent
	void movepiece2(ABasePiece* PieceB, ABasePiece* MyPiece);

	//reset the game
	void ResetChess();
protected:
	AChessHUD* ChessHUD;
};
