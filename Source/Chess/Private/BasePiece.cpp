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

void ABasePiece::SetPieceOwner(const int32 POwner)
{
	PieceOwner = POwner;
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

int32 ABasePiece::GetPieceOwner()
{
	return PieceOwner;
}

void ABasePiece::SetPiecePosition(const double InX, const double InY)
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

