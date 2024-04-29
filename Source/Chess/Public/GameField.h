// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "Pieces/ChessKing.h"
#include "Pieces/ChessQueen.h"
#include "Pieces/ChessBishop.h"
#include "Pieces/ChessKnight.h"
#include "Pieces/ChessRook.h"
#include "Pieces/ChessPawn.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"



UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()

public:
	// keeps track of tiles
	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	// keep tracks of possible moves
	UPROPERTY(Transient)
	TArray<ATile*> PossibleMoves;


	// keeps track of Pieces
	UPROPERTY(Transient)
	TArray<ABasePiece*> PieceArray;

	//given a position returns a tile
	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	//given a position returns a Piece
	UPROPERTY(Transient)
	TMap<FVector2D, ABasePiece*> PieceMap;



	static const int32 NOT_ASSIGNED = -1;

	

	// size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	//NONVA
	// size of winning line
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WinSize;

	// reference to a Tile object
	UPROPERTY(BlueprintReadOnly, Category = "Chess")
	ATile* SelectedTile;

	// reference to a Select Tile object
	UPROPERTY(BlueprintReadOnly, Category = "Chess")
	UMaterialInstance* SelectedTileMaterial;

	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass0;
	
	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WKingClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BKingClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WQueenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BQueenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WBishopClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BBishopClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WKnightClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BKnightClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WRookClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BRookClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> WPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> BPawnClass;


	

	// tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	// Sets default values for this actor's properties
	AGameField();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//remove all possible moves
	void ResetPossibleMoves();

	// generate an empty game field
	void GenerateField();

	//generate pieces
	void GeneratePieces();


	//Reset the original Tile color
	void ResetTilesColor();

	void ResetGa();

	// return a (x,y) position given a hit (click) on a field tile
	FVector2D GetPosition(const FHitResult& Hit);

	// return the array of tile pointers
	TArray<ATile*>& GetTileArray();

	// return the array of possible moves tile pointers
	TArray<ATile*>& GetPossibleMovesTileArray();

	//return the array of piece pointers
	TArray<ABasePiece*>& GetPieceArray();


	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) position given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	// return the tile given a position
	ATile* GetTileByLocation(const FVector2D& Location) const;

	

	//public:	
	//	// Called every frame
	//	virtual void Tick(float DeltaTime) override;

};
