// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePiece.h"
#include "Tile.h"



// Sets default values
ABasePiece::ABasePiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// template function that creates a components
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	// every actor has a RootComponent that defines the transform in the World
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	CurrentMaterial = nullptr;
	bHasEverMoved = false;
	PColor = EPieceColor::EMPTY;
	PType = EPieceType::EMPTY;
	PieceOwner = -1;
	PieceGridPosition = FVector2D(0, 0);
}

void ABasePiece::SetPieceColor(const EPieceColor PieceColor)
{
	PColor = PieceColor;

}

void ABasePiece::SetPieceType(const EPieceType PieceType)
{
	
		PType = PieceType;

}

EPieceColor ABasePiece::GetPieceColor()
{
	return PColor;
}

EPieceType ABasePiece::GetPieceType()
{
	return PType;
}

int32 ABasePiece::GetOwner()
{
	return PieceOwner;
}

void ABasePiece::SetPiecePosition(const int32 InX, const int32 InY)
{
	PieceGridPosition.Set(InX, InY);
}

FVector2D ABasePiece::GetGridPosition()
{
	return PieceGridPosition;
}

void ABasePiece::SetMaterial(UMaterialInterface* Material)
{

	if (Material)
	{
		StaticMeshComponent->SetMaterial(0, Material);
		CurrentMaterial = Material;
	}
}

void ABasePiece::GenerateMoves()
{
}

void ABasePiece::CalculateMoves(bool bDrawAvailableMove)
{
}

TArray<FVector2D> ABasePiece::GetMovementDirections() const
{
	return TArray<FVector2D>();
}

bool ABasePiece::IsValidBoardPosition(const FVector2D& Position) const
{
	return Position.X >= 0 && Position.X < 8 && Position.Y >= 0 && Position.Y < 8;
}


void ABasePiece::Moves()
{
	FVector NewLocation = GetActorLocation()*2;
	SetActorLocation(NewLocation);
}

/*
void ABasePiece::DetecSelectableGrids(TArray<ATile*>* SelectableGrids)
{
}

TArray<ATile*> ABasePiece::CalculateAvailableMoves()
{
	return TArray<ATile*>();
}

*/

/*void ABasePiece::MoveToPosition(const FVector2D& NewPosition)
{
	//implementata nelle classi derivate
}
*/


void ABasePiece::Eliminate()
{
	//this->Destroy();
	Destroy();
}

TArray<FVector2D> ABasePiece::GeneratePawnMoves(const FVector2D& CurrentPosition)
{
	TArray<FVector2D> PawnMoves;

	int Direction = bIsWhite ? 1 : -1; // White pawns move up, black pawns move down

	// Pawn can move one step forward
	PawnMoves.Add(FVector2D(CurrentPosition.X, CurrentPosition.Y + Direction));

	// If the pawn is in its initial position, it can move two steps forward
	if ((bIsWhite && CurrentPosition.Y == 1) || (!bIsWhite && CurrentPosition.Y == 6))
	{
		PawnMoves.Add(FVector2D(CurrentPosition.X, CurrentPosition.Y + 2 * Direction));
	}

	// Pawn can capture diagonally
	PawnMoves.Add(FVector2D(CurrentPosition.X + 1, CurrentPosition.Y + Direction));
	PawnMoves.Add(FVector2D(CurrentPosition.X - 1, CurrentPosition.Y + Direction));

	// TODO: Add additional conditions to filter out invalid moves, like capturing, en passant, etc.

	return PawnMoves;
}

// Called when the game starts or when spawned
void ABasePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

