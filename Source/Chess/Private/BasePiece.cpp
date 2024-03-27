// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePiece.h"




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
	PColor = EPieceColor::EMPTY;
	PType = EPieceType::EMPTY;
	PieceOwner = -1;
	PieceGridPosition = FVector2D(0, 0);
}

void ABasePiece::SetPieceColor(const int32 POwner, const EPieceColor PieceColor)
{
	PieceOwner = POwner;
	PColor = PieceColor;

}

void ABasePiece::SetPieceType(const int32 POwner, const EPieceType PieceType)
{
		PieceOwner = POwner;
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

void ABasePiece::SetGridPosition(const double InX, const double InY)
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

