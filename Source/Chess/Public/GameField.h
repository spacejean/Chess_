// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

#include "ChessKing.h"
#include "ChessQueen.h"
#include "ChessBishop.h"
#include "ChessKnight.h"
#include "ChessRook.h"
#include "ChessPawn.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"

// macro declaration for a dynamic multicast delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset);

UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()

public:
	// keeps track of tiles
	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	// Array di tile delle possibile mosse
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



	//NONVA
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NormalizedCellPadding;
	*/
	static const int32 NOT_ASSIGNED = -1;

	// BlueprintAssignable Usable with Multicast Delegates only. Exposes the property for assigning in Blueprints.
	// declare a variable of type FOnReset (delegate)
	UPROPERTY(BlueprintAssignable)
	FOnReset OnResetEvent;

	// size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	//NONVA
	// size of winning line
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WinSize;

	//Puntatore alla tile selezionata
	UPROPERTY(BlueprintReadOnly, Category = "Chess")
	ATile* SelectedTile;

	//Puntatore alla tile selezionata
	UPROPERTY(BlueprintReadOnly, Category = "Chess")
	UMaterialInstance* SelectedTileMaterial;

	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass0;
	
	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;
	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePiece> PieceClass;

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


	
	//NONVA
	// tile padding dimension
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CellPadding;

	// tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	// Sets default values for this actor's properties
	AGameField();

	//NONVA
	// Called when an instance of this class is placed (in editor) or spawned
	//virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// remove all signs from the field
	UFUNCTION(BlueprintCallable)
	void ResetField();

	//rimuovi le possibili mosse
	void ResetPossibleMoves();

	// generate an empty game field
	void GenerateField();

	//generate pieces
	void GeneratePieces();


	//rigenera il colore delle Tile
	void ResetTilesColor();


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

	//13-04-2024
	//ritorna un puntatore alla tile data la location
	ATile* GetTileByLocation(const FVector2D& Location) const;

	// check if a position is a win position
	bool IsWinPosition(const FVector2D Position) const;

	// check if is a win line
	inline bool IsWinLine(const FVector2D Begin, const FVector2D End) const;

	// checking if is a valid field position
	inline bool IsValidPosition(const FVector2D Position) const;

	// get a line given a begin and end positions
	TArray<int32> GetLine(const FVector2D Begin, const FVector2D End) const;

	// check if a line contains all equal elements
	bool AllEqual(const TArray<int32>& Array) const;

	//public:	
	//	// Called every frame
	//	virtual void Tick(float DeltaTime) override;

};
