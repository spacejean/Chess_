// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePiece.generated.h"
// Enum class per il colore dei pezzi degli scacchi
UENUM()
enum class EPieceColor : uint8
{
	WHITE,
	BLACK,
	EMPTY
};

// Enum class per i tipi di pezzi degli scacchi
UENUM()
enum class EPieceType : uint8
{
	EMPTY,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

UCLASS()
class CHESS_API ABasePiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePiece();
	// set the player owner and the status of a tile
	void SetPieceColor(const EPieceColor PieceColor);

	// set the player owner and the type of a piece
	void SetPieceType(const EPieceType PieceType);

	// get the Piece color
	EPieceColor GetPieceColor();

	// get the Piece Type
	EPieceType GetPieceType();

	// get the Piece owner
	int32 GetOwner();

	// set the (x, y) position
	void SetPiecePosition(const double InX, const double InY);

	// get the (x, y) position
	FVector2D GetGridPosition();

	// Set material function
	void SetMaterial(class UMaterialInterface* Material);



	
	virtual void CalculateMoves(bool bDrawAvailableMove);

	//definisci le direzione di movimento possibili per i pezzi
	virtual TArray<FVector2D> GetMovementDirections() const;
	
		
	//virtual  TArray<ATile*> CalculateAvailableMoves();

	bool IsValidBoardPosition(const FVector2D& Position) const ;

	


	

	//UFUNCTION(BlueprintCallable, Category = "Chess")
	//virtual  void MoveToPosition(const FVector2D& NewPosition);

	// Eliminates piece from the game.
	UFUNCTION()
	void Eliminate();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPieceColor PColor;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPieceType PType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PieceOwner;

	// (x, y) position of the piece
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D PieceGridPosition;

	UPROPERTY(EditAnywhere, Category = "Chess")
	bool bIsWhite;

	// Variable to check if pawn has ever moved.
	UPROPERTY(EditAnywhere)
	bool bHasEverMoved;





private:
	UMaterialInterface* CurrentMaterial;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
